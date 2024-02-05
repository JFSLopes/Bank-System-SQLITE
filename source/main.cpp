#include "../header/App.h"

int main(){
    std::string dbPath = "/Users/joselopes/Desktop/Bank-System/BankDB/schema.db";
    std::string pop1 = "/Users/joselopes/Desktop/Bank-System/BankDB/populate.db";
    std::string pop2 = "";
    App app(dbPath, pop1, pop2);
    return 0;
}
