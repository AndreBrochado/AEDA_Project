//
// Created by Andre on 06/11/2015.
//

#include <ctime>
#include "Service.h"
#include "ConfigFile.h"

Service::Service(Date startingDate) {
	this->startingDate = startingDate;
}

Service::Service(istream &in) {
	getline(in, this->description, '\n');
	in.ignore(1000, '\n');
	in >> this->price >> this->startingDate.day >> this->startingDate.month
			>> this->startingDate.year >> this->startingDate.hours
			>> this->startingDate.minutes >> this->duration;

}

void Service::saveObjectInfo(ostream &out) {
	out << this->classIdentifier() << endl << this->description << endl
			<< this->price << endl << this->startingDate.day << " "
			<< this->startingDate.month << " " << this->startingDate.year
			<< endl << this->startingDate.hours << " h "
			<< this->startingDate.minutes << " m" << endl << this->duration;
}

void Service::printObjectInfo() {
	cout << "Service: " << this->description << endl << "Price: " << this->price
			<< endl << "Starting Date: " << startingDate.day << "/"
			<< startingDate.month << "/" << startingDate.year << "|"
			<< startingDate.hours << " h " << startingDate.minutes << " m"
			<< endl << "Duration: " << this->duration << " day";
	if (this->duration != 1)
		cout << "s";

}

Date Service::getStartingDate() const {
	return startingDate;
}

NonStandardService::NonStandardService(Date startingDate, string description,
		float price, int duration) :
		Service(startingDate) {
	this->description = description;
	this->price = price;
	this->duration = duration;
}

OilChange::OilChange(Date startingDate) :
		StandardService(startingDate) {
	this->description = "Oil Change";
	this->duration = 0;
	this->price = 14.99;
}

Inspection::Inspection(Date startingDate) :
		StandardService(startingDate) {
	this->description = "Inspection";
	this->duration = 1;
	this->price = 24.99;
}

CarWash::CarWash(Date startingDate) :
		StandardService(startingDate) {
	this->description = "Car Wash";
	this->duration = 0;
	this->price = 9.49;
}

Service* createServiceObject(istream& in, int classIdentifier) {
	Service* newService;
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
		throw(e);
	}
	return newService;
}
