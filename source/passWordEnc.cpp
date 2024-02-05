#include <iostream>
#include "../header/passWordEnc.h"

namespace password
{
    std::string hashPassword(const std::string &password)
    {
        const int shift = 7;
        std::string hashedPassword = password;
        for (char &ch : hashedPassword)
        {
            ch += shift;
        }
        return hashedPassword;
    }

    bool verifyPassword(const std::string &password, const std::string &hashedPassword)
    {
        const int shift = 7;
        std::string originalPassword = hashedPassword;
        for (char &ch : originalPassword)
        {
            ch -= shift;
        }
        return originalPassword == password;
    }
}
