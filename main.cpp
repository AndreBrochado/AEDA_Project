#include <iostream>
#include <stdio.h>

#include "AutoRepairShop.h"
#include "Menus.h"

using namespace std;

int main() {
    srand(time(NULL));
    AutoRepairShop repairShop("");
    string returnString = "";
    int menuInput;
    displayMainMenu();
    menuInput = getMenuInput(3);
    switch (menuInput) {
        case 1:
            cout << endl;
            while (!readString("Please insert the Auto Repair Shop name: ", returnString)) {
                cout << "Please insert a valid name" << endl;
            }
            repairShop = AutoRepairShop(returnString);
            break;
        case 2:
            repairShop = loadRepairShop();
            break;
        case 3:
            cout << "Goodbye!" << endl;
            return 0;
        default:
            cout << "This isn't supposed to happen, please report the error!" << endl;
            return -1;
    }
    displayShopMenu();
    menuInput = getMenuInput(3);
    while (true) {
        switch (menuInput) {
            case 1:
                goToViewInfoMenu(repairShop);
                break;
            case 2:
                goToUpdateMenu(repairShop);
                break;
            case 3: {
                cout <<
                "Do you want to save the Auto Repair Shop state before exiting? (Press y for yes, any key to exit without saving) ";
                char c = getchar();
                cin.ignore(1000, '\n');
                if (c == 'y')
                    saveData(repairShop);
                cout << "Press any key to exit..." << endl;
                getchar();
                return 0;
            }
            default:
                cout << "This isn't supposed to happen, please report the error!" << endl;
                return -2;
        }
        cout << "Press any key to continue..." << endl;
        getchar();
        displayShopMenu();
        menuInput = getMenuInput(3);
    }
}