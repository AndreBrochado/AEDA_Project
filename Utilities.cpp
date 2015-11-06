//
// Created by Andre on 06/11/2015.
//

#include "Utilities.h"

ostream& operator<<(ostream& out, Date &d1){
    out<<d1.day<<"/"<<d1.month<<"/"<<d1.year;
    return out;
}

bool readString(const string &prompt, string &returnString) {
    string testString;
    cout << prompt;
    getline(cin, testString);
    cout << endl;
    if (cin.fail()) {
        if (!cin.eof())
            cin.ignore(1000, '\n');
        cin.clear();
        return false;
    }
    returnString = testString;
    return true;
}

