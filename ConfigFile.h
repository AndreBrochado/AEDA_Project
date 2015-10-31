//
// Created by up201403057 on 29-10-2015.
//

#ifndef AEDA_PROJECT_CONFIGFILE_H
#define AEDA_PROJECT_CONFIGFILE_H

#include "AutoRepairShop.h"


class ConfigFile {
    const string filename;
public:
    ConfigFile(const string &filename);
};

class VehiclesFile : ConfigFile {
public:
    VehiclesFile(const string &filename) : ConfigFile(filename) { }
};

class ClientsFile : ConfigFile {
public:
    ClientsFile(const string &filename) : ConfigFile(filename) { }
};

class EmployeesFile : ConfigFile {
public:
    EmployeesFile(const string &filename) : ConfigFile(filename) { }
};



#endif //AEDA_PROJECT_CONFIGFILE_H
