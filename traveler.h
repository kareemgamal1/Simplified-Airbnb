// #define TRAVELER_H
// #ifndef TRAVELER_H
#include "user.h"
#include "place.h"
class Traveler : public User
{
    string startDate;
    string endDate;
    location loc;
    int stayDuration;
    int priceRangeStart;
    int priceRangeEnd;

public:
    // vector to hold all Places, and check for each element if it satisfies every attribute we search with
    // another vector to hold the Places which satisfy the conditions
    // TODO: test this
    void signup();
    void login();

    Place searchByType();
    Place searchByLocation();
    Place searchByView();
    Place searchByPriceRange();
    Place searchByPaymentMethod();
    Place searchByNoOfRooms();
    Place searchByDuration();
    Place search(); // will contain all the above functions, narrowing it down, if at any choice there are no Places available, it will be shown to the traveler
    void choosePlace(Place place);
    int generateDiscount();   // if there is a discount for travelers who stay for over 3 nights, generate it based on that apartment
    int generateTotalPrice(); // total price for the no of days the traveler will stay for
    void viewBy();            // sort based on different Place attributes

    // Getters and Setters
    string getStartDate();
    void setStartDate(string startDate);
    string getEndDate();
    void setEndDate(string endDate);
    int getStayDuration();
    void setStayDuration(int stayDuration);
    location getLoc();
    void setLoc(location loc);
    int getPriceRangeStart();
    void setPriceRangeStart(int priceRangeStart);
    int getPriceRangeEnd();
    void setPriceRangeEnd(int priceRangeEnd);
};
// #endif