#include "SQLTable.hpp"

// SQLTable class contains all functions relevant to the handling
// of the SQL database, and executing sql commands.
class SQLTable {
public:
    InventoryLogger primaryLogger;

    // Opens database connection or creates database if it doesn't exist
    void openDatabaseConnection(){
        sqlite3* DB;
        char* messageError;
        int exit = sqlite3_open("boginventory.db", &DB);
        sqlite3_open("boginventory.db", &DB);
        // If sql throws an error, output error string, otherwise output success string
        if (exit != SQLITE_OK) {
            std::cerr << "Error Opening Database" << std::endl;
        }
        else
            std::cout << "Database opened successfully!" << std::endl;
    }

    // Checks for existence of "Inventory" table and calls createTable()
    // if it doesn't exist
    void checkOrCreateTable() {
        sqlite3* DB;
        char* messageError;
        string query = "SELECT * FROM Inventory";

        // If sql throws an error (table doesn't exist), call createTable()
        // otherwise output success string
        int exit = sqlite3_exec(DB, query.c_str(),NULL, nullptr,&messageError);
        if (exit != SQLITE_OK) {
            createTable();
        }
        else
            std::cout << "Table exists!" << std::endl;
    }

    // Callback function for the returns from SQL arguments
    static int callback(void* data, int argc, char** argv, char** azColName)
    {
        int i;

        for (i = 0; i < argc; i++) {
            cout << azColName[i] << "  -  " << argv[i] << "\n";
        }

        printf("\n");
        return 0;
    }

    // Creates a table called "Inventory" when called from checkOrCreateTable
    static void createTable() {
        sqlite3 *DB;
        char *messageError;
        int exit = sqlite3_open("boginventory.db", &DB);

        // Set string for sql instruction to create a table with preset values
        string sql = "CREATE TABLE Inventory (SKU INTEGER PRIMARY KEY,"
                     "PRODUCT TEXT NOT NULL, QUANTITY INTEGER DEFAULT 0);";

        // If sql throws an error, output error string, otherwise output success string
        exit = sqlite3_exec(DB, sql.c_str(), NULL, nullptr, &messageError);
        if (exit != SQLITE_OK) {
            std::cerr << "Error creating table." << "\n";
        } else
            std::cout << "Table created successfully!" << "\n";

    }

    // Function displays current contents of the "Inventory" table
    void viewCurrentInventory() {
        sqlite3 *DB;
        char *messageError;
        int exit = sqlite3_open("boginventory.db", &DB);
        string sql;

        // Set string for sql instruction to list table contents of "Inventory"
        sql = "SELECT * FROM INVENTORY;";

        sqlite3_exec(DB, sql.c_str(), callback, nullptr, &messageError);

    }

    // Function adds products to "Inventory" table
    void addProductToInventory() {
        sqlite3 *DB;
        char *messageError;
        int exit = sqlite3_open("boginventory.db", &DB);
        string sql;
        int sku;
        string product;
        int quantity;

        // Get user input on product details to be input.
        cout << "Enter SKU: ";
        cin >> sku;
        cout << "Enter product name: ";
        cin >> product;
        cout << "Enter quantity on hand: ";
        cin >> quantity;

        // Set string for sql instruction to add product into table "Inventory"
        sql = "INSERT INTO Inventory VALUES(" + std::to_string(sku) + ", '" + product + "', " +
              std::to_string(quantity) + ");";

        exit = sqlite3_exec(DB, sql.c_str(), NULL, nullptr, &messageError);
        if (exit != SQLITE_OK) {
            std::cerr << "Error adding data" << "\n";
            primaryLogger.createLogErrorEntry(std::to_string(*messageError));
        } else {
            std::cout << "Data added successfully!" << "\n";
            primaryLogger.createLogEntry(sql);
        }

    }

    // Function removes entries from "Inventory" table
    void removeProductFromInventory() {
        sqlite3 *DB;
        char *messageError;
        int exit = sqlite3_open("boginventory.db", &DB);
        int sku;
        string sql;

        // Get user input on sku of product they wish to delete
        cout << "Enter sku of the product to be removed: ";
        cin >> sku;

        // Set string for sql instruction to remove product from table "Inventory"
        sql = "DELETE FROM Inventory WHERE SKU = " + std::to_string(sku);

        exit = sqlite3_exec(DB, sql.c_str(), NULL, nullptr, &messageError);
        if (exit != SQLITE_OK) {
            std::cerr << "Error deleting product" << "\n";
        } else {
            std::cout << "Product deleted successfully!" << "\n";
            primaryLogger.createLogEntry(sql);
        }
    }

    // Function updates quantity of entries in "Inventory" table
    void updateProductQuantity() {
        sqlite3 *DB;
        char *messageError;
        int exit = sqlite3_open("boginventory.db", &DB);
        int sku;
        int quantity;
        string sql;

        // Get user input on product they wish to update quanitty of
        cout << "Enter sku of product to update: ";
        cin >> sku;
        cout << "Enter new quantity: ";
        cin >> quantity;

        // Set string for sql instruction to update product in table "Inventory"
        sql = "UPDATE Inventory SET quantity = " + std::to_string(quantity)
              + " WHERE sku = " + std::to_string(sku) + ";";

        exit = sqlite3_exec(DB, sql.c_str(), NULL, nullptr, &messageError);
        if (exit != SQLITE_OK) {
            std::cerr << "Error updating quantity." << "\n";
        } else {
            std::cout << "Quantity updated successfully!" << "\n";
            primaryLogger.createLogEntry(sql);
        }
    }
};