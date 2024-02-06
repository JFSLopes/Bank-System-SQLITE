#ifndef CLIENT_
#define CLIENT_

#include "AccountQueries.h"
#include "TransferQueries.h"
#include "CallBackFunc.h"
#include "ClientQueries.h"
#include <vector>

class Client{
    private:
        int clientID, accountID;

        void showTransfersHistory(const std::vector<TransferRecord>& transfers, sqlite3* db) const;

    public:
        Client();
        Client(int clientID, sqlite3* db);

        std::string getName(sqlite3* db) const;
        double currBalance(sqlite3* db) const;
        void seeTransferHistory(int numTransfers, sqlite3* db) const;
        void seeFailedTransfers(int numTransfers, sqlite3* db) const;

};

#endif