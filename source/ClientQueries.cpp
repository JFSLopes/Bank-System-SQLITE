#include "../header/ClientQueries.h"
#include <iostream>

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