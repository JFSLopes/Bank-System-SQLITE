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
    if (clientLogin()){
        std::cout << "Login sucessed. Welcome " << currLogin.getName(db) << ".\n";
    }
    else{
        std::cout << "Login failed.\n";
    }
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
    if (email == nullptr) return clientLogin();
    std::cout << email << '\n';

    std::cout << "Password: ";
    maxChars = 16;
    char* password = readCharFromInput(maxChars);
    if (password == nullptr) return clientLogin();

    std::string aux(email);
    std::pair<int, std::string> login = ClientQueries::get_ID_Email(aux, db);
    if (login.first == -1){
        std::cout << "Invalid email.\n";
        return false;
    }
    else if(password::verifyPassword(password, login.second)){
        currLogin = Client(login.first, db);
        return true;
    }
    else{
        std::cout << "Wrong password.\n";
        return false;
    }
}

char* App::readCharFromInput(int size) const{
    char* buffer = new char[size + 1];
    std::cin.getline(buffer, size + 1);
    if(std::cin.fail()){
        std::cerr << "Input error." << std::endl;
        delete [] buffer;
        std::cin.ignore();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return nullptr;
    }
    if(std::cin.gcount() == size){
        std::cin.ignore();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return buffer;
}