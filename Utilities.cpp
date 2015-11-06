//
// Created by Andre on 06/11/2015.
//

#include "Utilities.h"

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