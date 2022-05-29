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
	cout << "ID saved:" << ID;
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
			if (this->startDate.day > 31||this->startDate.day < 1)
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
			if (this->startDate.day > 30 || this->startDate.day < 1)
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
						j = ++j % 13;
						break;
					}
				}
			break;
		case 2:
			if (this->startDate.day > 28 || this->startDate.day < 1)
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
						j = ++j % 12;
						break;
					}
				}
			break;
		}
	}
}

void Place::calculateDuration()
{
	duration = daysofplace.size();
}
void Place::displaydays()
{
	for (int i = 0; i < daysofplace.size(); i++)
		if (daysofplace[i].reserved == false)
			cout << " valid : " << daysofplace[i].day << "/" << daysofplace[i].month << endl;
}

void Place::bookingcontinousperiod(int period, timereserve t)
{
	bool canreserve = false;
	int findindex;
	for (int i = 0; i < daysofplace.size(); i++)
		if (daysofplace[i].day == t.day && daysofplace[i].month == t.month)
		{
			canreserve = true;
			findindex = i;
			if (i + period > daysofplace.size())
				cout << " invalid date , you can't book";
			else
				for (int j = 1; j <= period; j++)
				{
					if (daysofplace[i++].reserved == true)
					{
						canreserve = false;
						break;
					}
				}
		}
	if (canreserve)
	{
		for (int j = 1; j <= period; j++)
		{
			daysofplace[findindex].reserved = true;
			findindex++;
		}
	}
	else
	{
		cout << "invalid date you can't book ";
	}
}
