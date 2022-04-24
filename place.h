#ifndef PLACE_H
#define PLACE_H
#include "user.h"
#include "timePeriod.h"
struct location
{
    string country;
    string city;
    string streetName;
};
class Place
{
public:
    location loc;
    // Time startDate, endDate;
    string view;
    string paymentMethod;
    bool room;
    // bool reserved = false; //should be based on the total time that the place will be available for
    int pricePerDay;
    int noOfRooms;
    int ID;
    //static int noOfPlaces;
    Place();
    Place(location loc, int pricePerDay, string view, bool room, int noOfRooms, string paymentMethod);
};
#endif