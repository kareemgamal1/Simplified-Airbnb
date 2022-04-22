#ifndef HOST_H
#define HOST_H
#include "place.h"
#include <vector>
using namespace std;
class Host : public User
{
    vector<Place> places; // vector
public:
    void signup();
    void login();
    void addAdvertisement();
    void displayAdvertisements();
    void editAdvertisement();
    void deleteAdvertisement();
    void serializePlaces();
    void deSerializePlaces();
    // Getters and Setters
    vector<Place> getPlaces(); // hashtable
    void setPlaces(vector<Place> places);
};
#endif