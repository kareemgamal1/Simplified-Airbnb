#include <array>
#include "traveler.h"
#include "host.h"

int main()
{
	Host h;
	h.login();
}

// Deserialize has to be fixed
// We should fix the static noOfPlaces, when we are done with it everytime we should update it's value in a file
// then when we start the program we should read it
// in admin & traveller we should deserialize all places into the allPlaces vector
// in host we should deseralize all of HIS places into the places vector
// for every traveller when he chooses a specific place it should be saved to his specific folder
// for admin we should have complete access to all folders
// can we have a map linking hostEmail with the host?