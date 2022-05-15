#include "place.h"
// TODO: add time to constructor


void Place::getNextID() {
    ifstream id("lastID.txt");
    string currentID;
    getline(id, currentID);
    this->ID = stoi(currentID)+1;
    id.close();
}

void Place::saveCurrentID() {
    ofstream id("lastID.txt");
    id << this->ID;
    cout << "ID saved:" << ID;
}

Place::Place()
{
    
}

Place::Place(int ID, location loc, int pricePerDay, string view, bool room, int noOfRooms, string paymentMethod, string hostEmail, float discount) {
    this->ID = ID;
    saveCurrentID();
    this->loc = loc;
    this->view = view;
    this->paymentMethod = paymentMethod;
    this->room = room;
    this->noOfRooms = noOfRooms;
    this->pricePerDay = pricePerDay;
    this->discount = discount;
    this->hostEmail = hostEmail;
}
Place::Place(location loc, int pricePerDay, string view, bool room, int noOfRooms, string paymentMethod, string hostEmail, timereserve startDate, timereserve endDate,float discount = 0)
{
    // if () // if startDate to endDate is reserved
    // {
    // this->reserved = reserved;
    // }
    getNextID();
    this->ID = ID++;
    saveCurrentID();
    this->loc = loc;
    this->view = view;
    this->paymentMethod = paymentMethod;
    this->room = room;
    this->noOfRooms = noOfRooms;
    this->pricePerDay = pricePerDay;
    this->discount = discount;
    this->hostEmail = hostEmail;
    this->availableduration = 0;
    this->startDate = startDate;
    this->endDate = endDate;
}

void Place::calculateDuration() {
    duration = daysofplace.size();
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
        return (pricePerDay - (discount * pricePerDay))*duration; // then multiply the whole expression by the number of days (Tamer&Ahmed)
    }
} // total price for the no of days the traveler will stay for
