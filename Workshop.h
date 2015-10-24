//
// Created by Andre on 17/10/2015.
//

#ifndef AEDA_PROJECT_WORKSHOP_H
#define AEDA_PROJECT_WORKSHOP_H

#include <iostream>
#include <vector>

#include "Vehicle.h"

using namespace std;

class Workshop {
    vector<Vehicle *> vehicles;
    vector<Employee> employees;
    vector<Client> clients;
public:
    Workshop(){};
    bool isClient(Client client1);
    bool isEmployee(Employee employee1);
    bool addClient(Client client); //bool needed ?
    bool addEmployee(Employee employee); //bool needed ?
    bool addVehicle(Vehicle* vehicle); //bool needed ?
};

class Employee {
    string name;
    int employeeID;
    vector<Vehicle *> vehicles;
public:
    Employee(string name);
    bool assignVehicle(Vehicle *v); //bool needed ?
    int getEmployeeID() const;
    void setEmployeeID(int employeeID);
};

class Client {
    string name;
    int clientID;
    vector<Vehicle *> vehicles;
public:
    Client(string name);
    bool addVehicle(Vehicle *v); //bool needed?
    int getClientID() const;
    void setClientID(int clientID);
};

class Service {

};

class Standard : Service {

};

class NonStandard : Service {

};

#endif //AEDA_PROJECT_WORKSHOP_H
