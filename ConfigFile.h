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
    class FileException{
    protected:
        string filename;
    public:
        FileException(string &filename){this->filename = filename;};
        const string& getFilename() const {return this->filename;};
        virtual void showErrorMessage() const = 0;
    };
    class BadFileException : public FileException{
    public:
        BadFileException(string &filename) : FileException(filename){};
        void showErrorMessage() const{cout<<"File "<<filename<<" doesn't have the correct format.";};
    };
    class InexistentFileException : public FileException{
    public:
        InexistentFileException(string &filename) : FileException{filename}{};
        void showErrorMessage() const{cout<<"File "<<filename<<" doesn't exist.";};
    };
};

class AutoRepairShopFile : public ConfigFile {
public:
    AutoRepairShopFile(string &filename) : ConfigFile(filename) { }
    bool saveData(AutoRepairShop &repairShop, string &vehiclesFilename, string &clientsFilename, string &employeesFileName, bool overwrite=false);
    AutoRepairShop loadData();
};

class VehiclesFile : public ConfigFile {
public:
    VehiclesFile(string &filename) : ConfigFile(filename) { }
    bool saveData(AutoRepairShop &repairShop, bool overwrite=false);
    bool loadData(AutoRepairShop &repairShop);
};

class ClientsFile : public ConfigFile {
public:
    ClientsFile(string &filename) : ConfigFile(filename) { }
    Client createClientObject(istream &in, vector<string> licensePlates, AutoRepairShop &repairShop);
    bool saveData(AutoRepairShop &repairShop, bool overwrite=false);
    bool loadData(AutoRepairShop &repairShop);
};

class EmployeesFile : public ConfigFile {
public:
    EmployeesFile(string &filename) : ConfigFile(filename) { }
    Employee createEmployeeObject(istream &in, vector<string> licensePlates, AutoRepairShop &repairShop);
    bool saveData(AutoRepairShop &repairShop, bool overwrite=false);
    bool loadData(AutoRepairShop &repairShop);
};


#endif //AEDA_PROJECT_CONFIGFILE_H
