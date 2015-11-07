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
    class BadFileException{
        string filename;
    public:
        BadFileException(string &filename){this->filename = filename;};
        const string& getFilename() const {return this->filename;};
    };
    class InexistentFileException{
        string filename;
    public:
        InexistentFileException(string &filename){this->filename = filename;};
        const string& getFilename() const {return this->filename;};
    };
};

class AutoRepairShopFile : ConfigFile {
public:
    AutoRepairShopFile(string &filename) : ConfigFile(filename) { }
    bool saveData(AutoRepairShop &repairShop, string &vehiclesFilename, string &clientsFilename, string &employeesFileName, bool overwrite=false);
    AutoRepairShop loadData();
};

class VehiclesFile : ConfigFile {
public:
    VehiclesFile(string &filename) : ConfigFile(filename) { }
    bool saveData(AutoRepairShop &repairShop, bool overwrite=false);
    bool loadData(AutoRepairShop &repairShop);
};

class ClientsFile : ConfigFile {
public:
    ClientsFile(string &filename) : ConfigFile(filename) { }
    Client createClientObject(istream &in, vector<string> licensePlates, AutoRepairShop &repairShop);
    bool saveData(AutoRepairShop &repairShop, bool overwrite=false);
    bool loadData(AutoRepairShop &repairShop);
};

class EmployeesFile : ConfigFile {
public:
    EmployeesFile(string &filename) : ConfigFile(filename) { }
    Employee createEmployeeObject(istream &in, vector<string> licensePlates, AutoRepairShop &repairShop);
    bool saveData(AutoRepairShop &repairShop, bool overwrite=false);
    bool loadData(AutoRepairShop &repairShop);
};


#endif //AEDA_PROJECT_CONFIGFILE_H
