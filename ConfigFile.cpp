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

bool ConfigFile::existsFile(string &filename) {
    ifstream inputStream;
    bool result = false;

    inputStream.open(filename);
    result = inputStream.is_open();
    inputStream.close();
    return result;
}

bool VehiclesFile::saveData(AutoRepairShop &repairShop, bool overwrite) {
    if(!overwrite && existsFile(filename))
        return false;
    ofstream out;
    out.open(this->filename);
    for(size_t i = 0; i < repairShop.getVehicles().size(); i++){
        repairShop.getVehicles()[i]->saveObjectInfo(out);
        if(i != repairShop.getVehicles().size()-1)
            out<<endl;
    }
    out.close();
    return true;
}

bool ClientsFile::saveData(AutoRepairShop &repairShop, bool overwrite) {
    if(!overwrite && existsFile(filename))
        return false;
    ofstream out;
    out.open(this->filename);
    writeVector(repairShop.getClients(), out);
    out.close();
    return true;
}

bool EmployeesFile::saveData(AutoRepairShop &repairShop, bool overwrite) {
    if(!overwrite && existsFile(filename))
        return false;
    ofstream out;
    out.open(this->filename);
    writeVector(repairShop.getEmployees(), out);
    out.close();
    return true;
}

bool AutoRepairShopFile::saveData(AutoRepairShop &repairShop, string &vehiclesFilename, string &clientsFilename,
                                  string &employeesFileName, bool overwrite) {
    if(!overwrite && existsFile(filename))
        return false;
    ofstream out;
    out.open(this->filename);
    out<<vehiclesFilename << endl << clientsFilename << endl << employeesFileName;
    out.close();
    return true;
}
