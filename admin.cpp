#include "admin.h"
void admin::declare() {}
void admin::createTraveler() {}
void admin::createHost() {}
void admin::generateDashboard() {}

void admin::addAdvertisement() {}
void admin::editAdvertisement() {}
void admin::deleteAdvertisement() {}
Place admin::searchByType(string type) {}
Place admin::searchByLocation(location loc) {}
Place admin::searchByView(string view) {}
Place admin::searchByPriceRange(int priceRangeStart, int priceRangeEnd) {}
Place admin::searchByPaymentMethod(string paymentMethod) {}
Place admin::searchByNoOfRooms(int noOfRooms) {}
Place admin::searchByDuration(string startDate, string endDate) {}
Place admin::search() {}

// Getters and Setters
vector<Host> admin::getHosts()
{
    return this->hosts;
}
void admin::setHosts(vector<Host> hosts)
{
    this->hosts = hosts;
}
vector<Traveler> admin::getTravelers()
{
    return this->travelers;
}
void admin::setTravelers(vector<Traveler> travelers)
{
    this->travelers = travelers;
}