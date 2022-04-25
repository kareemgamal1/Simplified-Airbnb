#include "admin.h"
void admin::createTraveler() {}
void admin::createHost() {}
void admin::generateDashboard() {}

void admin::addAdvertisement() {}
void admin::editAdvertisement() {}
void admin::deleteAdvertisement() {}
Place admin::searchByType() {}
Place admin::searchByLocation() {}
Place admin::searchByView() {}
Place admin::searchByPriceRange() {}
Place admin::searchByPaymentMethod() {}
Place admin::searchByNoOfRooms() {}
Place admin::searchByDuration() {}
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