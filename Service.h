//
// Created by Andre on 06/11/2015.
//

#ifndef AEDA_PROJECT_SERVICE_H
#define AEDA_PROJECT_SERVICE_H

#include "Utilities.h"

using namespace std;

struct Date {
    int day;
    int month;
    int year;
};


class Service {
protected:
    string description;
    float price;
    Date startingDate;
    int duration;
public:
    Service(Date startingDate);
    Service(istream& in);
    virtual int classIdentifier() {return 0;};
    virtual void saveObjectInfo(ostream& out);
    void printObjectInfo();
    virtual float getPrice() const = 0;
    virtual int getDuration() const = 0;
    virtual const string& getDescription() const = 0;
    Date getStartingDate() const;
};

class StandardService : public Service {
public:
    StandardService(Date startingDate) : Service(startingDate) {};
    StandardService(istream& in) : Service(in){};
    virtual int classIdentifier() {return 1;};
    virtual void saveObjectInfo(ostream& out){Service::saveObjectInfo(out);};
};

class NonStandardService : public Service {
public:
    NonStandardService(Date startingDate, string description ,float price, int duration);
    NonStandardService(istream& in) : Service(in){};
    int classIdentifier() {return 2;};
    void saveObjectInfo(ostream& out){Service::saveObjectInfo(out);};
    float getPrice() const {return price;};
    int getDuration() const {return duration;};
    const string& getDescription() const {return description;};
};

class OilChange : public StandardService {
public:
    OilChange(Date startingDate);
    OilChange(istream& in) : StandardService(in){};
    int classIdentifier() {return 3;};
    void saveObjectInfo(ostream& out){StandardService::saveObjectInfo(out);};
    float getPrice() const {return price;};
    int getDuration() const {return duration;};
    const string& getDescription() const {return description;};
};

class Inspection : public StandardService {
public:
    Inspection(Date startingDate);
    Inspection(istream& in) : StandardService(in){};
    int classIdentifier() {return 4;};
    void saveObjectInfo(ostream& out){StandardService::saveObjectInfo(out);};
    float getPrice() const {return price;};
    int getDuration() const {return duration;};
    const string& getDescription() const {return description;};
};

class CarWash : public StandardService {
public:
    CarWash(Date startingDate);
    CarWash(istream& in) : StandardService(in){};
    int classIdentifier() {return 5;};
    void saveObjectInfo(ostream& out){StandardService::saveObjectInfo(out);};
    float getPrice() const {return price;};
    int getDuration() const {return duration;};
    const string& getDescription() const {return description;};
};

Service* createServiceObject(istream& in, int classIdentifier);

#endif //AEDA_PROJECT_SERVICE_H