//
// Created by up201403057 on 29-10-2015.
//

#ifndef AEDA_PROJECT_CONFIGFILE_H
#define AEDA_PROJECT_CONFIGFILE_H

#include "AutoRepairShop.h"


class ConfigFile {
protected:
    string filename;
public:
    ConfigFile(string &filename);
    void createFile(string &filename);
    bool existsFile(string &filename);

};

class AutoRepairShopFile : ConfigFile {
public:
    AutoRepairShopFile(string &filename) : ConfigFile(filename) { }
    bool saveData(AutoRepairShop &repairShop, string &vehiclesFilename, string &clientsFilename, string &employeesFileName, bool overwrite);
};

class VehiclesFile : ConfigFile {
public:
    VehiclesFile(string &filename) : ConfigFile(filename) { }
    bool saveData(AutoRepairShop &repairShop, bool overwrite);
};

class ClientsFile : ConfigFile {
public:
    ClientsFile(string &filename) : ConfigFile(filename) { }
    bool saveData(AutoRepairShop &repairShop, bool overwrite);
};

class EmployeesFile : ConfigFile {
public:
    EmployeesFile(string &filename) : ConfigFile(filename) { }
    bool saveData(AutoRepairShop &repairShop, bool overwrite);
};



#endif //AEDA_PROJECT_CONFIGFILE_H
