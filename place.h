#ifndef PLACE_H
#define PLACE_H
#include "user.h"
#include "timePeriod.h"
#include <fstream>
struct timereserve
{
    int day;
    int month;
    bool reserved = false;
};
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
    int ID;
    int pricePerDay;
    int noOfRooms;
    int duration;
    float discount;
    string hostEmail;
    vector<timereserve> daysofplace;
    void getNextID();
    void saveCurrentID();
    Place();
    Place(int ID, location loc, int pricePerDay, string view, bool room, int noOfRooms, string paymentMethod, string hostEmail, float discount = 0);
    Place(location loc, int pricePerDay, string view, bool room, int noOfRooms, string paymentMethod, string hostEmail, float discount);
    void calculateDuration();
    float generateDiscount();   // if there is a discount for travelers who stay for over 3 nights, generate it based on that apartment
    float generateTotalPrice(); // total price for the no of days the traveler will stay for
};
#endif