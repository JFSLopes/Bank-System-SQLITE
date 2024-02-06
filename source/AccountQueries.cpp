#include "../header/AccountQueries.h"
#include <string>
#include <iostream>

double AccountQueries::getBalance(int id, sqlite3* db){
    std::string query = "SELECT balance FROM Account WHERE id = " + std::to_string(id) + ';';
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK){
        const char* errorMessage = sqlite3_errmsg(db);
        throw std::runtime_error("Query failed: " + std::string(errorMessage));
    }
    if(sqlite3_step(stmt) == SQLITE_ROW){
        double balance = std::stod(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
        return balance;
    }
    return -1;
}