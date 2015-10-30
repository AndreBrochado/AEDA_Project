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
bool exists(T obj, vector<T> v){
    for(size_t i = 0; i < v.size(); i++){
        if(obj == v[i])
            return true;
    }
    return false;
}

bool operator==(const Client &c1,const Client &c2){
    return c1.getClientID() == c2.getClientID();
}

bool operator==(const Employee &e1, const Employee &e2){
    return e1.getEmployeeID() == e2.getEmployeeID();
}

#endif //AEDA_PROJECT_UTILITIES_H
