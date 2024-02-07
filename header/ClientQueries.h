#ifndef CLIENTQUERIES_
#define CLIENTQUERIES_

#include "../header/AccountQueries.h"
#include <sqlite3.h>
#include <string>

class ClientQueries{
    public:
        static std::string fullName(int id, sqlite3* db);
        static std::pair<int, std::string> get_ID_Email(const std::string& input, sqlite3* db);
};

#endif