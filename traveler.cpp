#include "traveler.h"
#include "user.h"
#include "place.h"
void Traveler::signup()
{
    cout << "First name : ";
    cin >> firstName;
    cout << "Last name : ";
    cin >> lastName;
    cout << "E-mail: ";
    cin >> email; // validate email isn't already in use
    string path = "traveller/" + email + ".txt";
    while (filesystem::exists(path))
    {
        cout << "this E-Mail is already in use" << endl;
        cout << "E-mail: ";
        cin >> email;
        path = "traveller/" + email + ".txt";
    }
    cout << "Password : ";
    cin >> password;
    cout << "Phone : ";
    cin >> phone;
    cout << "Nationality :";
    cin >> nationality;
    cout << "Gender : ";
    cin >> gender;
    cout << "Age : ";
    cin >> age;

    ofstream stream(path.c_str());
    stream << password << endl;
    stream << firstName << endl;
    stream << lastName << endl;
    stream << email << endl;
    stream << phone << endl;
    stream << nationality << endl;
    stream << gender << endl;
    stream << age << endl;
    stream.close();
}
void Traveler::login()
{
    string em, pass;
    int num_tries = 0;
    bool validated = false;
    while (num_tries < 3)
    {
        cout << "Username : ";
        cin >> em;
        cout << "\nPassword : ";
        cin >> pass;
        // logging in

        string path = "traveller/" + em + ".txt";
        if (filesystem::exists(path))
        {
            string str;
            ifstream stream(path.c_str());
            getline(stream, str);
            validated = (str == pass);
        }

        if (validated)
        {
            search();
            cout << "Thank you for using our app.\n";
            break;
        }
        else
        {
            if (num_tries < 3)
            {
                cout << "The password or username you entered is incorrect. \n";
                cout << "You have: " << 3 - num_tries + 1 << "| tries to enter\n";
                num_tries++;
                cout << "Please try again.\n";
            }
            else
            {
                cout << "Please try again after 1 minute.\n";
                num_tries = 0;
            }
        }
    }
}

Place Traveler::searchByType() {}
Place Traveler::searchByLocation() {}
Place Traveler::searchByView() {}
Place Traveler::searchByPriceRange() {}
Place Traveler::searchByPaymentMethod() {}
Place Traveler::searchByNoOfRooms() {}
Place Traveler::searchByDuration() {}
Place Traveler::search()
{
    cout << "\n\n\nEnter your searching preferences:\n(1)Type (Room or Apartment)\n(2)Location\n(3)View\n(4)Price range\n(5)Payment method\n(6)Number of rooms in an apartment\n(7)Duration of stay\n";
    int choice;
    cin >> choice;
    switch (choice)
    {
    case 1:
    {
        searchByType();
        break;
    }
    case 2:
    {
        searchByLocation();
        break;
    }
    case 3:
    {
        searchByView();
        break;
    }
    case 4:
    {
        searchByPriceRange();
        break;
    }
    case 5:
    {
        searchByPaymentMethod();
        break;
    }
    case 6:
    {
        searchByNoOfRooms();
        break;
    }
    case 7:
    {
        searchByDuration();
        break;
    }
    }
} // will contain all the above functions, narrowing it down, if at any choice there are no Places available, it will be shown to the traveler
void Traveler::choosePlace(Place place) {}
int Traveler::generateDiscount() {}   // if there is a discount for travelers who stay for over 3 nights, generate it based on that apartment
int Traveler::generateTotalPrice() {} // total price for the no of days the traveler will stay for
void Traveler::viewBy() {}            // sort based on different Place attributes

// Getters and Setters
string Traveler::getStartDate()
{
    return this->startDate;
}
void Traveler::setStartDate(string startDate)
{
    this->startDate = startDate;
}
string Traveler::getEndDate()
{
    return this->endDate;
}
void Traveler::setEndDate(string endDate)
{
    this->endDate = endDate;
}
int Traveler::getStayDuration()
{
    return this->stayDuration;
}
void Traveler::setStayDuration(int stayDuration)
{
    this->stayDuration = stayDuration;
}
location Traveler::getLoc()
{
    return this->loc;
}
void Traveler::setLoc(location loc)
{
    this->loc = loc;
}
int Traveler::getPriceRangeStart()
{
    return this->priceRangeStart;
}
void Traveler::setPriceRangeStart(int priceRangeStart)
{
    this->priceRangeStart = priceRangeStart;
}
int Traveler::getPriceRangeEnd()
{
    return this->priceRangeEnd;
}
void Traveler::setPriceRangeEnd(int priceRangeEnd)
{
    this->priceRangeEnd = priceRangeEnd;
}