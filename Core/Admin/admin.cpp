#include "../Admin/admin.h"

void Admin::createTraveler()
{
    Traveler T;
    T.signup();
	travelers[T.getEmail()] = T; 
}
void Admin::createHost()
{
    Host h;
    h.signup();
	hosts[h.getEmail()] = h; 
}
//done

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
}

void Admin::displayHosts() {
	cout << "\nHosts: \n\n";
	for (auto i : hosts)
	{
		cout << "===============================\n";
		cout << "Host's E-mail:" << i.second.getEmail() << '\n';
		cout << "Host's name:" << i.second.getFirstName() << " " << i.second.getLastName()<<'\n';
		cout << "Host's nationality:" << i.second.getNationality() << '\n';
		cout << "Host's gender:" << ((tolower(i.second.getGender()) == 'm')? " Male" : " Female") << '\n';
		cout << "Host's age:" << i.second.getAge() << '\n';
		cout << "===============================\n\n\n";
	}
}
void Admin::displayTravelers() {
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
			hosts[email] = Host(password,firstName,lastName,email,phone,nationality,gender,age);
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
//done

void Admin::deleteHost(){
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
			string toBeDeleted = "Data/host/" + email +".txt";
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

				if (n>0)
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
}
void Admin::deleteTraveler(){
	std::unordered_map<string, Traveler> ::iterator i;
	while (true)
	{
		cout << "Which traveler would you like to delete? Please enter the traveler's E-mail.\n";
		string email;
		cin >> email;
		i = travelers.find(email);

		if (i == travelers.end())
			cout << "HOST NOT FOUND";
		else
		{			
		string toBeDeleted = "Data/traveller/" + email + ".txt";
			try
			{
				if (std::filesystem::remove(toBeDeleted))
				{
					cout << "Traveler with e-mail: " << email << " has been deleted.\n";
					hosts.erase(i->first);
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
Admin::Admin() {
	deserializeHosts();
	deserializeTravelers();
}