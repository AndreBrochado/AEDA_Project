#include "PointCard.h"
#include "Utilities.h"

time_t PointCard::pointsExpirationTime = 30 * HOURS_PER_DAY * MINs_PER_HOUR * SECS_PER_MIN;

int PointCard::costToPoints = 100;

PointCard::PointCard(tm date, float serviceCost, Client *client) {
    time_t dateSecs = mktime(&date);
    dateSecs += pointsExpirationTime;
    tm *finalDate = localtime(&dateSecs);
    this->date = *finalDate;
    this->points = (int) serviceCost * costToPoints;
    this->client = client;
}

void PointCard::addPoints(float cost) {
    this->points += cost * 100;
}

void PointCard::updateDate(tm date) {
    time_t dateSecs = mktime(&date);
    dateSecs += pointsExpirationTime;
    this->date = *localtime(&dateSecs);
}

void PointCard::removePoints(int numPoints) {
    if (numPoints == 0)
        points = 0;
    else
        points -= numPoints;
}

bool PointCard::checkPointsExpiration() {
    if (getToday() > date) {
        removePoints(0);
        return true;
    }
    else
        return false;
}

bool PointCard::operator<(const PointCard p2) const {
    if (points == p2.points)
        return client->getNumberOfServices() < p2.client->getNumberOfServices();
    else
        return points < p2.points;
}
