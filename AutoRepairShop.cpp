#include <time.h>
#include <stdlib.h>
#include <algorithm>

#include "AutoRepairShop.h"
#include "ConfigFile.h"
#include "Service.h"

// ============================================ PERSON ============================================ //

Person::Person(string name) {
    this->name = name;
    this->id = -1;
}

Person::Person(istream &in, string name, vector<string> &licensePlates) {
    this->name = name;
    string testString = "-";
    in >> testString;
    while (testString.find('-') != string::npos) {
        if (testString == "-") {
            string file = "Clients file";
            ConfigFile::BadFileException e(file);
            throw (e);
        }
        licensePlates.push_back(testString);
        in >> testString;
    }
    this->id = atoi(testString.c_str());
    in.ignore(1000, '\n');
}

void Person::saveObjectInfo(ostream &out) {
    out << this->name << endl;
    for (size_t i = 0; i < vehicles.size(); i++) {
        out << vehicles[i]->getLicensePlate() << endl;
    }
    out << this->id;
}

bool Person::addVehicle(Vehicle *vehicle) {
    return addsIfNotExist(vehicle, this->vehicles);
}

bool operator==(const Person &p1, const Person &p2) {
    return p1.getName() == p2.getName();
}

bool operator<(const Employee &e1, const Employee &e2) {
    if (e1.getVehicles().size() == e2.getVehicles().size())
        return e1.getID() < e2.getID();
    return e1.getVehicles().size() < e2.getVehicles().size();
}

bool operator>(const Client &c1, const Client &c2) {
    return c1.getID() > c2.getID();
}

bool operator>(const Employee &e1, const Employee &e2) {
    return e1.getID() > e2.getID();
}

// ============================================ CLIENT ============================================ //

Client::Client(istream &in, string name, vector<string> &licensePlates) : Person(in, name, licensePlates) {
    getline(in, address);
    getline(in, email);
    getline(in, phoneNumber);
    this->clientCard = NULL;
}

void Client::saveObjectInfo(ostream &out) {
    Person::saveObjectInfo(out);
    out << endl << address << endl << email << endl << phoneNumber;
    if (clientCard)
        out << endl << getLastServiceDate().tm_mday << " " << getLastServiceDate().tm_mon << " " <<
        getLastServiceDate().tm_year << endl << clientCard->getPoints();
}

void Client::createClientCard(tm date, float cost) {
    this->clientCard = new PointCard(date, cost, this);
}

void Client::deleteClientCard() {
    this->clientCard = NULL;
}

void Client::updatePoints(tm date, float cost) {
    this->clientCard->addPoints(cost);
    this->clientCard->updateDate(date);
}

void Client::removePoints(int numPoints) {
    this->clientCard->removePoints(numPoints);
}

bool Client::checkPointsExpiration() {
    return this->clientCard->checkPointsExpiration();
}

void Client::printServices() const {
    for (size_t i = 0; i < vehicles.size(); i++) {
        vehicles[i]->printServices();
        if (i != vehicles.size() - 1)
            cout << endl;
    }
}

tm Client::getLastServiceDate() {
    tm lastDate = getToday();
    for (size_t i = 0; i < vehicles.size(); i++) {
        for (size_t j = 0; j < vehicles[i]->getServices().size(); j++) {
            if (lastDate > vehicles[i]->getServices()[j]->getStartingDate())
                lastDate = vehicles[i]->getServices()[j]->getStartingDate();
        }
    }
    return lastDate;
}

bool Client::isInactive() {
    if (getNumberOfServices() == 0 || clientCard == NULL)
        return true;
    tm lastDate = getLastServiceDate();
    time_t lastDateSecs = mktime(&lastDate);
    tm today = getToday();
    time_t todaySecs = mktime(&lastDate);
    return ((todaySecs - lastDateSecs) >= SECS_PER_MIN * MINs_PER_HOUR * HOURS_PER_DAY * DAYS_PER_YEAR);
}

// ============================================ EMPLOYEE ============================================ //

// ===================================== AUTOREPAIRSHOP ===================================== //

int AutoRepairShop::nextClientID = 0;

AutoRepairShop::AutoRepairShop(string name) : scheduledServices(NULL) {
    this->name = name;
}

Vehicle *AutoRepairShop::vehicleWithLicensePlate(string licensePlate) {
    for (size_t i = 0; i < vehicles.size(); i++) {
        if (vehicles[i]->getLicensePlate() == licensePlate)
            return vehicles[i];
    }
    throw (InexistentVehicle(licensePlate));
}

vector<Client *> AutoRepairShop::clientsWithName(string name) {
    vector<Client *> clientsWithName;
    for (size_t i = 0; i < clients.size(); i++) {
        if (clients[i]->getName() == name)
            clientsWithName.push_back(clients[i]);
    }
    unordered_set<Client *, clientHash, clientHash>::iterator it = inactiveClients.begin();
    while (it != inactiveClients.end()) {
        if ((*it)->getName() == name)
            clientsWithName.push_back(*it);
        it++;
    }
    return clientsWithName;
}

vector<Employee *> AutoRepairShop::employeesWithName(string name) {
    vector<Employee *> employeesWithName;
    for (size_t i = 0; i < employees.size(); i++) {
        if (employees[i]->getName() == name)
            employeesWithName.push_back(employees[i]);
    }
    return employeesWithName;
}

bool AutoRepairShop::isClient(Client *client1) {
    return exists(client1, clients);
}

bool AutoRepairShop::isEmployee(Employee *employee1) {
    return exists(employee1, employees);
}

bool AutoRepairShop::addClient(Client *client) {
    client->setID(nextClientID);
    nextClientID++;
    if (client->getClientCard())
        clients.push_back(client);
    else
        inactiveClients.insert(client);
    return true;
}

bool AutoRepairShop::addEmployee(Employee *employee) {
    if (isEmployee(employee))
        return false;
    employees.push_back(employee);
    employees[employees.size() - 1]->setID(employees.size() - 1);
    if (employees.size() == 1)
        for (size_t i = 0; i < vehicles.size(); i++) {
            assignEmployee(vehicles[i]);
        }
    return true;
}

bool AutoRepairShop::addVehicle(Vehicle *vehicle) {
    if (!addsIfNotExist(vehicle, this->vehicles))
        return false;
    if (employees.size() != 0) {
        insertionSort(employees);
        employees[0]->addVehicle(vehicle);
    }
    return true;
}

void AutoRepairShop::checkForInactiveClients() {
    for (size_t i = 0; i < clients.size(); i++) {
        if (clients[i]->isInactive()) {
            clients.erase(clients.begin() + i);
            removeClientCard(*clients[i]->getClientCard());
            clients[i]->deleteClientCard();
            inactiveClients.insert(clients[i]);
        }
    }
}

bool AutoRepairShop::removeVehicle(Vehicle *vehicle) {
    int index = sequentialSearch(vehicles, vehicle);
    if (index == -1) {
        return false;
    }
    for (size_t i = 0; i < employees.size(); i++) {
        employees[i]->removeVehicle(vehicle); //only removes from the one who actually has it
    }
    for (size_t i = 0; i < clients.size(); i++) {
        clients[i]->removeVehicle(vehicle); //only removes from the one who actually has it
    }
    unordered_set<Client *, clientHash, clientHash>::iterator it = inactiveClients.begin();
    while (it != inactiveClients.end()) {
        (*it)->removeVehicle(vehicle);
        it++;
    }
    vehicles.erase(vehicles.begin() + index);
    return true;
}

const string &AutoRepairShop::getName() const {
    return this->name;
}

bool Person::removeVehicle(Vehicle *vehicle) {
    int index = sequentialSearch(vehicles, vehicle);
    if (index == -1)
        return false;
    vehicles.erase(vehicles.begin() + index);
    return true;
}

bool AutoRepairShop::assignEmployee(Vehicle *vehicle) {
    if (employees.size() == 0)
        return false;
    insertionSort(employees);
    employees[0]->addVehicle(vehicle);
    return true;
}

bool AutoRepairShop::removeEmployee(Employee *employee) {
    int index = sequentialSearch(employees, employee);
    if (index == -1)
        return false;
    vector<Vehicle *> employeeVehicles = employee->getVehicles(); // - working ?
    employees.erase(employees.begin() + index);
    for (size_t i = 0; i < employeeVehicles.size(); i++) {
        assignEmployee(employeeVehicles[i]);
    }
    return true;
}

bool AutoRepairShop::removeClient(Client *client) {
    int index = sequentialSearch(clients, client);
    for (size_t i = 0; i < client->getVehicles().size(); i++) {
        removeVehicle(client->getVehicles()[i]);
    }
    if (!client->isInactive()) {
        removeClientCard(*client->getClientCard());
        clients.erase(clients.begin() + index);
    }
    else
        inactiveClients.erase(client);

    return true;
}

void AutoRepairShop::removeClientCard(PointCard clientCard) {
    priority_queue<PointCard> temp;
    while (!clientCards.empty()) {
        if (clientCards.top().getClient() != clientCard.getClient())
            temp.push(clientCards.top());
        clientCards.pop();
    }
    clientCards = temp;
}

void Person::printObjectInfo() const {
    cout << "Name: " << this->name << endl << "ID: " << this->id << endl;
}

void Client::printObjectInfo() const {
    Person::printObjectInfo();
    if (clientCard)
        cout << "Number of Points: " << clientCard->getPoints() << endl << "Expiring at: " <<
        clientCard->getDate().tm_mday << "/" << clientCard->getDate().tm_mon + 1 << "/" <<
        clientCard->getDate().tm_year + 1900 << endl;
    cout << "Address: " << address << endl << "Email: " << email << endl << "Telephone: " << phoneNumber << endl;
    cout << "Owned vehicles: ";
    for (size_t i = 0; i < vehicles.size(); i++) {
        cout << endl << "Vehicle " << i << ":" << endl;
        vehicles[i]->printObjectInfo();
    }
}

void Employee::printObjectInfo() const {
    Person::printObjectInfo();
    cout << "Assigned vehicles: ";
    for (size_t i = 0; i < vehicles.size(); i++) {
        cout << endl << "Vehicle " << i << ":" << endl;
        vehicles[i]->printObjectInfo();
    }
}

void AutoRepairShop::printVehiclesInfo() const {
    if (vehicles.size() == 0)
        cout << "There are 0 vehicles here. Go ahead and add some!";
    for (size_t i = 0; i < vehicles.size(); i++) {
        cout << "Vehicle " << i << ":" << endl;
        vehicles[i]->printObjectInfo();
        if (i != vehicles.size() - 1)
            cout << endl;
    }
}

void AutoRepairShop::printEmployeesInfo() const {
    if (employees.size() == 0)
        cout << "There are 0 employees here. Go ahead and add some!";
    vector<Employee *> employeesById = employees;
    inverseInsertionSort(employeesById);
    reverse(employeesById.begin(), employeesById.end());
    for (size_t i = 0; i < employeesById.size(); i++) {
        employeesById[i]->printObjectInfo();
        if (i != employeesById.size() - 1)
            cout << endl;
    }
}

void AutoRepairShop::printClientsInfo() const {
    if (clients.size() == 0)
        cout << "There are 0 clients here. Go ahead and add some!";
    vector<Client *> clientsById = clients;
    inverseInsertionSort(clientsById);
    reverse(clientsById.begin(), clientsById.end());
    for (size_t i = 0; i < clientsById.size(); i++) {
        clientsById[i]->printObjectInfo();
        if (i != clientsById.size() - 1)
            cout << endl;
    }
}

void AutoRepairShop::printServices() const {
    for (size_t i = 0; i < clients.size(); i++) {
        clients[i]->printServices();
        if (i != clients.size() - 1)
            cout << endl;
    }
}

void AutoRepairShop::printClientsWithFirstLetter(char firstLetter) const {
    vector<Client *> clientsById = clients;
    inverseInsertionSort(clientsById);
    reverse(clientsById.begin(), clientsById.end());
    for (size_t i = 0; i < clientsById.size(); i++) {
        if (clientsById[i]->getName()[0] == firstLetter) {
            if (i != 0)
                cout << endl;
            clientsById[i]->printObjectInfo();
        }
    }
}

void AutoRepairShop::printEmployeesWithFirstLetter(char firstLetter) const {
    vector<Employee *> employeesById = employees;
    inverseInsertionSort(employeesById);
    reverse(employeesById.begin(), employeesById.end());
    for (size_t i = 0; i < employeesById.size(); i++) {
        if (employeesById[i]->getName()[0] == firstLetter) {
            if (i != 0)
                cout << endl;
            employeesById[i]->printObjectInfo();
        }
    }
}

void AutoRepairShop::printAllInfo() const {
    cout << "Auto Repair Shop: " << this->name << endl;
    printClientsInfo();
    cout << endl;
    printEmployeesInfo();
    cout << endl;
    if (vehicles.size() == 0)
        cout << "There are 0 vehicles here. Go ahead and add some!" << endl <<
        "Note: you need to have at least 1 client and 1 employee to add vehicles";
}

bool AutoRepairShop::addVehicleToClient(Vehicle *vehicle, Client *client) {
    return client->addVehicle(vehicle);
}

Client *AutoRepairShop::clientWithID(int id) {
    for (size_t i = 0; i < clients.size(); i++) {
        if (id == clients[i]->getID())
            return clients[i];
    }
    unordered_set<Client *, clientHash, clientHash>::iterator it = inactiveClients.begin();
    while (it != inactiveClients.end()) {
        if ((*it)->getID() == id)
            return *it;
    }
    return NULL;
}

void AutoRepairShop::addScheduledService(Service *service) {
    scheduledServices.insert(service);
}

Client *AutoRepairShop::clientWithVehicle(Vehicle *vehicle) {
    for (size_t i = 0; i < clients.size(); i++) {
        if (sequentialSearch(clients[i]->getVehicles(), vehicle) != -1)
            return clients[i];
    }
    return NULL;
}

bool AutoRepairShop::addServiceToVehicle(Service *service, Vehicle *vehicle) {
    Client *client = clientWithVehicle(vehicle);
    if (!client)
        client = inactiveClientWithVehicle(vehicle);
    if (!client)
        return false;
    if (client->isInactive()) {
        client->createClientCard(service->getStartingDate(), service->getPrice());
        clients.push_back(client);
        inactiveClients.erase(client);
        clientCards.push(*client->getClientCard());
    }
    else {
        removeClientCard(*client->getClientCard());
        client->getClientCard()->addPoints(service->getPrice());
        clientCards.push(*client->getClientCard());
    }
    service->addClient(client);
    service->addVehicle(vehicle);
    vehicle->addService(service);
    return true;
}

Client *AutoRepairShop::inactiveClientWithVehicle(Vehicle *vehicle) {
    unordered_set<Client *, clientHash, clientHash>::iterator it = inactiveClients.begin();
    while (it != inactiveClients.end()) {
        for (size_t i = 0; i < (*it)->getVehicles().size(); i++) {
            if ((*it)->getVehicles()[i] == vehicle)
                return (*it);
        }
        it++;
    }
    return NULL;
}

int Client::getNumberOfServices() {
    int sum = 0;
    for (size_t i = 0; i < vehicles.size(); i++) {
        sum += vehicles[i]->getServices().size();
    }
    return sum;
}

bool AutoRepairShop::removeScheduledService(Service *service) {
    if (!existsScheduledService(service))
        return false;
    scheduledServices.remove(service);
    return true;
}

bool AutoRepairShop::existsScheduledService(Service *service) {
    BSTItrIn<Service *> it(scheduledServices);
    while (!it.isAtEnd()) {
        if (it.retrieve() == service)
            return true;
        it.advance();
    }
    return false;
}

bool AutoRepairShop::removeService(Service *service, Vehicle *vehicle) {
    Client *client = clientWithVehicle(vehicle);
    service->addVehicle(vehicle);
    service->addClient(client);
    if (vehicle->removeService(service)) {
        client->removePoints((int) service->getPrice() * PointCard::getCostToPoints());
        return true;
    }
    else
        return false;
}

void AutoRepairShop::printInactiveClientsInfo() {
    if (inactiveClients.size() == 0)
        cout << "There are no inactive clients!" << endl;
    else {
        unordered_set<Client *, clientHash, clientHash>::iterator it = inactiveClients.begin();
        while (it != inactiveClients.end()) {
            (*it)->printObjectInfo();
            cout << endl;
            it++;
        }
    }
}

Service *AutoRepairShop::findService(Service *service, Vehicle *vehicle) {
    service->addClient(clientWithVehicle(vehicle));
    service->addVehicle(vehicle);
    for (size_t i = 0; i < vehicle->getServices().size(); i++) {
        if (*service == vehicle->getServices()[i])
            return vehicle->getServices()[i];
    }
    return NULL;
}

Service *AutoRepairShop::findScheduledService(Service *service, Vehicle *vehicle) {
    service->addClient(clientWithVehicle(vehicle));
    service->addVehicle(vehicle);
    BSTItrIn<Service *> it(scheduledServices);
    while (!it.isAtEnd()) {
        if (*service == it.retrieve())
            return it.retrieve();
    }
    return NULL;
}

void AutoRepairShop::printScheduledServicesInOrder() {
    BSTItrIn<Service *> it(scheduledServices);

    while (!it.isAtEnd()) {
        it.retrieve()->printObjectInfo();
        cout << endl;
        it.advance();
    }
}

void AutoRepairShop::printInactiveClientsWithName(string name) {
    unordered_set<Client*, clientHash, clientHash>::iterator it = inactiveClients.begin();
    int count = 0;
    while(it != inactiveClients.end()){
        if((*it)->getName() == name) {
            count++;
            (*it)->printObjectInfo();
            cout << endl;
        }
        it++;
    }
    if(count == 0)
        cout << "There are no inactive clients with that name!" << endl;
}

bool AutoRepairShop::isTopClient(Client *client) {
    priority_queue<PointCard> temp = clientCards;
    for(int i = 0; i < 3; i++){
        if(temp.empty())
            return false;
        if(temp.top().getClient() == client)
            return true;
        else
            temp.pop();
    }
    return false;
}

void AutoRepairShop::removeClientPoints(Client *client) {
    removeClientCard(*client->getClientCard());
    client->removePoints(0);
    clientCards.push(*client->getClientCard());
}
