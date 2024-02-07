#include "../header/TransferQueries.h"
#include <iostream>
#include <fstream>
#include <sstream>

std::vector<TransferRecord> TransferQueries::getTransfers(int accountID, int clientID, int numTransfers, bool failed, sqlite3* db){
    std::string query = "SELECT T.type, date, amount, dest, origin "
                        "FROM Transfer "
                        "JOIN Type T ON T.id = Transfer.type "
                        "JOIN State S ON S.id = Transfer.state ";

    if(failed) query += "WHERE S.state = 'Failed' ";
    else query += "WHERE S.state = 'Completed' ";
    
    query +="AND (dest = " + std::to_string(clientID) +
            " OR origin = " +  std::to_string(clientID) + ") "
            "ORDER BY date DESC ";
    if (numTransfers != -1) query += "LIMIT " + std::to_string(numTransfers);
    query += ';';

    char* errMsg = nullptr;
    std::vector<TransferRecord> transferRecords;
    if (sqlite3_exec(db, query.c_str(), callback::transferCallBack, &transferRecords, &errMsg) != SQLITE_OK){
        std::cout << errMsg << '\n';
        throw std::runtime_error("Failure on the transfer history.\n");
    }
    return transferRecords;
}

void TransferQueries::processTranfer(const std::string& date, const std::string& amount, int origin, int dest, int type, int state, sqlite3* db, const std::string& path){
    std::stringstream ss;
    ss << "INSERT INTO Transfer (date, amount, origin, dest, type, state) VALUES ('" << date << "', " << amount << ", " << origin << ", " << dest << ", " << type << ", " << state << ");\n";
    std::string query = ss.str();

    char* errMsg = nullptr;
    if (sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::string errorMessage = "SQL error: ";
        errorMessage += errMsg;
        std::cout << errorMessage << '\n';
        sqlite3_free(errMsg);
        return;
    }
    std::ofstream file(path, std::ios::app);
    if (!file.is_open()){
        std::cout << "File path is invalid";
    }
    file << query;
    file.close();
}