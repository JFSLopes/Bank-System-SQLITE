#include "../header/Display.h"
#include <iostream>



void Display::description(){
    std::cout << "\n\t\t\t\tWelcome to the Bank API.\n";
    std::cout << "\t1. Login\n"
              << "\t2. Register client"
              << "\t3. Register account\n"
              << "\t4. Register new transfer\n"
              << "\t9. Close app\n\n"
              << "[1..9]: ";
}
void Display::afterLoginOptions(){
    std::cout << "Choose an option by enter the corresponding number:\n";
    std::cout << "\t1. See balance\n";
    std::cout << "\t2. See completed tranfers\n";
    std::cout << "\t3. See failed transfers\n";
    std::cout << "\t9. Log out.\n\n";
    std::cout << "[1..9]: ";
}