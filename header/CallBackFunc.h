#ifndef CALLBACKFUNC_
#define CALLBACKFUNC_

#include <string>

struct TransferRecord{
    std::string type;
    std::string date;
    double amount;
    int dest;
    int origin;
};

namespace callback{
    int clientCallback(void* data, int argc, char** argv, char** colNames);
    int callback(void* NotUsed, int argc, char** argv, char** azColName);
    /**
     * data will be cast to a pointer to a data struct cointaining the transfer history
    */
    int transferCallBack(void* data, int argc, char** argv, char** colNames);
}

#endif