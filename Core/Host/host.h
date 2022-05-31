#ifndef HOST_H
#define HOST_H
#include "../Place/place.h"
#include <filesystem>
#include <vector>
#include <unordered_map>

using namespace std;

class Host : public User
{
    unordered_map<int,Place> places;
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
    void showSpecificPlace();
    Host(string password, string firstName, string lastName, string email, string phone, string nationality, char gender, int age);
    Host();
};
#endif