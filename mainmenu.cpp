#include <iostream>

using std::cout;
using std::cin;
using std::string;
using std::endl;

class MainMenu{
private:

public:

    void printMainMenu (){

        cout << "***************************************************\n\n";
        cout << "\tWelcome to Inventory Manager Version:1\n\n";
        cout << "***************************************************\n\n";
        cout << "\tWhat would you like to do?\n\n";
        cout << "1. View Current Inventory \t3. Update Quantity\n";
        cout << "2. Add a Product \t\t4. Remove a Product\n";
        cout << "5. Quit \n\n";


    }

    int getUserSelectionFromMainMenu(){
        int userMainMenuSelection;

        cout << "Enter your selection: ";
        cin >> userMainMenuSelection;
        cout << "\n";

        return userMainMenuSelection;
    }
};