#include "../header/Display.h"
#include <iostream>



void Display::description(){
    std::cout << "\n\t\t\t\tWelcome to the Bank API.\n";
    std::cout << "\t1. Login\n"
              << "\t2. Register client\n"
              << "\t9. Close app\n\n"
              << "[1..9]: ";
}
void Display::afterLoginOptions(){
    std::cout << "Choose an option by enter the corresponding number:\n"
              << "\t1. See balance\n"
              << "\t2. See completed tranfers\n"
              << "\t3. See failed transfers\n"
              << "\t4. Register a new account\n"
              << "\t5. Make a transfer\n"
              << "\t9. Log out.\n\n"
              << "[1..9]: ";
}