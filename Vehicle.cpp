//
// Created by Andre on 17/10/2015.
//

#include "Vehicle.h"

Vehicle::Vehicle(string manufacturer, string model, string licensePlate, string color) {
    this->manufacturer = manufacturer;
    this->model = model;
    this->licensePlate = licensePlate;
    this->color = color;
}

Automobile::Automobile(string manufacturer, string model, string licensePlate, string color, int numDoors)
        : Vehicle(manufacturer, model, licensePlate, color) {
    this->numDoors = numDoors;
}

Motorcycle::Motorcycle(string manufacturer, string model, string licensePlate, string color, string type)
        : Vehicle(manufacturer, model, licensePlate, color) {
    this->type = type;
}

Truck::Truck(string manufacturer, string model, string licensePlate, string color, int maxWeight)
        : Vehicle(manufacturer, model, licensePlate, color) {
    this->maxWeight = maxWeight;
}

Bus::Bus(string manufacturer, string model, string licensePlate, string color, int numSitttingSpots,
         int numStandingSpots)
        : Vehicle(manufacturer, model, licensePlate, color) {
    this->numSittingSpots = numSitttingSpots;
    this->numStandingSpots = numStandingSpots;
}

bool Vehicle::setColor(string color) {
    this->color = color;
    return true;
}

void Vehicle::saveObjectInfo(ostream &out) {
    out << this->classIdentifier() << endl
    << this->manufacturer << " " << this->model << endl
    << this->licensePlate << endl << this->color;
}


void Automobile::saveObjectInfo(ostream &out) {
    Vehicle::saveObjectInfo(out);
    out << endl << this->numDoors;
}

void Motorcycle::saveObjectInfo(ostream &out) {
    Vehicle::saveObjectInfo(out);
    out << endl << this->type;
}

void Truck::saveObjectInfo(ostream &out) {
    Vehicle::saveObjectInfo(out);
    out << endl << this->maxWeight;
}

void Bus::saveObjectInfo(ostream &out) {
    Vehicle::saveObjectInfo(out);
    out << endl << this->numSittingSpots << " " << this->numStandingSpots;
}

Vehicle::Vehicle(istream& in) {
    in >> this->manufacturer >> this->model >> this->licensePlate >> this->color;
}

Automobile::Automobile(istream &in) : Vehicle(in) {
    in >> this->numDoors;
}

Motorcycle::Motorcycle(istream &in) : Vehicle(in) {
    in >> this->type;
}

Truck::Truck(istream &in) : Vehicle(in) {
    in >> this->maxWeight;
}

Bus::Bus(istream &in) : Vehicle(in) {
    in >> this->numSittingSpots >> this->numStandingSpots;
}

const string &Vehicle::getLicensePlate() const {
        return licensePlate;
}
