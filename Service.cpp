//
// Created by Andre on 06/11/2015.
//

#include <ctime>
#include "Service.h"

Service::Service(Date startingDate){
    tm temp{0};
    temp.tm_year = startingDate.year - 1990;
    temp.tm_mon = startingDate.month - 1;
    temp.tm_mday = startingDate.day;
    this->startingDate = mktime(&temp);
}

Service::Service(istream &in) {
    getline(in, this->description, '\n');
    in.ignore(1000, '\n');
    in>> this->price >> this->startingDate >> this->duration;
}

void Service::saveObjectInfo(ostream &out) {
    out<< this->classIdentifier() << endl << this->description << endl << this->price << endl << this->startingDate << endl << duration;
}

Date Service::getStartingDate() const {
    tm* date = localtime(&startingDate);
    return Date{date->tm_mday, date->tm_mon+1, date->tm_year+1900};
}

NonStandardService::NonStandardService(Date startingDate, string description, float price, int duration) : Service(startingDate) {
    this->description = description;
    this->price = price;
    this->duration = duration;
}

OilChange::OilChange(Date startingDate) : StandardService(startingDate) {
    this->description = "Oil Change";
    this->duration = 0;
    this->price = 14.99;
}

Inspection::Inspection(Date startingDate) : StandardService(startingDate) {
    this->description = "Inspection";
    this->duration = 1;
    this->price = 24.99;
}

CarWash::CarWash(Date startingDate) : StandardService(startingDate) {
    this->description = "Car Wash";
    this->duration = 0;
    this->price = 9.49;
}

Service* createServiceObject(int classIdentifier, istream& in){
    Service* newService;
    switch(classIdentifier){
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
            exception e; //TODO SPECIFY
            throw(e);
    }
    return newService;
}