#include <sqlite3.h>
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <string>

class InventoryLogger {
public:

    void createLogEntry(std::string logText){
        time_t my_time = time(NULL);

        std::ofstream inventorylog;
        inventorylog.open("Inventory Log.txt", std::ios_base::app);
        inventorylog << logText << "\t" << ctime(&my_time) << "\n";
        inventorylog.close();

    }

    void createLogErrorEntry(std::string logErrorText){
        time_t my_time = time(NULL);

        std::ofstream inventorylog;
        inventorylog.open("Inventory Log.txt", std::ios_base::app);
        inventorylog << "ERROR: " << logErrorText << "\t" << ctime(&my_time) << "\n";
        inventorylog.close();

    }

};