#include "traveler.h"
#include "../User/user.h"
#include "../Place/place.h"
#include <filesystem>

int queryNumber = 0;

void Traveler::signup()
{
	std::cout << "First name : ";
	std::cin >> firstName;
	std::cout << "Last name : ";
	std::cin >> lastName;
	std::cout << "E-mail: ";
	std::cin >> email;
	string path = validateEmail(email); // if the email is not in use, return its newly created path
	std::cout << "Password : ";
	std::cin >> password;
	std::cout << "Phone : ";
	std::cin >> phone;
	std::cout << "Nationality :";
	std::cin >> nationality;
	std::cout << "Gender : ";
	std::cin >> gender;
	std::cout << "Age : ";
	std::cin >> age;
	serializeUser(path);
}

void Traveler::login()
{
	string em, pass;
	int num_tries = 0;
	bool validated = false;
	while (num_tries < 3 && !validated)
	{
		//std::cout << "Username : ";
		//std::cin >> em;
		string temp;
		for (char c : email)
		{
			temp += (char)tolower(c);
		}
		em = temp;//email into lowercase
		//std::cout << "\nPassword : ";
		//std::cin >> pass;
		em = "A@mail";
		pass = "1";
		string path = "Data/traveller/" + em + ".txt";
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
				std::cout << "The password or username you entered is incorrect. \n";
				std::cout << "You have: " << 3 - (num_tries + 1) << "| tries to enter\n";
				num_tries++;
				std::cout << "Please try again.\n";
			}
			else
			{
				std::cout << "Please try again after 1 minute.\n";
				num_tries = 0;
				login();
			}
		}
	}
	search();
}

void Traveler::serializePlace(Place p)
{
	string folder = "Data/place/" + p.hostEmail;
	filesystem::create_directory(folder);
	string path = folder + "/" + to_string(p.ID) + ".txt";
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
	std::cout << "SIZE: " << p.daysofplace.size() << endl;
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

void Traveler::deSerializePlaces()
{
	string path = "Data/place";
	for (const auto& host_directory_entry : filesystem::directory_iterator(path))
	{
		string host_name_path = host_directory_entry.path().string();
		for (const auto& place_directory_entry : filesystem::directory_iterator(host_name_path))
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
			allPlaces[currentPlace.ID] = currentPlace;
			stream.close();
		}
	}
}

void Traveler::restartAll()
{
	queryNumber = 0;
	search();

}

void Traveler::endProgram()
{
	std::cout << "Thank you for using our program.\n";
	exit(0);
}

void Traveler::displayAll()
{
	if (currentPlaces.size() == 0)
	{
		std::cout << "\nThere are no matching advertisements.\nWould you like to restart the searching process?y/n";
		char choice;
		std::cin >> choice;
		tolower(choice) == 'y' ? restartAll() : endProgram();
	}
	std::cout << "\nAdvertisements: \n\n";
	for (auto i : currentPlaces) {
		cout << "===============================\n";
		cout << "Advertisement ID:" << i.first << '\n';
		i.second.room ? cout << "Room.\n" : cout << "Apartment.\n";
		cout << "Location:" << i.second.loc.country << ' ' << i.second.loc.city << ' ' << i.second.loc.streetName << '\n';
		cout << "Price: " << i.second.pricePerDay << '\n';
		cout << "View:" << i.second.view << '\n';
		cout << "Payment method: " << i.second.paymentMethod << "\n";
		cout << "===============================\n\n\n";
	}
}

unordered_map<int, Place> Traveler::chooseContainer()
{
	return (queryNumber == 0) ? allPlaces : currentPlaces;
}

void Traveler::searchByType()
{
	int choice;
	bool room;
	std::cout << "Enter (1) for apartment or (2) for room.";
	std::cin >> choice;
	// choice = 2;
	room = (choice == 2);
	unordered_map<int, Place> currentContainer = chooseContainer();
	unordered_map<int, Place>::iterator i;
	for (i = currentContainer.begin(); i != currentContainer.end();)
	{
		if (i->second.room != room)
		{
			i = currentContainer.erase(i);
			//i--;
		}
		else
			i++;
	}
	currentPlaces = currentContainer;
	displayAll();
	queryNumber++;
}

void Traveler::searchByCountry()
{
	string country;
	std::cout << "Country: ";
	std::cin >> country;
	unordered_map<int, Place> currentContainer = chooseContainer();
	unordered_map<int, Place>::iterator i;
	for (i = currentContainer.begin(); i != currentContainer.end(); i++)
	{
		if (i->second.loc.country != country)
		{
			i = currentContainer.erase(i);
		}
	}
	currentPlaces = currentContainer;
	queryNumber++;
	displayAll();
}

void Traveler::searchByCity()
{
	string city;
	std::cout << "City: ";
	std::cin >> city;
	unordered_map<int, Place> currentContainer = chooseContainer();
	unordered_map<int, Place>::iterator i;
	for (i = currentContainer.begin(); i != currentContainer.end();)
	{
		if (i->second.loc.city != city)
		{
			i = currentContainer.erase(i);
		}
		else
			i++;
	}
	currentPlaces = currentContainer;
	queryNumber++;
	displayAll();
}
void Traveler::searchByStreet()
{
	string streetName;
	std::cout << "Street name: ";
	std::cin >> streetName;
	unordered_map<int, Place> currentContainer = chooseContainer();
	unordered_map<int, Place>::iterator i;
	for (i = currentContainer.begin(); i != currentContainer.end();)
	{
		if ((i->second).loc.streetName != streetName)
		{
			i = currentContainer.erase(i);
		}
		else
			i++;
	}
	currentPlaces = currentContainer;
	queryNumber++;
	displayAll();
}

void Traveler::searchByLocation()
{
	std::cout << "(1)Country\n(2)City\n(3)Street Name\n(0)to stop searching.\n";
	int locationChoice;
	std::cin >> locationChoice;
	while (locationChoice != 0)
	{
		switch (locationChoice)
		{
		case 1:
		{
			searchByCountry();
			break;
		}
		case 2:
		{
			searchByCity();
			break;
		}
		case 3:
		{
			searchByStreet();
			break;
		}
		}
		std::cout << "(1)Country\n(2)City\n(3)Street Name\n(0)to stop searching by location.\n";
		std::cin >> locationChoice;
		/*searchByCountry();
		searchByCity();
		searchByStreet();*/
	}
}

void Traveler::searchByView()
{
	string view;
	std::cout << "View: ";
	std::cin >> view;
	unordered_map<int, Place> currentContainer = chooseContainer();
	unordered_map<int, Place>::iterator i;
	for (i = currentContainer.begin(); i != currentContainer.end(); i)
	{
		if (i->second.view != view)
		{
			i = currentContainer.erase(i);
		}
		else
			i++;
	}
	currentPlaces = currentContainer;
	queryNumber++;
	displayAll();
}

void Traveler::searchByPriceRange()
{
	int priceRangeStart, priceRangeEnd;
	std::cout << "Price from: ";
	std::cin >> priceRangeStart;
	std::cout << "To: ";
	std::cin >> priceRangeEnd;
	unordered_map<int, Place> currentContainer = chooseContainer();
	unordered_map<int, Place>::iterator i;
	for (i = currentContainer.begin(); i != currentContainer.end();)
	{
		if (i->second.pricePerDay < priceRangeStart || i->second.pricePerDay > priceRangeEnd)
		{
			i = currentContainer.erase(i);
		}
		else
			i++;
	}
	currentPlaces = currentContainer;
	queryNumber++;
	displayAll();
}

void Traveler::searchByPaymentMethod()
{
	string paymentMethod;
	std::cout << "Payment method: ";
	std::cin >> paymentMethod;
	unordered_map<int, Place> currentContainer = chooseContainer();
	unordered_map<int, Place>::iterator i;
	for (i = currentContainer.begin(); i != currentContainer.end();)
	{
		if (i->second.paymentMethod != paymentMethod)
		{
			i = currentContainer.erase(i);
		}
		else
			i++;
	}
	currentPlaces = currentContainer;
	queryNumber++;
	displayAll();
}

void Traveler::searchByNoOfRooms()
{
	// available only if it's an apartment.
	int noOfRooms;
	std::cout << "Number of rooms: ";
	std::cin >> noOfRooms;
	unordered_map<int, Place> currentContainer = chooseContainer();
	unordered_map<int, Place>::iterator i;
	for (i = currentContainer.begin(); i != currentContainer.end();)
	{
		if (i->second.noOfRooms != noOfRooms && !i->second.room)
		{
			i = currentContainer.erase(i);
		}
		else
			i++;
	}
	currentPlaces = currentContainer;
	queryNumber++;
	displayAll();
}
void Traveler::searchByDuration()
{
	int duration;
	std::cout << "enter duration ";
	std::cin >> duration;
	unordered_map<int, Place> currentContainer = chooseContainer();
	unordered_map<int, Place>::iterator i;
	for (i = currentContainer.begin(); i != currentContainer.end();)
	{
		if (i->second.availableduration <= duration)
		{
			i = currentContainer.erase(i);
		}
		else
			i++;
	}
	currentPlaces = currentContainer;
	queryNumber++;
	displayAll();
}

void Traveler::searchByDate()
{
	timereserve startdateofuser, enddateofuser;
	std::cout << "please enter start date\n";
	std::cin >> startdateofuser.day >> startdateofuser.month;
	std::cout << "please enter end date\n";
	std::cin >> enddateofuser.day >> enddateofuser.month;
	unordered_map<int, Place> currentContainer = chooseContainer();
	unordered_map<int, Place>::iterator i;
	for (i = currentContainer.begin(); i != currentContainer.end();)
	{
		if (!((i->second.startDate.month < startdateofuser.month) || (i->second.startDate.day <= startdateofuser.day && i->second.startDate.month == startdateofuser.month)) || !((i->second.endDate.month > enddateofuser.month) || (i->second.endDate.day >= enddateofuser.day && i->second.endDate.month == startdateofuser.month)))
			//period contains requested time
		{
			i = currentContainer.erase(i);
		}
		else
			i++;
	}
	currentPlaces = currentContainer;
	queryNumber++;
	displayAll();
}

void showPreferences()
{
	std::cout << "\nEnter your searching preferences:\n(1)Type (Room or Apartment)\n(2)Location\n(3)View\n(4)Price range\n(5)Payment method\n(6)Number of rooms in an apartment\n(7)Duration of stay\n(8)Date\n";
	std::cout << "(9)Restart search\n(0)Stop searching\n";
}

void Traveler::search()
{
	while (true) {
		showPreferences();
		int choice;
		std::cin >> choice;
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
		case 9:
		{
			restartAll();

			return;
		}
		case 0: {
			endProgram();
			break;
		}
		default: {
			cout << " invalid choice , try again \n";
		}
		}
		std::cout << "Would you like to select any current advertisements?y/n\n";
		char bookChoice;
		std::cin >> bookChoice;
		tolower(bookChoice) == 'y' ? choosePlace() : search();
		std::cin >> choice;
	}
}

void Traveler::displayDate(Place p) {
	std::cout << "Available date : \n";
	for (int i = 0; i < p.daysofplace.size(); i++)
		if (p.daysofplace[i].reserved == false)
			std::cout << p.daysofplace[i].day << "/" << p.daysofplace[i].month << endl;
}

bool Traveler::bookingcontinousperiod(Place& p, timereserve startdate, int period) {
	bool canreserve = false;
	int findindex;
	for (int i = 0; i < p.daysofplace.size(); i++) {
		if (p.daysofplace[i].day == startdate.day && p.daysofplace[i].month == startdate.month) {
			canreserve = true;
			findindex = i;
			if (i + period > p.daysofplace.size()) {
				canreserve = false;
			}
			else
				for (int j = 1; j <= period; j++) {
					if (p.daysofplace[i++].reserved == true) {
						canreserve = false;
						break;
					}

				}
			break;
		}
	}
	if (canreserve) {
		for (int j = 1; j <= period; j++) {
			p.daysofplace[findindex].reserved = true;
			p.daysofplace[findindex].userreserve = this->email;
			findindex++;
		}
		p.availableduration -= period;
		std::cout << "Please pay " << generateTotalPrice(p, period) << " using: " << p.paymentMethod << endl;
		return true;
	}
	else {
		std::cout << "invalid date you can't book ";
		return false;
	}
}

int Traveler::bookingSeperateDate(Place& p) {
	int numofreservedate = 0;
	bool booking = false;
	timereserve t;
	int choice;
	bool canreserve;
	do {
		std::cout << " please enter date you want to reserve";
		std::cin >> t.day >> t.month;
		booking = bookingcontinousperiod(p, t, 1);
		if (booking == true)
			numofreservedate++;
		std::cout << "do you want another date, put 1 to yes ";
		std::cin >> choice;
	} while (choice == 1);
	return numofreservedate;
}

void Traveler::choosePlace()
{
	bool booking = false;
	int choice;
	std::cout << "Enter the ID of the advertisement you want to select.";
	int ID;
	std::cin >> ID;
	timereserve t;
	int period;
	std::unordered_map<int, Place> ::iterator i;
	i = currentPlaces.find(ID);
	if (i == currentPlaces.end())
		cout << "ID NOT FOUND";
	else
	{
		while (booking == false) {
			displayDate(i->second);
			std::cout << " if you want continous date press 1, if you want seperate press 2 \n if you want not to book press any number\n";
			std::cin >> choice;
			if (choice == 1) {
				std::cout << " please enter start date ";
				std::cin >> t.day >> t.month;
				std::cout << " please enter period";
				std::cin >> period;
				booking = bookingcontinousperiod(i->second, t, period);
			}
			else if (choice == 2) {
				int num = bookingSeperateDate(i->second);
				booking = true;
				std::cout << " you have booking " << num << " days . \n";
				std::cout << "Please pay " << generateTotalPrice(i->second, num) << " using: " << i->second.paymentMethod << endl;
				break;
			}
			else {
				break;
			}
		}
		serializePlace(i->second);
		search();
		return;
	}
	std::cout << "Invalid ID.\n";
	choosePlace();
}



int Traveler::calculateBookedDuration(timereserve startDate, timereserve endDate)
{
	return 0;
}

string Traveler::validateEmail(string email)
{
	{
		string temp;
		for (char c : email)
		{
			temp += (char)tolower(c);
		}
		email = temp; //email into lowercase
		string path = "Data/traveller/" + email + ".txt";
		ifstream ifile(path);
		if (email.find('@') == std::string::npos) {
			std::cout << "this E-Mail must contain a domain" << endl;
			std::cout << "E-mail: ";
			string mail;
			std::cin >> mail;
			ifile.close();
			return validateEmail(mail);
		}
		else if (email.substr(email.length() - 4, 4) != ".com") {
			std::cout << "this E-Mail must end in .com suffix" << endl;
			std::cout << "E-mail: ";
			string mail;
			std::cin >> mail;
			ifile.close();
			return validateEmail(mail);
		}
		else if (ifile.is_open())
		{
			std::cout << "this E-Mail is already in use" << endl;
			std::cout << "E-mail: ";
			string mail;
			std::cin >> mail;
			ifile.close();
			return validateEmail(mail);
		}
		//ERROR if the user enters the email wrong, it will never let him correct it afterwards
		return path;
	}
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
	getline(stream, this->phone); // born to find horrible code, forced to cope
	//this->phone = stoi(placeHolderString);
	getline(stream, this->nationality);
	getline(stream, placeHolderString);
	this->gender = placeHolderString[0];
	getline(stream, placeHolderString);
	this->age = stoi(placeHolderString);
	deSerializePlaces();
}

float Traveler::generateTotalPrice(Place p, int duration)
{
	int totalPrice = 0;
	if (p.discount != 0)
	{
		float discount = p.discount / 100;
		totalPrice = (p.pricePerDay - (discount * p.pricePerDay)) * duration; // then multiply the whole expression by the number of days (Tamer&Ahmed)
	}
	else
	{
		totalPrice = p.pricePerDay * duration; // duration is calculated by the number of days the user reserves.
	}
	return totalPrice;
}

Traveler::Traveler(string password, string firstName, string lastName, string email, string phone, string nationality, char gender, int age) {
	this->password = password;
	this->firstName = firstName;
	this->lastName = lastName;
	this->email = email;
	this->phone = phone;
	this->nationality = nationality;
	this->gender = gender;
	this->age = age;
}
Traveler::Traveler() {

}