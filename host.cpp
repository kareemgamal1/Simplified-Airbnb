#include "host.h"
#include "time.h"

// TODO: test this
void Host::signup()
{
    cout << "First name : ";
    cin >> firstName;
    cout << "Last name : ";
    cin >> lastName;
    cout << "E-mail: ";
    cin >> email; // validate email&password
    string path = "host/" + email + ".txt";
    ifstream ifile;
    ifile.open(path);
    while (ifile)
    {
        cout << "this E-Mail is already in use" << endl;
        cout << "E-mail: ";
        cin >> email;
        path = "host/" + email + ".txt";
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

    // for each new user, create a new file with it's email name
    // TODO: check email isn't already registered
    // repetitve code, make a serializeUser() function
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
void Host::login()
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
        string path = "host/" + em + ".txt";
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
void Host::serializePlace(Place p)
{
    // TODO: create serializePlace(Place p) function to add to advertisement registration,
    //  as an alternative to this redundance-heavy function
    //  TODO: test this
    string path = "/Places/" + to_string(p.ID) + ".txt";
    ofstream stream(path.c_str());
    stream << p.loc.country << endl;
    stream << p.loc.city << endl;
    stream << p.loc.streetName << endl;
    // todo: time serialization
    stream << p.view << endl;
    stream << p.paymentMethod << endl;
    stream << p.room << endl;
    // stream << p.reserved << endl; uncomment it after we handle reservation in place
    stream << p.pricePerDay << endl;
    stream << p.noOfRooms << endl;
    stream << p.ID << endl;
    stream.close();
}
void Host::addAdvertisement()
{
    int noOfAds;
    cout << "Enter how many advertisements you want to make:";
    cin >> noOfAds;
    for (int i = 0; i < noOfAds; i++)
    {
        cout << "Enter advertisement number: " << i + 1 << " information:\n";
        cout << "Enter advertisement type, Choose(1) for Apartment or Choose(2) for Room\n";
        // Time startDate, endDate;
        // cout << "Available from: ";
        // cin >> startDate;
        // cout << " to: ";
        // cin >> endDate;
        location loc;
        string view;
        string paymentMethod;
        bool room; // decides if the Place is a room or apartment
        int pricePerDay;
        int noOfRooms;
        int type;
        float discount = 0;
        char choice;
        cin >> type;
        if (type == 1)
        {
            room = false;
            cout << "Number of rooms: ";
            cin >> noOfRooms;
        }
        else if (type == 2)
            room = true;
        else
            cout << "Please enter a correct choice.\n";
        cout << "Country: ";
        cin >> loc.country;
        cout << "City: ";
        cin >> loc.city;
        cout << "Street name: ";
        cin >> loc.streetName;
        cout << "Price: ";
        cin >> pricePerDay;
        cout << "View:";
        cin >> view;
        cout << "Payment method: ";
        cin >> paymentMethod;
        cout << "Would you like to add a discount for stays that are over 3 nights?(y) or (n)";
        cin >> choice;
        if (choice == 'y')
        {
            cout << "Enter your discount in percentage: ";
            cin >> discount;
        }
        // we are adding the place to both the places of the host and the total places in the system.
        Place currentPlace = Place(loc, pricePerDay, view, room, noOfRooms, paymentMethod, discount);
        places.push_back(currentPlace);
        serializePlace(currentPlace);
    }
}
void Host::displayAdvertisements()
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
void Host::editAdvertisement()
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
void Host::deleteAdvertisement()
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

// Getters and Setters
vector<Place>
Host::getPlaces() // hashtable
{
    return this->places;
}
void Host::setPlaces(vector<Place> places)
{
    this->places = places;
}