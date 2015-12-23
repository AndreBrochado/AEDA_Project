#include "ConfigFile.h"
#include "Service.h"
#include <fstream>
#include <time.h>

ConfigFile::ConfigFile(string &filename) {
    if (filename.find('.') == string::npos)
        filename += ".txt";
    this->filename = filename;
}

void ConfigFile::createFile(string &filename) {
    ofstream outputStream;

    outputStream.open(filename);
    outputStream.close();
}

Client *ClientsFile::createClientObject(istream &in, string name,
                                        AutoRepairShop &repairShop) {
    vector<string> licensePlates;
    Client *newClient = new Client(in, name, licensePlates);
    for (size_t i = 0; i < licensePlates.size(); i++) {
        newClient->addVehicle(repairShop.vehicleWithLicensePlate(licensePlates[i]));
    }
    return newClient;
}

Employee *EmployeesFile::createEmployeeObject(istream &in, string name,
                                              AutoRepairShop &repairShop) {
    vector<string> licensePlates;
    Employee *newEmployee = new Employee(in, name, licensePlates);
    for (size_t i = 0; i < licensePlates.size(); i++) {
        newEmployee->addVehicle(repairShop.vehicleWithLicensePlate(licensePlates[i]));
    }
    return newEmployee;
}

Service *ServicesFile::createServiceObject(istream &in, AutoRepairShop &repairShop, int classIdentifier) {
    int clientID;
    string licensePlate;
    Service *newService = createService(in, classIdentifier);
    in >> clientID >> licensePlate;
    newService->addClient(repairShop.clientWithID(clientID));
    newService->addVehicle(repairShop.vehicleWithLicensePlate(licensePlate));
    return newService;
}

bool ConfigFile::existsFile(string &filename) {
    ifstream inputStream;
    bool result = false;

    inputStream.open(filename);
    result = inputStream.is_open();
    inputStream.close();
    return result;
}

bool VehiclesFile::saveData(AutoRepairShop &repairShop, bool overwrite) {
    if (!overwrite && existsFile(filename))
        return false;
    ofstream out;
    out.open(this->filename);
    for (size_t i = 0; i < repairShop.getVehicles().size(); i++) {
        repairShop.getVehicles()[i]->saveObjectInfo(out);
        if (i != repairShop.getVehicles().size() - 1)
            out << endl;
    }
    out.close();
    return true;
}

bool ClientsFile::saveData(AutoRepairShop &repairShop, bool overwrite) {
    if (!overwrite && existsFile(filename))
        return false;
    ofstream out;
    out.open(this->filename);
    writeVector(repairShop.getClients(), out);
    out.close();
    return true;
}

bool InactiveClientsFile::saveData(AutoRepairShop &repairShop, bool overwrite) {
    if (!overwrite && existsFile(filename))
        return false;
    ofstream out;
    out.open(this->filename);
    writeUnorderedSet(repairShop.getInactiveClients(), out);
    out.close();
    return true;
}

bool EmployeesFile::saveData(AutoRepairShop &repairShop, bool overwrite) {
    if (!overwrite && existsFile(filename))
        return false;
    ofstream out;
    out.open(this->filename);
    writeVector(repairShop.getEmployees(), out);
    out.close();
    return true;
}

bool ServicesFile::saveData(AutoRepairShop &repairShop, bool overwrite) {
    if (!overwrite && existsFile(filename))
        return false;
    ofstream out;
    out.open(this->filename);
    tm saveDate = getToday();
    out << saveDate.tm_mday << " " << saveDate.tm_mon << " " << saveDate.tm_year;
    writeBST(repairShop.getScheduledServices(), out);
    for (size_t i = 0; i < repairShop.getClients().size(); i++)
            writeVector(repairShop.getVehicles()[i]->getServices(), out);
    out.close();
    return true;
}

bool AutoRepairShopFile::saveData(AutoRepairShop &repairShop, string &vehiclesFilename, string &clientsFilename,
                                  string &employeesFileName, string &servicesFilename, string &inactiveClientsFilename, bool overwrite) {
    if (!overwrite && existsFile(filename))
        return false;
    ofstream out;
    out.open(this->filename);
    out << vehiclesFilename << endl << clientsFilename << endl << employeesFileName << endl << servicesFilename <<
    endl << inactiveClientsFilename << endl << repairShop.getName() /*<< endl << repairShop.getNextClientID()*/;
    out.close();
    VehiclesFile vf(vehiclesFilename);
    ClientsFile cf(clientsFilename);
    EmployeesFile ef(employeesFileName);
    ServicesFile sf(servicesFilename);
    InactiveClientsFile icf(inactiveClientsFilename);
    for (size_t i = 0; i < repairShop.getVehicles().size(); i++) {
        repairShop.assignEmployee(repairShop.getVehicles()[i]);
    }
    return (vf.saveData(repairShop, overwrite) && cf.saveData(repairShop, overwrite) &&
            ef.saveData(repairShop, overwrite) && sf.saveData(repairShop, overwrite) && icf.saveData(repairShop, overwrite));
}

bool VehiclesFile::loadData(AutoRepairShop &repairShop) {
    ifstream in;
    Vehicle *v;
    int classIdentifier = 0;
    if (!existsFile(this->filename))
        return false;
    in.open(this->filename);
    in >> classIdentifier;
    while (!in.eof()) {
        v = createVehicleObject(in, classIdentifier);
        repairShop.addVehicle(v);
        in >> classIdentifier;
    }
    return true;
}

bool ClientsFile::loadData(AutoRepairShop &repairShop) {
    ifstream in;
    string name;
    int points;
    tm date = {0};
    if (!existsFile(this->filename))
        return false;
    in.open(this->filename);
    while (getline(in, name)) {
        Client *c = createClientObject(in, name, repairShop);
        in >> date.tm_mday >> date.tm_mon >> date.tm_year >> points;
        c->createClientCard(date, points/100);
        c->checkPointsExpiration();
        repairShop.addClient(c);
    }
    return true;
}

bool InactiveClientsFile::loadData(AutoRepairShop &repairShop){
    ifstream in;
    string name;
    int points;
    tm date;
    if (!existsFile(this->filename))
        return false;
    in.open(this->filename);
    while (getline(in, name)) {
        Client *c = createClientObject(in, name, repairShop);
        repairShop.addClient(c);
    }
    return true;
}

bool EmployeesFile::loadData(AutoRepairShop &repairShop) {
    ifstream in;
    string name;
    if (!existsFile(this->filename))
        return false;
    in.open(this->filename);
    while (getline(in, name)) {
        Employee *e = createEmployeeObject(in, name, repairShop);
        repairShop.addEmployee(e);
    }
    return true;
}

bool ServicesFile::loadData(AutoRepairShop &repairShop) {
    ifstream in;
    int classIdentifier;
    if (!existsFile(this->filename))
        return false;
    in.open(this->filename);
    tm saveData = {0};
    in >> saveData.tm_mday >> saveData.tm_mon >> saveData.tm_year;
    while (in >> classIdentifier) {
        Service *newService = createServiceObject(in, repairShop, classIdentifier);
        if (newService->getStartingDate() > getToday()) {
            repairShop.addScheduledService(newService);
        }
        else {
           if(newService->getStartingDate() > saveData)
               repairShop.addServiceToVehicle(newService, newService->getVehicle());
            else
               newService->getVehicle()->addService(newService);
        }
    }
    return true;
}

AutoRepairShop AutoRepairShopFile::loadData() {
    ifstream in;
    //int nextClientID;
    string vehiclesFilename = "", clientsFilename = "", employeesFilename = "", repairShopName = "", servicesFilename = "", inactiveClientsFilename = "";
    if (!existsFile(this->filename))
        throw (InexistentFileException(this->filename));
    in.open(this->filename);
    getline(in, vehiclesFilename);
    getline(in, clientsFilename);
    getline(in, employeesFilename);
    getline(in, servicesFilename);
    getline(in, inactiveClientsFilename);
    getline(in, repairShopName);
    //in >> nextClientID;
    in.close();
    if (vehiclesFilename == "" || clientsFilename == "" || employeesFilename == "" || repairShopName == "" ||
        servicesFilename == "" || inactiveClientsFilename == "")
        throw (BadFileException(this->filename));
    VehiclesFile vf(vehiclesFilename);
    ClientsFile cf(clientsFilename);
    EmployeesFile ef(employeesFilename);
    ServicesFile sf(servicesFilename);
    InactiveClientsFile icf(inactiveClientsFilename);
    AutoRepairShop repairShop(repairShopName);
    vf.loadData(repairShop);
    cf.loadData(repairShop);
    icf.loadData(repairShop);
    ef.loadData(repairShop);
    sf.loadData(repairShop);
    repairShop.checkForInactiveClients();
    return repairShop;
}
