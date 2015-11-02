//
// Created by Andre on 17/10/2015.
//

#include <stdlib.h>
#include "AutoRepairShop.h"
#include "Utilities.h"

bool AutoRepairShop::addClient(Client client) {
    if(isClient(client)) //TODO IMPLEMENT WITH addsIfNotExist()
        return false;
    clients.push_back(client);
    clients[clients.size()-1].setID(clients.size()-1);
    return true;
}

bool AutoRepairShop::addEmployee(Employee employee) {
    if(isEmployee(employee)) //TODO IMPLEMENT WITH addsIfNotExist()
        return false;
    employees.push_back(employee);
    employees[employees.size()-1].setID(employees.size()-1);
    return true;
}

bool AutoRepairShop::isClient(Client client1) {
    return exists(client1, clients);
}

bool AutoRepairShop::isEmployee(Employee employee1){
    return exists(employee1, employees);
}

bool AutoRepairShop::addVehicle(Vehicle *vehicle) {
    return addsIfNotExist(vehicle, this->vehicles);
}

Person::Person(string name) {
    this->name = name;
    this->id = -1;
}

void Person::saveObjectInfo(ostream& out) {
    out << this->name << endl;
    for(size_t i = 0; i < vehicles.size(); i++){
        out << vehicles[i]->getLicensePlate() << endl;
    }
    out << this->id;
}

void Client::saveObjectInfo(ostream &out) {
    Person::saveObjectInfo(out);
}

void Employee::saveObjectInfo(ostream &out) {
    Person::saveObjectInfo(out);
}

Person::Person(istream &in, vector<string>& licensePlates) {
    in >> this->name;
    string testString = "-";
    in >> testString;
    while(testString.find('-') != string::npos){
        if(testString == "-"){
            exception e; //TODO specify
            throw(e);
        }
        licensePlates.push_back(testString);
    }
    this->id = atoi(testString.c_str());
}

bool Client::addVehicle(Vehicle *vehicle) {
    return addsIfNotExist(vehicle, this->vehicles);
}

bool Employee::assignVehicle(Vehicle *vehicle) {
    return addsIfNotExist(vehicle, this->vehicles);
}

AutoRepairShop::AutoRepairShop(string name) {
    this->name = name;
}

const string &AutoRepairShop::getName() const {
    return this->name;
}

Vehicle *Person::vehicleWithLicensePlate(string licensePlate) {
    for(size_t i = 0; i < vehicles.size(); i++){
        if(vehicles[i]->getLicensePlate() == licensePlate)
            return vehicles[i];
    }
    throw(InexistentVehicle(licensePlate));
}
