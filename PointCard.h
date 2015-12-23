#ifndef AEDA_PROJECT_POINTCARD_H
#define AEDA_PROJECT_POINTCARD_H

#include <ctime>
#include "AutoRepairShop.h"

using namespace std;

class Client;

class PointCard {
    static time_t pointsExpirationTime;
    static int costToPoints;
    int points;
    tm date;
    Client* client;
public:
    PointCard(tm date, float cost, Client* client);

    void addPoints(float cost);

    void updateDate(tm date);

    void removePoints(int numPoints);

    bool checkPointsExpiration();

    int getPoints() const { return points; };

    const tm &getDate() const { return date; };

    Client* getClient() const { return client;};

    bool operator<(const PointCard p2) const;

    static int getCostToPoints() { return costToPoints;}
};

#endif //AEDA_PROJECT_POINTCARD_H
