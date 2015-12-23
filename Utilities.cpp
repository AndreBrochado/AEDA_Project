#include <time.h>
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
    if (testString == "" || testString == "\n")
        return false;
    returnString = testString;
    return true;
}

/*long int dateToDayNumber(Date date) {
    date.month = (date.month + 9) % 12;
    date.year = date.year - date.month / 10;
    return 365 * date.year + date.year / 4 - date.year / 100 + date.year / 400 + (date.month * 306 + 5) / 10 +
           (date.day - 1);
}

Date dayNumberToDate(long int g) {
    Date returnDate;
    returnDate.year = (10000 * g + 14780) / 3652425;
    int ddd = g - (365 * returnDate.year + returnDate.year / 4 - returnDate.year / 100 + returnDate.year / 400);
    if (ddd < 0) {
        returnDate.year--;
        ddd = g - (365 * returnDate.year + returnDate.year / 4 - returnDate.year / 100 + returnDate.year / 400);
    }
    int mi = (100 * ddd + 52) / 3060;
    returnDate.month = (mi + 2) % 12 + 1;
    returnDate.year = returnDate.year + (mi + 2) / 12;
    returnDate.day = ddd - (mi * 306 + 5) / 10 + 1;
    return returnDate;
}*/

bool validDay(int year, int month, int day) {
    switch (month) {
        case 4:
        case 6:
        case 9:
        case 11:
            return day <= 30;
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return day <= 31;
        case 2: {
            bool leapyear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
            if (leapyear)
                return day <= 29;
            else
                return day <= 28;
        }
        default:
            return false;
    }
}

bool validHour(int hour, int minute) {
    return hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59;
}

bool operator>(tm d1, tm d2){
    return mktime(&d1) > mktime(&d2);

}

bool operator==(tm d1, tm d2){
    return mktime(&d1) == mktime(&d2);
}

tm getToday() {
    time_t now = time(NULL);
    tm *today = localtime(&now);
    return *today;
}