//
// Created by Andre on 06/11/2015.
//

#include <ctime>
#include "Service.h"
#include "ConfigFile.h"

Service::Service(Date startingDate, Client *client, Vehicle *vehicle) {
    this->startingDate = startingDate;
    this->client = client;
    this->vehicle = vehicle;
}

Service::Service(istream &in) {
    char dummy;
    getline(in, this->description, '\n');
    in.ignore(1000, '\n');
    in >> this->price >> this->startingDate.day >> this->startingDate.month
    >> this->startingDate.year >> this->startingDate.hour >> dummy
    >> this->startingDate.minute >> dummy >> this->duration;
    this->client = NULL;
    this->vehicle = NULL;
}

void Service::saveObjectInfo(ostream &out) {
    out << this->classIdentifier() << endl << this->description << endl
    << this->price << endl << this->startingDate.day << " "
    << this->startingDate.month << " " << this->startingDate.year
    << endl << this->startingDate.hour << "h"
    << this->startingDate.minute << "m" << endl << this->duration << endl << this->client->getID() << endl
    this->vehicle->getLicensePlate();
}

void Service::printObjectInfo() {
    cout << "Service: " << this->description << endl << "Price: " << this->price
    << endl << "Starting Date: " << startingDate.day << "/"
    << startingDate.month << "/" << startingDate.year << endl
    << startingDate.hour << "h" << startingDate.minute << "m"
    << endl << "Duration: " << this->duration << " day";    //TODO: CHANGE DURATION TO HOURS
    if (this->duration != 1)
        cout << "s";

}

Date Service::getStartingDate() const {
    return startingDate;
}

NonStandardService::NonStandardService(Date startingDate, string description,
                                       float price, int duration, Client *client, Vehicle *vehicle) :
        Service(startingDate, client, vehicle) {
    this->description = description;
    this->price = price;
    this->duration = duration;
}

OilChange::OilChange(Date startingDate, Client *client, Vehicle *vehicle) :
        StandardService(startingDate, client, vehicle) {
    this->description = "Oil Change";
    this->duration = 0;
    this->price = 14.99;
}

Inspection::Inspection(Date startingDate, Client *client, Vehicle *vehicle) :
        StandardService(startingDate, client, vehicle) {
    this->description = "Inspection";
    this->duration = 1;
    this->price = 24.99;
}

CarWash::CarWash(Date startingDate, Client *client, Vehicle *vehicle) :
        StandardService(startingDate, client, vehicle) {
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

bool operator<(Date d1, Date d2) {
    if (d1.year != d2.year)
        return d1.year < d2.year;
    if (d1.month != d2.month)
        return d1.month < d2.month;
    if (d1.day != d2.day)
        return d1.day < d2.day;
    if (d1.hour != d2.hour)
        return d1.hour < d2.hour;
    return d1.minute < d2.minute;
}

bool operator==(Date d1, Date d2) {
    return d1.year == d2.year && d1.month == d2.month && d1.day == d2.day && d1.hour == d2.hour &&
           d1.minute == d2.minute;
}

void Service::addClient(Client *client) {
    this->client = client;
}

void Service::addVehicle(Vehicle *vehicle) {
    this->vehicle = vehicle;
}
