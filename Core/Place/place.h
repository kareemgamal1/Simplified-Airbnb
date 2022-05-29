#ifndef PLACE_H
#define PLACE_H
#include "../User/user.h"
#include <fstream>
struct timereserve
{
    int day;
    int month;
    bool reserved = false;
    string userreserve = "none"; 
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
    timereserve startDate, endDate;
    string view;
    string paymentMethod;
    bool room;
    // bool reserved = false; //should be based on the total time that the place will be available for
    int availableduration;
    int ID;
    int pricePerDay;
    int noOfRooms;
    int duration;
    float discount;
    string hostEmail;
    vector<timereserve> daysofplace;
    void getNextID();
    void saveCurrentID();
    void createTimeForPlace();
    Place();
    Place(timereserve startDate, timereserve endDate);
    Place(int ID, location loc, int pricePerDay, string view, bool room, int noOfRooms, string paymentMethod, string hostEmail, timereserve startDate, timereserve endDate, int discount);
    Place(location loc, int pricePerDay, string view, bool room, int noOfRooms, string paymentMethod, string hostEmail, int discount);
    Place(location loc, int pricePerDay, string view, bool room, int noOfRooms, string paymentMethod, string hostEmail, timereserve startDate, timereserve endDate, int discount);
    void bookingcontinousperiod(int period, timereserve t);
    void displaydays();
    void calculateDuration();
};
#endif