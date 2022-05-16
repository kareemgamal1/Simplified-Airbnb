#include "host.h"
#include "time.h"
#include <filesystem>
using namespace std;

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
	// repetitve code, make a serializeUser() function in User.cpp and call it here
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
		ifile.open(path); // this is never closed.
		if (ifile)
		{
			string str;
			ifstream stream(path.c_str());
			getline(stream, str);
			validated = (str == pass);
			stream.close();
		}

		if (validated)
		{
			ifstream stream(path.c_str());
			string placeHolderString; // Rest in Peace placeHolderString, gone but not forgotten
			// set user to stuff in file::
			getline(stream, this->password);
			getline(stream, this->firstName);
			getline(stream, this->lastName);
			getline(stream, this->email);
			getline(stream, placeHolderString); // born to find horrible code, forced to cope
			this->phone = stoi(placeHolderString);
			getline(stream, this->nationality);
			getline(stream, placeHolderString);
			this->gender = placeHolderString[0]; // string to char
			getline(stream, placeHolderString);
			this->age = stoi(placeHolderString); // string to int
			deSerializePlaces();
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
				cout << "You have: " << 3 - (num_tries + 1) << "| tries to enter\n";
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
	string folder = "place/" + this->email;
	filesystem::create_directory(folder);
	string path = folder + '/' + to_string(p.ID) + ".txt";
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
	stream << p.hostEmail << endl;
	stream << p.startDate.day << endl;
	stream << p.startDate.month << endl;
	stream << p.endDate.day << endl;
	stream << p.endDate.month << endl;
	// p.createTimeForPlace();
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
void Host::deSerializePlaces()
{
	// TODO: test this
	string path = "place/" + this->email;
	// gives error: path not found
	cout << path;
	try
	{
		for (const auto &entry : filesystem::directory_iterator(path))
		{
			ifstream stream(entry.path());
			timereserve startDate, endDate;
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
			// getline(stream, x);
			// discount = (float)stoi(x);
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
			Place p = Place(loc, pricePerDay, view, room, noOfRooms, paymentMethod, hostEmail, startDate, endDate, 0); /// It's supposed to work without providing the discount as it's a defeault argument
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
			places.push_back(p);
			stream.close();
		}
	}
	catch (exception e)
	{
		cout << "ERROR" << endl;
		// oh no, there's no directory for this host, anyways..
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

void Host::addAdvertisement()
{
	int noOfAds;
	int noOfRooms = 0;
	int type;
	bool room = true; // decides if the Place is a room or apartment
	cout << "Enter how many advertisements you want to make:";
	cin >> noOfAds;
	Place p;
	for (int i = 0; i < noOfAds; i++)
	{
		cout << "Enter advertisement number: " << i << " information:\n";
		cout << "Enter advertisement type, Choose(1) for Apartment or Choose(2) for Room\n";
		cin >> type;
		if (type == 1)
		{
			room = false;
			cout << "Number of rooms: ";
			cin >> noOfRooms;
		}
		else if (type == 2)
		{
			room = true;
			cout << "Number of rooms with this specifications: "; // for hostels.
			cin >> noOfRooms;
		}
		else
		{
			cout << "Please enter a correct choice.\n";
			i--;
			continue;
		}
		timereserve startdate, enddate;
		location loc;
		string view;
		string paymentMethod;
		bool room = true; // decides if the Place is a room or apartment
		int pricePerDay = 0;
		int noOfRooms = 0;
		int type;
		float discount = 0;
		char choice;

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
		cout << "please enter the start date";
		cin >> startdate.day >> startdate.month;
		cout << "please enter the end date";
		cin >> enddate.day >> enddate.month;
		cout << "datedone" << endl;
		// we are adding the place to both the places of the host and the total places in the system.
		string hostEmail = this->email;
		cout << "hostdone" << endl;
		Place currentPlace = Place(loc, pricePerDay, view, room, noOfRooms, paymentMethod, hostEmail, startdate, enddate, 0);
		cout << "constructor" << endl;
		currentPlace.createTimeForPlace();
		cout << "time done" << endl;
		places.push_back(currentPlace);
		serializePlace(currentPlace);
	}
}

void Host::editAdvertisement()
{
	displayAdvertisements();
	int index = -404;
	int advID;
	// does the host know this??
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
	if (index == -404)
	{
		cout << "Please enter a correct ID.";
		editAdvertisement();
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
	serializePlace(places[index]);
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
			string toBeDeleted = "place/" + this->email + "/" + to_string(places[i].ID) + ".txt";
			cout << endl
				 << toBeDeleted << endl;
			// cout << "Advertisement with ID: " << places[i].ID << " has been deleted.\n";
			try
			{
				if (std::filesystem::remove(toBeDeleted))
					std::cout << "file " << toBeDeleted << " deleted.\n";
				else
					std::cout << "file " << toBeDeleted << " not found.\n";
			}
			catch (const std::filesystem::filesystem_error &err)
			{
				std::cout << "filesystem error: " << err.what() << '\n';
			}
			break;
		}
	}
}
