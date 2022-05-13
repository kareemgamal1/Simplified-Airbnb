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
    float discount;
    static int noOfPlaces;
    string hostEmail;
    Place();
    Place(location loc, int pricePerDay, string view, bool room, int noOfRooms, string paymentMethod, string hostEmail, float discount);
    float generateDiscount();   // if there is a discount for travelers who stay for over 3 nights, generate it based on that apartment
    float generateTotalPrice(); // total price for the no of days the traveler will stay for
};
#endif