//
// Created by Andre on 17/10/2015.
//

#include <stdlib.h>
#include "Vehicle.h"

// ================================= VEHICLE ================================= //

Vehicle::Vehicle(string manufacturer, string model, string licensePlate) {
    this->manufacturer = manufacturer;
    this->model = model;
    this->licensePlate = licensePlate;
}

Vehicle::Vehicle(istream& in) {
    string testString = "";
    int classIdentifier = 0;
    in >> this->manufacturer >> this->model;
    in >> testString;
    while(testString.find("-") == string::npos){
        classIdentifier = atoi(testString.c_str());
        this->services.push_back(createServiceObject(in, classIdentifier));
        testString = "";
        in>>testString;
    }
    this->licensePlate = testString;
}

void Vehicle::saveObjectInfo(ostream &out) {
    out << this->classIdentifier() << endl
    << this->manufacturer << " " << this->model << endl;
    for(size_t i = 0; i < services.size(); i++){
        services[i]->saveObjectInfo(out);
        out<< endl;
    }
    out << this->licensePlate;
}

bool Vehicle::addService(Service *s1) {
    return addsIfNotExist(s1, services);
}

bool operator==(const Vehicle &v1, const Vehicle &v2){
    return v1.getLicensePlate() == v2.getLicensePlate();
}

// ================================= AUTOMOBILE ================================= //

Automobile::Automobile(string manufacturer, string model, string licensePlate, int numDoors)
        : Vehicle(manufacturer, model, licensePlate) {
    this->numDoors = numDoors;
}

Automobile::Automobile(istream &in) : Vehicle(in) {
    in >> this->numDoors;
}

void Automobile::saveObjectInfo(ostream &out) {
    Vehicle::saveObjectInfo(out);
    out << endl << this->numDoors;
}

// ================================= MOTORCYCLE ================================= //

Motorcycle::Motorcycle(string manufacturer, string model, string licensePlate, string type)
        : Vehicle(manufacturer, model, licensePlate) {
    this->type = type;
}

Motorcycle::Motorcycle(istream &in) : Vehicle(in) {
    in >> this->type;
}

void Motorcycle::saveObjectInfo(ostream &out) {
    Vehicle::saveObjectInfo(out);
    out << endl << this->type;
}

// ================================= TRUCK ================================= //

Truck::Truck(string manufacturer, string model, string licensePlate, int maxWeight)
        : Vehicle(manufacturer, model, licensePlate) {
    this->maxWeight = maxWeight;
}

Truck::Truck(istream &in) : Vehicle(in) {
    in >> this->maxWeight;
}

void Truck::saveObjectInfo(ostream &out) {
    Vehicle::saveObjectInfo(out);
    out << endl << this->maxWeight;
}

// ================================= BUS ================================= //

Bus::Bus(string manufacturer, string model, string licensePlate, int numSittingSpots,
         int numStandingSpots)
        : Vehicle(manufacturer, model, licensePlate) {
    this->numSittingSpots = numSittingSpots;
    this->numStandingSpots = numStandingSpots;
}

Bus::Bus(istream &in) : Vehicle(in) {
    in >> this->numSittingSpots >> this->numStandingSpots;
}

void Bus::saveObjectInfo(ostream &out) {
    Vehicle::saveObjectInfo(out);
    out << endl << this->numSittingSpots << " " << this->numStandingSpots;
}

Vehicle* createVehicleObject(istream& in, int classIdentifier){
    Vehicle* newVehicle;
    switch(classIdentifier){
        case 1:
            newVehicle = new Automobile(in);
            break;
        case 2:
            newVehicle = new Motorcycle(in);
            break;
        case 3:
            newVehicle = new Truck(in);
            break;
        case 4:
            newVehicle = new Bus(in);
            break;
        default:
            exception e; //TODO SPECIFY
            throw(e);
    }
    return newVehicle;
}