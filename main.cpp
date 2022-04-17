#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

struct location
{
    string country;
    string city;
    string streetName;
};

struct Place
{
    int ID;
    location loc;
    int pricePerDay;
    string view;
    string paymentMethod;
    bool room; // decides if the Place is a room or apartment
    bool reserved;
    int noOfRooms;
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

        ofstream boba("heyo.txt");
        boba << "hewwo!" << endl;
        boba << "hewwo!" << endl;
        boba.close();
    }

    void login()
    {
        string em, pass;
        int p, num_tries = 0;
        bool validated = false;
        while (num_tries < 3)
        {
            cout << "Username : ";
            cin >> em;
            cout << "\nPassword : ";
            // cin >> pass;
            // for (int i = 0; i < TempArr.size(); i++) // in order to access all users, we should put them in a file first and then iterate over that file
            // {
            //     if (em == TempArr.email)
            //     {
            //         if (p == TempArr.Password)
            //         {
            //             validated = true;
            //             break;
            //         }
            //     }
            // }
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
    void addAdvertisement();
    void editAdvertisement();
    void deleteAdvertisement();

    // Getters and Setters
    vector<Place> getPlaces() // hashtable
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
    Host kareem;
    kareem.signup();
}
