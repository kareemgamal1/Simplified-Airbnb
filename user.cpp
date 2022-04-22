#include "user.h"
void User::signup()
{
}
void User::login()
{
}

// Getters and Setters
string User::getFirstName()
{
    return this->firstName;
}
void User::setFirstName(string firstName)
{
    this->firstName = firstName;
}
string User::getLastName()
{
    return this->lastName;
}
void User::setLastName(string lastName)
{
    this->lastName = lastName;
}
string User::getEmail()
{
    return this->email;
}
void User::setEmail(string email)
{
    this->email = email;
}
string User::getPassword()
{
    return this->password;
}
void User::setPassword(string password)
{
    this->password = password;
}
string User::getNationality()
{
    return this->nationality;
}
void User::setNationality(string nationality)
{
    this->nationality = nationality;
}
char User::getGender()
{
    return this->gender;
}
void User::setGender(char gender)
{
    this->gender = gender;
}
int User::getAge()
{
    return this->age;
}
void User::setAge(int age)
{
    this->age = age;
}