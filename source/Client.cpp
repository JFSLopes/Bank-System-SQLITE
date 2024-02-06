#include "../header/Client.h"

Client::Client() : clientID(-1) {}
Client::Client(int clientID, sqlite3* db) : clientID(clientID) {
    std::string query = "SELECT id FROM Account WHERE client = " + std::to_string(clientID) + ';';
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK){
        throw std::runtime_error("Query on Client failed");
    }
    if (sqlite3_step(stmt) == SQLITE_ROW){
        accountID = std::stoi(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
    }
}


std::string Client::getName(sqlite3* db) const{
    return ClientQueries::fullName(clientID, db);
}

double Client::currBalance(sqlite3* db) const{
    return AccountQueries::getBalance(accountID, db);
}