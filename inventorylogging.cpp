#include "inventorylogging.hpp"

// This class handles logging of all interactions with the SQL database as
// well as logging sql errors.
class InventoryLogger {
public:

    // Function writes log entries to a log .txt file
    void createLogEntry(std::string logText){
        time_t my_time = time(NULL);

        // Open output file stream and output text from function in SQLTable.cpp
        std::ofstream inventorylog;
        inventorylog.open("Inventory Log.txt", std::ios_base::app);
        inventorylog << logText << "\t" << ctime(&my_time) << "\n";
        inventorylog.close();

    }

    // Function writes error log entries to log .txt file
    void createLogErrorEntry(std::string logErrorText){
        time_t my_time = time(NULL);

        // Open output file stream and output error text from SQL callback
        std::ofstream inventorylog;
        inventorylog.open("Inventory Log.txt", std::ios_base::app);
        inventorylog << "ERROR: " << logErrorText << "\t" << ctime(&my_time) << "\n";
        inventorylog.close();

    }

};