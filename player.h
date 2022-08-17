#pragma once


#include "object.h"


//   Class to handle Player Assets
class player
{
private:

	object galaxy;
	vector<object> galaxyRoster;
	vector<int> deleteRoster;


public:

	//   Constructor initializes Player's Galaxy and Galaxy Roster
	player(object galaxy_, vector<object> galaxyList_)
	{
		galaxy = galaxy_;
		galaxyRoster = galaxyList_;
	}


	//   Returns the Player's Galaxy
	object getGalaxy()
	{return galaxy;}


	//   Removes the Galaxy specified from the Galaxy Roster, using the index as the parameter
	void removeGalaxy(int number_)
	{
		vector<object>::iterator it;

		it = galaxyRoster.begin() + number_;
		galaxyRoster.erase(it);
	}


	//   Returns the Player's Galaxy Roster
	vector<object> getGalaxyRoster()
	{return galaxyRoster;}

	vector<int> getDeleteRoster()
	{return deleteRoster;}


	//   Displays all the remaining Galaxies left in the Player's Galaxy Roster
	void dispAllGalaxies()
	{
		for (unsigned int i = 0; i < galaxyRoster.size(); i++)
		{galaxyRoster[i].display();}
	}
};

