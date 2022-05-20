#ifndef HOST_H
#define HOST_H
#include "place.h"
#include <filesystem>
#include <vector>
using namespace std;
class Host : public User
{
    vector<Place> places; // vector
public:
    void signup();
    void login();
    void showChoices();
    string validateEmail(string email);
    bool checkForCredintials(string email, string password);
    void fillHostInfo(string path);
    void serializePlace(Place p);
    void deSerializePlaces();
    void addAdvertisement();
    void displayAdvertisements();
    void editAdvertisement();
    void deleteAdvertisement();
};
#endif