// #define TRAVELER_H
// #ifndef TRAVELER_H
#include "user.h"
#include "place.h"
#include <filesystem>

class Traveler : public User
{
	string startDate;
	string endDate;
	location loc;
	int stayDuration;
	int priceRangeStart;
	int priceRangeEnd;
	int queryNumber;
	vector<Place> allPlaces;
	vector<Place> currentPlaces;
	Place reservedPlace;
	// test
public:
	// vector to hold all Places, and check for each element if it satisfies every attribute we search with
	// another vector to hold the Places which satisfy the conditions
	void signup();
	void login();

	string validateEmail(string email);
	bool checkForCredintials(string email, string password);
	void fillTravelerInfo(string path);
	void deSerializePlaces();
	void serializePlace(Place p);
	void displayAll();
	void restartAll();
	void endProgram();
	int calculateBookedDuration(timereserve startDate, timereserve endDate);
	vector<Place> chooseContainer();
	void searchByType();
	void searchByCountry();
	void searchByCity();
	void searchByStreet();
	void searchByLocation();
	void searchByView();
	void searchByPriceRange();
	void searchByPaymentMethod();
	void searchByNoOfRooms();
	void searchByDuration();
	void searchByDate();
	void search(); // will contain all the above functions, narrowing it down, if at any choice there are no Places available, it will be shown to the traveler
	void choosePlace();
	float generateDiscount(Place p);
	float generateTotalPrice(Place p);
	void viewBy(); // sort based on different Place attributes
};
// #endif