#include "place.h"
// TODO: add time to constructor
Place::Place()
{
    noOfPlaces++;
    ID = noOfPlaces + 1;
}
Place::Place(location loc, int pricePerDay, string view, bool room, int noOfRooms, string paymentMethod)
{
    // if () // if startDate to endDate is reserved
    // {
    // this->reserved = reserved;
    // }
    noOfPlaces++;
    ID = noOfPlaces + 1;
    this->loc = loc;
    this->view = view;
    this->paymentMethod = paymentMethod;
    this->room = room;
    this->noOfRooms = noOfRooms;
    this->pricePerDay = pricePerDay;
}