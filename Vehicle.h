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
    Vehicle(istream& in);
    virtual bool setColor(string color); //bool needed?
    virtual int classIdentifier() {return 0;};
    virtual void saveObjectInfo(ostream& out);
    const string& getLicensePlate() const;
};

class Automobile : Vehicle {
    int numDoors;
public:
    Automobile(string manufacturer, string model, string licensePlate, string color, int numDoors); //add relevant parameters
    Automobile(istream& in);
    int classIdentifier() {return 1;};
    void saveObjectInfo(ostream& out);
    };

class Motorcycle : Vehicle {
    string type;
public:
    Motorcycle(string manufacturer, string model, string licensePlate, string color, string type); //add relevant parameters
    Motorcycle(istream& in);
    int classIdentifier() {return 2;};
    void saveObjectInfo(ostream& out);
    };

class Truck : Vehicle {
    int maxWeight;
public:
    Truck(string manufacturer, string model, string licensePlate, string color, int maxWeight); //add relevant parameters
    Truck(istream& in);
    int classIdentifier() {return 3;};
    void saveObjectInfo(ostream& out);
    };

class Bus : Vehicle {
    int numSittingSpots, numStandingSpots;
public:
    Bus(string manufacturer, string model, string licensePlate, string color, int numSittingSpots, int numStandingSpots); //add relevant parameters
    Bus(istream& in);
    int classIdentifier() {return 3;};
    void saveObjectInfo(ostream& out);
    };

#endif //AEDA_PROJECT_VEHICLE_H
