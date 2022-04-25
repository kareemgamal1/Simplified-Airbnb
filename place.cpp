#include "place.h"
// TODO: add time to constructor
Place::Place()
{
    // noOfPlaces++;
    // ID = noOfPlaces + 1;
    ID = 66;
}
Place::Place(location loc, int pricePerDay, string view, bool room, int noOfRooms, string paymentMethod, float discount = 0)
{
    // if () // if startDate to endDate is reserved
    // {
    // this->reserved = reserved;
    // }
    // noOfPlaces++;
    // ID = noOfPlaces + 1;
    ID = 66;
    this->loc = loc;
    this->view = view;
    this->paymentMethod = paymentMethod;
    this->room = room;
    this->noOfRooms = noOfRooms;
    this->pricePerDay = pricePerDay;
    this->discount = discount;
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
