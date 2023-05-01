// Project: Inventory Manager
// Date: 5/1/23
// Course: COP3003
// Developer: Caleb Newman
// Description: InventoryManager is a simple command line program that
// is designed to manage a small inventory of products that are assigned
// unique SKU numbers. It allows a user to add and remove products, adjust
// quantity on hand, and view their current stock.
// --------------------------------------------------------------------
#include <iostream>
#include <sqlite3.h>
#include "mainmenu.cpp"
#include "SQLTable.cpp"

using std::cout;
using std::cin;
using std::string;
using std::endl;

// Main loop. Continue looping the main menu display and getting
// user interaction until the user chooses to quit or closes
// terminal window.
int main(){
    MainMenu mainMenu;
    SQLTable primaryTable;

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
            default:
                cout << "An error occurred, you may need to check your input!";
                return 1;
        }
    }

    return 0;
}