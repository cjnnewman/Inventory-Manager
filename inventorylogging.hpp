#ifndef INVENTORY_MANAGER_INVENTORYLOGGING_HPP
#define INVENTORY_MANAGER_INVENTORYLOGGING_HPP
#include <sqlite3.h>
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <string>

void createLogEntry(std::string logText);
void createLogErrorEntry(std::string logErrorText);
#endif //INVENTORY_MANAGER_INVENTORYLOGGING_HPP
