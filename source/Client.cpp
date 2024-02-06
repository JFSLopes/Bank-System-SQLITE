#include "../header/Client.h"
#include "../header/CallBackFunc.h"
#include <iostream>
#include <iomanip>

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

/**
 * state must be completed
*/
void Client::seeTransferHistory(int numTransfers, sqlite3* db) const{
    std::string query = "SELECT T.type, date, amount, dest, origin "
                        "FROM Transfer "
                        "JOIN Type T ON T.id = Transfer.type "
                        "JOIN State S ON S.id = Transfer.state "
                        "WHERE S.state = 'Completed' "
                        "AND (dest = " + std::to_string(clientID) +
                        " OR origin = " +  std::to_string(clientID) + ") "
                        "ORDER BY date DESC ";
    if (numTransfers != -1){
        query += "LIMIT " + std::to_string(numTransfers);
    }
    query += ';';
    char* errMsg = nullptr;
    std::vector<TransferRecord> transferRecords;
    if (sqlite3_exec(db, query.c_str(), callback::transferCallBack, &transferRecords, &errMsg) != SQLITE_OK){
        std::cout << errMsg << '\n';
        throw std::runtime_error("Failure on the transfer history.\n");
    }
    showTransfersHistory(transferRecords, db);
}

void Client::showTransfersHistory(const std::vector<TransferRecord>& transfers, sqlite3* db) const{
    double curr = currBalance(db);
    for (const auto& t : transfers){
        std::cout << std::setw(7) << std::left << "DATE: " << std::setw(10) << std::left << t.date 
                  << " / Type: " << std::setw(10) << std::left << t.type;
              
        if (t.origin == clientID){
            std::cout << " /   TO: " << std::setw(20) << std::left << ClientQueries::fullName(t.dest, db) 
                      << " -" << std::setw(10) << std::left << t.amount 
                      << " / Inicial Balance: " << std::setw(8) << std::left << curr;
            curr -= t.amount;
        }
        else{
            std::cout << " / FROM: " << std::setw(20) << std::left << ClientQueries::fullName(t.origin, db) 
                      << " +" << std::setw(10) << std::left << t.amount 
                      << " / Inicial Balance: " << std::setw(8) << std::left << curr;
            curr += t.amount;
        }
        std::cout << " / Final Balance: " << curr << '\n';
    }
}