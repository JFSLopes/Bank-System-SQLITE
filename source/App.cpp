#include "../header/App.h"
#include "../header/passWordEnc.h"
#include "../header/ClientQueries.h"
#include "../header/Display.h"
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
    bool leave = false;
    while (true){
        Display::description();
        switch (askNumber(9)){
            case 1:{
                loginInterface();
                break;
            }
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 9:
                leave = true;
                break;
        }
        if(leave) break;
    }
    sqlite3_close(db);
}

void App::loginInterface(){
    std::cout << "Please enter your credentials.\n";
    while(!clientLogin()){
        std::cout << "Login failed, try again.\n";
    }
    std::cout << "Welcome " << currLogin.getName(db) << ".\n";
    while(true){
        Display::afterLoginOptions();
        switch(askNumber(9)){
            case 1: {
                std::cout << "Your current balance is " << currLogin.currBalance(db) << ".\n";
                break;
            }
            case 2: {
                std::cout << "How many transfer do you want to be displayed? ";
                int num = askNumber(30);
                currLogin.seeTransferHistory(num, db, false);
                break;
            }
            case 3: {
                std::cout << "How many transfer do you want to be displayed? ";
                int num = askNumber(30);
                currLogin.seeTransferHistory(num, db, true);
                break;
            }
            case 9:
                std::cout << '\n';
                return;
        }
        std::cout << '\n';
    }
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

int App::askNumber(int upperLimit) const{
    int num;
    while (true) {
        if (!(std::cin >> num)){
            std::cout << "Invalid input. Please enter a number: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else if (num <= 0 || num > upperLimit){
            std::cout << "Invalid number. Please enter a number between 1 and " << upperLimit << ": ";
        } else {
            break;
        }
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return num;
}
/*
void App::newClient() const{
    std::cout << "Email: ";
    int maxChars = 30;
    char* email = readCharFromInput(maxChars);
    if (email == nullptr){
        std::cout << "Invalid email.\n";
    }

    std::cout << "Password: ";
    maxChars = 16;
    char* password = readCharFromInput(maxChars);
    std::cout << '\n';
    if (password == nullptr){
        std::cout << "Invalid password.\n";
    }

    std::string aux(email);
    std::pair<int, std::string> login = ClientQueries::get_ID_Email(aux, db);
    if (login.first != -1){
        std::cout << aux << " is already registered.\n";
    }
    else{

    }
}
*/