// #define TRAVELER_H
// #ifndef TRAVELER_H
#include "../User/user.h"
#include "../Place/place.h"
#include <filesystem>
#include <unordered_map>

class Traveler : public User
{
	int queryNumber;
	unordered_map<int, Place> allPlaces;
	unordered_map<int, Place> currentPlaces;
public:
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
	unordered_map<int, Place> chooseContainer();
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
	void displayDate(Place p); 
	bool bookingcontinousperiod(Place& p, timereserve startdate, int period);
	int bookingSeperateDate(Place& p); 
	void choosePlace();
	float generateTotalPrice(Place p,int );
	void viewBy(); // sort based on different Place attributes
	Traveler(string password, string firstName, string lastName, string email, string phone, string nationality, char gender, int age);
	Traveler();
};
// #endif