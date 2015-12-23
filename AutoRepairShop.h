#ifndef AEDA_PROJECT_WORKSHOP_H
#define AEDA_PROJECT_WORKSHOP_H

#include <iostream>
#include <vector>
#include <unordered_set>

#include "BST.h"
#include "Vehicle.h"
#include "Service.h"
#include "Utilities.h"
#include "PointCard.h"

using namespace std;

class Vehicle;

class Service;

class PointCard;

/**
 *@class Person
 *@brief Superclass to Employee and Client
 */
class Person {
protected:
    string name;
    vector<Vehicle *> vehicles;
    int id;
public:
    /**
     * @brief creates an object of Person class
     */
    Person(string name);

    /**
     * @brief reads an object of Person class from a stream
     * @param[out]  licensePlates   returns the license plates of all vehicles related to Person
     */
    Person(istream &in, string name, vector<string> &licensePlates);

    /**
     * @brief saves the objects' info to a stream
     */
    virtual void saveObjectInfo(ostream &out);

    /**
     * @brief prints the objects' info to std::cout
     */
    virtual void printObjectInfo() const;

    /**
     * @brief adds a vehicle to the person's vector of vehicles
     */
    bool addVehicle(Vehicle *vehicle);

    /**
     * @brief removes a vehicle from the person's vector of vehicles
     */
    bool removeVehicle(Vehicle *vehicle);

    /**
     * @brief sets the person ID to the given value
     */
    void setID(int id) { this->id = id; };

    /**
     * @returns the person's ID
     */
    int getID() const { return id; };

    /**
     * @returns the person's name
     */
    string getName() const { return name; };

    /**
     * @returns the person's vehicle vector
     */
    vector<Vehicle *> getVehicles() const { return vehicles; };
};

/**
 * @class Client
 * @brief subclass of Person, someone with cars on the Auto Repair Shop
 */
class Client : public Person {
    PointCard *clientCard;
    string address, email, phoneNumber;
public:
    /**
     * @brief creates an object of Client class
     */
    Client(string name, string address, string email, string phoneNumber) : Person(name), address(address), email(email), phoneNumber(phoneNumber) { clientCard = NULL; };

    /**
     * @brief reads an object of Client class from a stream
     * @param[out]  licensePlates   returns the license plates of all vehicles owned by Client
     */
    Client(istream &in, string name, vector<string> &licensePlates);

    void saveObjectInfo(ostream &out);

    bool isInactive();

    void createClientCard(tm date, float cost);

    void deleteClientCard();

    void updatePoints(tm data, float cost);

    void removePoints(int numPoints = 0);

    bool checkPointsExpiration();

    int getNumberOfServices();

    tm getLastServiceDate();

    PointCard *getClientCard() const { return clientCard; };

    void setAddress(string address){this->address=address;};

    void setEmail(string email){this->email = email;};

    void setPhoneNumber(string phoneNumber){this->phoneNumber = phoneNumber;};

/**
     * @brief prints the objects' info to std::cout
     */
    void printObjectInfo() const;

    /**
     * @brief prints to std::cout all services made on the client's car
     */
    void printServices() const;
};

/**
 * @class Employee
 * @brief subclass of Person, responsible by cars on the Auto Repair Shop
 */
class Employee : public Person {
public:
    /**
     * @brief creates an object of Employee class
     */
    Employee(string name) : Person(name) { };

    /**
    * @brief reads an object of Employee class from a stream
    * @param[out]  licensePlates   returns the license plates of all vehicles assigned to Employee
    */
    Employee(istream &in, string name, vector<string> &licensePlates) : Person(in, name, licensePlates) { };

    /**
     * @brief prints the objects' info to std::cout
     */
    void printObjectInfo() const;
};

struct clientHash {

    int operator()(const Client *c1) const {
        return c1->getID();
    }

    int operator()(const Client *c1, const Client *c2) const {
        return c1->getID() == c2->getID();
    }
};

/**
 * @class AutoRepairShop
 * @brief main class of the project, contains info of all vehicles, employees and clients on it
 */
class AutoRepairShop {
    static int nextClientID;
    string name;
    vector<Vehicle *> vehicles;
    vector<Employee *> employees;
    vector<Client *> clients;
    BST<Service *> scheduledServices;
    unordered_set<Client *, clientHash, clientHash> inactiveClients;
    priority_queue<PointCard> clientCards;
public:
    /**
     * @brief creates an object of AutoRepairShop class
     */
    AutoRepairShop(string name);

    /**
     * @returns true if client1 is on the clients vector, false otherwise
     */
    bool isClient(Client *client1);

    /**
     * @returns true if employee1 is on the employees vector, false otherwise
     */
    bool isEmployee(Employee *employee1);

    /**
     * @brief adds client to the clients vector if he wasn't there
     * @returns true if it adds the client to the vector, false otherwise
     */
    bool addClient(Client *client);

    /**
     * @brief adds employee to the employees vector if he wasn't there
     * @returns true if it adds the employee to the vector, false otherwise
     */
    bool addEmployee(Employee *employee);

    /**
     * @brief adds vehicle to the vehicles vector if it wasn't there
     * @returns true if it adds the vehicle to the vector, false otherwise
     */
    bool addVehicle(Vehicle *vehicle);

    /**
     * @brief adds vehicle to the vehicles vector of a client on the clients vector if it wasn't there
     * @returns true if it adds the vehicle to the vector, false otherwise
     */
    bool addVehicleToClient(Vehicle *vehicle, Client *client);

    bool addServiceToVehicle(Service *service, Vehicle *vehicle);

    bool isTopClient(Client* client);

    void removeClientCard(PointCard clientCard);

    Client* inactiveClientWithVehicle(Vehicle* vehicle);

    void printInactiveClientsWithName(string name);

    void checkForInactiveClients();

    void removeClientPoints(Client* client);

    /**
     * @returns the vehicle with the given license plate
     */
    Vehicle *vehicleWithLicensePlate(string licensePlate);

    /**
     * @returns a vector of clients with the given name
     */
    vector<Client *> clientsWithName(string name);

    Client *clientWithVehicle(Vehicle *vehicle);

    /**
     * @returns the clients' vector index of the client with the given ID
     */
    Client *clientWithID(int id);

    /**
     * @returns a vector of employees with the given name
     */
    vector<Employee *> employeesWithName(string name);

    /**
     * @brief assigns a vehicle to an employee, keeping the vehicle distribution even
     * @returns false if there are no employees
     */
    bool assignEmployee(Vehicle *vehicle);

    bool existsScheduledService(Service *service);

    Service* findService(Service *service, Vehicle* vehicle);

    Service* findScheduledService(Service *service, Vehicle* vehicle);

    /**
     * @brief adds a future service to the scheduled services BST
     */
    void addScheduledService(Service *service);

    bool removeScheduledService(Service* service);

    bool removeService(Service* service, Vehicle* vehicle);

    /**
     * @brief removes a vehicle from the Auto Repair Shop (and from its' Client owner and assigned Employee)
     * @returns false if the vehicle doesn't exist on the Auto Repair Shop
     */
    bool removeVehicle(Vehicle *vehicle);

    /**
     * @brief removes an employee from the Auto Repair Shop (assigns the employees' vehicles to others if possible)
     * @returns false if the employee doesn't exist on the Auto Repair Shop
     */
    bool removeEmployee(Employee *employee);

    /**
     * @brief removes a client and his vehicles from the Auto Repair Shop
     * @returns false if the client doesn't exist on the Auto Repair Shop
     */
    bool removeClient(Client *client);

    /**
     * @returns Auto Repair Shop name
     */
    const string &getName() const;

    /**
     * @brief prints all vehicles info to std::cout
     */
    void printVehiclesInfo() const;

    /**
     * @brief prints all employees info to std::cout
     */
    void printEmployeesInfo() const;

    /**
     *@brief prints all clients info to std::cout
     */
    void printClientsInfo() const;

    void printInactiveClientsInfo();

    /**
     * @brief prints all services info to std::cout
     */
    void printServices() const;

    void printScheduledServicesInOrder();

    /**
     * @brief prints info of clients whose name start with firstLetter
     */
    void printClientsWithFirstLetter(char firstLetter) const;

    /**
     * @brief prints info of employees whose name start with firstLetter
     */
    void printEmployeesWithFirstLetter(char firstLetter) const;

    /**
     * @brief prints all info present on the Auto Repair Shop
     * Doesn't print the vehicles vector because it would just be duplicated info after clients and employees
     */
    void printAllInfo() const;

    /**
     * @returns the vehicles vector
     */
    const vector<Vehicle *> &getVehicles() const { return vehicles; };

    /**
     * @returns the employees vector
     */
    const vector<Employee *> &getEmployees() const { return employees; };

    /**
     * @returns the clients vector
     */
    const vector<Client *> &getClients() const { return clients; };

    const unordered_set<Client *, clientHash, clientHash> &getInactiveClients() const { return inactiveClients;}

    const BST<Service *> &getScheduledServices() const { return scheduledServices; };

    static int getNextClientID() { return nextClientID; };

    static void setNextClientID(int nextClientID) { AutoRepairShop::nextClientID = nextClientID; }

/**
     * @exception InexistentVehicle exception to throw when vehicleWithLicensePlate() doesn't find any vehicle
     */
    class InexistentVehicle {
        string licensePlate;
    public:
        InexistentVehicle(string licensePlate) : licensePlate(licensePlate) { };

        void showErrorMessage() { cout << "There isn't a vehicle with the license plate " << this->licensePlate; };
    };
};


#endif //AEDA_PROJECT_WORKSHOP_H
