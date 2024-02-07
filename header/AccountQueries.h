#ifndef ACCOUNTQUERIES_
#define ACCOUNTQUERIES_

#include <sqlite3.h>
#include <string>

class AccountQueries{
    public:
        static double getBalance(int id, sqlite3* db);
        static int getID(int clientID, sqlite3* db);
        static void createAccount(const std::string& balance, const std::string& date, int clientID, sqlite3* db, const std::string& path);
};

#endif