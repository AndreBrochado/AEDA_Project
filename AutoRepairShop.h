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
    vector<Vehicle*> vehicles;
    int id;
public:
    Person(string name);
    Person(istream& in, vector<string>& licensePlates);
    void saveObjectInfo(ostream& out);
    virtual void printObjectInfo();
    bool addVehicle(Vehicle* vehicle);
    bool removeVehicle(Vehicle* vehicle);

    void setID(int id){this->id = id;};
    int getID() const{return id;};
    string getName() const{return name;};
    vector<Vehicle*> getVehicles() const{return vehicles;};
};

class Client : public Person {
public:
    Client(string name) : Person(name){};
    Client(istream& in, vector<string>& licensePlates) : Person(in, licensePlates){};
    void printObjectInfo();
    void printServices();
};

class Employee : public Person {
public:
    Employee(string name) : Person(name){};
    Employee(istream& in, vector<string>& licensePlates) : Person(in, licensePlates){};
    void printObjectInfo();
};

class AutoRepairShop {
    string name;
    vector<Vehicle *> vehicles;
    vector<Employee> employees;
    vector<Client> clients;
public:
    AutoRepairShop(string name);
    Vehicle* vehicleWithLicensePlate(string licensePlate);
    bool isClient(Client client1);
    bool isEmployee(Employee employee1);
    bool addClient(Client client); //bool needed ?
    bool addEmployee(Employee employee); //bool needed ?
    bool addVehicle(Vehicle* vehicle); //bool needed ?
    bool assignEmployee(Vehicle *vehicle);
    bool removeVehicle(Vehicle *vehicle);
    bool removeEmployee(Employee employee);
    bool removeClient(Client client);
    const string& getName() const;
    void printVehiclesInfo();
    void printEmployeesInfo();
    void printClientsInfo();
    void printServices();
    void printClientsWithFirstLetter(char firstLetter);
    void printEmployeesWithFirstLetter(char firstLetter);
    void printAllInfo();
    vector<Vehicle *> getVehicles() const {return vehicles;};
    vector<Employee> getEmployees() const {return employees;};
    vector<Client> getClients() const {return clients;};
    class InexistentVehicle{
        string licensePlate;
    public:
        InexistentVehicle(string licensePlate) : licensePlate(licensePlate){};
        void showErrorMessage(){cout << "There isn't a vehicle with the license plate " << this->licensePlate;};
    };
};



#endif //AEDA_PROJECT_WORKSHOP_H
