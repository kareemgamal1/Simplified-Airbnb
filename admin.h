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
    void createTraveler();
    void createHost();
    void generateDashboard();

    void addAdvertisement();
    void editAdvertisement();
    void deleteAdvertisement();
    Place searchByType();
    Place searchByCountry();
    Place searchByCity();
    Place searchByStreet();
    Place searchByLocation();
    Place searchByView();
    Place searchByPriceRange();
    Place searchByPaymentMethod();
    Place searchByNoOfRooms();
    Place searchByDuration();
    Place search();
};
#endif