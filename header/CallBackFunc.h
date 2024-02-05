#ifndef CALLBACKFUNC_
#define CALLBACKFUNC_

namespace callback{
    int clientCallback(void* data, int argc, char** argv, char** colNames);
    int callback(void* NotUsed, int argc, char** argv, char** azColName);
}

#endif