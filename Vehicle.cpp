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
}
