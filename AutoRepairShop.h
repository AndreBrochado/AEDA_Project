//
// Created by Andre on 17/10/2015.
//

#ifndef AEDA_PROJECT_WORKSHOP_H
#define AEDA_PROJECT_WORKSHOP_H

#include <iostream>
#include <vector>

#include "Vehicle.h"
#include "Utilities.h"

using namespace std;

class Vehicle;

class Person {
protected:
    string name;
    vector<Vehicle *> vehicles;
    int id;
public:
    Person(string name);

    Person(istream &in, string name, vector<string> &licensePlates);

    void saveObjectInfo(ostream &out);

    virtual void printObjectInfo() const;

    bool addVehicle(Vehicle *vehicle);

    bool removeVehicle(Vehicle *vehicle);

    void setID(int id) { this->id = id; };

    int getID() const { return id; };

    string getName() const { return name; };

    vector<Vehicle *> getVehicles() const { return vehicles; };
};

class Client : public Person {
public:
    Client(string name) : Person(name) { };

    Client(istream &in, string name, vector<string> &licensePlates) : Person(in, name, licensePlates) { };

    void printObjectInfo() const;

    void printServices() const;
};

class Employee : public Person {
public:
    Employee(string name) : Person(name) { };

    Employee(istream &in, string name, vector<string> &licensePlates) : Person(in, name, licensePlates) { };

    void printObjectInfo() const;
};

class AutoRepairShop {
    string name;
    vector<Vehicle *> vehicles;
    vector<Employee> employees;
    vector<Client> clients;
public:
    AutoRepairShop(string name);

    Vehicle *vehicleWithLicensePlate(string licensePlate);

    bool isClient(Client client1);

    bool isEmployee(Employee employee1);

    bool addClient(Client client);
    bool addEmployee(Employee employee);
    bool addVehicle(Vehicle *vehicle);
    bool addVehicleToClient(Vehicle *vehicle, int clientIndex);

    bool assignEmployee(Vehicle *vehicle);

    bool removeVehicle(Vehicle *vehicle);

    bool removeEmployee(Employee employee);

    bool removeClient(Client client);

    const string &getName() const;

    void printVehiclesInfo() const;

    void printEmployeesInfo() const;

    void printClientsInfo() const;

    void printServices() const;

    void printClientsWithFirstLetter(char firstLetter) const;

    void printEmployeesWithFirstLetter(char firstLetter) const;

    void printAllInfo() const;

    const vector<Vehicle *> &getVehicles() const { return vehicles; };

    const vector<Employee> &getEmployees() const { return employees; };

    const vector<Client> &getClients() const { return clients; };

    class InexistentVehicle {
        string licensePlate;
    public:
        InexistentVehicle(string licensePlate) : licensePlate(licensePlate) { };

        void showErrorMessage() { cout << "There isn't a vehicle with the license plate " << this->licensePlate; };
    };
};


#endif //AEDA_PROJECT_WORKSHOP_H
