#include <iostream>
#include <stdio.h>
#include <sqlite3.h>
#include "mainmenu.cpp"
#include <stdlib.h>

using std::cout;
using std::cin;
using std::string;
using std::endl;

static int callback(void* data, int argc, char** argv, char** azColName)
{
    int i;

    for (i = 0; i < argc; i++) {
        cout << azColName[i] << "  -  " << argv[i] << endl;
    }

    printf("\n");
    return 0;
}

void createTable(){
    sqlite3* DB;
    char* messageError;
    int exit = sqlite3_open("boginventory.db", &DB);

    string sql = "CREATE TABLE Inventory (SKU INTEGER PRIMARY KEY,"
                 "PRODUCT TEXT NOT NULL, QUANTITY INTEGER DEFAULT 0);";

    exit = sqlite3_exec(DB,sql.c_str(),NULL, nullptr,&messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error creating table." << std::endl;
    }
    else
        std::cout << "Table created successfully!" << std::endl;
}

void viewCurrentInventory(){
    sqlite3*DB;
    char* messageError;
    int exit = sqlite3_open("boginventory.db", &DB);
    string sql;

    sql = "SELECT * FROM INVENTORY;";

    sqlite3_exec(DB,sql.c_str(), callback, nullptr,&messageError);

}

void addProductToInventory() {
    sqlite3* DB;
    char* messageError;
    int exit = sqlite3_open("boginventory.db", &DB);
    string sql;
    int sku;
    string product;
    int quantity;

    cout << "Enter SKU: ";
    cin >> sku;
    cout << "Enter product name: ";
    cin >> product;
    cout << "Enter quantity on hand: ";
    cin >> quantity;

    sql = "INSERT INTO Inventory VALUES(" + std::to_string(sku) + ", '" + product + "', " + std::to_string(quantity) + ");";

    exit = sqlite3_exec(DB, sql.c_str(),NULL, nullptr,&messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error adding data" << std::endl;
    }
    else
        std::cout << "Data added successfully!" << std::endl;

}

void removeProductFromInventory() {
    sqlite3* DB;
    char* messageError;
    int exit = sqlite3_open("boginventory.db", &DB);
    int sku;
    string sql;

    cout << "Enter sku of the product to be removed: ";
    cin >> sku;

    sql = "DELETE FROM Inventory WHERE SKU = " + std::to_string(sku);

    exit = sqlite3_exec(DB, sql.c_str(),NULL, nullptr,&messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error deleting product" << std::endl;
    }
    else
        std::cout << "Product deleted successfully!" << std::endl;

}

void updateProductQuantity(){
    sqlite3* DB;
    char* messageError;
    int exit = sqlite3_open("boginventory.db", &DB);
    int sku;
    int quantity;
    string sql;

    cout << "Enter sku of product to update: ";
    cin >> sku;
    cout << "Enter new quantity: ";
    cin >> quantity;

    sql = "UPDATE Inventory SET quantity = " + std::to_string(quantity)
            + " WHERE sku = " + std::to_string(sku) + ";";

    exit = sqlite3_exec(DB, sql.c_str(),NULL, nullptr,&messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error updating quantity." << std::endl;
    }
    else
        std::cout << "Quantity updated successfully!" << std::endl;
}

int main(){
    MainMenu mainMenu;
    int userContinue = 1;
    sqlite3* DB;
    char* messageError;
    int exit = sqlite3_open("boginventory.db", &DB);
    string query = "SELECT * FROM Inventory";

    sqlite3_open("boginventory.db", &DB);

    if (exit != SQLITE_OK) {
        std::cerr << "Error Opening Database" << std::endl;
    }
    else
        std::cout << "Database opened successfully!" << std::endl;

    exit = sqlite3_exec(DB, query.c_str(),NULL, nullptr,&messageError);
    if (exit != SQLITE_OK) {
        createTable();
    }
    else
        std::cout << "Table exists!" << std::endl;

    do {

        mainMenu.printMainMenu();
        switch (mainMenu.getUserSelectionFromMainMenu()){
            case 1:
                viewCurrentInventory();
                break;
            case 2:
                addProductToInventory();
                break;
            case 3:
                updateProductQuantity();
                break;
            case 4:
                removeProductFromInventory();
                break;
            case 5:
                return 0;
                break;
        }


        cout << "Enter 1 to continue, 0 to quit: ";
        cin >> std::ws >> userContinue;
        while (userContinue < 0 || userContinue > 1 || std::cin.fail()){
            cin.clear();
            cin.ignore();
            cout << "Invalid input, 0 or 1 ONLY, try again: ";
            cin >> userContinue;
        }
        system("clear");
        cout << std::flush;
    } while(userContinue == 1);

    return 0;
}