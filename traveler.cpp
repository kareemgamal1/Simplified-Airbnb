#include "traveler.h"
#include "user.h"
#include "place.h"
#include <filesystem>
using namespace std;

int queryNumber = 0;

void Traveler::signup()
{
    cout << "First name : ";
    cin >> firstName;
    cout << "Last name : ";
    cin >> lastName;
    cout << "E-mail: ";
    cin >> email;
    string path = validateEmail(email); // if the email is not in use, return its path
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
    serializeUser(path);
}

void Traveler::login()
{
    string em, pass;
    int num_tries = 0;
    bool validated = false;
    while (num_tries < 3 && !validated)
    {
        /*cout << "Username : ";
        cin >> em;
        cout << "\nPassword : ";
        cin >> pass;*/
        em = "A@mail";
        pass = "1";
        string path = "traveller/" + em + ".txt";
        validated = checkForCredintials(path, pass);
        if (validated)
        {
            fillTravelerInfo(path);
            search();
        }
        else
        {
            if (num_tries < 3)
            {
                cout << "The password or username you entered is incorrect. \n";
                cout << "You have: " << 3 - (num_tries + 1) << "| tries to enter\n";
                num_tries++;
                cout << "Please try again.\n";
            }
            else
            {
                cout << "Please try again after 1 minute.\n";
                num_tries = 0;
                login();
            }
        }
    }
}

void Traveler::serializePlace(Place p)
{
    string path = "place/" + p.hostEmail + "/" + to_string(p.ID) + ".txt";
    filesystem::create_directory(path);
    ofstream stream(path.c_str());
    stream << p.loc.country << endl;
    stream << p.loc.city << endl;
    stream << p.loc.streetName << endl;
    stream << p.view << endl;
    stream << p.paymentMethod << endl;
    stream << p.room << endl;
    // stream << p.reserved << endl; uncomment it after we handle reservation in place
    stream << p.pricePerDay << endl;
    stream << p.noOfRooms << endl;
    stream << p.ID << endl;
    stream << p.hostEmail << endl;
    stream << p.startDate.day << endl;
    stream << p.startDate.month << endl;
    stream << p.endDate.day << endl;
    stream << p.endDate.month << endl;
    stream << p.availableduration << endl;
    cout << "SIZE: " << p.daysofplace.size() << endl;
    for (int i = 0; i < p.daysofplace.size(); i++)
    {
        stream << p.daysofplace[i].day << endl;
        stream << p.daysofplace[i].month << endl;
        stream << p.daysofplace[i].reserved << endl;
        stream << endl;
    }
    stream.close();
}

void Traveler::deSerializePlaces()
{
    string path = "place";
    for (const auto &host_directory_entry : filesystem::directory_iterator(path))
    {
        string host_name_path = host_directory_entry.path().string();
        for (const auto &place_directory_entry : filesystem::directory_iterator(host_name_path))
        {
            ifstream stream(place_directory_entry.path());
            timereserve startDate, endDate;
            string x;
            location loc;
            string view;
            string paymentMethod;
            string hostEmail;
            bool room;
            // bool reserved;
            int pricePerDay;
            int noOfRooms;
            int ID;
            int discount = 0;
            int availableduration;
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
            // getline(stream, x);
            // reserved = (x == "1");
            getline(stream, x);
            pricePerDay = stoi(x);
            getline(stream, x);
            noOfRooms = stoi(x);
            getline(stream, x);
            discount = stoi(x);
            getline(stream, x);
            ID = stoi(x);
            getline(stream, x);
            hostEmail = x;
            getline(stream, x);
            startDate.day = stoi(x);
            getline(stream, x);
            startDate.month = stoi(x);
            getline(stream, x);
            endDate.day = stoi(x);
            getline(stream, x);
            endDate.month = stoi(x);
            getline(stream, x);
            availableduration = stoi(x);
            stream.close();
            Place p = Place(ID, loc, pricePerDay, view, room, noOfRooms, paymentMethod, hostEmail, startDate, endDate, discount); /// It's supposed to work without providing the discount as it's a defeault argument
            p.availableduration = availableduration;
            int i = 0;
            while (getline(stream, x))
            {
                timereserve t;
                if (i < 3)
                {
                    if (i == 0)
                        t.day = stoi(x);
                    else if (i == 1)
                        t.month = stoi(x);
                    else
                        t.reserved = (x == "1");
                    i++;
                }
                else
                {
                    i = 0;
                    p.daysofplace.push_back(t);
                }
            }
            allPlaces.push_back(p);
        }
    }
}

void Traveler::displayAll()
{
    vector<Place> currentContainer = chooseContainer();
    cout << "\nAdvertisements: \n\n";
    for (int i = 0; i < currentContainer.size(); i++)
    {
        cout << "===============================\n";
        cout << "Advertisement ID:" << currentContainer[i].ID << '\n';
        currentContainer[i].room ? cout << "Room.\n" : cout << "Apartment.\n";
        cout << "Location:" << currentContainer[i].loc.country << ' ' << currentContainer[i].loc.city << ' ' << currentContainer[i].loc.streetName << '\n';
        cout << "Price: " << currentContainer[i].pricePerDay << '\n';
        cout << "View:" << currentContainer[i].view << '\n';
        cout << "Payment method: " << currentContainer[i].paymentMethod << "\n";
        cout << "===============================\n\n\n";
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
    /*cin >> choice;*/
    choice = 2;
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
    displayAll();
    queryNumber++;
}

void Traveler::searchByCountry()
{
    string country;
    cout << "Country: ";
    cin >> country;
    vector<Place> currentContainer = chooseContainer();
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
    cout << "enter duration ";
    cin >> duration;
    vector<Place> currentContainer = chooseContainer();
    for (int i = 0; i < currentContainer.size(); i++)
    {
        if (currentContainer[i].availableduration <= duration)
        {
            currentContainer.erase(currentContainer.begin() + i);
        }
    }
    currentPlaces = currentContainer;
    queryNumber++;
    displayAll();
}

void Traveler::searchByDate()
{
    timereserve startdateofuser, enddateofuser;
    cout << " please enter start date\n";
    cin >> startdateofuser.day >> startdateofuser.month;
    cout << "please enter end date\n";
    ;
    cin >> enddateofuser.day >> enddateofuser.month;
    vector<Place> currentContainer = chooseContainer();
    for (int i = 0; i < currentContainer.size(); i++)
    {
        if (!(currentContainer[i].startDate.month < startdateofuser.month || (currentContainer[i].startDate.day <= startdateofuser.day && currentContainer[i].startDate.month == startdateofuser.month)) || !(currentContainer[i].endDate.month > enddateofuser.month || (currentContainer[i].endDate.day >= enddateofuser.day && currentContainer[i].startDate.month == startdateofuser.month)))
            currentContainer.erase(currentContainer.begin() + i);
    }
    currentPlaces = currentContainer;
    queryNumber++;
    displayAll();
}

void showPreferences()
{
    cout << "\n\n\nEnter your searching preferences:\n(1)Type (Room or Apartment)\n(2)Location\n(3)View\n(4)Price range\n(5)Payment method\n(6)Number of rooms in an apartment\n(7)Duration of stay\n";
    cout << "Enter (0) to stop searching.";
}

void Traveler::search()
{
    showPreferences();
    int choice;

    while (choice != 0)
    {
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
        case 8:
        {
            searchByDate();
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
            for (int j = 0; j < currentPlaces[i].daysofplace.size(); j++)
                currentPlaces[i].daysofplace[j].reserved = true;
            serializePlace(currentPlaces[i]);
            reservedPlace = currentPlaces[i];
            cout << "Please pay " << reservedPlace.generateTotalPrice() << " using: " << reservedPlace.paymentMethod;
            break;
        }
    }
}

void Traveler::viewBy() {} // sort based on different Place attributes (Tamer)

string Traveler::validateEmail(string email)
{
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
    return path;
}

bool Traveler::checkForCredintials(string email, string password)
{
    ifstream ifile;
    bool validated = false;
    ifile.open(email); // this is never closed.
    if (ifile)
    {
        string str;
        ifstream stream(email.c_str());
        getline(stream, str);
        validated = (str == password);
        stream.close();
    }
    return validated;
}

void Traveler::fillTravelerInfo(string path)
{
    ifstream stream(path.c_str());
    string placeHolderString; // Rest in Peace placeHolderString, gone but not forgotten
    getline(stream, this->password);
    getline(stream, this->firstName);
    getline(stream, this->lastName);
    getline(stream, this->email);
    getline(stream, placeHolderString); // born to find horrible code, forced to cope
    this->phone = stoi(placeHolderString);
    getline(stream, this->nationality);
    getline(stream, placeHolderString);
    this->gender = placeHolderString[0];
    getline(stream, placeHolderString);
    this->age = stoi(placeHolderString);
    deSerializePlaces();
}