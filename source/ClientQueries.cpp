#include "../header/ClientQueries.h"
#include <iostream>
#include <fstream>

std::string ClientQueries::fullName(int id, sqlite3* db){
    const std::string query = "SELECT firstName, lastName FROM Client WHERE id = " + std::to_string(id) + ';';
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, query.c_str(), -1 , &stmt, nullptr) != SQLITE_OK){
        throw std::runtime_error("Query was invalid");
    }
    if(sqlite3_step(stmt) == SQLITE_ROW){
        const char *firstName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        const char *lastName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        std::string name = std::string(firstName) + " " + std::string(lastName);
        return name;
    }
    else{
        std::cout << "Something unexpect occur.\n";
    }
    return "";
}

std::pair<int, std::string> ClientQueries::get_ID_Email(const std::string& input, sqlite3* db){
    std::string query = "SELECT id, encPassWord FROM Client WHERE email = '" + input + "';";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        sqlite3_close(db);
        throw std::runtime_error("Query was invalid");
    }
    if(sqlite3_step(stmt) == SQLITE_ROW){
        int id = std::stoi(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
        const char *encPass = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        std::string pass(encPass); 
        return std::make_pair(id, pass);
    }
    return std::make_pair(-1,"");
}

bool ClientQueries::insertClient(const std::string& firstName, const std::string& lastName, const std::string& email, const std::string& encPass, sqlite3* db, const std::string& path){
    std::string query = "INSERT INTO Client (firstName, lastName, email, encPassWord, bank) VALUES ('" + firstName + "', '" + lastName + "', '" + email + "', '" + encPass + "', 1);\n";

    char* errMsg = nullptr;
    if (sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::string errorMessage = "SQL error: ";
        errorMessage += errMsg;
        std::cout << errorMessage << '\n';
        sqlite3_free(errMsg); // Free the error message buffer allocated by SQLite
        return false;
    }
    std::ofstream file(path, std::ios::app);
    if (!file.is_open()){
        std::cout << "File path is invalid";
    }
    file << query;
    file.close();
    return true;
}