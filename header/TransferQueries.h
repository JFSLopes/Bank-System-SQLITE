#ifndef TRANSFERQUERIES_
#define TRANSFERQUERIES_

#include "CallBackFunc.h"
#include <vector>
#include <sqlite3.h>

class TransferQueries{
    public:
        static std::vector<TransferRecord> getTransfers(int accountID, int clientID, int numTransfers, bool failed, sqlite3* db);
        static void processTranfer(const std::string& date, const std::string& amount, int origin, int dest, int type, int state, sqlite3* db, const std::string& path);
};

#endif