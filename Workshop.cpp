//
// Created by Andre on 17/10/2015.
//

#include "Workshop.h"
#include "Utilities.h"

bool Workshop::addClient(Client client) {
    if(isClient(client))
        return false;
    clients.push_back(client);
    clients[clients.size()-1].setClientID(clients.size()-1);
    return true;
}

bool Workshop::addEmployee(Employee employee) {
    if(isEmployee(employee))
        return false;
    employees.push_back(employee);
    employees[employees.size()-1].setEmployeeID(employees.size()-1);
    return true;
}

void Client::setClientID(int clientID) {
    this->clientID = clientID;
}

int Client::getClientID() const {
    return clientID;
}

Client::Client(string name) : Person(name) {
    this->clientID = -1;
}

bool Workshop::isClient(Client client1) {
    return exists(client1, clients);
}

bool Workshop::isEmployee(Employee employee1){
    return exists(employee1, employees);
}

Employee::Employee(string name) : Person(name) {
    this->employeeID = -1;
}

int Employee::getEmployeeID() const {
    return this->employeeID;
}

void Employee::setEmployeeID(int employeeID) {
    this->employeeID = employeeID;
}

bool Workshop::addVehicle(Vehicle *vehicle) {
    if(exists(vehicle, vehicles))
        return false;
    vehicles.push_back(vehicle);
    return true;
}

Person::Person(string name) {
    this->name = name;
}

void Person::saveObjectInfo(ostream& out) {
    out << this->name << endl;
    for(size_t i = 0; i < vehicles.size(); i++){
        out << vehicles[i]->getLicensePlate() << endl;
    }
}

void Client::saveObjectInfo(ostream &out) {
    Person::saveObjectInfo(out);
    out << this->clientID;
}

void Employee::saveObjectInfo(ostream &out) {
    Person::saveObjectInfo(out);
    out << this->employeeID;
}
