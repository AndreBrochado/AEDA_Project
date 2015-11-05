//
// Created by Andre on 17/10/2015.
//

#ifndef AEDA_PROJECT_WORKSHOP_H
#define AEDA_PROJECT_WORKSHOP_H

#include <iostream>
#include <vector>

#include "Vehicle.h"

using namespace std;

class Person {
    string name;
    vector<Vehicle*> vehicles;
public:
    Person(string name);
    Person(istream& in, vector<string>& licensePlates);
    virtual void saveObjectInfo(ostream& out);
};

class Client : public Person {
    string name;
    int clientID;
    vector<Vehicle *> vehicles;
public:
    Client(string name);
    Client(istream& in, vector<string>& licensePlates);
    bool addVehicle(Vehicle* vehicle); //bool needed?
    int getClientID() const;
    void setClientID(int clientID);
    void saveObjectInfo(ostream& out);
};

class Employee : public Person {
    string name;
    int employeeID;
    vector<Vehicle *> vehicles;
public:
    Employee(string name);
    Employee(istream& in, vector<string>& licensePlates);
    bool assignVehicle(Vehicle* vehicle); //bool needed ?
    int getEmployeeID() const;
    void setEmployeeID(int employeeID);
    void saveObjectInfo(ostream& out);
};

class AutoRepairShop {
    string name;
    vector<Vehicle *> vehicles;
    vector<Employee> employees;
    vector<Client> clients;
public:
    AutoRepairShop(string name);
    bool isClient(Client client1);
    bool isEmployee(Employee employee1);
    bool addClient(Client client); //bool needed ?
    bool addEmployee(Employee employee); //bool needed ?
    bool addVehicle(Vehicle* vehicle); //bool needed ?
    const string& getName() const;
};



class Service {
    string description;
    float price;
    time_t startingDate;
    int duration;
public:
    Service(int day, int month, int year);
    virtual float getPrice() const = 0;
};

class Standard : Service {
public:
    Standard(int day, int month, int year) : Service(day, month, year) {};
};

class NonStandard : Service {
    NonStandard(int day, int month, int year, string description ,float price, int duration);
};

#endif //AEDA_PROJECT_WORKSHOP_H
