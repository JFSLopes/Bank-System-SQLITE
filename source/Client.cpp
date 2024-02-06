#include "../header/Client.h"
#include "../header/CallBackFunc.h"
#include <iostream>
#include <iomanip>

Client::Client() : clientID(-1) {}
Client::Client(int clientID, sqlite3* db) : clientID(clientID) {
    accountID = AccountQueries::getID(clientID, db);
    if(accountID == -1){
        throw std::runtime_error("A invalid Client was created");
    }
}


std::string Client::getName(sqlite3* db) const{
    return ClientQueries::fullName(clientID, db);
}

double Client::currBalance(sqlite3* db) const{
    return AccountQueries::getBalance(accountID, db);
}

void Client::seeTransferHistory(int numTransfers, sqlite3* db, bool failed) const{
    std::vector<TransferRecord> transferRecords = TransferQueries::getTransfers(accountID, clientID, numTransfers, failed, db);
    std::cout << (!failed ? "\n\n\t\t\t\t\t\t" : "\n\n\t\t\t\t") << (!failed ? " Completed" : " Failed") <<  " transfers\n\n";
    showTransfersHistory(transferRecords, db, failed);
}

void Client::showTransfersHistory(const std::vector<TransferRecord>& transfers, sqlite3* db, bool failed) const{
    double curr = currBalance(db);
    for (const auto& t : transfers){
        std::cout << std::setw(7) << std::left << "DATE: " << std::setw(10) << std::left << t.date 
                  << " / Type: " << std::setw(10) << std::left << t.type;
              
        if (t.origin == clientID){
            std::cout << " /   TO: " << std::setw(20) << std::left << ClientQueries::fullName(t.dest, db) 
                      << " -" << std::setw(10) << std::left << t.amount;
            if (!failed){
                std::cout << " / Inicial Balance: " << std::setw(8) << std::left << curr;
                curr -= t.amount;
            }
        }
        else{
            std::cout << " / FROM: " << std::setw(20) << std::left << ClientQueries::fullName(t.origin, db) 
                      << " +" << std::setw(10) << std::left << t.amount;
            if (!failed){
                std::cout << " / Inicial Balance: " << std::setw(8) << std::left << curr;
                curr += t.amount;
            }
        }
        if (!failed) std::cout << " / Final Balance: " << curr;
        std::cout << '\n';
    }
}