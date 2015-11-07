//
// Created by Andre on 17/10/2015.
//

#ifndef AEDA_PROJECT_VEHICLE_H
#define AEDA_PROJECT_VEHICLE_H

#include <iostream>
#include "Service.h"

using namespace std;

class Vehicle {
    string manufacturer, model, licensePlate;
    vector<Service*> services;
public:
    Vehicle(string manufacturer, string model, string licensePlate); //add relevant parameters
    Vehicle(istream& in);
    virtual int classIdentifier() {return 0;};
    virtual void saveObjectInfo(ostream& out);
    bool addService(Service* s1);
    const string& getLicensePlate() const{return licensePlate;};
    const string& getManufacturer() const { return manufacturer;};
};

class Automobile : public Vehicle {
    int numDoors;
public:
    Automobile(string manufacturer, string model, string licensePlate, int numDoors); //add relevant parameters
    Automobile(istream& in);
    int classIdentifier() {return 1;};
    void saveObjectInfo(ostream& out);
    };

class Motorcycle : public Vehicle {
    string type;
public:
    Motorcycle(string manufacturer, string model, string licensePlate, string type); //add relevant parameters
    Motorcycle(istream& in);
    int classIdentifier() {return 2;};
    void saveObjectInfo(ostream& out);
    };

class Truck : public Vehicle {
    int maxWeight;
public:
    Truck(string manufacturer, string model, string licensePlate, int maxWeight); //add relevant parameters
    Truck(istream& in);
    int classIdentifier() {return 3;};
    void saveObjectInfo(ostream& out);
    };

class Bus : public Vehicle {
    int numSittingSpots, numStandingSpots;
public:
    Bus(string manufacturer, string model, string licensePlate, int numSittingSpots, int numStandingSpots); //add relevant parameters
    Bus(istream& in);
    int classIdentifier() {return 3;};
    void saveObjectInfo(ostream& out);
    };

Vehicle* createVehicleObject(istream &in, int classIdentifier);

#endif //AEDA_PROJECT_VEHICLE_H
