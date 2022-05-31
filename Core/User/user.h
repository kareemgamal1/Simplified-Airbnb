#ifndef USER_H
#define USER_H
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
using namespace std;

class User
{
protected:
    string firstName;
    string lastName;
    string email;
    string password;
    string nationality;
    string phone;
    char gender;
    int age;

public:
    void signup();
    void login();
    void serializeUser(string path);
    // Getters and Setters
    string getFirstName();
    void setFirstName(string firstName);
    string getLastName();
    void setLastName(string lastName);
    string getEmail();
    void setEmail(string email);
    string getPassword();
    void setPassword(string password);
    string getNationality();
    void setNationality(string nationality);
    string getPhone();
    void setPhone(string phone);
    char getGender();
    void setGender(char gender);
    int getAge();
    void setAge(int age);
};
#endif