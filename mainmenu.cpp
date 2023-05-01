#include <iostream>

using std::cout;
using std::cin;
using std::string;

// MainMenu class handles displaying the menu to the user
// and getting user input for their selection.
class MainMenu{
private:
    class MainMenuVerification {
    public:
        int getUserSelectionFromMainMenu(){
            int userMainMenuSelection;

            cout << "Enter your selection: ";
            cin >> userMainMenuSelection;
            while (userMainMenuSelection < 1 || userMainMenuSelection > 5){
                cout << "Invalid selection, try again: ";
                cin >> userMainMenuSelection;
            }
            cout << "\n";

            return userMainMenuSelection;
        }

    };

public:

    int printMainMenu (){

        MainMenuVerification menuVerificationInstance;

        cout << "***************************************************\n\n";
        cout << "\tWelcome to Inventory Manager Version:1\n\n";
        cout << "***************************************************\n\n";
        cout << "\tWhat would you like to do?\n\n";
        cout << "1. View Current Inventory \t3. Update Quantity\n";
        cout << "2. Add a Product \t\t4. Remove a Product\n";
        cout << "5. Quit \n\n";

        return menuVerificationInstance.getUserSelectionFromMainMenu();
    }

};