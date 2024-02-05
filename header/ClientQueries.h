#ifndef CLIENTQUERIES_
#define CLIENTQUERIES_

#include <sqlite3.h>
#include <string>

class ClientQueries{
    public:
        static std::string fullName(int id, sqlite3* db);
        
};

#endif