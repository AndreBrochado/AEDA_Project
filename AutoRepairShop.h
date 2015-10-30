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
    virtual void saveObjectInfo(ostream& out);
};

class Client : public Person {
    string name;
    int clientID;
    vector<Vehicle *> vehicles;
public:
    Client(string name);
    bool addVehicle(Vehicle *v); //bool needed?
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
    bool assignVehicle(Vehicle *v); //bool needed ?
    int getEmployeeID() const;
    void setEmployeeID(int employeeID);
    void saveObjectInfo(ostream& out);
};

class AutoRepairShop {
    vector<Vehicle *> vehicles;
    vector<Employee> employees;
    vector<Client> clients;
public:
    AutoRepairShop(){};
    bool isClient(Client client1);
    bool isEmployee(Employee employee1);
    bool addClient(Client client); //bool needed ?
    bool addEmployee(Employee employee); //bool needed ?
    bool addVehicle(Vehicle* vehicle); //bool needed ?
};



class Service {

};

class Standard : Service {

};

class NonStandard : Service {

};

#endif //AEDA_PROJECT_WORKSHOP_H
