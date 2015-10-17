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
    Workshop();
};

class Employee {
    string name;
    vector<Vehicle *> vehicles;
public:
    Employee(string name);

    bool assignVehicle(Vehicle *v); //bool needed ?
};

class Client {
    string name;
    vector<Vehicle *> vehicles;
public:
    Client(string name);

    bool addVehicle(Vehicle *v); //bool needed?
};

class Service {

};

class Standard : Service {

};

class NonStandard : Service {

};

#endif //AEDA_PROJECT_WORKSHOP_H
