//
// Created by Andre on 17/10/2015.
//

#include "AutoRepairShop.h"
#include "Utilities.h"

bool AutoRepairShop::addClient(Client client) {
    if(isClient(client)) //TODO IMPLEMENT WITH addsIfNotExist()
        return false;
    clients.push_back(client);
    clients[clients.size()-1].setClientID(clients.size()-1);
    return true;
}

bool AutoRepairShop::addEmployee(Employee employee) {
    if(isEmployee(employee)) //TODO IMPLEMENT WITH addsIfNotExist()
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

bool AutoRepairShop::isClient(Client client1) {
    return exists(client1, clients);
}

bool AutoRepairShop::isEmployee(Employee employee1){
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

bool AutoRepairShop::addVehicle(Vehicle *vehicle) {
    return addsIfNotExist(vehicle, this->vehicles);
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
}

Client::Client(istream &in, vector<string>& licensePlates) : Person(in, licensePlates) {
    in >> clientID;
}

Employee::Employee(istream &in, vector<string> &licensePlates) : Person(in, licensePlates) {
    in >> employeeID;
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
