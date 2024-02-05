#ifndef APP_
#define APP_

#include <string>
#include <iostream>
#include <sqlite3.h>

class App{
    private:
        std::string schemaPath, pop1, pop2;
        sqlite3* db;

        void init();
        void api() const;
        void populate() const;
        bool clientLogin() const;
    public:
        App(std::string& db, std::string& pop1, std::string& pop2);
        void readFile(std::ifstream& in) const;
        char* readCharFromInput(int size) const;
};

#endif