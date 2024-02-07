#ifndef ACCOUNTQUERIES_
#define ACCOUNTQUERIES_

#include <sqlite3.h>
#include <string>

struct accountData{
    int id;
    double balance;
    std::string date;
};

class AccountQueries{
    public:
        static std::vector<accountData> getAccountsFromClient(int clientID, sqlite3* db);
        static double getBalance(int id, sqlite3* db);
        static void createAccount(const std::string& balance, const std::string& date, int clientID, sqlite3* db, const std::string& path);
        static void updateAmount(int accountID, double offset, sqlite3* db, const std::string& path);
};

#endif