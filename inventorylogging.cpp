#include <sqlite3.h>
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <string>

class InventoryLogger {
public:

    void createLogEntry(){
        //std::time_t systemTime = std::chrono::system_clock::now();
        std::ofstream inventorylog;
        inventorylog.open("Inventory Log.txt");
        inventorylog << "some test text\t" << std::time(0) << "\n";
        inventorylog.close();

    }

};