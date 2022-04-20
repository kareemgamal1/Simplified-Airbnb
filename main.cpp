#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <filesystem>
using namespace std;
struct location
{
    string country;
    string city;
    string streetName;
};

struct Time
{
    int time_mday; // day of month from 1 to 31
    int time_mon;  // month of year from 0 to 11
    int time_year; // year since 1900
};
class timePeriod
{
public:
    bool includesDate(Time t);
    bool includesPeriod();
};

class Place
{
public:
    location loc;
    Time startDate, endDate;
    string view;
    string paymentMethod;
    bool room; // decides if the Place is a room or apartment
    bool reserved = false;
    int pricePerDay;
    int noOfRooms;
    int ID;
    static int noOfPlaces;

    // Incomplete constructor, number of rooms and reservation status
    // also fixed order of entry to correspond to class
    // TODO: add time to constructor
    Place(location loc, string view, string paymentMethod, bool room, bool reserved, int noOfRooms, int pricePerDay)
    {
        noOfPlaces++;
        ID = noOfPlaces + 1;
        this->loc = loc;
        this->view = view;
        this->paymentMethod = paymentMethod;
        this->room = room;
        this->reserved = reserved;
        this->noOfRooms = noOfRooms;
        this->pricePerDay = pricePerDay;
    }
};

class User
{
protected:
    string firstName;
    string lastName;
    string email;
    string password;
    string nationality;
    char gender;
    int phone;
    int age;

public:
    void signup();
    void login();

    // Getters and Setters
    string getFirstName()
    {
        return this->firstName;
    }
    void setFirstName(string firstName)
    {
        this->firstName = firstName;
    }
    string getLastName()
    {
        return this->lastName;
    }
    void setLastName(string lastName)
    {
        this->lastName = lastName;
    }
    string getEmail()
    {
        return this->email;
    }
    void setEmail(string email)
    {
        this->email = email;
    }
    string getPassword()
    {
        return this->password;
    }
    void setPassword(string password)
    {
        this->password = password;
    }
    string getNationality()
    {
        return this->nationality;
    }
    void setNationality(string nationality)
    {
        this->nationality = nationality;
    }
    char getGender()
    {
        return this->gender;
    }
    void setGender(char gender)
    {
        this->gender = gender;
    }
    int getAge()
    {
        return this->age;
    }
    void setAge(int age)
    {
        this->age = age;
    }
};

class traveler : public User
{
    string startDate;
    string endDate;
    location loc;
    int stayDuration;
    int priceRangeStart;
    int priceRangeEnd;

public:
    // vector to hold all Places, and check for each element if it satisfies every attribute we search with
    // another vector to hold the Places which satisfy the conditions

    //TODO: test this
    void signup()
    {
        cout << "First name : ";
        cin >> firstName;
        cout << "Last name : ";
        cin >> lastName;
        cout << "E-mail: ";
        cin >> email; // validate email&password
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

        // TODO: check email isn't already registered
        // repetitve code, make a serializeUser() function
        string path = "/travelers/" + email + ".txt";
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
    // Aly
    void login()
    {
        // TODO: test this
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
            
            string path = "/travelers/" + em + ".txt";
            if (filesystem::exists(path))
            {
                string str;
                ifstream stream(path.c_str());
                getline(stream, str);
                validated = (str == pass);
            }

            if (validated)
            {
                cout << "\n\n\n-Choose (1) to add a new Advertisement\t,\tChoose (2) to edit an advertisement\tor Choose (3) to delete an advertisement\n";
                int choice;
                cin >> choice;
                switch (choice)
                {
                case 1:
                {
                    break;
                }
                case 2:
                {
                    break;
                }
                case 3:
                {
                    break;
                }
                }

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

    Place searchByType(string type);
    Place searchByLocation(location loc);
    Place searchByView(string view);
    Place searchByPriceRange(int priceRangeStart, int priceRangeEnd);
    Place searchByPaymentMethod(string paymentMethod);
    Place searchByNoOfRooms(int noOfRooms);
    Place searchByDuration(string startDate, string endDate);
    Place search(); // will contain all the above functions, narrowing it down, if at any choice there are no Places available, it will be shown to the traveler
    void choosePlace(Place place);
    int generateDiscount();   // if there is a discount for travelers who stay for over 3 nights, generate it based on that apartment
    int generateTotalPrice(); // total price for the no of days the traveler will stay for
    void viewBy();            // sort based on different Place attributes

    // Getters and Setters
    string getStartDate()
    {
        return this->startDate;
    }
    void setStartDate(string startDate)
    {
        this->startDate = startDate;
    }
    string getEndDate()
    {
        return this->endDate;
    }
    void setEndDate(string endDate)
    {
        this->endDate = endDate;
    }
    int getStayDuration()
    {
        return this->stayDuration;
    }
    void setStayDuration(int stayDuration)
    {
        this->stayDuration = stayDuration;
    }
    location getLoc()
    {
        return this->loc;
    }
    void setLoc(location loc)
    {
        this->loc = loc;
    }
    int getPriceRangeStart()
    {
        return this->priceRangeStart;
    }
    void setPriceRangeStart(int priceRangeStart)
    {
        this->priceRangeStart = priceRangeStart;
    }
    int getPriceRangeEnd()
    {
        return this->priceRangeEnd;
    }
    void setPriceRangeEnd(int priceRangeEnd)
    {
        this->priceRangeEnd = priceRangeEnd;
    }
};

class Host : public User
{
    vector<Place> places; // vector

public:
    // Aly
    //TODO: test this
    void signup()
    {
        cout << "First name : ";
        cin >> firstName;
        cout << "Last name : ";
        cin >> lastName;
        cout << "E-mail: ";
        cin >> email; // validate email&password
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

        // for each new user, create a new file with it's email name
        // TODO: check email isn't already registered
        // repetitve code, make a serializeUser() function 
        string path = "/hosts/" + email + ".txt";
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
    // Aly
    //TODO: test this
    void login()
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
            string path = "/hosts/" + em + ".txt";
            if (filesystem::exists(path))
            {
                string str;
                ifstream stream(path.c_str());
                getline(stream, str);
                validated = (str == pass);
            }

            if (validated)
            {
                cout << "\n\n\n-Choose (1) to add a new Advertisement\t,\tChoose (2) to edit an advertisement\tor Choose (3) to delete an advertisement\n";
                int choice;
                cin >> choice;
                switch (choice)
                {
                case 1:
                {
                    addAdvertisement();
                    break;
                }
                case 2:
                {
                    editAdvertisement();
                    break;
                }
                case 3:
                {
                    deleteAdvertisement();
                    break;
                }
                }

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
    // TODO: conform this to new Place consturctor:: Karim
    void addAdvertisement()
    {
        int noOfAds;
        cout << "Enter how many advertisements you want to make:";
        cin >> noOfAds;
        for (int i = 0; i < noOfAds; i++)
        {
            cout << "Enter advertisement number: " << i + 1 << " information:\n";
            cout << "Enter advertisement type, Choose(1) for Apartment or Choose(2) for Room\n";
            int type;
            cin >> type;
            // Dangerous code, overwrites prevous entries in places[]
            if (type == 1)
                places[i].room = false;
            else if (type == 2)
                places[i].room = true;
            else
                cout << "Please enter a correct choice.\n";
            cout << "Country: ";
            cin >> places[i].loc.country;
            cout << "City: ";
            cin >> places[i].loc.city;
            cout << "Street name: ";
            cin >> places[i].loc.streetName;
            cout << "Price: ";
            cin >> places[i].pricePerDay;
            cout << "View:";
            cin >> places[i].view;
            cout << "Payment method: ";
            cin >> places[i].paymentMethod;
            // So you alter an existing entry in places[], overwriting it with a new entry
            // THEN you add THE SAME ENTRY into the back of the array
            // Place currentPlace = Place(places[i].loc, places[i].pricePerDay, places[i].view, places[i].paymentMethod, places[i].room);
            // places.push_back(currentPlace); //COMMENTED OUT to prevent errors
        }
    }
    // Kareem
    void displayAdvertisements()
    {
        for (int i = 0; i < places.size(); i++)
        {
            cout << "Advertisements: \n";
            cout << "Advertisement ID:" << places[i].ID << '\n';
            places[i].room ? cout << "Room.\n" : cout << "Apartment.\n";
            cout << "Location:" << places[i].loc.country << ' ' << places[i].loc.city << ' ' << places[i].loc.streetName << '\n';
            cout << "Price: " << places[i].pricePerDay << '\n';
            cout << "View:" << places[i].view << '\n';
            cout << "Payment method: " << places[i].paymentMethod;
        }
    }
    void editAdvertisement()
    {
        displayAdvertisements();
        int index;
        int advID;
        cout << "Which advertisement would you like to edit? Please enter the advertisement's ID.\n";
        cin >> advID;
        for (int i = 0; i < places.size(); i++)
        {
            if (places[i].ID == advID)
            {
                index = i;
                break;
            }
        }
        cout << "What would you like to edit? Choose(1) for price or Choose(2) for payment method";
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            int newPrice;
            cout << "Enter your new price: ";
            cin >> newPrice;
            places[index].pricePerDay = newPrice;
            break;
        }
        case 2:
        {
            string newMethod;
            cout << "Enter your new payment method (cash or visa): ";
            cin >> newMethod;
            places[index].paymentMethod = newMethod;
            break;
        }

        default:
            break;
        }
    }

    void deleteAdvertisement()
    {
        displayAdvertisements();
        int advID;
        cout << "Which advertisement would you like to delete? Please enter the advertisement's ID.\n";
        cin >> advID;
        for (int i = 0; i < places.size(); i++)
        {
            if (places[i].ID == advID)
            {
                places.erase(places.begin() + i);
                cout << "Advertisement with ID: " << places[i].ID << " has been deleted.\n";
                break;
            }
        }
    }
    // Aly
    void serializePlaces()
    {
        // TODO: create serializePlace(Place p) function to add to advertisement registration,
        // as an alternative to this redundance-heavy function
        //  TODO: test this
        for (Place x : places)
        {
            string path = "/Places/" + to_string(x.ID) + ".txt";
            ofstream stream(path.c_str());
            stream << x.loc.country << endl;
            stream << x.loc.city << endl;
            stream << x.loc.streetName << endl;
            // todo: time serialization
            stream << x.view << endl;
            stream << x.paymentMethod << endl;
            stream << x.room << endl;
            stream << x.reserved << endl;
            stream << x.pricePerDay << endl;
            stream << x.noOfRooms << endl;
            stream << x.ID << endl;
            stream.close();
        }
    }
    void deSerializePlaces()
    {
        // TODO: test this
        string path = "/places";
        for (const auto &entry : filesystem::directory_iterator(path.c_str()))
        {
            ifstream stream(entry.path());
            string x;
            location l;
            string view;
            string paymentMethod;
            bool room;
            bool reserved;
            int pricePerDay;
            int noOfRooms;
            int ID;
            getline(stream, x);
            l.country = x;
            getline(stream, x);
            l.city = x;
            getline(stream, x);
            l.streetName = x;
            getline(stream, x);
            view = x;
            getline(stream, x);
            paymentMethod = x;
            getline(stream, x);
            room = (x == "true");
            getline(stream, x);
            reserved = (x == "true");
            getline(stream, x);
            pricePerDay = stoi(x);
            getline(stream, x);
            noOfRooms = stoi(x);
            stream.close();
            Place p = Place(l, view, paymentMethod, room, reserved, noOfRooms, pricePerDay);
        }
    }
    // Getters and Setters
    vector<Place>
    getPlaces() // hashtable
    {
        return this->places;
    }
    void setPlaces(vector<Place> places)
    {
        this->places = places;
    }
};

class admin
{
    vector<Host> hosts;         // hash table
    vector<traveler> travelers; // hash table

public:
    void declare()
    {
        // 3 hosts each having 2 places, 3 travelers.
    }
    void createTraveler();
    void createHost();
    void generateDashboard();

    void addAdvertisement();
    void editAdvertisement();
    void deleteAdvertisement();
    Place searchByType(string type);
    Place searchByLocation(location loc);
    Place searchByView(string view);
    Place searchByPriceRange(int priceRangeStart, int priceRangeEnd);
    Place searchByPaymentMethod(string paymentMethod);
    Place searchByNoOfRooms(int noOfRooms);
    Place searchByDuration(string startDate, string endDate);
    Place search();

    // Getters and Setters
    vector<Host> getHosts()
    {
        return this->hosts;
    }
    void setHosts(vector<Host> hosts)
    {
        this->hosts = hosts;
    }
    vector<traveler> getTravelers()
    {
        return this->travelers;
    }
    void setTravelers(vector<traveler> travelers)
    {
        this->travelers = travelers;
    }
};

int main()
{
}