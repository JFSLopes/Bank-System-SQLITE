#ifndef CLIENT_
#define CLIENT_

#include "AccountQueries.h"
#include "TransferQueries.h"
#include "ClientQueries.h"

class Client{
    private:
        int clientID, accountID;

        void showTransfersHistory(const std::vector<TransferRecord>& transfers, sqlite3* db, bool failed) const;
    public:
        Client();
        Client(int clientID, sqlite3* db);

        void setAccountID(int value);
        int getAccountID() const;

        std::string getName(sqlite3* db) const;
        double currBalance(sqlite3* db) const;
        void seeTransferHistory(int numTransfers, sqlite3* db, bool failed) const;
        void newAccount(sqlite3* db, const std::string& path) const;
        std::vector<accountData> getAllAccounts(sqlite3* db) const;
        bool processTranfer(int type, const std::string& amount, int dest, sqlite3* db, const std::string& path) const;
};

#endif