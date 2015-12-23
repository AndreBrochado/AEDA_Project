#include <ctime>
#include "Service.h"
#include "ConfigFile.h"

Service::Service(tm startingDate) {
    this->startingDate = startingDate;
    this->client = NULL;
    this->vehicle = NULL;
}

Service::Service(istream &in) {
    char dummy;
    this->startingDate = {0};
    in.ignore(1000, '\n');
    getline(in, this->description);
    in >> this->price >> this->startingDate.tm_mday >> this->startingDate.tm_mon
    >> this->startingDate.tm_year >> this->startingDate.tm_hour >> dummy
    >> this->startingDate.tm_min >> dummy >> this->duration;
    this->client = NULL;
    this->vehicle = NULL;
}

void Service::saveObjectInfo(ostream &out) {
    out << endl << this->classIdentifier() << endl << this->description << endl
    << this->price << endl << this->startingDate.tm_mday << " "
    << this->startingDate.tm_mon << " " << this->startingDate.tm_year
    << endl << this->startingDate.tm_hour << "h"
    << this->startingDate.tm_min << "m" << endl << this->duration << endl << this->client->getID() << endl
    << this->vehicle->getLicensePlate();
}

void Service::printObjectInfo() {
    cout << "Service: " << this->description << endl << "Price: " << this->price
    << endl << "Starting Date: " << startingDate.tm_mday << "/"
    << startingDate.tm_mon + 1 << "/" << startingDate.tm_year+1900 << " at "
    << startingDate.tm_hour << "h" << startingDate.tm_min << "m"
    << endl << "Duration: " << this->duration << " day";    //TODO: CHANGE DURATION TO HOURS
    if (this->duration != 1)
        cout << "s";

}

tm Service::getStartingDate() const {
    return startingDate;
}

NonStandardService::NonStandardService(tm startingDate, string description,
                                       float price, int duration) :
        Service(startingDate) {
    this->description = description;
    this->price = price;
    this->duration = duration;
}

OilChange::OilChange(tm startingDate) :
        StandardService(startingDate) {
    this->description = "Oil Change";
    this->duration = 0;
    this->price = 14.99;
}

Inspection::Inspection(tm startingDate) :
        StandardService(startingDate) {
    this->description = "Inspection";
    this->duration = 1;
    this->price = 24.99;
}

CarWash::CarWash(tm startingDate) :
        StandardService(startingDate) {
    this->description = "Car Wash";
    this->duration = 0;
    this->price = 9.49;
}

Service *createService(istream &in, int classIdentifier) {
    Service *newService;
    switch (classIdentifier) {
        case 2:
            newService = new NonStandardService(in);
            break;
        case 3:
            newService = new OilChange(in);
            break;
        case 4:
            newService = new Inspection(in);
            break;
        case 5:
            newService = new CarWash(in);
            break;
        default:
            string file = "Vehicles file";
            ConfigFile::BadFileException e(file);
            throw (e);
    }
    return newService;
}

void Service::addClient(Client *client) {
    this->client = client;
}

void Service::addVehicle(Vehicle *vehicle) {
    this->vehicle = vehicle;
}

Vehicle *Service::getVehicle() {
    return this->vehicle;
}

Client *Service::getClient() {
    return this->client;
}

bool Service::operator==(Service* s) {
    return description == s->description && client == s->client && startingDate == s->startingDate && vehicle == s->vehicle;
}

bool Service::operator<(Service *s) {
    if(startingDate == s->startingDate)
        return client->getName() < s->client->getName();
    return s->startingDate > startingDate;
}
