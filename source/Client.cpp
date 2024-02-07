#include "../header/Client.h"
#include "../header/CallBackFunc.h"
#include <iostream>
#include <iomanip>
#include <random>
#include <sstream>

Client::Client() : clientID(-1) {}
Client::Client(int clientID, sqlite3* db) : clientID(clientID), accountID(-1) {}

std::string Client::getName(sqlite3* db) const{
    return ClientQueries::fullName(clientID, db);
}

void Client::setAccountID(int value){
    accountID = value;
}

double Client::currBalance(sqlite3* db) const{
    if (accountID == -1){
        std::cout << "You do not have an account.\n";
        return -1;
    }
    return AccountQueries::getBalance(accountID, db);
}

void Client::seeTransferHistory(int numTransfers, sqlite3* db, bool failed) const{
    if (accountID == -1){
        std::cout << "You do not have an account.\n";
        return;
    }
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

void Client::newAccount(sqlite3* db, const std::string& path) const{
    std::random_device rd;
    std::mt19937 gen(rd());
    
    std::uniform_real_distribution<double> dist(2000, 10000);
    double randomValue = dist(gen);
    std::stringstream balance;
    balance << std::fixed << std::setprecision(2) << randomValue;

    // Get the current time point
    auto now = std::chrono::system_clock::now();
    std::time_t nowTimeT = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&nowTimeT), "%Y-%m-%d %H:%M:%S");

    AccountQueries::createAccount(balance.str(), ss.str(), clientID, db, path);
}

std::vector<accountData> Client::getAllAccounts(sqlite3* db) const{
    std::vector<accountData> vec = AccountQueries::getAccountsFromClient(clientID, db);
    return vec;
}