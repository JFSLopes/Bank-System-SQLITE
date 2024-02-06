#ifndef TRANSFERQUERIES_
#define TRANSFERQUERIES_

#include "CallBackFunc.h"
#include <vector>
#include <sqlite3.h>

class TransferQueries{
    public:
        static std::vector<TransferRecord> getTransfers(int accountID, int clientID, int numTransfers, bool failed, sqlite3* db);
};

#endif