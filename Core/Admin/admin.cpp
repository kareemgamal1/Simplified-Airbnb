#include "../Admin/admin.h"

void Admin::createTraveler()
{
	Traveler T;
	T.signup();
	travelers[T.getEmail()] = T;
	mainmenu();
}
void Admin::createHost()
{
	Host h;
	h.signup();
	hosts[h.getEmail()] = h;
	mainmenu();
}

void Admin::addAdvertisement() {
	string mail;
	Host h;
	unordered_map <string, Host> ::iterator i;

	while (true) {
		cout << " please enter the email of the host \n";
		cin >> mail;
		i = hosts.find(mail);
		if (i == hosts.end()) {
			cout << " this email is not found \n ";
		}
		else {
			break;
		}
	}
	i->second.addAdvertisement();
	mainmenu();
}
void Admin::editAdvertisement() {
	string mail;
	Host h;
	unordered_map <string, Host> ::iterator i;

	while (true) {
		cout << " please enter the email of the host \n";
		cin >> mail;
		i = hosts.find(mail);
		if (i == hosts.end()) {
			cout << " this email is not found \n ";
		}
		else {
			break;
		}
	}
	i->second.editAdvertisement();
	mainmenu();
}
void Admin::deleteAdvertisement() {
	string mail;
	Host h;
	unordered_map <string, Host> ::iterator i;

	while (true) {
		cout << " please enter the email of the host \n";
		cin >> mail;
		i = hosts.find(mail);
		if (i == hosts.end()) {
			cout << " this email is not found \n ";
		}
		else {
			break;
		}
	}
	i->second.deleteAdvertisement();
	mainmenu();
}

void Admin::displayHosts() {
	deserializeHosts();
	if (hosts.size() == 0)
	{
		std::cout << "\nThere are no hosts..\n";
	}
	else {
		cout << "\nHosts: \n\n";
		for (auto i : hosts)
		{
			cout << "===============================\n";
			cout << "Host's E-mail:" << i.second.getEmail() << '\n';
			cout << "Host's name:" << i.second.getFirstName() << " " << i.second.getLastName() << '\n';
			cout << "Host's nationality:" << i.second.getNationality() << '\n';
			cout << "Host's gender:" << ((tolower(i.second.getGender()) == 'm') ? " Male" : " Female") << '\n';
			cout << "Host's age:" << i.second.getAge() << '\n';
			cout << "===============================\n\n\n";
		}
	}
	mainmenu();
}
void Admin::displayTravelers() {
	deserializeTravelers();
	if (travelers.size() == 0)
	{
		std::cout << "\nThere are no travelers..\n";
	}
	else {
		cout << "\nTravelers: \n\n";
		for (auto i : travelers)
		{
			cout << "===============================\n";
			cout << "Traveler's E-mail:" << i.second.getEmail() << '\n';
			cout << "Traveler's name:" << i.second.getFirstName() << " " << i.second.getLastName() << '\n';
			cout << "Traveler's nationality:" << i.second.getNationality() << '\n';
			cout << "Traveler's age:" << i.second.getAge() << '\n';
			cout << "===============================\n\n\n";
		}
	}
	mainmenu();
}
//done
void Admin::deserializeHosts() {
	string path = "Data/host/";
	try
	{
		for (const auto& entry : filesystem::directory_iterator(path))
		{
			ifstream stream(entry.path());
			string x;
			string password, firstName, lastName, email, phone, nationality;
			char gender;
			int age;

			getline(stream, x);
			password = x;
			getline(stream, x);
			firstName = x;
			getline(stream, x);
			lastName = x;
			getline(stream, x);
			email = x;
			getline(stream, x);
			phone = x;
			getline(stream, x);
			nationality = x;
			getline(stream, x);
			gender = x[0]; //reads ascii
			getline(stream, x);
			age = stoi(x);
			hosts[email] = Host(password, firstName, lastName, email, phone, nationality, gender, age);
			hosts[email].deSerializePlaces();
			stream.close();
		}
	}
	catch (exception e)
	{
		cout << e.what();
		cout << "ERROR" << endl;
		// oh no, there's no directory for this host, anyways..
		return;
	}
}
void Admin::deserializeTravelers() {
	string path = "Data/traveller/";
	try
	{
		for (const auto& entry : filesystem::directory_iterator(path))
		{
			ifstream stream(entry.path());
			string x;
			string password, firstName, lastName, email, phone, nationality;
			char gender;
			int age;

			getline(stream, x);
			password = x;
			getline(stream, x);
			firstName = x;
			getline(stream, x);
			lastName = x;
			getline(stream, x);
			email = x;
			getline(stream, x);
			phone = x;
			getline(stream, x);
			nationality = x;
			getline(stream, x);
			gender = x[0];
			getline(stream, x);
			age = stoi(x);

			travelers[email] = Traveler(password, firstName, lastName, email, phone, nationality, gender, age);
			stream.close();
		}
	}
	catch (exception e)
	{
		cout << e.what();
		cout << "ERROR" << endl;
		// oh no, there's no directory for this traveler, anyways..
		return;
	}
}

void Admin::deleteHost() {

	std::unordered_map<string, Host> ::iterator i;
	while (true)
	{
		cout << "Which host would you like to delete? Please enter the hosts's E-mail.\n";
		string email;
		cin >> email;
		i = hosts.find(email);

		if (i == hosts.end())
			cout << "HOST NOT FOUND";
		else
		{
			string toBeDeleted = "Data/host/" + email + ".txt";
			string folderToBeDeleted = "Data/place/" + email;
			std::uintmax_t n = filesystem::remove_all(folderToBeDeleted);
			try
			{
				if (std::filesystem::remove(toBeDeleted))
				{
					cout << "Advertisement with e-mail: " << email << " has been deleted.\n";
					hosts.erase(i->first);
					break;
				}
				else
				{
					std::cout << "file " << toBeDeleted << " not found.\n";
				}

				if (n > 0)
				{
					cout << "All places associated with e-mail: " << email << " has been deleted.\n";
					break;
				}
				else
				{
					std::cout << "this host had no places, none were deleted.\n";
				}
			}
			catch (const std::filesystem::filesystem_error& err)
			{
				std::cout << "filesystem error: " << err.what() << '\n';
			}
		}

	}
	mainmenu();
}
void Admin::deleteTraveler() {
	std::unordered_map<string, Traveler> ::iterator i;
	while (true)
	{
		cout << "Which traveler would you like to delete? Please enter the traveler's E-mail.\n";
		string email;
		cin >> email;
		i = travelers.find(email);

		if (i == travelers.end())
			cout << "TRAVELLER NOT FOUND";
		else
		{
			string toBeDeleted = "Data/traveller/" + email + ".txt";
			try
			{
				if (std::filesystem::remove(toBeDeleted))
				{
					cout << "Traveler with e-mail: " << email << " has been deleted.\n";
					travelers.erase(i->first);
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
	mainmenu();
}
void Admin::mainmenu() { ///// updateeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
	int choice;
	cout << "\n-Choose (1) if you want to create a new traveller.\n-Choose (2) if you want to create a new host.\n-Choose (3) if you want to delete a traveller.\n-Choose (4) if you want to delete a host.\n-Choose (5) if you want to add an advertisment to a specific host.\n-Choose (6) if you want to edit advertisment.\n-Choose (7) if you want to delete advertisment.\n-Choose (8) if you want to display all travellers.\n-Choose (9) if you want to display all hosts.\n-Choose (10) if you want to generate a statistical insights about the whole system.\n-Choose (0)if you want to sign out.\n";
	while (true) {
		cin >> choice;
		switch (choice) {
		case 1: {
			createTraveler();
			return;
		}
		case 2: {
			createHost();
			return;
		}
		case 3: {
			deleteTraveler();
			return;
		}
		case 4: {
			deleteHost();
			return;
		}
		case 5: {
			addAdvertisement();
			return;
		}
		case 6: {
			editAdvertisement();
			return;
		}
		case 7: {
			deleteAdvertisement();
			return;
		}
		case 8: {
			displayTravelers();
			return;

		}
		case 9: {
			displayHosts();
			return;
		}
		case 10: {
			generateDashboard();
			return;
		}
		case 0: {
			return;
		}
		default: {
			cout << "Invalid choice!\n";
			break;
		}
		}
	}
}
void Admin::generateDashboard()
{
	// getTotalNoOfUsers();
	// getTotalNoOfHosts();
	// getTotalNoOfTravellers();
	// getTotalNoOfAdvertisements();
	// getPercentageOfMaleUsers();
	// getPercentageOfFemaleUsers();
	// getNoOfDiscounts();
	// getPercentageOfDiscounts();
	// getTotalNumberOfRooms();
	// getPercentageOfRooms&Apartments();
	// getNoOfReservedPlaces();
}

void Admin::validateAdmin() {
	string passcode;
	cin >> passcode;
	if (passcode != "045")
	{
		return;
	}
	cout << "Hello admin!\n";
	mainmenu();
}

Admin::Admin() {
	deserializeHosts();
	deserializeTravelers();
}