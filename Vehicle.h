//
// Created by Andre on 17/10/2015.
//

#ifndef AEDA_PROJECT_VEHICLE_H
#define AEDA_PROJECT_VEHICLE_H

#include <iostream>

using namespace std;

class Vehicle {
    string manufacturer, model, licensePlate, color;
public:
    Vehicle(string manufacturer, string model, string licensePlate, string color); //add relevant parameters
    virtual bool setColor(string color); //bool needed?
};

class Automobile : Vehicle {
    int numDoors;
public:
    Automobile(string manufacturer, string model, string licensePlate, string color, int numDoors); //add relevant parameters
};

class Motorcycle : Vehicle {
    string type;
public:
    Motorcycle(string manufacturer, string model, string licensePlate, string color, string type); //add relevant parameters
};

class Truck : Vehicle {
    int maxWeight;
public:
    Truck(string manufacturer, string model, string licensePlate, string color, int maxWeight); //add relevant parameters
};

class Bus : Vehicle {
    int numSittingSpots, numStandingSpots;
public:
    Bus(string manufacturer, string model, string licensePlate, string color, int numSitttingSpots, int numStandingSpots); //add relevant parameters
};

#endif //AEDA_PROJECT_VEHICLE_H
