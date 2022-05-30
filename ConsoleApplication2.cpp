#include "Core/Admin/admin.h"

int main()
{
	int choice;
	while (true) {
		cout << "-Choose (1) to sign up as a host.\n-Choose (2) sign up as traveller\n-Choose (3) to login as a host.\n-Choose (4) to login as a traveller. \n if you want to login as admin press 5 \n ";
		cin >> choice;
		if (choice == 1) {
			Host h;
			h.signup();
			h.login();
			break;
		}
		else if (choice == 2) {
			Traveler T;
			T.signup();
			T.login();
			break;
		}
		else if (choice == 3) {
			Host h;
			h.login();
			break;
		}
		else if (choice == 4) {
			Traveler T;
			T.login();
			break;
		}
		else if (choice == 5) {
			Admin a;
			a.mainmenu();
		}
		else
		{
			cout << "Invalid choice, please try again.\n";
			continue;
		}
	}
}

//Let everyone test every single running scenario of the program... 
//Deadline: No deadline, everyone should always test newly implemented features and how they work with the system logic.

//Fully implement the program with a very appealing graphical user interface... (Canceled)

//Use python for the admin dashboard, generate a web page for all the statistics of the program... Deadline:
//Current issues::
// 
// 
//TODO::
//give host ability to be contacted by mail or phone