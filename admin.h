#ifndef ADMIN_H
#define ADMIN_H
#include "place.h"
#include "host.h"
#include "traveler.h"
#include <vector>
using namespace std;

class admin
{
    vector<Host> hosts;         // hash table
    vector<Traveler> travelers; // hash table

public:
    void declare();
    void createTraveler();
    void createHost();
    void generateDashboard();

    void addAdvertisement();
    void editAdvertisement();
    void deleteAdvertisement();
    Place searchByType(string type);
    Place searchByLocation(location loc);
    Place searchByView(string view);
    Place searchByPriceRange(int priceRangeStart, int priceRangeEnd);
    Place searchByPaymentMethod(string paymentMethod);
    Place searchByNoOfRooms(int noOfRooms);
    Place searchByDuration(string startDate, string endDate);
    Place search();

    // Getters and Setters
    vector<Host> getHosts();
    void setHosts(vector<Host> hosts);
    vector<Traveler> getTravelers();
    void setTravelers(vector<Traveler> travelers);
};
#endif