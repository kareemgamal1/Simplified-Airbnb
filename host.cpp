#include "host.h"
using namespace std;

void Host::signup()
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
void Host::login()
{
	string em, pass;
	int num_tries = 0;
	bool validated = false;
	while (num_tries < 3 && !validated)
	{
		cout << "Username : ";
		cin >> em;
		cout << "\nPassword : ";
		cin >> pass;
		em = "kg@zeby.com";
		pass = "kkk";
		string path = "host/" + em + ".txt";
		validated = checkForCredintials(path, pass);
		if (validated)
		{
			fillHostInfo(path);
			showChoices();
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
		cout << "Enter advertisement number: " << i + 1 << " information:\n";
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
		int pricePerDay;
		int discount = 0;
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
		string hostEmail = this->email;
		cout << "hostdone" << endl;
		Place currentPlace;
		while (true)
		{
			try
			{
				// TODO:: try catch for 30th of Feb case
				cout << "please enter the start date";
				cout << "month:";
				cin >> startdate.day;
				cout << "day:";
				cin >> startdate.month;
				cout << "please enter the end date";
				cout << "month:";
				cin >> enddate.day;
				cout << "day:";
				cin >> enddate.month;
				currentPlace = Place(loc, pricePerDay, view, room, noOfRooms, paymentMethod, hostEmail, startdate, enddate, discount);
				currentPlace.createTimeForPlace();
			}
			catch (std::exception e)
			{
				continue;
			}
			break;
		}
		// we are adding the place to both the places of the host and the total places in the system.
		cout << "constructor" << endl;
		cout << "time done" << endl;
		places.push_back(currentPlace);
		serializePlace(currentPlace);
	}
}

void Host::editAdvertisement()
{
	displayAdvertisements();
	cout << "Which advertisement would you like to edit? Please enter the advertisement's ID.\n";
tryAgain:
	int index = -404;
	int advID;
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
		cout << "\nPlease enter a correct ID.\n\n";
		goto tryAgain; // a price to pay for salvation
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
	// TODO: allow the user to edit more attributes (discount, how about date?)
	default:
		break;
	}
	serializePlace(places[index]);
}

void Host::deleteAdvertisement()
{
	displayAdvertisements();
	cout << "Which advertisement would you like to delete? Please enter the advertisement's ID.\n";
tryAgain:
	int index = -404;
	int advID;
	cin >> advID;

	for (int i = 0; i < places.size(); i++)
	{
		if (places[i].ID == advID)
		{
			index = i;
			string toBeDeleted = "place/" + this->email + "/" + to_string(places[i].ID) + ".txt";
			try
			{
				if (std::filesystem::remove(toBeDeleted))
				{
					cout << "Advertisement with ID: " << places[i].ID << " has been deleted.\n";
					places.erase(places.begin() + i);
				}
				else
				{
					std::cout << "file " << toBeDeleted << " not found.\n";
				}
			}
			catch (const std::filesystem::filesystem_error &err)
			{
				std::cout << "filesystem error: " << err.what() << '\n';
			}
			break;
		}
	}
	if (index == -404)
	{
		cout << "\nPlease enter a correct ID.\n\n";
		goto tryAgain; // a price to pay for salvation
	}
}

string Host::validateEmail(string email)
{
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
	return path;
}

void Host::displayAdvertisements()
{
	cout << "\nAdvertisements: \n\n";
	for (int i = 0; i < places.size(); i++)
	{
		cout << "===============================\n";
		cout << "Advertisement ID:" << places[i].ID << '\n';
		places[i].room ? cout << "Room.\n" : cout << "Apartment.\n";
		cout << "Location:" << places[i].loc.country << ' ' << places[i].loc.city << ' ' << places[i].loc.streetName << '\n';
		cout << "Price: " << places[i].pricePerDay << '\n';
		cout << "View:" << places[i].view << '\n';
		cout << "Payment method: " << places[i].paymentMethod << "\n";
		cout << "===============================\n\n\n";
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
	stream << p.view << endl;
	stream << p.paymentMethod << endl;
	stream << p.room << endl;
	// stream << p.reserved << endl; uncomment it after we handle reservation in place
	stream << p.pricePerDay << endl;
	stream << p.noOfRooms << endl;
	stream << p.discount << endl;
	stream << p.ID << endl;
	stream << p.hostEmail << endl;
	stream << p.startDate.day << endl;
	stream << p.startDate.month << endl;
	stream << p.endDate.day << endl;
	stream << p.endDate.month << endl;
	stream << p.availableduration << endl;
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
	string path = "place/" + this->email;
	if (!std::filesystem::exists(path))
		return;
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
			places.push_back(p);
			stream.close();
		}
	}
	catch (exception e)
	{
		cout << e.what();
		cout << "ERROR" << endl;
		// oh no, there's no directory for this host, anyways..
	}
}

void Host::showChoices()
{
	cout << "\n\n-Choose (1) to add a new Advertisement\n-Choose (2) to edit an advertisement\n-Choose (3) to delete an advertisement\n-Choose (0) to end the program.\n";
tryAgain:
	int choice;
	cin >> choice;
	switch (choice)
	{
	case 0:
	{
		cout << "Thank you for using our app.\n";
		return;
	}
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
	default:
		cout << "Enter a correct number.\n";
		goto tryAgain; // a price to pay for salvation
	}
}

bool Host::checkForCredintials(string email, string password)
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

void Host::fillHostInfo(string path)
{
	ifstream stream(path.c_str());
	string placeHolderString; // Rest in Peace placeHolderString, gone but not forgotten
	getline(stream, this->password);
	getline(stream, this->firstName);
	getline(stream, this->lastName);
	getline(stream, this->email);
	getline(stream, placeHolderString); // born to find horrible code, forced to cope
	this->phone = (placeHolderString);
	getline(stream, this->nationality);
	getline(stream, placeHolderString);
	this->gender = placeHolderString[0];
	getline(stream, placeHolderString);
	this->age = stoi(placeHolderString);
	deSerializePlaces();
}