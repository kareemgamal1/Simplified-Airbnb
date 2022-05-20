#include "place.h"
#include <stdexcept>
// TODO: add time to constructor

void Place::getNextID()
{
    ifstream id("lastID.txt");
    string currentID;
    getline(id, currentID);
    this->ID = stoi(currentID) + 1;
    id.close();
}
void Place::saveCurrentID()
{
    ofstream id("lastID.txt");
    id << this->ID;
    cout << "ID saved:" << ID;
}
Place::Place()
{
}
Place::Place(int ID, location loc, int pricePerDay, string view, bool room, int noOfRooms, string paymentMethod, string hostEmail, timereserve startDate, timereserve endDate, int discount)
{
    this->ID = ID;
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
Place::Place(location loc, int pricePerDay, string view, bool room, int noOfRooms, string paymentMethod, string hostEmail, int discount)
{
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
}
Place::Place(location loc, int pricePerDay, string view, bool room, int noOfRooms, string paymentMethod, string hostEmail, timereserve startDate, timereserve endDate, int discount)
{
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
void Place::createTimeForPlace()
{
    // TODO:: fix 30th of Feb case
    timereserve t;
    int j = this->startDate.month;
    int i = this->startDate.day;
    while (!(t.day == this->endDate.day && t.month == this->endDate.month))
    {
        switch (j)
        {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            if (this->startDate.day > 31)
            {
                std::logic_error ex("Invalid Date");
                throw std::exception(ex);
            }
            else
            {
                for (i; !(t.day == this->endDate.day && t.month == this->endDate.month); i++)
                {
                    if (i <= 31)
                    {
                        t.day = i;
                        t.month = j;
                        this->daysofplace.push_back(t);
                        this->availableduration++;
                    }
                    else
                    {
                        i = 1;
                        j = ++j % 12;
                        break;
                    }
                }
            }
            break;

        case 4:
        case 6:
        case 9:
        case 11:
            if (this->startDate.day > 30)
            {
                std::logic_error ex("Invalid Date");
                throw std::exception(ex);
            }
            else
                for (i; !(t.day == this->endDate.day && t.month == this->endDate.month); i++)
                {
                    if (i <= 30)
                    {
                        t.day = i;
                        t.month = j;
                        this->daysofplace.push_back(t);
                        this->availableduration++;
                    }
                    else
                    {
                        i = 1;
                        j = ++j % 12;
                        break;
                    }
                }
            break;
        case 2:
            if (this->startDate.day > 28)
            {
                std::logic_error ex("Invalid Date");
                throw std::exception(ex);
            }
            else
                for (i; !(t.day == this->endDate.day && t.month == this->endDate.month); i++)
                {
                    if (i <= 28)
                    {
                        t.day = i;
                        t.month = j;
                        this->daysofplace.push_back(t);
                        this->availableduration++;
                    }
                    else
                    {
                        i = 1;
                        j = ++j % 12;
                        break;
                    }
                }
            break;
        }
    }
}
void Place::calculateDuration()
{
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
        return (pricePerDay - (discount * pricePerDay)) * duration; // then multiply the whole expression by the number of days (Tamer&Ahmed)
    }
} // total price for the no of days the traveler will stay for