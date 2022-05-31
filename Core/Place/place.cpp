#include "place.h"
#include <stdexcept>
// TODO: add time to constructor

void Place::getNextID()
{
	ifstream id("Data/lastID.txt");
	string currentID;
	getline(id, currentID);
	this->ID = stoi(currentID) + 1;
	id.close();
}

void Place::saveCurrentID()
{
	ofstream id("Data/lastID.txt");
	id << this->ID;
	cout << "ID saved:" << ID<<"\n";
}

Place::Place() {

}
Place::Place(timereserve startDate,timereserve endDate)
{
	this->startDate = startDate;
	this->endDate = endDate;
}

Place::Place(int ID, location loc, int pricePerDay, string view, bool room, int noOfRooms, string paymentMethod, string hostEmail, timereserve startDate, timereserve endDate, int discount)
{
	this->ID = ID;
	this->loc = loc;
	this->view = view;
	this->paymentMethod = paymentMethod;
	this->room = room;
	this->noOfRooms = noOfRooms;
	this->pricePerDay = pricePerDay;
	this->discount = discount;
	this->hostEmail = hostEmail;
	this->availableduration = 0;
	this->startDate = startDate;
	this->endDate = endDate;
}
Place::Place(location loc, int pricePerDay, string view, bool room, int noOfRooms, string paymentMethod, string hostEmail, int discount)
{
	getNextID();
	this->ID = ID++;
	saveCurrentID();
	this->loc = loc;
	this->view = view;
	this->paymentMethod = paymentMethod;
	this->room = room;
	this->noOfRooms = noOfRooms;
	this->pricePerDay = pricePerDay;
	this->discount = discount;
	this->hostEmail = hostEmail;
}
Place::Place(location loc, int pricePerDay, string view, bool room, int noOfRooms, string paymentMethod, string hostEmail, timereserve startDate, timereserve endDate, int discount)
{
	getNextID();
	this->ID = ID++;
	saveCurrentID();
	this->loc = loc;
	this->view = view;
	this->paymentMethod = paymentMethod;
	this->room = room;
	this->noOfRooms = noOfRooms;
	this->pricePerDay = pricePerDay;
	this->discount = discount;
	this->hostEmail = hostEmail;
	this->availableduration = 0;
	this->startDate = startDate;
	this->endDate = endDate;
}
void Place::createTimeForPlace()
{
	timereserve t;
	int date = this->startDate.day;
	int j = this->startDate.month;
	int i = this->startDate.day;
	if (this->startDate.month > 12 || this->endDate.month > 12 || this->endDate.month < this->startDate.month|| this->startDate.month<1||this->endDate.month<1) {
		std::logic_error ex("Invalid Date");
		throw std::exception(ex);
	}
	while (!(t.day == this->endDate.day && t.month == this->endDate.month))
	{
		switch (j)
		{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			if (date > 31||date< 1)
			{
				std::logic_error ex("Invalid Date");
				throw std::exception(ex);
			}
			else
			{
				for (i; !(t.day == this->endDate.day && t.month == this->endDate.month); i++)
				{
					if (i <= 31)
					{
						t.day = i;
						t.month = j;
						this->daysofplace.push_back(t);
						this->availableduration++;
					}
					else
					{
						i = 1;
						date = 1;
						j = ++j % 12;
						break;
					}
				}
			}
			break;

		case 4:
		case 6:
		case 9:
		case 11:
			if (date > 30 || date< 1)
			{
				std::logic_error ex("Invalid Date");
				throw std::exception(ex);
			}
			else
				for (i; !(t.day == this->endDate.day && t.month == this->endDate.month); i++)
				{
					if (i <= 30)
					{
						t.day = i;
						t.month = j;
						this->daysofplace.push_back(t);
						this->availableduration++;
					}
					else
					{
						i = 1;
						date = 1; 
						j = ++j % 13;
						break;
					}
				}
			break;
		case 2:
			if (date > 28 || date < 1)
			{
				std::logic_error ex("Invalid Date");
				throw std::exception(ex);
			}
			else
				for (i; !(t.day == this->endDate.day && t.month == this->endDate.month); i++)
				{
					if (i <= 28)
					{
						t.day = i;
						t.month = j;
						this->daysofplace.push_back(t);
						this->availableduration++;
					}
					else
					{
						i = 1;
						date = 1; 
						j = ++j % 12;
						break;
					}
				}
			break;
		}
	}
}
