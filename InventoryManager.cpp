#include <iostream>
#include <sqlite3.h>
#include "mainmenu.cpp"
#include "SQLTable.cpp"
#include "inventorylogging.cpp"

using std::cout;
using std::cin;
using std::string;
using std::endl;

int main(){
    MainMenu mainMenu;
    SQLTable primaryTable;
    InventoryLogger primaryLogger;


    primaryTable.openDatabaseConnection();
    primaryTable.checkOrCreateTable();

    while(true) {

        switch (mainMenu.printMainMenu()) {
            case 1:
                primaryTable.viewCurrentInventory();
                break;
            case 2:
                primaryTable.addProductToInventory();
                break;
            case 3:
                primaryTable.updateProductQuantity();
                break;
            case 4:
                primaryTable.removeProductFromInventory();
                break;
            case 5:
                return 0;
                break;
            case 6:
                primaryLogger.createLogEntry();
                break;
            default:
                cout << "An error occurred, you may need to check your input!";
                return 1;
        }
    }

    return 0;
}