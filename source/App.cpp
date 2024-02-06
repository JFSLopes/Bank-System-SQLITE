#include "../header/App.h"
#include "../header/CallBackFunc.h"
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
        std::cout << "Login sucessed.\n";
    }
    else{
        std::cout << "Login failed.\n";
    }
    std::cout << currLogin.getName(db) << '\n';
    std::cout << currLogin.currBalance(db) << '\n';
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

    std::cout << "Password: ";
    maxChars = 16;
    char* password = readCharFromInput(maxChars);

    std::string aux(email);
    std::string query = "SELECT id, encPassWord FROM Client WHERE email = '" + aux + "';";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        sqlite3_close(db);
        throw std::runtime_error("Query was invalid");
    }
    bool ans = false;
    if(sqlite3_step(stmt) == SQLITE_ROW){
        int id = std::stoi(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
        const char *encPass = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));

        std::string pass(encPass);
        if(password::verifyPassword(password, pass)){
            currLogin = Client(id, db);
            ans = true;
        }
        else{
            std::cout << "Wrong password.\n";
        }
    }
    else{
        std::cout << "Invalid email or password.\n";
    }
    sqlite3_finalize(stmt);
    return ans;
}

char* App::readCharFromInput(int size) const{
    char* buffer = new char[size + 1];
    std::cin.getline(buffer, size);
    if(std::cin.fail()){
        std::cerr << "Input error." << std::endl;
        return nullptr;
    }
    if(std::cin.gcount() == size){
        std::cin.ignore();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return buffer;
}