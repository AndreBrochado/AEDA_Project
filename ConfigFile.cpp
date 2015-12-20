//
// Created by up201403057 on 29-10-2015.
//

#include "ConfigFile.h"
#include <fstream>

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

Client ClientsFile::createClientObject(istream &in, string name, vector<string> licensePlates,
                                       AutoRepairShop &repairShop) {
    Client newClient(in, name, licensePlates);
    for (size_t i = 0; i < licensePlates.size(); i++) {
        newClient.addVehicle(repairShop.vehicleWithLicensePlate(licensePlates[i]));
    }
    return newClient;
}

Employee EmployeesFile::createEmployeeObject(istream &in, string name, vector<string> licensePlates,
                                             AutoRepairShop &repairShop) {
    Employee newEmployee(in, name, licensePlates);
    for (size_t i = 0; i < licensePlates.size(); i++) {
        newEmployee.addVehicle(repairShop.vehicleWithLicensePlate(licensePlates[i]));
    }
    return newEmployee;
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

bool EmployeesFile::saveData(AutoRepairShop &repairShop, bool overwrite) {
    if (!overwrite && existsFile(filename))
        return false;
    ofstream out;
    out.open(this->filename);
    writeVector(repairShop.getEmployees(), out);
    out.close();
    return true;
}

bool AutoRepairShopFile::saveData(AutoRepairShop &repairShop, string &vehiclesFilename, string &clientsFilename,
                                  string &employeesFileName, bool overwrite) {
    if (!overwrite && existsFile(filename))
        return false;
    ofstream out;
    out.open(this->filename);
    out << vehiclesFilename << endl << clientsFilename << endl << employeesFileName << endl << repairShop.getName();
    out.close();
    VehiclesFile vf(vehiclesFilename);
    ClientsFile cf(clientsFilename);
    EmployeesFile ef(employeesFileName);
    for (size_t i = 0; i < repairShop.getVehicles().size(); i++) {
        repairShop.assignEmployee(repairShop.getVehicles()[i]);
    }
    return (vf.saveData(repairShop, overwrite) && cf.saveData(repairShop, overwrite) &&
            ef.saveData(repairShop, overwrite));
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
    vector<string> licensePlates;
    if (!existsFile(this->filename))
        return false;
    in.open(this->filename);
    while (getline(in, name)) {
        Client c = createClientObject(in, name, licensePlates, repairShop);
        repairShop.addClient(&c);
    }
    return true;
}

bool EmployeesFile::loadData(AutoRepairShop &repairShop) {
    ifstream in;
    string name;
    vector<string> licensePlates;
    if (!existsFile(this->filename))
        return false;
    in.open(this->filename);
    while (getline(in, name)) {
        Employee e = createEmployeeObject(in, name, licensePlates, repairShop);
        repairShop.addEmployee(&e);
    }
    return true;
}

AutoRepairShop AutoRepairShopFile::loadData() {
    ifstream in;
    string vehiclesFilename = "", clientsFilename = "", employeesFilename = "", repairShopName = "";
    if (!existsFile(this->filename))
        throw (InexistentFileException(this->filename));
    in.open(this->filename);
    getline(in, vehiclesFilename);
    getline(in, clientsFilename);
    getline(in, employeesFilename);
    getline(in, repairShopName);
    in.close();
    if (vehiclesFilename == "" || clientsFilename == "" || employeesFilename == "" || repairShopName == "")
        throw (BadFileException(this->filename));
    VehiclesFile vf(vehiclesFilename);
    ClientsFile cf(clientsFilename);
    EmployeesFile ef(employeesFilename);
    AutoRepairShop repairShop(repairShopName);
    vf.loadData(repairShop);
    cf.loadData(repairShop);
    ef.loadData(repairShop);
    return repairShop;
}
