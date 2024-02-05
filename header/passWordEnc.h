#ifndef PASSWORDENC_
#define PASSWORDENC_

#include <string>

namespace password
{
    std::string hashPassword(const std::string &password);
    bool verifyPassword(const std::string &password, const std::string &hashedPassword);
}

#endif
