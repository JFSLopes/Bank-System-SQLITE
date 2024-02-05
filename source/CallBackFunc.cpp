#include "../header/CallBackFunc.h"
#include <iostream>

namespace callback{

    int clientCallback(void* data, int argc, char** argv, char** colNames){
        for (int i = 0; i < argc; i++) {
            std::cout << colNames[i] << ": " << (argv[i] ? argv[i] : "NULL") << std::endl;
        }
        std::cout << "------------------------" << std::endl;

        return 0;// Returning 0 indicates that the callback should continue processing rows
    }

    int callback(void* NotUsed, int argc, char** argv, char** azColName) {
    // Do nothing
    return 0;
}
}