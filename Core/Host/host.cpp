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
	login();
}

void Host::login()
{
	string em, pass;
	int num_tries = 0;
	bool validated = false;
	while (num_tries < 3 && !validated)
	{
		// cout << "Username : ";
		// cin >> em;
		// cout << "\nPassword : ";
		// cin >> pass;
		string temp;
		for (char c : em)
		{
			temp += (char)tolower(c);
		}
		em = temp; //email into lowercase
		em = "kg@mail.com";
		pass = "kkk";
		string path = "Data/host/" + em + ".txt";
		validated = checkForCredintials(path, pass);
		if (validated)
		{
			fillHostInfo(path);

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
				cout << "Please try again .\n";
				num_tries = 0;
				login();
			}
		}
	}
	showChoices();
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
		/*cout << "Enter advertisement type, Choose(1) for Apartment or Choose(2) for Room\n";
		cin >> type;*/
		type = 1;
		if (type == 1)
		{
			room = false;
			//cout << "Number of rooms: ";
			noOfRooms = 3;
			//cin >> noOfRooms;
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
		loc.country = "Egypt";
		loc.city = "cai";
		loc.streetName = "St";
		pricePerDay = 300;
		view = "Share3";
		paymentMethod = "cash";
		choice = 'n';
		/*cout << "Country: ";
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
		cin >> choice;*/
		if (choice == 'y')
		{
			cout << "Enter your discount in percentage: ";
			cin >> discount;
		}
		string hostEmail = this->email;
		cout << "hostdone" << endl;
		Place currentPlace;
		bool done = false;
		while (done == false) // infinite loop
		{
			try
			{
				cout << "please enter the start date";
				cout << "month:";
				cin >> startdate.month;
				cout << "day:";
				cin >> startdate.day;
				cout << "please enter the end date";
				cout << "month:";
				cin >> enddate.month;
				cout << "day:";
				cin >> enddate.day;
				currentPlace = Place(startdate, enddate);
				currentPlace.createTimeForPlace();
				currentPlace = Place(loc, pricePerDay, view, room, noOfRooms, paymentMethod, hostEmail, startdate, enddate, discount);
				currentPlace.createTimeForPlace();
				done = true;
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
		places[currentPlace.ID] = currentPlace;
		serializePlace(currentPlace);
	}
	showChoices();
}

void Host::editAdvertisement()
{
	displayAdvertisements();
	std::unordered_map<int, Place> ::iterator i;
	while (true)
	{
		cout << "Which advertisement would you like to edit? Please enter the advertisement's ID.\n";
		int advID;
		cin >> advID;
		i = places.find(advID);

		if (i == places.end())
			cout << "ID NOT FOUND";
		else {
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
				i->second.pricePerDay = newPrice;
				break;
			}
			case 2:
			{
				string newMethod;
				cout << "Enter your new payment method (cash or visa): ";
				cin >> newMethod;
				i->second.paymentMethod = newMethod;
				break;
			}
			// TODO: allow the user to edit more attributes (discount, how about date?)
			default:
				break;
			}
			serializePlace(i->second);
			break;
		}
	}
	showChoices();
}

void Host::deleteAdvertisement()
{
	displayAdvertisements();
	std::unordered_map<int, Place> ::iterator i;
	while (true)
	{
		cout << "Which advertisement would you like to delete? Please enter the advertisement's ID.\n";
		int advID;
		cin >> advID;
		i = places.find(advID);

		if (i == places.end())
			cout << "ID NOT FOUND";
		else
		{
			string toBeDeleted = "Data/place/" + this->email + "/" + to_string(i->second.ID) + ".txt";
			try
			{
				if (std::filesystem::remove(toBeDeleted))
				{
					cout << "Advertisement with ID: " << i->second.ID << " has been deleted.\n";
					places.erase(i->first);
					break;
				}
				else
				{
					std::cout << "file " << toBeDeleted << " not found.\n";
				}
			}
			catch (const std::filesystem::filesystem_error& err)
			{
				std::cout << "filesystem error: " << err.what() << '\n';
			}
		}
	}
	showChoices();
}

string Host::validateEmail(string email)
{
	string temp;
	for (char c : email)
	{
		temp += (char)tolower(c);
	}
	email = temp; // email into lowercase
	string path = "Data/traveller/" + email + ".txt";
	ifstream ifile(path);
	if (email.find('@') == std::string::npos)
	{
		cout << "this E-Mail must contain a domain" << endl;
		cout << "E-mail: ";
		string mail;
		cin >> mail;
		ifile.close();
		return validateEmail(mail);
	}
	else if (email.substr(email.length() - 4, 4) != ".com")
	{
		cout << "this E-Mail must end in .com suffix" << endl;
		cout << "E-mail: ";
		string mail;
		cin >> mail;
		ifile.close();
		return validateEmail(mail);
	}
	if (ifile.is_open())
	{
		cout << "this E-Mail is already in use" << endl;
		cout << "E-mail: ";
		string mail;
		cin >> mail;
		ifile.close();
		return validateEmail(mail);
	}
	return path;
}

void Host::displayAdvertisements()
{
	cout << "\nAdvertisements: \n\n";
	for (auto i : places)
	{
		cout << "===============================\n";
		cout << "Advertisement ID:" << i.second.ID << '\n';
		i.second.room ? cout << "Room.\n" : cout << "Apartment.\n";
		cout << "Location:" << i.second.loc.country << ' ' << i.second.loc.city << ' ' << i.second.loc.streetName << '\n';
		cout << "Price: " << i.second.pricePerDay << '\n';
		cout << "View:" << i.second.view << '\n';
		cout << "Payment method: " << i.second.paymentMethod << "\n";
		cout << "===============================\n\n\n";
	}
}

void Host::serializePlace(Place p)
{
	string folder = "Data/place/" + this->email;
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
		stream << p.daysofplace[i].userreserve << endl;
		stream << endl;
	}
	stream.close();
}

void Host::deSerializePlaces()
{
	string path = "Data/place/" + this->email;
	if (!std::filesystem::exists(path))
		return;
	try
	{
		for (const auto& entry : filesystem::directory_iterator(path))
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
			// reserved = (x == "1"); //Fully reserved.
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

			Place currentPlace = Place(ID, loc, pricePerDay, view, room, noOfRooms, paymentMethod, hostEmail, startDate, endDate, discount); /// It's supposed to work without providing the discount as it's a defeault argument
			currentPlace.availableduration = availableduration;
			int i = 0;
			timereserve t;
			while (getline(stream, x))
			{

				if (i < 4)
				{
					if (i == 0)
						t.day = stoi(x);
					else if (i == 1)
						t.month = stoi(x);
					else if (i == 2)
						t.reserved = (x == "1");
					else
						t.userreserve = x;
					i++;
				}
				else
				{
					i = 0;
					currentPlace.daysofplace.push_back(t);
				}
			}
			places[currentPlace.ID] = currentPlace;
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
	cout << "\n\n-Choose (1) to add a new Advertisement\n-Choose (2) to edit an advertisement\n-Choose (3) to delete an advertisement\n choose 4 to display information about specific place \n -Choose (0) to end the program.\n";
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
	case 4:
	{
		showSpecificPlace();
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
	this->phone = stoi(placeHolderString);
	getline(stream, this->nationality);
	getline(stream, placeHolderString);
	this->gender = placeHolderString[0];
	getline(stream, placeHolderString);
	this->age = stoi(placeHolderString);
	deSerializePlaces();
}

void Host::showSpecificPlace() {
	int id;
	displayAdvertisements();
	cout << " please enter the id of place you want";
	cin >> id;
	std::unordered_map<int, Place> ::iterator i;
	i = places.find(id);
	if (i == places.end())
		cout << "ID NOT FOUND";
	else
		for (int j = 0; j < i->second.daysofplace.size(); j++)
			cout << " Date : " << i->second.daysofplace[j].day << "/" << i->second.daysofplace[j].month << " \t reserver : " << i->second.daysofplace[j].userreserve << endl;
	showChoices();
}