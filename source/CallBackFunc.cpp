#include "../header/CallBackFunc.h"
#include <iostream>

namespace callback{

    int clientCallback(void* data, int argc, char** argv, char** colNames){
        for (int i = 0; i < argc; i++) {
            std::cout << colNames[i] << ": " << (argv[i] ? argv[i] : "NULL") << std::endl;
        }
        std::cout << "------------------------" << std::endl;
        // Returning 0 indicates that the callback should continue processing rows
        return 0;
    }

    int callback(void* NotUsed, int argc, char** argv, char** azColName) {
        return 0;
    }

    int transferCallBack(void* data, int argc, char** argv, char** colNames){
        std::vector<TransferRecord>* transferRecords = static_cast<std::vector<TransferRecord>*>(data);
    
        // Create a TransferRecord object and populate it with values from the query result
        TransferRecord record;
        record.type = argv[0] ? argv[0] : "";   /// Making sure is not null
        record.date = argv[1] ? argv[1] : "";
        record.amount = argv[2] ? std::stod(argv[2]) : 0.0;
        record.dest = argv[3] ? std::stoi(argv[3]) : 0;
        record.origin = argv[4] ? std::stoi(argv[4]) : 0;
    
        // Add the TransferRecord object to the vector
        transferRecords->push_back(record);
        return 0;
    }
}