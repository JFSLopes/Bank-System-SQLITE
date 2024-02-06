#ifndef APP_
#define APP_

#include "Client.h"
#include <string>
#include <iostream>
#include <sqlite3.h>

class App{
    private:
        std::string schemaPath, pop1, pop2;
        sqlite3* db;
        Client currLogin;

        void init();
        void api();
        void populate() const;
        bool clientLogin();
        int askNumber(int upperLimit) const;
    public:
        App(std::string& db, std::string& pop1, std::string& pop2);
        void readFile(std::ifstream& in) const;
        char* readCharFromInput(int size) const;
};

#endif