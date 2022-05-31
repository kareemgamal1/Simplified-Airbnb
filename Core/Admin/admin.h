#ifndef ADMIN_H
#define ADMIN_H
#include "../Place/place.h"
#include "../Host/host.h"
#include "../Traveler/traveler.h"
#include <vector>
using namespace std;

class Admin
{
	unordered_map<string, Host> hosts;         
	unordered_map<string, Traveler> travelers; 

public:
	void createTraveler();
	void createHost();
	void mainmenu();
	void addAdvertisement();
	void editAdvertisement();
	void deleteAdvertisement();
	void deserializeHosts();
	void deserializeTravelers();
	void displayHosts();
	void displayTravelers();
	void deleteHost();
	void deleteTraveler();
	void generateDashboard();
	void validateAdmin();
	Admin();
};
#endif