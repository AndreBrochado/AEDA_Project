#include <stdlib.h>
#include <stdio.h>

#include "ConfigFile.h"

#define SERVICE_OFFER 1 //rand()%2

/**
 * @returns true if the string contains only an integer
 */
bool isInt(string s) {
    for (size_t i = 0; i < s.size(); i++) {
        if (!isdigit(s[i]))
            return false;
    }
    return true;
}

/**
 * @returns true if the string contains only an integer or a float
 */
bool isFloat(string s) {
    int numPoints = 0;
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] == '.')
            numPoints++;
        else if (!isdigit(s[i]))
            return false;
    }
    return (numPoints == 0 || numPoints == 1);
}

/**
 * @returns true if the string contains only a valid license plate (XX-XX-XX with only 1 consecutive pair of letters and 2 pairs of digits)
 */
bool isValidLicensePlate(string licensePlate) {
    if (licensePlate.size() != 8)
        return false;
    if (licensePlate[2] != '-' || licensePlate[5] != '-')
        return false;
    if (isdigit(licensePlate[0]) && isdigit(licensePlate[1])) {
        if (isdigit(licensePlate[3]) && isdigit(licensePlate[4]) && isalpha(licensePlate[6]) &&
            isalpha(licensePlate[7]))
            return true;
        if (isalpha(licensePlate[3]) && isalpha(licensePlate[4]) && isdigit(licensePlate[6]) &&
            isdigit(licensePlate[7]))
            return true;
    }
    else if (isalpha(licensePlate[0]) && isalpha(licensePlate[1]) && isdigit(licensePlate[3]) &&
             isdigit(licensePlate[4]) && isdigit(licensePlate[6]) && isdigit(licensePlate[7]))
        return true;
    return false;
}

/**
 * @brief reads user selection on a menu
 */
int getMenuInput(int numberOfOptions) {
    string returnString = "";
    readString("Your selection is: ", returnString);
    while (atoi(returnString.c_str()) < 1 || atoi(returnString.c_str()) > numberOfOptions) {
        cout << "Invalid selection! Try again!" << endl;
        readString("Your selection is: ", returnString);
    }
    return atoi(returnString.c_str());
}

/**
 * @brief reads filenames to save files
 */
void getFilenames(string &repairShopFilename, string &vFilename, string &cFilename, string &eFilename,
                  string &sFilename, string &icFilename) {
    string returnString;
    while (!readString("Please insert the Auto Repair Shop File name: ", returnString)) {
        cout << "Please insert a valid file name" << endl;
    }
    repairShopFilename = returnString;
    while (!readString("Please insert the Vehicles File name: ", returnString)) {
        cout << "Please insert a valid file name" << endl;
    }
    vFilename = returnString;
    while (!readString("Please insert the Clients File name: ", returnString)) {
        cout << "Please insert a valid file name" << endl;
    }
    cFilename = returnString;
    while (!readString("Please insert the Employees File name: ", returnString)) {
        cout << "Please insert a valid file name" << endl;
    }
    eFilename = returnString;
    while (!readString("Please insert the Services File name: ", returnString)) {
        cout << "Please insert a valid file name" << endl;
    }
    sFilename = returnString;
    while (!readString("Please insert the Inactive Clients File name: ", returnString)) {
        cout << "Please insert a valid file name" << endl;
    }
    icFilename = returnString;
}

/**
 * @brief asks for user input to create and return a client
 */
Client *askForClientInput() {
    string returnString = "";
    string name, address, email, phoneNumber;
    while (!readString("Please insert the client name: ", returnString)) {
        cout << "Please insert a valid name" << endl;
    }
    name = returnString;
    while (!readString("Please insert the client address: ", returnString)) {
        cout << "Please insert a valid address" << endl;
    }
    address = returnString;
    while (!readString("Please insert the client email: ", returnString)) {
        cout << "Please insert a valid email" << endl;
    }
    email = returnString;
    while (!readString("Please insert the client telephone number: ", returnString)) {
        cout << "Please insert a valid telephone number" << endl;
    }
    phoneNumber = returnString;

    return new Client(name, address, email, phoneNumber);
}

Client *askForClientName() {
    string returnString = "";
    while (!readString("Please insert the client name: ", returnString)) {
        cout << "Please insert a valid name" << endl;
    }
    return new Client(returnString, "", "", "");
}

/**
 * @brief asks for user input to create and return an employee
 */
Employee *askForEmployeeInput() {
    string returnString = "";
    while (!readString("Please insert the employee name: ", returnString)) {
        cout << "Please insert a valid employee name" << endl;
    }
    return new Employee(returnString);
}

/**
 * @brief asks for a license plate and returns the corresponding vehicle on returnVehicle (if it exists)
 * @returns false if the vehicle doesn't exist
 */
bool askForVehicleLicensePlate(AutoRepairShop &repairShop, Vehicle *&returnVehicle) {
    string returnString;
    while (true) {
        while (!readString("Please insert the vehicle license plate: ", returnString) ||
               !isValidLicensePlate(returnString)) {
            cout << "Please insert a valid license plate" << endl;
            cout <<
            "Note: a valid license plate is of type: XX-XX-XX where only 1 pair of consecutive X's can be letters, the others must be digits";
        }
        try {
            returnVehicle = repairShop.vehicleWithLicensePlate(returnString);
            return true;
        } catch (AutoRepairShop::InexistentVehicle e) {
            e.showErrorMessage();
            cout << endl << "Do you wish to try again? (y for yes, Any other key for no)";
            char c = getchar();
            cin.ignore(100, '\n');
            if (c != 'y')
                break;
        }
        return false;
    }
    return false;
}

/**
 * @brief asks for user input to create and return a vehicle
 */
Vehicle *askForVehicleInput() {
    string returnString = "", manufacturer, model, licensePlate;
    int typeOfVehicle;
    cout << "Choose a type of vehicle: " << endl;
    cout << "1 - Automobile" << endl;
    cout << "2 - Motorcycle" << endl;
    cout << "3 - Truck" << endl;
    cout << "4 - Bus" << endl;
    typeOfVehicle = getMenuInput(4);
    while (!readString("Please insert the vehicle manufacturer: ", returnString)) {
        cout << "Please insert a valid manufacturer name" << endl;
    }
    manufacturer = returnString;
    while (!readString("Please insert the vehicle model: ", returnString)) {
        cout << "Please insert a valid model name" << endl;
    }
    model = returnString;
    while (!readString("Please insert the vehicle license plate: ", returnString) ||
           !isValidLicensePlate(returnString)) {
        cout << "Please insert a valid license plate" << endl;
        cout <<
        "Note: a valid license plate is of type: XX-XX-XX where only 1 pair of consecutive X's can be letters, the others must be digits" <<
        endl;
    }
    licensePlate = returnString;
    Vehicle *returnVehicle;
    switch (typeOfVehicle) {
        case 1: {
            while (!readString("Please insert the number of doors of the automobile: ", returnString) ||
                   !isInt(returnString)) {
                cout << "Please insert a valid number of doors" << endl;
            }
            returnVehicle = new Automobile(manufacturer, model, licensePlate, atoi(returnString.c_str()));
            break;
        }
        case 2: {
            while (!readString("Please insert the motorcycle's type: ", returnString)) {
                cout << "Please insert a valid type" << endl;
            }
            returnVehicle = new Motorcycle(manufacturer, model, licensePlate, returnString);
            break;
        }
        case 3: {
            while (!readString("Please insert the maximum weight of the truck: ", returnString) ||
                   !isInt(returnString)) {
                cout << "Please insert a valid weight" << endl;
            }
            returnVehicle = new Truck(manufacturer, model, licensePlate, atoi(returnString.c_str()));
            break;
        }
        case 4: {
            while (!readString("Please insert the number of seats on the bus: ", returnString) ||
                   !isInt(returnString)) {
                cout << "Please insert a valid number of seats" << endl;
            }
            int numberOfSeats = atoi(returnString.c_str());
            while (!readString("Please insert the number of standing room on the bus: (in number of people who fit)",
                               returnString) ||
                   !isInt(returnString)) {
                cout << "Please insert a valid number for the standing room" << endl;
            }
            returnVehicle = new Bus(manufacturer, model, licensePlate, numberOfSeats, atoi(returnString.c_str()));
            break;
        }
        default:
            cout << "This isn't supposed to happen, please report the error!" << endl;
    }
    return returnVehicle;
}

void getDate(tm &date) {
    string returnString = "";
    do {
        while (!readString("Please insert the starting date year: ", returnString) || !isInt(returnString)) {
            cout << "Please insert a valid starting date year" << endl;
        }
        date.tm_year = atoi(returnString.c_str()) - 1900;
        while (!readString("Please insert the starting date month: ", returnString) || !isInt(returnString)) {
            cout << "Please insert a valid starting date month" << endl;
        }
        date.tm_mon = atoi(returnString.c_str()) - 1;
        while (!readString("Please insert the starting date day: ", returnString) || !isInt(returnString)) {
            cout << "Please insert a valid starting date day" << endl;
        }
        date.tm_mday = atoi(returnString.c_str());

        if (!validDay(date.tm_year + 1900, date.tm_mon + 1, date.tm_mday))
            cout << "Invalid date! Insert a correct one: " << endl;

    } while (!validDay(date.tm_year + 1900, date.tm_mon + 1, date.tm_mday));
    do {
        while (!readString("Please insert the starting hour: ", returnString) || !isInt(returnString)) {
            cout << "Please insert a valid starting hour" << endl;
        }
        date.tm_hour = atoi(returnString.c_str());
        while (!readString("Please insert the starting minute: ", returnString) || !isInt(returnString)) {
            cout << "Please insert a valid starting minute" << endl;
        }
        date.tm_min = atoi(returnString.c_str());
        if (!validHour(date.tm_hour, date.tm_min))
            cout << "Invalid hour! Insert a correct one: " << endl;
    } while (!validHour(date.tm_hour, date.tm_min));
}

Service *askForServiceTypeAndDate(Client *client, Vehicle *vehicle) {
    int typeOfService;
    Service *returnService;
    tm startingDate = {0};
    string returnString = "";
    cout << "Choose a type of service: " << endl;
    cout << "1 - Oil Change" << endl;
    cout << "2 - Inspection" << endl;
    cout << "3 - Car Wash" << endl;
    cout << "4 - Other (Non Standard Service)" << endl;
    typeOfService = getMenuInput(4);
    do {
        getDate(startingDate);
        if (!(startingDate > getToday()))
            cout << "Please insert a date in the future" << endl;
    } while (!(startingDate > getToday()));
    switch (typeOfService) {
        case 1:
            returnService = new OilChange(startingDate);
            break;
        case 2:
            returnService = new Inspection(startingDate);
            break;
        case 3:
            returnService = new CarWash(startingDate);
            break;
        case 4: {
            while (!readString("Please insert the service's description: ", returnString)) {
                cout << "Please insert a valid description" << endl;
            }
            string description = returnString;
            while (!readString("Please insert the service's price: ", returnString) || !isFloat(returnString)) {
                cout << "Please insert a valid price (integer or float)" << endl;
            }
            float price = (float) atof(returnString.c_str());
            while (!readString("Please insert the service's duration in days: ", returnString) ||
                   !isInt(returnString)) {
                cout << "Please insert a valid duration (an integer number of days)" << endl;
            }
            int duration = atoi(returnString.c_str());
            returnService = new NonStandardService(startingDate, description, price, duration);
            break;
        }
        default:
            cout << "This isn't supposed to happen, please report the error!" << endl;
    }
    returnService->addClient(client);
    returnService->addVehicle(vehicle);
    return returnService;
}


/**
 * @brief asks for user input to create and return a service
 */
Service *askForServiceInput(int isScheduled) {
    string returnString = "";
    int typeOfService;
    Service *returnService;
    tm startingDate = {0};
    cout << "Choose a type of service: " << endl;
    cout << "1 - Oil Change" << endl;
    cout << "2 - Inspection" << endl;
    cout << "3 - Car Wash" << endl;
    cout << "4 - Other (Non Standard Service)" << endl;
    typeOfService = getMenuInput(4);
    if (isScheduled) {
        do {
            getDate(startingDate);
            if (!(startingDate > getToday()))
                cout << "Please insert a date in the future" << endl;
        } while (!(startingDate > getToday()));
    }
    else
        do {
            getDate(startingDate);
            if (!(getToday() > startingDate))
                cout << "Please insert a date in the past" << endl;
        } while (!(getToday() > startingDate));

    switch (typeOfService) {
        case 1:
            returnService = new OilChange(startingDate);
            break;
        case 2:
            returnService = new Inspection(startingDate);
            break;
        case 3:
            returnService = new CarWash(startingDate);
            break;
        case 4: {
            while (!readString("Please insert the service's description: ", returnString)) {
                cout << "Please insert a valid description" << endl;
            }
            string description = returnString;
            while (!readString("Please insert the service's price: ", returnString) || !isFloat(returnString)) {
                cout << "Please insert a valid price (integer or float)" << endl;
            }
            float price = (float) atof(returnString.c_str());
            while (!readString("Please insert the service's duration in days: ", returnString) ||
                   !isInt(returnString)) {
                cout << "Please insert a valid duration (an integer number of days)" << endl;
            }
            int duration = atoi(returnString.c_str());
            returnService = new NonStandardService(startingDate, description, price, duration);
            break;
        }
        default:
            cout << "This isn't supposed to happen, please report the error!" << endl;
    }
    return returnService;
}

/**
 * @brief asks user for filename and loads Auto Repair Shop from file
 */
AutoRepairShop loadRepairShop() {
    string returnString = "";
    AutoRepairShop repairShop("");
    bool loaded = false;
    while (!loaded) {
        while (!readString("Please insert the Auto Repair Shop file name: ", returnString)) {
            cout << "Please insert a valid file name" << endl;
        }
        try {
            AutoRepairShopFile file(returnString);
            repairShop = file.loadData();
            loaded = true;
        } catch (AutoRepairShopFile::FileException &e) {
            e.showErrorMessage();
            cout << endl;
        }
    }
    return repairShop;
}

/**
 * @brief adds a vehicle to the Auto Repair Shop (and its dependencies - Employee and Client, if needed)
 */
void addVehicle(AutoRepairShop &repairShop) {
    if (repairShop.getEmployees().size() == 0) {
        cout << "You need an employee to be responsible for this vehicle! " << endl;
        Employee *newEmployee = askForEmployeeInput();
        repairShop.addEmployee(newEmployee);
    }
    Vehicle *newVehicle = askForVehicleInput();
    cout << "Vehicle owner: " << endl;
    Client *newClient = askForClientName();
    vector<Client *> clientsWithGivenName = repairShop.clientsWithName(newClient->getName());
    if (clientsWithGivenName.size() == 1)
        newClient = clientsWithGivenName[0];
    else if (clientsWithGivenName.size() > 1) {
        cout << "There are " << clientsWithGivenName.size() <<
        " clients with that name. Which one owns the vehicle?";
        for (size_t i = 0; i < clientsWithGivenName.size(); i++) {
            cout << endl << i + 1 << " - ";
            clientsWithGivenName[i]->printObjectInfo();
        }
        cout << endl << "Or enter " << clientsWithGivenName.size() + 1 << " to back" << endl;
        int clientChoice = getMenuInput(clientsWithGivenName.size() + 1);
        if (clientChoice == clientsWithGivenName.size() + 1)
            return;
        else
            newClient = clientsWithGivenName[clientChoice - 1];
    }
    else
        repairShop.addClient(newClient);

    if (repairShop.addVehicle(newVehicle)) {
        if (repairShop.addVehicleToClient(newVehicle, newClient))
            cout << newVehicle->getManufacturer() << " " << newVehicle->getModel() << " with license plate " <<
            newVehicle->getLicensePlate() << " added successfully!" << endl;
        else
            cout << "That vehicle already exists!" << endl;
    }
    else
        cout << "That vehicle already exists!" << endl;
}

/**
 * @brief displays main menu
 */
void displayMainMenu() {
    cout << "Main Menu" << endl;
    cout << "Please make your selection" << endl;
    cout << "1 - Create a new Auto Repair Shop" << endl;
    cout << "2 - Load an Auto Repair Shop from files" << endl;
    cout << "3 - Exit" << endl;
};

/**
 * @brief displays Auto Repair Shop menu (after load)
 */
void displayShopMenu() {
    cout << "Auto Repair Shop Menu" << endl;
    cout << "Please make your selection" << endl;
    cout << "1 - View info (All info, clients, vehicles, ...)" << endl;
    cout << "2 - Update info (Add or remove: clients, vehicles, ...)" << endl;
    cout << "3 - Exit" << endl;
}

/**
 * @brief displays View Info menu
 */
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
    cout << "10 - View Inactive Clients Info" << endl;
    cout << "11 - View Scheduled Services (Ordered by decrescent service date)" << endl;
    cout << "12 - View Inactive Clients with name" << endl;
    cout << "13 - Back" << endl;
}

/**
 * @brief displays Update menu
 */
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
    cout << "9 - Schedule a Service" << endl;
    cout << "10 - Change a Scheduled Service (change date or/and type of Service)" << endl;
    cout << "11 - Cancel a Scheduled Service" << endl;
    cout << "12 - Back" << endl;

}

/**
 * @brief deals with user choices on View Info menu
 */
void goToViewInfoMenu(AutoRepairShop &repairShop) {
    int menuInput;
    displayViewInfoMenu();
    menuInput = getMenuInput(13);
    while (menuInput != 13) {
        switch (menuInput) {
            case 1:
                repairShop.printAllInfo();
                cout << endl;
                break;
            case 2:
                repairShop.printServices();
                cout << endl;
                break;
            case 3: {
                Client *client = askForClientInput();
                int clientIndex = sequentialSearch(repairShop.getClients(), client);
                if (clientIndex == -1) {
                    cout << "Client " << client->getName() << " doesn't exist" << endl;
                    break;
                }
                repairShop.getClients()[clientIndex]->printServices();
                cout << endl;
                break;
            }
            case 4: {
                Vehicle *vehicle;
                if (askForVehicleLicensePlate(repairShop, vehicle)) {
                    int vehicleIndex = sequentialSearch(repairShop.getVehicles(), vehicle);
                    if (vehicleIndex == -1) {
                        cout << "This isn't supposed to happen, please report the error!" << endl;
                        break;
                    }
                    repairShop.getVehicles()[vehicleIndex]->printServices();
                    cout << endl;
                    break;
                }
                else {
                    cout << "You didn't choose a vehicle to show its services." << endl;
                    break;
                }
            }
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
            case 8: {
                string returnString;
                while (!readString("Please insert the clients' name first letter: ", returnString) ||
                       returnString.size() != 1) {
                    cout << "Please insert a valid input (only 1 letter)" << endl;
                }
                repairShop.printClientsWithFirstLetter(returnString[0]);
                cout << endl;
                break;
            }
            case 9: {
                string returnString;
                while (!readString("Please insert the clients' name first letter: ", returnString) ||
                       returnString.size() != 1) {
                    cout << "Please insert a valid input (only 1 letter)" << endl;
                }
                repairShop.printEmployeesWithFirstLetter(returnString[0]);
                cout << endl;
                break;
            }
            case 10: {
                repairShop.printInactiveClientsInfo();
                break;
            }
            case 11: {
                repairShop.printScheduledServicesInOrder();
                break;
            }
            case 12: {
                string returnString = "";
                while (!readString("Please insert the Inactive Client name: ", returnString)) {
                    cout << "Please insert a valid name" << endl;
                }
                repairShop.printInactiveClientsWithName(returnString);
            }
            default:
                cout << "This isn't supposed to happen, please report the error!" << endl;
        }
        cout << "Press any key to continue..." << endl;
        getchar();
        displayViewInfoMenu();
        menuInput = getMenuInput(13);
    }
}

/**
 * @brief deals with user choices on Update menu
 */
void goToUpdateMenu(AutoRepairShop &repairShop) {
    int menuInput;
    displayUpdateMenu();
    menuInput = getMenuInput(12);
    while (menuInput != 12) {
        switch (menuInput) {
            case 1: {
                Client *newClient = askForClientInput();
                repairShop.addClient(newClient);
                cout << "Client " << newClient->getName() << " added successfully!" << endl;
                break;
            }
            case 2: {
                Employee *newEmployee = askForEmployeeInput();
                repairShop.addEmployee(newEmployee);
                cout << "Employee " << newEmployee->getName() << " added successfully!" << endl;
                break;
            }
            case 3:
                addVehicle(repairShop);
                break;
            case 4: {
                int vehicleIndex;
                Service *newService = askForServiceInput(0);
                if (repairShop.getVehicles().size() == 0) {
                    cout << "You need a vehicle to add that service!" << endl;
                    addVehicle(repairShop);
                    vehicleIndex = repairShop.getVehicles().size() - 1;
                }
                else {
                    Vehicle *targetVehicle;
                    cout << "To which vehicle do you want to add the service? " << endl;
                    if (askForVehicleLicensePlate(repairShop, targetVehicle)) {
                        vehicleIndex = sequentialSearch(repairShop.getVehicles(), targetVehicle);
                    }
                    else {
                        cout << "No service added because you didn't provide a target vehicle" << endl;
                        break;
                    }
                }
                Client* client = repairShop.clientWithVehicle(repairShop.getVehicles()[vehicleIndex]);
                repairShop.addServiceToVehicle(newService, repairShop.getVehicles()[vehicleIndex]);
                if (SERVICE_OFFER && repairShop.isTopClient(client) && client->getClientCard()->getPoints() != 0) {
                    cout << "You are one our best 3 clients! Do you want to trade your points for a free service? (y for yes, any key for no) ";
                    char c = getchar();
                    cin.ignore(1000, '\n');
                    if(c == 'y'){
                        repairShop.removeClientPoints(client);
                        cout << "Enjoy your free service!" << endl;
                    }
                }
                cout << "Service " << newService->getDescription() << " added successfully!" << endl;
                break;
            }
            case 5: {
                Client *toRemoveClient = askForClientName();
                vector<Client *> clientsWithGivenName = repairShop.clientsWithName(toRemoveClient->getName());
                if (clientsWithGivenName.size() == 1) {
                    repairShop.removeClient(clientsWithGivenName[0]);
                    cout << "Client " << toRemoveClient->getName() << " removed successfully!" << endl;
                }
                else if (clientsWithGivenName.size() > 1) {
                    cout << "There are " << clientsWithGivenName.size() <<
                    " clients with that name. Which one do you want to remove?";
                    for (size_t i = 0; i < clientsWithGivenName.size(); i++) {
                        cout << endl << i + 1 << " - ";
                        clientsWithGivenName[i]->printObjectInfo();
                    }
                    cout << endl << "Or enter " << clientsWithGivenName.size() + 1 << " to back" << endl;
                    int clientChoice = getMenuInput(clientsWithGivenName.size() + 1);
                    if (clientChoice == clientsWithGivenName.size() + 1)
                        break;
                    else {
                        repairShop.removeClient(clientsWithGivenName[clientChoice - 1]);
                        cout << "Client " << toRemoveClient->getName() << " removed successfully!" << endl;
                    }
                }
                else
                    cout << "Client " << toRemoveClient->getName() << " doesn't exist!" << endl;
                break;
            }
            case 6: {
                Employee *toRemoveEmployee = askForEmployeeInput();
                vector<Employee *> employeesWithGivenName = repairShop.employeesWithName(toRemoveEmployee->getName());
                if (employeesWithGivenName.size() == 1) {
                    repairShop.removeEmployee(employeesWithGivenName[0]);
                    cout << "Employee " << toRemoveEmployee->getName() << " removed successfully!" << endl;
                }
                else if (employeesWithGivenName.size() > 1) {
                    cout << "There are " << employeesWithGivenName.size() <<
                    " employees with that name. Which one do you want to remove?";
                    for (size_t i = 0; i < employeesWithGivenName.size(); i++) {
                        cout << endl << i + 1 << " - ";
                        employeesWithGivenName[i]->printObjectInfo();
                    }
                    cout << endl << "Or enter " << employeesWithGivenName.size() + 1 << " to back" << endl;
                    int employeeChoice = getMenuInput(employeesWithGivenName.size() + 1);
                    if (employeeChoice == employeesWithGivenName.size() + 1)
                        break;
                    else {
                        repairShop.removeEmployee(employeesWithGivenName[employeeChoice - 1]);
                        cout << "Employee " << toRemoveEmployee->getName() << " removed successfully!" << endl;
                        break;
                    }
                }
                else
                    cout << "Employee " << toRemoveEmployee->getName() << " doesn't exist!" << endl;
                break;
            }
            case 7: {
                Vehicle *toRemoveVehicle;
                if (askForVehicleLicensePlate(repairShop, toRemoveVehicle) && repairShop.removeVehicle(toRemoveVehicle))
                    cout << toRemoveVehicle->getManufacturer() << " " << toRemoveVehicle->getModel() <<
                    " with license plate " << toRemoveVehicle->getLicensePlate() << " removed successfully!" << endl;
                else
                    cout << toRemoveVehicle->getManufacturer() << " " << toRemoveVehicle->getModel() <<
                    "with license plate " << toRemoveVehicle->getLicensePlate() << " doesn't exist!" << endl;
                break;
            }
            case 8: {
                Service *toRemoveServiceInfo = askForServiceInput(0);
                Vehicle *toRemoveFromVehicle;
                cout << "From which vehicle do you want to remove the service? " << endl;
                if (askForVehicleLicensePlate(repairShop, toRemoveFromVehicle)) {
                    Service *toRemoveService = repairShop.findService(toRemoveServiceInfo, toRemoveFromVehicle);
                    if (toRemoveService != NULL && repairShop.removeService(toRemoveService, toRemoveFromVehicle)) {
                        cout << "Service " << toRemoveServiceInfo->getDescription() << " removed successfully!" << endl;
                        break;
                    }
                    else {
                        cout << "The " << toRemoveServiceInfo->getDescription() <<
                        " service you provided doesn't exist!" <<
                        endl;
                        break;
                    }
                }
                else {
                    cout << "No service removed because you didn't provide a target vehicle" << endl;
                    break;
                }
            }
            case 9: {
                Vehicle *targetVehicle;
                Service *newScheduledService = askForServiceInput(1);
                if (repairShop.getVehicles().size() == 0) {
                    cout << "You need a vehicle to add that service!" << endl;
                    addVehicle(repairShop);
                    targetVehicle = repairShop.getVehicles()[0];
                }
                else {
                    cout << "To which vehicle do you want to add the service? " << endl;
                    if (!askForVehicleLicensePlate(repairShop, targetVehicle)) {
                        cout << "No service added because you didn't provide a target vehicle" << endl;
                        break;
                    }
                }
                newScheduledService->addVehicle(targetVehicle);
                newScheduledService->addClient(repairShop.clientWithVehicle(targetVehicle));
                repairShop.addScheduledService(newScheduledService);
                cout << "Service " << newScheduledService->getDescription() << " added successfully!" << endl;
                break;
            }
            case 10: {
                Service *targetServiceInfo = askForServiceInput(1);
                Vehicle *targetVehicle;
                cout << "Which vehicle is associated with the service you wish to change? " << endl;
                if (askForVehicleLicensePlate(repairShop, targetVehicle)) {
                    Service *targetService = repairShop.findScheduledService(targetServiceInfo, targetVehicle);
                    if (targetService == NULL) {
                        cout << "The " << targetServiceInfo->getDescription() <<
                        " service you provided doesn't exist!";
                        break;
                    }
                    else {
                        Client *client = targetService->getClient();
                        cout << "Choose the Service you want to change to: " << endl;
                        Service *newService = askForServiceTypeAndDate(client, targetVehicle);
                        if (repairShop.removeScheduledService(targetService)) {
                            cout << "Service changed successfully!" << endl;
                            repairShop.addScheduledService(newService);
                        }
                        else
                            cout << "Error changing service" << endl;
                    }
                }
                else
                    cout << "No service changed because you didn't provide a target vehicle" << endl;
                break;
            }
            case 11: {
                Service *targetServiceInfo = askForServiceInput(1);
                Vehicle *targetVehicle;
                cout << "Which vehicle is associated with the service you wish to cancel? " << endl;
                if (askForVehicleLicensePlate(repairShop, targetVehicle)) {
                    Service *targetService = repairShop.findScheduledService(targetServiceInfo, targetVehicle);
                    if (targetService == NULL) {
                        cout << "The " << targetServiceInfo->getDescription() <<
                        " service you provided doesn't exist!";
                        break;
                    }
                    else {
                        if (repairShop.removeScheduledService(targetService))
                            cout << "Service cancelled successfully!" << endl;
                        else
                            cout << "Error cancelling service" << endl;
                    }
                }
                else
                    cout << "No service removed because you didn't provide a target vehicle" << endl;
                break;
            }
            default:
                cout << "This isn't supposed to happen, please report the error!" << endl;
        }
        cout << "Press any key to continue..." << endl;
        getchar();
        displayUpdateMenu();
        menuInput = getMenuInput(12);
    }

}

/**
 * @brief saves data to files
 */
bool saveData(AutoRepairShop &repairShop) {
    string returnString, repairShopFilename, vFilename, cFilename, eFilename, sFilename, icFilename;
    int choice = 0;
    while (choice != 3) {
        getFilenames(repairShopFilename, vFilename, cFilename, eFilename, sFilename, icFilename);
        AutoRepairShopFile repairShopFile(repairShopFilename);
        if (!repairShopFile.saveData(repairShop, vFilename, cFilename, eFilename, sFilename, icFilename)) {
            cout << "There are existing files with the same name!" << endl << "What do you want to do? " << endl;
            cout << "1 - Overwrite files" << endl;
            cout << "2 - Choose another name for files" << endl;
            cout << "3 - Exit" << endl;
            choice = getMenuInput(3);
            switch (choice) {
                case 1:
                    return repairShopFile.saveData(repairShop, vFilename, cFilename, eFilename, sFilename,
                                                   icFilename,
                                                   true);
                case 2:
                    choice = 2;
                    break;
                case 3:
                    break;
                default:
                    cout << "This isn't supposed to happen, please report the error!" << endl;
            }
        }
        else
            break;
    }
    return false;
}
