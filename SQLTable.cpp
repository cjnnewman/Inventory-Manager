#include <sqlite3.h>
#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::cin;

class SQLTable {
public:
        void openDatabaseConnection(){
        sqlite3* DB;
        char* messageError;
        int exit = sqlite3_open("boginventory.db", &DB);
        sqlite3_open("boginventory.db", &DB);
        if (exit != SQLITE_OK) {
            std::cerr << "Error Opening Database" << std::endl;
        }
        else
            std::cout << "Database opened successfully!" << std::endl;
    }

    void checkOrCreateTable() {
        sqlite3* DB;
        char* messageError;
        string query = "SELECT * FROM Inventory";

        int exit = sqlite3_exec(DB, query.c_str(),NULL, nullptr,&messageError);
        if (exit != SQLITE_OK) {
            createTable();
        }
        else
            std::cout << "Table exists!" << std::endl;
    }

    static int callback(void* data, int argc, char** argv, char** azColName)
    {
        int i;

        for (i = 0; i < argc; i++) {
            cout << azColName[i] << "  -  " << argv[i] << "\n";
        }

        printf("\n");
        return 0;
    }

    static void createTable() {
        sqlite3 *DB;
        char *messageError;
        int exit = sqlite3_open("boginventory.db", &DB);

        string sql = "CREATE TABLE Inventory (SKU INTEGER PRIMARY KEY,"
                     "PRODUCT TEXT NOT NULL, QUANTITY INTEGER DEFAULT 0);";

        exit = sqlite3_exec(DB, sql.c_str(), NULL, nullptr, &messageError);
        if (exit != SQLITE_OK) {
            std::cerr << "Error creating table." << "\n";
        } else
            std::cout << "Table created successfully!" << "\n";
    }

    void viewCurrentInventory() {
        sqlite3 *DB;
        char *messageError;
        int exit = sqlite3_open("boginventory.db", &DB);
        string sql;

        sql = "SELECT * FROM INVENTORY;";

        sqlite3_exec(DB, sql.c_str(), callback, nullptr, &messageError);

    }

    void addProductToInventory() {
        sqlite3 *DB;
        char *messageError;
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

        sql = "INSERT INTO Inventory VALUES(" + std::to_string(sku) + ", '" + product + "', " +
              std::to_string(quantity) + ");";

        exit = sqlite3_exec(DB, sql.c_str(), NULL, nullptr, &messageError);
        if (exit != SQLITE_OK) {
            std::cerr << "Error adding data" << "\n";
        } else
            std::cout << "Data added successfully!" << "\n";

    }

    void removeProductFromInventory() {
        sqlite3 *DB;
        char *messageError;
        int exit = sqlite3_open("boginventory.db", &DB);
        int sku;
        string sql;

        cout << "Enter sku of the product to be removed: ";
        cin >> sku;

        sql = "DELETE FROM Inventory WHERE SKU = " + std::to_string(sku);

        exit = sqlite3_exec(DB, sql.c_str(), NULL, nullptr, &messageError);
        if (exit != SQLITE_OK) {
            std::cerr << "Error deleting product" << "\n";
        } else
            std::cout << "Product deleted successfully!" << "\n";

    }

    void updateProductQuantity() {
        sqlite3 *DB;
        char *messageError;
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

        exit = sqlite3_exec(DB, sql.c_str(), NULL, nullptr, &messageError);
        if (exit != SQLITE_OK) {
            std::cerr << "Error updating quantity." << "\n";
        } else
            std::cout << "Quantity updated successfully!" << "\n";
    }
};