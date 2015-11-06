//
// Created by Andre on 17/10/2015.
//

#include "Vehicle.h"

// ================================= VEHICLE ================================= //

Vehicle::Vehicle(string manufacturer, string model, string licensePlate) {
    this->manufacturer = manufacturer;
    this->model = model;
    this->licensePlate = licensePlate;
}

Vehicle::Vehicle(istream& in) {
    in >> this->manufacturer >> this->model >> this->licensePlate;
}

void Vehicle::saveObjectInfo(ostream &out) {
    out << this->classIdentifier() << endl
    << this->manufacturer << " " << this->model << endl
    << this->licensePlate;
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