cmake_minimum_required(VERSION 3.23)
project(Inventory-Manager)

set(CMAKE_CXX_STANDARD 14)

add_executable(InventoryManager InventoryManager.cpp mainmenu.cpp SQLTable.cpp inventorylogging.cpp inventorylogging.hpp SQLTable.hpp)
target_link_libraries(InventoryManager LINK_PUBLIC sqlite3)