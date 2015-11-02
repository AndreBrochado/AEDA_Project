//
// Created by up201403057 on 24-10-2015.
//

#ifndef AEDA_PROJECT_UTILITIES_H
#define AEDA_PROJECT_UTILITIES_H

#include <iostream>
#include <vector>
#include "AutoRepairShop.h"

using namespace std;

template<class T>
bool exists(T obj, const vector<T>& v){
    for(size_t i = 0; i < v.size(); i++){
        if(obj == v[i])
            return true;
    }
    return false;
}

template<class T>
bool addsIfNotExist(T obj, vector<T>& v){
    if(exists(obj, v))
        return false;
    v.push_back(obj);
    return true;
}

bool operator==(const Client &c1,const Client &c2){
    return c1.getID() == c2.getID();
}

bool operator==(const Employee &e1, const Employee &e2){
    return e1.getID() == e2.getID();
}

bool operator==(const Vehicle &v1, const Vehicle &v2){
    return v1.getLicensePlate() == v2.getLicensePlate();
}

#endif //AEDA_PROJECT_UTILITIES_H
