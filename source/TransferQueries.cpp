#include "../header/TransferQueries.h"
#include <iostream>

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