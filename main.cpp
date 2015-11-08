#include <iostream>
#include <string>
#include <stdlib.h>
#include <conio.h>

#include "AutoRepairShop.h"
#include "ConfigFile.h"

using namespace std;





AutoRepairShop loadRepairShop(){
    string returnString = "";
    AutoRepairShop repairShop("");
    while(true) {
        while (!readString("Please insert the Auto Repair Shop file name: ", returnString)) {
            cout << "Please insert a valid file name" << endl;
        }
        try {
            AutoRepairShopFile file(returnString);
            repairShop = file.loadData();
            break;
        } catch (AutoRepairShopFile::FileException &e) {
            e.showErrorMessage();
            cout<<endl;
        }
    }
    return repairShop;
}

void displayMainMenu() {
    cout << "Main Menu" << endl;
    cout << "Please make your selection" << endl;
    cout << "1 - Create a new Auto Repair Shop" << endl;
    cout << "2 - Load an Auto Repair Shop from files" << endl;
    cout << "3 - Exit" << endl;
};

void displayShopMenu() {
    cout << "Auto Repair Shop Menu" << endl;
    cout << "Please make your selection" << endl;
    cout << "1 - View info (All info, clients, vehicles, ...)" << endl;
    cout << "2 - Update info (Add or remove: clients, vehicles, ...)" << endl;
    cout << "3 - Exit" << endl;
}

void displayViewInfoMenu() {
    cout << "Auto Repair Shop Menu" << endl;
    cout << "Please make your selection" << endl;
    cout << "1 - View All Info" << endl;
    cout << "2 - View All Services Info" << endl;
    cout << "3 - View Services of a Client Info" << endl;
    cout << "4 - View Services of a Vehicle Info" << endl;
    cout << "5 - View Vehicles Info" << endl;
    cout << "6 - View Clients Info" << endl;
    cout << "7 - View Employees Info" << endl;
    cout << "8 - View Clients Info -- Filter by the first letter of the client name" << endl;
    cout << "9 - View Employees Info -- Filter by the first letter of the client name" << endl;
    cout << "10 - Back" << endl;
}

void displayUpdateMenu() {
    cout << "Auto Repair Shop Menu" << endl;
    cout << "Please make your selection" << endl;
    cout << "1 - Add Client" << endl;
    cout << "2 - Add Employee" << endl;
    cout << "3 - Add Vehicle" << endl;
    cout << "4 - Add Service" << endl;
    cout << "5 - Remove Client" << endl;
    cout << "6 - Remove Employee" << endl;
    cout << "7 - Remove Vehicle" << endl;
    cout << "8 - Remove Service" << endl;
    cout << "9 - Back" << endl;

}

int getMenuInput(int numberOfOptions){
    string returnString = "";
    readString("Your selection is: ", returnString);
    while(atoi(returnString.c_str()) < 1 || atoi(returnString.c_str()) > numberOfOptions){
        cout << "Invalid selection! Try again!" << endl;
        readString("Your selection is: ", returnString);
    }
    return atoi(returnString.c_str());
}

void goToViewInfoMenu(AutoRepairShop &repairShop){
    int menuInput;
    displayViewInfoMenu();
    menuInput = getMenuInput(10);
    while(menuInput != 10) {
        switch (menuInput) {
            case 1:
                repairShop.printAllInfo();
                cout << endl;
                break;
            case 2:
                repairShop.printServices();
                cout << endl;
                break;
            case 3:
                //TODO ASK FOR CLIENT
                repairShop.getClients()[1/*TODO*/].printServices();
                cout << endl;
                break;
            case 4:
                //TODO ASK FOR VEHICLE
                repairShop.getVehicles()[1/*TODO*/]->printServices();
                cout << endl;
                break;
            case 5:
                repairShop.printVehiclesInfo();
                cout << endl;
                break;
            case 6:
                repairShop.printClientsInfo();
                cout << endl;
                break;
            case 7:
                repairShop.printEmployeesInfo();
                cout << endl;
                break;
            case 8:
                //TODO ASK FOR LETTER
                repairShop.printClientsWithFirstLetter('a');
                cout << endl;
                break;
            case 9:
                //TODO ASK FOR LETTER
                repairShop.printEmployeesWithFirstLetter('a');
                cout << endl;
                break;
            default:
                cout << "This isn't supposed to happen, please report the error!" << endl;
        }
        cout << "Press any key to continue..." << endl;
        getch();
        displayViewInfoMenu();
        menuInput = getMenuInput(10);
    }
}







int main() {
    AutoRepairShop repairShop("");
    string returnString = "";
    int menuInput;
    displayMainMenu();
    menuInput = getMenuInput(3);
    switch(menuInput){
        case 1:
            while(!readString("Please insert the Auto Repair Shop name: ", returnString)){
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
    switch(menuInput){
        case 1:
            goToViewInfoMenu(repairShop);
            break;
        case 2:
            //TODO go to update menu
            break;
        case 3:
            //TODO ask if wants to save
            cout << "Goodbye!" << endl;
            return 0;
        default:
            cout << "This isn't supposed to happen, please report the error!" << endl;
            return -2;
    }

}