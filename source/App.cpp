#include "../header/App.h"
#include "../header/passWordEnc.h"
#include "../header/ClientQueries.h"
#include <stdexcept>
#include <fstream>

App::App(std::string& db, std::string& pop1, std::string& pop2) : schemaPath(std::move(db)), pop1(std::move(pop1)), pop2(std::move(pop2)){
    init();
}

void App::init(){
    int x = sqlite3_open("build/db.sql", &db);
    if (x != SQLITE_OK){
        throw std::runtime_error("Failed to open the SQLite database.");
    }
    api();
}

void App::api(){
    populate();
    std::cout << "Welcome to the Bank API.\n\n";
    std::cout << "Please enter your credentials.\n";
    while(!clientLogin()){
        std::cout << "Login failed, try again.\n";
    }
    std::cout << "Login sucessed. Welcome " << currLogin.getName(db) << ".\n";
    currLogin.seeTransferHistory(5, db, false);
    currLogin.seeTransferHistory(5, db, true);
    sqlite3_close(db);
}

void App::populate() const{
    std::ifstream schema(schemaPath);
    readFile(schema);
    std::ifstream populate1(pop1);
    readFile(populate1);
    std::ifstream populate2(pop2);
    readFile(populate2);
}

void App::readFile(std::ifstream& in) const{
    if (in.is_open()){
        std::string statement, line;
        while(std::getline(in, line)){
            if(line.front() == '-') continue;
            statement += line;
            if(line.back() == ';') statement += '\n';
        }
        int rc = sqlite3_exec(db, statement.c_str(), callback::callback, 0, 0);
        if (rc != SQLITE_OK) {
            throw std::runtime_error("Failed to populate the SQLite database.");
        }
    }
}

bool App::clientLogin(){
    std::cout << "Email: ";
    int maxChars = 30;
    char* email = readCharFromInput(maxChars);
    if (email == nullptr) return false;

    std::cout << "Password: ";
    maxChars = 16;
    char* password = readCharFromInput(maxChars);
    std::cout << '\n';
    if (password == nullptr) return false;

    std::string aux(email);
    std::pair<int, std::string> login = ClientQueries::get_ID_Email(aux, db);
    bool ans = false;
    if (login.first == -1){
        std::cout << "Invalid email. " << email << " does not exist.\n";
    }
    else if(password::verifyPassword(password, login.second)){
        currLogin = Client(login.first, db);
        ans = true;
    }
    else{
        std::cout << "Wrong password.\n";
    }
    if (email != nullptr) delete[] email;
    if (password != nullptr) delete[] password;
    return ans;
}

char* App::readCharFromInput(int size) const{
    char* buffer = new char[size + 1];
    std::cin.getline(buffer, size + 1);
    bool failed = false;
    if(std::cin.fail()){
        failed = true;
        buffer[size] = 0;
    }
    if(std::cin.gcount() >= size){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    if (failed) return nullptr;
    return buffer;
}