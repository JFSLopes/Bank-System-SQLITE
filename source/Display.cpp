#include "../header/Display.h"
#include <iostream>



void Display::description(){
    std::cout << "\nWelcome to the Bank API.\n\n";
}
void Display::options(){
    std::cout << "Choose an option by enter the corresponding number:\n";
    std::cout << "\t1. See balance\n";
    std::cout << "\t2. See completed tranfers\n";
    std::cout << "\t3. See failed transfers\n";
    std::cout << "\t9. Log out.\n";
    std::cout << "[1..9]: ";
}