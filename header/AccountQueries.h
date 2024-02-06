#ifndef ACCOUNTQUERIES_
#define ACCOUNTQUERIES_

#include <sqlite3.h>

class AccountQueries{
    public:
        static double getBalance(int id, sqlite3* db);
        static int getID(int clientID, sqlite3* db);
};

#endif