#include "Core/Traveler/traveler.h"
#include "Core/Host/host.h"

int main()
{
	Traveler t;
	t.login();
}

//Finish choosePlace (serializePlace and bookContiniousPeriod)... Deadline: Today.

//Re-check all data structures and add/replace suitable ones:
//LinkedList or hashtable of <placesOfCurrentView> for the GUI searching... Deadline: 29/5
//Priority Queue for the premium users (Host for number of possible places, 
//Traveller for discount generated)... Deadline:

//Let everyone test every single running scenario of the program... 
//Deadline: No deadline, everyone should always test newly implemented features and how they work with the system logic.

//Fully implement the program with a very appealing graphical user interface... (Ongoing)


//Use python for the admin dashboard, generate a web page for all the statistics of the program... Deadline:
//Current issues:
//Validate e-mail not working properly
//Infinite loop when adding new advertisement's date