#include "ConfigFile.h"

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
void getFilenames(string &repairShopFilename, string &vFilename, string &cFilename, string &eFilename) {
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
}

/**
 * @brief asks for user input to create and return a client
 */
Client askForClientInput() {
    string returnString = "";
    while (!readString("Please insert the client name: ", returnString)) {
        cout << "Please insert a valid client name" << endl;
    }
    return Client(returnString);
}

/**
 * @brief asks for user input to create and return an employee
 */
Employee askForEmployeeInput() {
    string returnString = "";
    while (!readString("Please insert the employee name: ", returnString)) {
        cout << "Please insert a valid employee name" << endl;
    }
    return Employee(returnString);
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
        "Note: a valid license plate is of type: XX-XX-XX where only 1 pair of consecutive X's can be letters, the others must be digits" << endl;
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

/**
 * @brief asks for user input to create and return a service
 */
Service *askForServiceInput() {
    string returnString = "";
    int typeOfService;
    Service *returnService;
    Date startingDate{0};
    cout << "Choose a type of service: " << endl;
    cout << "1 - Oil Change" << endl;
    cout << "2 - Inspection" << endl;
    cout << "3 - Car Wash" << endl;
    cout << "4 - Other (Non Standard Service)" << endl;
    typeOfService = getMenuInput(4);
    while (!validDay(startingDate.year, startingDate.month, startingDate.day)) {
        while (!readString("Please insert the starting date year: ", returnString) || !isInt(returnString)) {
            cout << "Please insert a valid starting date year" << endl;
        }
        startingDate.year = atoi(returnString.c_str());
        while (!readString("Please insert the starting date month: ", returnString) || !isInt(returnString)) {
            cout << "Please insert a valid starting date month" << endl;
        }
        startingDate.month = atoi(returnString.c_str());
        while (!readString("Please insert the starting date day: ", returnString) || !isInt(returnString)) {
            cout << "Please insert a valid starting date day" << endl;
        }
        startingDate.day = atoi(returnString.c_str());
        if (!validDay(startingDate.year, startingDate.month, startingDate.day))
            cout << "Invalid date! Insert a correct one: " << endl;
    }
    cout << startingDate.day << "/" << startingDate.month << "/" << startingDate.year << endl;
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
        Employee newEmployee = askForEmployeeInput();
        repairShop.addEmployee(newEmployee);
    }
    Vehicle *newVehicle = askForVehicleInput();
    cout << "Vehicle owner: " << endl;
    Client newClient = askForClientInput();
    int clientIndex = sequentialSearch(repairShop.getClients(), newClient);
    if (clientIndex == -1) {
        repairShop.addClient(newClient);
        clientIndex = repairShop.getClients().size() - 1;
    }
    if (repairShop.addVehicle(newVehicle)) {
        if (repairShop.addVehicleToClient(newVehicle, clientIndex))
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
    cout << "10 - Back" << endl;
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
    cout << "9 - Back" << endl;

}

/**
 * @brief deals with user choices on View Info menu
 */
void goToViewInfoMenu(AutoRepairShop &repairShop) {
    int menuInput;
    displayViewInfoMenu();
    menuInput = getMenuInput(10);
    while (menuInput != 10) {
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
                Client client = askForClientInput();
                int clientIndex = sequentialSearch(repairShop.getClients(), client);
                if (clientIndex == -1) {
                    cout << "Client " << client.getName() << " doesn't exist" << endl;
                    break;
                }
                repairShop.getClients()[clientIndex].printServices();
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
            default:
                cout << "This isn't supposed to happen, please report the error!" << endl;
        }
        cout << "Press any key to continue..." << endl;
        getchar();
        displayViewInfoMenu();
        menuInput = getMenuInput(10);
    }
}

/**
 * @brief deals with user choices on Update menu
 */
void goToUpdateMenu(AutoRepairShop &repairShop) {
    int menuInput;
    displayUpdateMenu();
    menuInput = getMenuInput(9);
    while (menuInput != 9) {
        switch (menuInput) {
            case 1: {
                Client newClient = askForClientInput();
                if (repairShop.addClient(newClient))
                    cout << "Client " << newClient.getName() << " added successfully!" << endl;
                else
                    cout << "There's already a client with the name " << newClient.getName() << "!" << endl;
                break;
            }
            case 2: {
                Employee newEmployee = askForEmployeeInput();
                if (repairShop.addEmployee(newEmployee))
                    cout << "Employee " << newEmployee.getName() << " added successfully!" << endl;
                else
                    cout << "There's already an employee with the name " << newEmployee.getName() << "!" << endl;
                break;
            }
            case 3:
                addVehicle(repairShop);
                break;
            case 4: {
                int vehicleIndex;
                Service *newService = askForServiceInput();
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
                repairShop.getVehicles()[vehicleIndex]->addService(newService);
                cout << "Service " << newService->getDescription() << " added successfully!" << endl;
                break;
            }
            case 5: {
                Client toRemoveClient = askForClientInput();
                if (repairShop.removeClient(toRemoveClient))
                    cout << "Client " << toRemoveClient.getName() << " removed successfully!" << endl;
                else
                    cout << "Client " << toRemoveClient.getName() << " doesn't exist!" << endl;
                break;
            }
            case 6: {
                Employee toRemoveEmployee = askForEmployeeInput();
                if (repairShop.removeEmployee(toRemoveEmployee))
                    cout << "Employee " << toRemoveEmployee.getName() << " removed successfully!" << endl;
                else
                    cout << "Employee " << toRemoveEmployee.getName() << " doesn't exist!" << endl;
                break;
            }
            case 7: {
                Vehicle *toRemoveVehicle = askForVehicleInput();
                if (repairShop.removeVehicle(toRemoveVehicle))
                    cout << toRemoveVehicle->getManufacturer() << " " << toRemoveVehicle->getModel() <<
                    "with license plate " << toRemoveVehicle->getLicensePlate() << " removed successfully!" << endl;
                else
                    cout << toRemoveVehicle->getManufacturer() << " " << toRemoveVehicle->getModel() <<
                    "with license plate " << toRemoveVehicle->getLicensePlate() << " doesn't exist!" << endl;
                break;
            }
            case 8: {
                Service *toRemoveService = askForServiceInput();
                Vehicle *toRemoveFromVehicle;
                int vehicleIndex;
                cout << "From which vehicle do you want to add the service? " << endl;
                if (askForVehicleLicensePlate(repairShop, toRemoveFromVehicle)) {
                    vehicleIndex = sequentialSearch(repairShop.getVehicles(), toRemoveFromVehicle);
                    if (repairShop.getVehicles()[vehicleIndex]->removeService(toRemoveService)) {
                        cout << "Service " << toRemoveService->getDescription() << " removed successfully!" << endl;
                        break;
                    }
                    else {
                        cout << "The " << toRemoveService->getDescription() << " service you provided doesn't exist!" <<
                        endl;
                        break;
                    }
                }
                else {
                    cout << "No service removed because you didn't provide a target vehicle" << endl;
                    break;
                }
            }
            default:
                cout << "This isn't supposed to happen, please report the error!" << endl;
        }
        cout << "Press any key to continue..." << endl;
        getchar();
        displayUpdateMenu();
        menuInput = getMenuInput(9);
    }
}

/**
 * @brief saves data to files
 */
bool saveData(AutoRepairShop &repairShop) {
    string returnString, repairShopFilename, vFilename, cFilename, eFilename;
    int choice = 0;
    while (choice != 3) {
        getFilenames(repairShopFilename, vFilename, cFilename, eFilename);
        AutoRepairShopFile repairShopFile(repairShopFilename);
        if (!repairShopFile.saveData(repairShop, vFilename, cFilename, eFilename)) {
            cout << "There are existing files with the same name!" << endl << "What do you want to do? " << endl;
            cout << "1 - Overwrite files" << endl;
            cout << "2 - Choose another name for files" << endl;
            cout << "3 - Exit" << endl;
            choice = getMenuInput(3);
            switch (choice) {
                case 1:
                    return repairShopFile.saveData(repairShop, vFilename, cFilename, eFilename, true);
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
