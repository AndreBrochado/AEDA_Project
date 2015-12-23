#ifndef AEDA_PROJECT_UTILITIES_H
#define AEDA_PROJECT_UTILITIES_H

#include <iostream>
#include <vector>
#include "Service.h"
#include "AutoRepairShop.h"
#include "PointCard.h"

#define SECS_PER_MIN 60
#define MINs_PER_HOUR 60
#define HOURS_PER_DAY 24
#define DAYS_PER_YEAR 365

using namespace std;

struct Date;

class Person;

bool operator==(const Person &p1, const Person &p2);

template<class T>
bool exists(T obj, const vector<T> &v) {
    for (size_t i = 0; i < v.size(); i++) {
        if (obj == v[i])
            return true;
    }
    return false;
}

template<class T>
bool addsIfNotExist(T obj, vector<T> &v) {
    if (exists(obj, v))
        return false;
    v.push_back(obj);
    return true;
}

bool readString(const string &prompt, string &returnString);

ostream &operator<<(ostream &out, Date &d1);

template<class T>
void writeVector(vector<T *> vec, ostream &out) {
    for (size_t i = 0; i < vec.size(); i++) {
        vec[i]->saveObjectInfo(out);
        if (i != vec.size() - 1)
            out << endl;
    }
}

template<class T, class Y>
void writeUnorderedSet(unordered_set<T *, Y, Y> set, ostream &out){
    typename unordered_set<T *, Y, Y>::iterator it = set.begin();
    while(it != set.end()){
        (*it)->saveObjectInfo(out);
        it++;
        if(it != set.end())
            out<<endl;
    }
}

template<class T>
void writeBST(BST<T *> tree, ostream &out) {
    BSTItrLevel <T *> it(tree);
    while (!it.isAtEnd()) {
        it.retrieve()->saveObjectInfo(out);
        it.advance();
        if(!it.isAtEnd())
            out << endl;
    }
}

template<class T>
int sequentialSearch(const vector<T> &v, T x) {
    for (unsigned int i = 0; i < v.size(); i++)
        if (v[i] == x)
            return i;
    return -1;
}

template<class T>
void insertionSort(vector<T> &v) {
    for (unsigned int p = 1; p < v.size(); p++) {
        T tmp = v[p];
        int j;
        for (j = p; j > 0 && tmp < v[j - 1]; j--)
            v[j] = v[j - 1];
        v[j] = tmp;
    }
};

template<class T>
void inverseInsertionSort(vector<T> &v) {
    for (unsigned int p = 1; p < v.size(); p++) {
        T tmp = v[p];
        int j;
        for (j = p; j > 0 && tmp > v[j - 1]; j--)
            v[j] = v[j - 1];
        v[j] = tmp;
    }
};

/*long int dateToDayNumber(Date date);

Date dayNumberToDate(long int g);

Date operator+(Date d, int i);*/

bool operator==(tm d1, tm d2);

bool operator>(tm d1, tm d2);

bool validDay(int year, int month, int day);

bool validHour(int hour, int minute);

tm getToday();

#endif //AEDA_PROJECT_UTILITIES_H
