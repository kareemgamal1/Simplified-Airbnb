#include "Core/Traveler/traveler.h"
#include "Core/Host/host.h"

int main()
{

	int choice;
	while (true) {
		cout << "\n\n-Choose (1) to sign up as traveller -Choose (2) to login as traveller \n -Choose (3) sign up as host\n choose 4 to login as host \n";
		cin >> choice;
		if (choice == 1) {
			Traveler T;
			T.signup();
			break;
		}
		else if (choice == 2) {
			Traveler T;
			T.login();
			break;
		}
		else if (choice == 3) {
			Host h;
			h.signup();
			break;
		}
		else if (choice == 4) {
			Host h;
			h.login();
			break;
		}
		else
		{
			cout << " invalid choice , try again\n";
			continue;
		}
	}

}

//Re-check all data structures and add/replace suitable ones:
//LinkedList or hashtable of <placesOfCurrentView> for the GUI searching... Deadline: 29/5
//Priority Queue for the premium users (Host for number of possible places, 
//Traveller for discount generated)... Deadline:

//Let everyone test every single running scenario of the program... 
//Deadline: No deadline, everyone should always test newly implemented features and how they work with the system logic.

//Fully implement the program with a very appealing graphical user interface... (Ongoing)


//Use python for the admin dashboard, generate a web page for all the statistics of the program... Deadline:
//Current issues::
// 
// 
// 
//TODO::
//main menu to login and signup etc
//give host ability to be contacted by mail or phone