#ifndef CLIENT_
#define CLIENT_

#include "AccountQueries.h"
#include "TransferQueries.h"
#include "ClientQueries.h"

class Client{
    private:
        int clientID, accountID;

    public:
        Client();
        Client(int clientID, sqlite3* db);

        std::string getName(sqlite3* db) const;
        double currBalance(sqlite3* db) const;

};

#endif