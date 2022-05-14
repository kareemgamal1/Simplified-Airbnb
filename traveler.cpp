#include "traveler.h"
#include "user.h"
#include "place.h"
#include <filesystem>
using namespace std;

void Traveler::signup()
{
    cout << "First name : ";
    cin >> firstName;
    cout << "Last name : ";
    cin >> lastName;
    cout << "E-mail: ";
    cin >> email; // validate email isn't already in use
    string path = "traveller/" + email + ".txt";
    ifstream ifile;
    ifile.open(path);
    while (ifile)
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
        ifstream ifile;
        ifile.open(path);
        if (ifile)
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
void Traveler::deSerializePlaces()
{
    // TODO: test this
    string path = "place";
    for (const auto &host_directory_entry : filesystem::directory_iterator(path))
    {
        string host_name_path = host_directory_entry.path().string();
        for (const auto &place_directory_entry : filesystem::directory_iterator(host_name_path))
        {
            ifstream stream(place_directory_entry.path().string());
            string x;
            location loc;
            string view;
            string paymentMethod;
            string hostEmail;
            bool room;
            bool reserved;
            int pricePerDay;
            int noOfRooms;
            int ID;
            float discount;
            getline(stream, x);
            loc.country = x;
            getline(stream, x);
            loc.city = x;
            getline(stream, x);
            loc.streetName = x;
            getline(stream, x);
            view = x;
            getline(stream, x);
            paymentMethod = x;
            getline(stream, x);
            room = (x == "1");
            getline(stream, x);
            reserved = (x == "1");
            getline(stream, x);
            pricePerDay = stoi(x);
            getline(stream, x);
            noOfRooms = stoi(x);
            getline(stream, x);
            //discount = stof(x);
            getline(stream, x);
            hostEmail = x;
            stream.close();
            //TODO discount
            Place p = Place(loc, pricePerDay, view, room, noOfRooms, paymentMethod, hostEmail, 0); // It's supposed to work without providing the discount as it's a defeault argument
            allPlaces.push_back(p);
        }
    }
}

void Traveler::displayAll()
{
    for (int i = 0; i < currentPlaces.size(); i++)
    {
        cout << "Advertisements: \n";
        cout << "Advertisement ID:" << currentPlaces[i].ID << '\n';
        currentPlaces[i].room ? cout << "Room.\n" : cout << "Apartment.\n";
        cout << "Location:" << currentPlaces[i].loc.country << ' ' << currentPlaces[i].loc.city << ' ' << currentPlaces[i].loc.streetName << '\n';
        cout << "Price: " << currentPlaces[i].pricePerDay << '\n';
        cout << "View:" << currentPlaces[i].view << '\n';
        cout << "Payment method: " << currentPlaces[i].paymentMethod;
    }
}

vector<Place> Traveler::chooseContainer()
{
    return (queryNumber == 0) ? allPlaces : currentPlaces;
}
void Traveler::searchByType()
{
    int choice;
    bool room;
    cout << "Enter (1) for room or (2) for apartment.";
    cin >> choice;
    room = (choice == 1);
    vector<Place> currentContainer = chooseContainer();
    for (int i = 0; i < currentContainer.size(); i++)
    {
        if (currentContainer[i].room != room)
        {
            currentContainer.erase(currentContainer.begin() + i);
        }
    }
    currentPlaces = currentContainer;
    queryNumber++;
    displayAll();
}
void Traveler::searchByCountry()
{
    string country;
    cout << "Country: ";
    cin >> country;
    vector<Place>
        currentContainer = chooseContainer();
    for (int i = 0; i < currentContainer.size(); i++)
    {
        if (currentContainer[i].loc.country != country)
        {
            currentContainer.erase(currentContainer.begin() + i);
        }
    }
    currentPlaces = currentContainer;
    queryNumber++;
    displayAll();
}

void Traveler::searchByCity()
{
    string city;
    cout << "City: ";
    cin >> city;
    vector<Place> currentContainer = chooseContainer();
    for (int i = 0; i < currentContainer.size(); i++)
    {
        if (currentContainer[i].loc.city != city)
        {
            currentContainer.erase(currentContainer.begin() + i);
        }
    }
    currentPlaces = currentContainer;
    queryNumber++;
    displayAll();
}
void Traveler::searchByStreet()
{
    string streetName;
    cout << "Street name: ";
    cin >> streetName;
    vector<Place> currentContainer = chooseContainer();
    for (int i = 0; i < currentContainer.size(); i++)
    {
        if (currentContainer[i].loc.streetName != streetName)
        {
            currentContainer.erase(currentContainer.begin() + i);
        }
    }
    currentPlaces = currentContainer;
    queryNumber++;
    displayAll();
}
void Traveler::searchByLocation()
{
    searchByCountry();
    searchByCity();
    searchByStreet();
}
void Traveler::searchByView()
{
    string view;
    cout << "View: ";
    cin >> view;
    vector<Place> currentContainer = chooseContainer();
    for (int i = 0; i < currentContainer.size(); i++)
    {
        if (currentContainer[i].view != view)
        {
            currentContainer.erase(currentContainer.begin() + i);
        }
    }
    currentPlaces = currentContainer;
    queryNumber++;
    displayAll();
}

void Traveler::searchByPriceRange()
{
    int priceRangeStart, priceRangeEnd;
    cout << "Price from: ";
    cin >> priceRangeStart;
    cout << "To: ";
    cin >> priceRangeEnd;
    vector<Place> currentContainer = chooseContainer();
    for (int i = 0; i < currentContainer.size(); i++)
    {
        if (currentContainer[i].pricePerDay < priceRangeStart && currentContainer[i].pricePerDay > priceRangeEnd)
        {
            currentContainer.erase(currentContainer.begin() + i);
        }
    }
    currentPlaces = currentContainer;
    queryNumber++;
    displayAll();
}

void Traveler::searchByPaymentMethod()
{
    string paymentMethod;
    cout << "Payment method: ";
    cin >> paymentMethod;
    vector<Place> currentContainer = chooseContainer();
    for (int i = 0; i < currentContainer.size(); i++)
    {
        if (currentContainer[i].paymentMethod != paymentMethod)
        {
            currentContainer.erase(currentContainer.begin() + i);
        }
    }
    currentPlaces = currentContainer;
    queryNumber++;
    displayAll();
}
void Traveler::searchByNoOfRooms()
{
    // available only if it's an apartment.
    int noOfRooms;
    cout << "Number of rooms: ";
    cin >> noOfRooms;
    vector<Place> currentContainer = chooseContainer();
    for (int i = 0; i < currentContainer.size(); i++)
    {
        if (currentContainer[i].noOfRooms != noOfRooms && !currentContainer[i].room)
        {
            currentContainer.erase(currentContainer.begin() + i);
        }
    }
    currentPlaces = currentContainer;
    queryNumber++;
    displayAll();
}

void Traveler::searchByDuration()
{
    int duration;
    cout << "Enter number of days";
    cin >> duration;
    vector<Place> currentContainer = chooseContainer();
    for (int i = 0; i < currentContainer.size(); i++)
    {
        if (currentContainer[i].duration != duration)
        {
            currentContainer.erase(currentContainer.begin() + i);
        }
    }
    currentPlaces = currentContainer;
    queryNumber++;
    displayAll();
}

void Traveler::searchByDate() {
    timereserve startdate, enddate;
    cout << " please enter the start date";
    cin >> startdate.day >> startdate.month;
    cout << " please enter the end date ";
    cin >> enddate.day >> enddate.month;
    
}

void Traveler::search()
{
    queryNumber = 0;
    deSerializePlaces();
    cout << "\n\n\nEnter your searching preferences:\n(1)Type (Room or Apartment)\n(2)Location\n(3)View\n(4)Price range\n(5)Payment method\n(6)Number of rooms in an apartment\n(7)Duration of stay\n";
    cout << "Enter (0) to stop searching.";
    int choice;
    cin >> choice;
    while (choice != 0)
    {
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
    }
}

void Traveler::choosePlace()
{
    displayAll();
    cout << "Enter the ID of the advertisement you want to select.";
    int ID;
    cin >> ID;
    for (int i = 0; i < currentPlaces.size(); i++)
    {
        if (currentPlaces[i].ID == ID)
        {
            reservedPlace = currentPlaces[i];
            cout << "Please pay " << reservedPlace.generateTotalPrice() << " using: " << reservedPlace.paymentMethod;
            break;
        }
    }
}

void Traveler::viewBy() {} // sort based on different Place attributes (Tamer)

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