cmake_minimum_required(VERSION 3.23)
project(SQLite_Testing)

set(CMAKE_CXX_STANDARD 14)

add_executable(InventoryManager InventoryManager.cpp mainmenu.cpp)
target_link_libraries(InventoryManager LINK_PUBLIC sqlite3)