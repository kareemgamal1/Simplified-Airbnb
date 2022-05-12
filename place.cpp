#include "place.h"
// TODO: add time to constructor
int Place::noOfPlaces = 0; //I want to save it in a file

Place::Place() {
    noOfPlaces++;
    this->ID = noOfPlaces;
}
Place::Place(location loc, int pricePerDay, string view, bool room, int noOfRooms, string paymentMethod, float discount = 0,string hostEmail)
{
    // if () // if startDate to endDate is reserved
    // {
    // this->reserved = reserved;
    // }
    noOfPlaces++;
    this->ID = noOfPlaces;
    this->loc = loc;
    this->view = view;
    this->paymentMethod = paymentMethod;
    this->room = room;
    this->noOfRooms = noOfRooms;
    this->pricePerDay = pricePerDay;
    this->discount = discount;
    this->hostEmail = hostEmail;
}

float Place::generateDiscount()
{
    if (discount != 0)
    {
        return (discount / 100);
    }

} // if there is a discount for travelers who stay for over 3 nights, generate it based on that apartment
float Place::generateTotalPrice()
{
    if (discount != 0)
    {
        discount = generateDiscount();
        return (pricePerDay - (discount * pricePerDay)); // then multiply the whole expression by the number of days (Tamer&Ahmed)
    }
} // total price for the no of days the traveler will stay for
