//
// Created by Andre on 17/10/2015.
//

#ifndef AEDA_PROJECT_WORKSHOP_H
#define AEDA_PROJECT_WORKSHOP_H

#include <iostream>
#include <vector>

#include "Vehicle.h"

using namespace std;

class Person {
protected:
    string name;
    vector<Vehicle*> vehicles;
    int id;
public:
    Person(string name);
    Person(istream& in, vector<string>& licensePlates);
    virtual void saveObjectInfo(ostream& out);
    Vehicle* vehicleWithLicensePlate(string licensePlate);

    void setID(int id){this->id = id;};
    int getID() const{return id;};
    class InexistentVehicle{
        string licensePlate;
    public:
        InexistentVehicle(string licensePlate) : licensePlate(licensePlate){};
        const string& getLicensePlate(){return licensePlate;};
    };
};

class Client : public Person {
public:
    Client(string name) : Person(name){};
    Client(istream& in, vector<string>& licensePlates) : Person(in, licensePlates){};
    bool addVehicle(Vehicle* vehicle); //bool needed?
    //int getID() const;
   // void setID(int id);
    void saveObjectInfo(ostream& out);
};

class Employee : public Person {
public:
    Employee(string name) : Person(name){};
    Employee(istream& in, vector<string>& licensePlates) : Person(in, licensePlates){};
    bool assignVehicle(Vehicle* vehicle); //bool needed ?
   // int getID() const;
  //  void setID(int id);
    void saveObjectInfo(ostream& out);
};

class AutoRepairShop {
    string name;
    vector<Vehicle *> vehicles;
    vector<Employee> employees;
    vector<Client> clients;
public:
    AutoRepairShop(string name);
    bool isClient(Client client1);
    bool isEmployee(Employee employee1);
    bool addClient(Client client); //bool needed ?
    bool addEmployee(Employee employee); //bool needed ?
    bool addVehicle(Vehicle* vehicle); //bool needed ?
    const string& getName() const;
};



class Service {

};

class Standard : Service {

};

class NonStandard : Service {

};

#endif //AEDA_PROJECT_WORKSHOP_H
