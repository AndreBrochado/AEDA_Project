//
// Created by up201403057 on 24-10-2015.
//

#ifndef AEDA_PROJECT_UTILITIES_H
#define AEDA_PROJECT_UTILITIES_H

#include <iostream>
#include <vector>

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

bool readString(const string &prompt, string &returnString);

struct Date{
    int day;
    int month;
    int year;
};

#endif //AEDA_PROJECT_UTILITIES_H
