//
// Created by Andre on 17/10/2015.
//

#ifndef AEDA_PROJECT_VEHICLE_H
#define AEDA_PROJECT_VEHICLE_H

#include <iostream>

using namespace std;

class Vehicle {
    string manufacturer, model, licensePlate;
public:
    Vehicle(string manufacturer, string model, string licensePlate); //add relevant parameters
};

class Automobile : Vehicle {
public:
    Automobile(string manufacturer, string model, string licensePlate); //add relevant parameters
};

class Motorcycle : Vehicle {
public:
    Motorcycle(string manufacturer, string model, string licensePlate); //add relevant parameters
};

class Truck : Vehicle {
public:
    Truck(string manufacturer, string model, string licensePlate); //add relevant parameters
};

class Bus : Vehicle {
public:
    Bus(string manufacturer, string model, string licensePlate); //add relevant parameters
};

#endif //AEDA_PROJECT_VEHICLE_H
