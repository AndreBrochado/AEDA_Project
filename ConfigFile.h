//
// Created by up201403057 on 29-10-2015.
//

#ifndef AEDA_PROJECT_CONFIGFILE_H
#define AEDA_PROJECT_CONFIGFILE_H

#include "AutoRepairShop.h"

/**
 * @class ConfigFile
 * @brief superclass to all types of file
 * Keeps their common behaviour
 */
class ConfigFile {
protected:
    string filename;
public:
    /**
     * @brief creates a ConfigFile object
     */
    ConfigFile(string &filename);

    /**
     * @brief creates a file with given filename
     */
    void createFile(string &filename);

    /**
     * @returns true if a file with the given filename exists
     * @returns false if it doesn't exist
     */
    bool existsFile(string &filename);

    /**
     * @exception FileException superclass has the common behaviour of File-related exceptions
     */
    class FileException {
    protected:
        string filename;
    public:
        FileException(string &filename) { this->filename = filename; };

        const string &getFilename() const { return this->filename; };

        virtual void showErrorMessage() const = 0;
    };

    /**
     * @exception BadFileException exception to throw when the file has the wrong format
     */
    class BadFileException : public FileException {
    public:
        BadFileException(string &filename) : FileException(filename) { };

        void showErrorMessage() const { cout << filename << " doesn't have the correct format."; };
    };

    /**
     * @exception InexistentFileException exception to throw when the file doesn't exists
     */
    class InexistentFileException : public FileException {
    public:
        InexistentFileException(string &filename) : FileException{filename} { };

        void showErrorMessage() const { cout << "File " << filename << " doesn't exist."; };
    };

    /**
     * @exception InexistentFileException exception to throw when the file doesn't exists
     */
    class EmptyFileException {
    public:
        EmptyFileException() { };
    };
};

/**
 * @class AutoRepairShopFile
 * @brief contains the name of the vehiclesfile, clientsfile and employeesfile and the name of the Auto Repair Shop
 */
class AutoRepairShopFile : public ConfigFile {
public:
    AutoRepairShopFile(string &filename) : ConfigFile(filename) { }

    /**
     * @brief saves the file data
     */
    bool saveData(AutoRepairShop &repairShop, string &vehiclesFilename, string &clientsFilename,
                  string &employeesFileName, bool overwrite = false);

    /**
     * @brief loads data from the file, creating an AutoRepairShop
     */
    AutoRepairShop loadData();
};

/**
 * @class VehiclesFile
 * @brief contains the info of all the vehicles on the Auto Repair Shop
 */
class VehiclesFile : public ConfigFile {
public:
    VehiclesFile(string &filename) : ConfigFile(filename) { }

    /**
     * @brief saves the file data
     */
    bool saveData(AutoRepairShop &repairShop, bool overwrite = false);

    /**
     * @brief loads data from the file
     * @returns false if the file doesn't exist
     */
    bool loadData(AutoRepairShop &repairShop);
};

/**
 * @class ClientsFile
 * @brief contains the info of all the clients of the Auto Repair Shop
 */
class ClientsFile : public ConfigFile {
public:
    ClientsFile(string &filename) : ConfigFile(filename) { }

    /**
     * @brief creates and returns a client, adding all vehicles with license plates on the licensePlates vector
     */
    Client createClientObject(istream &in, string name, AutoRepairShop &repairShop);

    /**
     * @brief saves the file data
     */
    bool saveData(AutoRepairShop &repairShop, bool overwrite = false);

    /**
     * @brief loads data from the file
     * @returns false if the file doesn't exist
     */
    bool loadData(AutoRepairShop &repairShop);
};

/**
 * @class ClientsFile
 * @brief contains the info of all the Auto Repair Shop's employees
 */
class EmployeesFile : public ConfigFile {
public:
    EmployeesFile(string &filename) : ConfigFile(filename) { }

    /**
     * @brief creates and returns an employee, adding all vehicles with license plates on the licensePlates vector
     */
    Employee createEmployeeObject(istream &in, string name, AutoRepairShop &repairShop);

    /**
     * @brief saves the file data
     */
    bool saveData(AutoRepairShop &repairShop, bool overwrite = false);

    /**
     * @brief loads data from the file
     * @returns false if the file doesn't exist
     */
    bool loadData(AutoRepairShop &repairShop);
};

/**
 * @class ServicesFile
 * @brief contains the info of all the Auto Repair Shop's services
 */
class ServicesFile : public ConfigFile {
public:
    ServicesFile(string &filename) : ConfigFile(filename) { }

    /**
     * @brief creates and returns a service
     */
    Service* createServiceObject(istream &in, AutoRepairShop &repairShop);

    /**
    * @brief saves the file data
    */
    bool saveData(AutoRepairShop &repairShop, bool overwrite = false);

    /**
    * @brief loads data from the file
    * @returns false if the file doesn't exist
    */
    bool loadData(AutoRepairShop &repairShop);

};


#endif //AEDA_PROJECT_CONFIGFILE_H
