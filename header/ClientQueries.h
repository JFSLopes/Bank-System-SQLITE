#ifndef CLIENTQUERIES_
#define CLIENTQUERIES_

#include "../header/AccountQueries.h"
#include <sqlite3.h>
#include <string>

class ClientQueries{
    public:
        static std::string fullName(int id, sqlite3* db);
        static std::pair<int, std::string> get_ID_Email(const std::string& input, sqlite3* db);
        static bool insertClient(const std::string& firstName, const std::string& lastName, const std::string& email, const std::string& encPass, sqlite3* db, const std::string& path);
};

#endif