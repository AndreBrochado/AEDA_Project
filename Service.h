//
// Created by Andre on 06/11/2015.
//

#ifndef AEDA_PROJECT_SERVICE_H
#define AEDA_PROJECT_SERVICE_H

#include "Utilities.h"
#include "AutoRepairShop.h"

using namespace std;

struct Date {
    int day;
    int month;
    int year;
    int hour;
    int minute;
};

class Client;

/**
 * @class Service
 * @brief superclass to StandardService and NonStandardService
 */
class Service {
protected:
    string description;
    float price;
    Date startingDate;
    int duration;
    Client* client;
    Vehicle* vehicle;
public:
    Service(Date startingDate, Client* client, Vehicle* vehicle);

    Service(istream &in);

    void addClient(Client* client);

    void addVehicle(Vehicle* vehicle);

    virtual int classIdentifier() { return 0; };

    virtual void saveObjectInfo(ostream &out);

    void printObjectInfo();

    virtual float getPrice() const = 0;

    virtual int getDuration() const = 0;

    virtual const string &getDescription() const = 0;

    Date getStartingDate() const;
};

/**
 * @class StandardService
 * @brief superclass to OilChange, Inspection and CarWash
 */
class StandardService : public Service {
public:
    StandardService(Date startingDate, Client* client, Vehicle* vehicle) : Service(startingDate, client, vehicle) { };

    StandardService(istream &in) : Service(in) { };

    virtual int classIdentifier() { return 1; };

    virtual void saveObjectInfo(ostream &out) { Service::saveObjectInfo(out); };
};

/**
 * @class NonStandardService
 * @brief Non Standard Services Performed on Vehicles
 */
class NonStandardService : public Service {
public:
    NonStandardService(Date startingDate, string description, float price, int duration, Client* client, Vehicle* vehicle);

    NonStandardService(istream &in) : Service(in) { };

    int classIdentifier() { return 2; };

    void saveObjectInfo(ostream &out) { Service::saveObjectInfo(out); };

    float getPrice() const { return price; };

    int getDuration() const { return duration; };

    const string &getDescription() const { return description; };
};

/**
 * @class OilChange
 * @brief Oil Change Service Performed on Vehicles
 */
class OilChange : public StandardService {
public:
    OilChange(Date startingDate, Client* client, Vehicle* vehicle);

    OilChange(istream &in) : StandardService(in) { };

    int classIdentifier() { return 3; };

    void saveObjectInfo(ostream &out) { StandardService::saveObjectInfo(out); };

    float getPrice() const { return price; };

    int getDuration() const { return duration; };

    const string &getDescription() const { return description; };
};

/**
 * @class OilChange
 * @brief Inspection Service Performed on Vehicles
 */
class Inspection : public StandardService {
public:
    Inspection(Date startingDate, Client* client, Vehicle* vehicle);

    Inspection(istream &in) : StandardService(in) { };

    int classIdentifier() { return 4; };

    void saveObjectInfo(ostream &out) { StandardService::saveObjectInfo(out); };

    float getPrice() const { return price; };

    int getDuration() const { return duration; };

    const string &getDescription() const { return description; };
};

class CarWash : public StandardService {
public:
    CarWash(Date startingDate, Client* client, Vehicle* vehicle);

    CarWash(istream &in) : StandardService(in) { };

    int classIdentifier() { return 5; };

    void saveObjectInfo(ostream &out) { StandardService::saveObjectInfo(out); };

    float getPrice() const { return price; };

    int getDuration() const { return duration; };

    const string &getDescription() const { return description; };
};

Service *createService(istream &in, int classIdentifier);

#endif //AEDA_PROJECT_SERVICE_H