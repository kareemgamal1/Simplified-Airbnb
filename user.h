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
};
#endif