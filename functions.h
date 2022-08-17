#pragma once


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include "object.h"
#include "player.h"
using namespace std;



//   Reads Galaxy Data from the input file
void fileReader(ifstream& in_, vector<object>& objectList_)
{
	//===================================================================================================
	//		Input File Format		//
	//===============================
	//   Name: [NAME]
	//
	//   Type:						Barred Spiral, Spheroidal, Magellanic Spiral, Elliptical, 
	//								Irregular, Spiral
	//
	//   Size:						Dwarf, Non-dwarf
	//
	//   Distance from Milky Way:	0 - 1 mly, 1 - 2.5 mly, 2.5 - 5 mly
	//
	//   Color:						White, Unknown, Lavender, Rainbow, Orange, Purple, Blue, 
	//								Brown, Red, Yellow
	//
	//   Sattelite of:				None, Milky Way, Andromeda, Triangulum
	//
	//=============================================================================


	string name, type, size, distFrMW, color, sattlOf, blankLine;
	int galaxyNumber = 0;


	do
	{
		getline(in_, name);
		getline(in_, type);
		getline(in_, size);
		getline(in_, distFrMW);
		getline(in_, color);
		getline(in_, sattlOf);
		getline(in_, blankLine);

		galaxyNumber++;

		object temp(galaxyNumber, name, type, size, distFrMW, color, sattlOf);

		objectList_.push_back(temp);
	}

	while (!in_.eof());
}


//   Displays the Player Menu & handles player input
void playerMenu(int& turn_, int& selectionP1_, int& selectionP2_, bool& dispTurn_)
{
	int tempSelection = -1;
	selectionP1_ = 0;
	selectionP2_ = 0;


	if (turn_ == 0)
	{
		if (!dispTurn_)
		{
			dispTurn_ = true;

			cout << "  /$$$$$$$   / $$   /$$                /$$$$$$$$" << endl;
			cout << " | $$__  $$ / $$$$ | $/               |__  $$__/" << endl;
			cout << " | $$  \\ $$|_  $$  |_/   /$$$$$$$        | $$    /$$ / $$   / $$$$$$  /$$$$$$$" << endl;
			cout << " | $$$$$$$/  | $$       /$$_____/        | $$   | $$ | $$  / $$__  $$| $$__  $$" << endl;
			cout << " | $$____/   | $$      |  $$$$$$         | $$   | $$ | $$ | $$  \\__/ | $$  \\ $$" << endl;
			cout << " | $$        | $$       \\____  $$        | $$   | $$ | $$ | $$       | $$  | $$" << endl;
			cout << " | $$       /$$$$$$     /$$$$$$$/        | $$   | $$$$$$/ | $$       | $$  | $$" << endl;
			cout << " |__/      |______/    |_______/         |__/    \\______/ |__/       |__/  |__/" << endl << endl;
		}

		cout << "     Player 1, please make a Selection:\n" << endl;
	}

	else
	{
		if (!dispTurn_)
		{
			dispTurn_ = true;

			cout << "  /$$$$$$$   /$$$$$$  /$$                 /$$$$$$$$" << endl;
			cout << " | $$__  $$ /$$__  $$| $/                |__  $$__/" << endl;
			cout << " | $$  \\ $$|__/  \\ $$|_/   /$$$$$$$         | $$    /$$   /$$  /$$$$$$  /$$$$$$$" << endl;
			cout << " | $$$$$$$/  /$$$$$$/     /$$_____/         | $$   | $$  | $$ /$$__  $$| $$__  $$" << endl;
			cout << " | $$____/  /$$____/     |  $$$$$$          | $$   | $$  | $$| $$  \\__/| $$  \\ $$" << endl;
			cout << " | $$      | $$           \\____  $$         | $$   | $$  | $$| $$      | $$  | $$" << endl;
			cout << " | $$      | $$$$$$$$     /$$$$$$$/         | $$   |  $$$$$$/| $$      | $$  | $$" << endl;
			cout << " |__/      |________/    |_______/          |__/    \\______/ |__/      |__/  |__/" << endl << endl;
		}

		cout << "     Player 2, please make a Selection:\n" << endl;
	}


	cout << "   1. Display remaining possible Galaxies" << endl;
	cout << "   2. Make a General Guess" << endl;
	cout << "   3. Make a Specific Guess\n" << endl;
	cout << "     Selection: ";

	cin >> tempSelection;


	while (cin.fail() || tempSelection < 1 || tempSelection > 3)
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "\n";
		cout << "   !!!       Invalid input entered. Please try again.       !!!\n\n" << endl;
		cout << "     Selection: ";
		cin >> tempSelection;
	}


	if (turn_ == 0)
	{selectionP1_ = tempSelection;}

	else
	{selectionP2_ = tempSelection;}


	cout << "\n" << endl;
}


//   Performs the turn player's chosen action
void performAction(int& turn_, player& P1_, int& selectionP1_, player& P2_, int& selectionP2_,
				   bool& endTurn_, bool& endGame_)
{
	int choice, subChoice;
	char finalChoice;


	if (endGame_)
	{return;}


	//   Player 1's Turn
	if (turn_ == 0)
	{
		//   Player Action 1: Display list of opponent's possible galaxies
		if (selectionP1_ == 1)
		{
			cout << "\n   --------------------------------------------------" << endl;
			cout << "   ---     Display Remaining Possible Galaxies    ---" << endl;
			cout << "   --------------------------------------------------\n" << endl;
			cout << "     Player 2's possible galaxies:" << endl;
			cout << "   ------------------------------------------------------------------------------------------------------------" << endl;
			cout << "     ##  Galaxy Name                Type                Size         Distance from     Color       Sattelite" << endl;
			cout << "                                                                     Milky Way                     of ________\n" << endl;

			P1_.dispAllGalaxies();

			cout << "   ------------------------------------------------------------------------------------------------------------" << endl;

			cout << "\n\n" << endl;
		}

		//   Player Action 2: Perform general guess on opponent's galaxy
		else if (selectionP1_ == 2)
		{
			cout << "\n   ============================================" << endl;
			cout << "   ===          Make a General Guess        ===" << endl;
			cout << "   ============================================\n" << endl;
			cout << "     Choose a criteria to guess with:\n" << endl;
			cout << "     1. Type" << endl;
			cout << "     2. Size" << endl;
			cout << "     3. Distance from Milky Way" << endl;
			cout << "     4. Color" << endl;
			cout << "     5. Sattelite of _______\n" << endl;
			cout << "     Selection: ";
			cin >> choice;

			//   Error-checking user input
			while (cin.fail() || choice < 1 || choice > 5)
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "\n";
				cout << "   !!!       Invalid input entered. Please try again.       !!!\n\n" << endl;
				cout << "     Selection: ";
				cin >> choice;
			}

			//   Guessing with Galaxy Type
			if (choice == 1)
			{
				cout << "\n\n   -------------------------------------------" << endl;
				cout << "   ---      Guessing with Galaxy Type      ---" << endl;
				cout << "   -------------------------------------------\n" << endl;
				cout << "     Enter in the Type of Galaxy to guess with: \n" << endl;
				cout << "     1. Barred Spiral" << endl;
				cout << "     2. Spheroidal" << endl;
				cout << "     3. Magellanic Spiral" << endl;
				cout << "     4. Elliptical" << endl;
				cout << "     5. Irregular" << endl;
				cout << "     6. Spiral" << endl << endl;
				cout << "     Selection: ";
				cin >> subChoice;

				//   Error-checking user input
				while (cin.fail() || subChoice < 1 || subChoice > 6)
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "\n";
					cout << "   !!!       Invalid input entered. Please try again.       !!!\n\n" << endl;
					cout << "     Selection: ";
					cin >> subChoice;
				}

				cout << "\n\n   ---       RESULT:       ---" << endl;

				//   Searching for Barred Spiral Galaxies
				if (subChoice == 1)
				{
					//   If P1 chose the Galaxy Type correctly
					if (P2_.getGalaxy().getType() == "Barred Spiral")
					{
						cout << "\n     Player 2's Galaxy is a Barred Spiral!\n" << endl;

						//   Search P1's Galaxy Roster & remove all listings that aren't the guess
						for (int i = 0; i < P1_.getGalaxyRoster().size(); i++)
						{
							if (P1_.getGalaxyRoster()[i].getType() != "Barred Spiral")
							{
								cout << "     " << P1_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P1_.removeGalaxy(i);
								i--;
							}
						}
					}

					//   P1 chose incorrectly
					else
					{
						cout << "\n     Player 2's Galaxy isn't a Barred Spiral!\n" << endl;

						//   Search P1's Galaxy Roster & remove all the listings that are the guess
						for (int i = 0; i < P1_.getGalaxyRoster().size(); i++)
						{
							if (P1_.getGalaxyRoster()[i].getType() == "Barred Spiral")
							{
								cout << "     " << P1_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P1_.removeGalaxy(i);
								i--;
							}
						}
					}
				}

				//   Searching for Spheroidal Galaxies
				else if (subChoice == 2)
				{
					//   If P1 chose the Galaxy Type correctly
					if (P2_.getGalaxy().getType() == "Spheroidal")
					{
						cout << "\n     Player 2's Galaxy is a Spheroidal!\n" << endl;

						//   Search P1's Galaxy Roster & remove all listings that aren't the guess
						for (int i = 0; i < P1_.getGalaxyRoster().size(); i++)
						{
							if (P1_.getGalaxyRoster()[i].getType() != "Spheroidal")
							{
								cout << "     " << P1_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P1_.removeGalaxy(i);
								i--;
							}
						}
					}

					//   P1 chose incorrectly
					else
					{
						cout << "\n     Player 2's Galaxy isn't a Spheroidal!\n" << endl;

						//   Search P1's Galaxy Roster & remove all the listings that are the guess
						for (int i = 0; i < P1_.getGalaxyRoster().size(); i++)
						{
							if (P1_.getGalaxyRoster()[i].getType() == "Spheroidal")
							{
								cout << "     " << P1_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P1_.removeGalaxy(i);
								i--;
							}
						}
					}
				}

				//   Searching for Magellanic Spiral Galaxies
				else if (subChoice == 3)
				{
					//   If P1 chose the Galaxy Type correctly
					if (P2_.getGalaxy().getType() == "Magellanic Spiral")
					{
						cout << "\n     Player 2's Galaxy is a Magellanic Spiral!\n" << endl;

						//   Search P1's Galaxy Roster & remove all listings that aren't the guess
						for (int i = 0; i < P1_.getGalaxyRoster().size(); i++)
						{
							if (P1_.getGalaxyRoster()[i].getType() != "Magellanic Spiral")
							{
								cout << "     " << P1_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P1_.removeGalaxy(i);
								i--;
							}
						}
					}

					//   P1 chose incorrectly
					else
					{
						cout << "\n     Player 2's Galaxy isn't a Magellanic Spiral!\n" << endl;

						//   Search P1's Galaxy Roster & remove all the listings that are the guess
						for (int i = 0; i < P1_.getGalaxyRoster().size(); i++)
						{
							if (P1_.getGalaxyRoster()[i].getType() == "Magellanic Spiral")
							{
								cout << "     " << P1_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P1_.removeGalaxy(i);
								i--;
							}
						}
					}
				}

				//   Searching for Elliptical Galaxies
				else if (subChoice == 4)
				{
					//   If P1 chose the Galaxy Type correctly
					if (P2_.getGalaxy().getType() == "Elliptical")
					{
						cout << "\n     Player 2's Galaxy is an Elliptical!\n" << endl;

						//   Search P1's Galaxy Roster & remove all listings that aren't the guess
						for (int i = 0; i < P1_.getGalaxyRoster().size(); i++)
						{
							if (P1_.getGalaxyRoster()[i].getType() != "Elliptical")
							{
								cout << "     " << P1_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P1_.removeGalaxy(i);
								i--;
							}
						}
					}

					//   P1 chose incorrectly
					else
					{
						cout << "\n     Player 2's Galaxy isn't an Elliptical!\n" << endl;

						//   Search P1's Galaxy Roster & remove all the listings that are the guess
						for (int i = 0; i < P1_.getGalaxyRoster().size(); i++)
						{
							if (P1_.getGalaxyRoster()[i].getType() == "Elliptical")
							{
								cout << "     " << P1_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P1_.removeGalaxy(i);
								i--;
							}
						}
					}
				}

				//   Searching for Irregular Galaxies
				else if (subChoice == 5)
				{
					//   If P1 chose the Galaxy Type correctly
					if (P2_.getGalaxy().getType() == "Irregular")
					{
						cout << "\n     Player 2's Galaxy is an Irregular!\n" << endl;

						//   Search P1's Galaxy Roster & remove all listings that aren't the guess
						for (int i = 0; i < P1_.getGalaxyRoster().size(); i++)
						{
							if (P1_.getGalaxyRoster()[i].getType() != "Irregular")
							{
								cout << "     " << P1_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P1_.removeGalaxy(i);
								i--;
							}
						}
					}

					//   P1 chose incorrectly
					else
					{
						cout << "\n     Player 2's Galaxy isn't an Irregular!\n" << endl;

						//   Search P1's Galaxy Roster & remove all the listings that are the guess
						for (int i = 0; i < P1_.getGalaxyRoster().size(); i++)
						{
							if (P1_.getGalaxyRoster()[i].getType() == "Irregular")
							{
								cout << "     " << P1_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P1_.removeGalaxy(i);
								i--;
							}
						}
					}
				}

				//   Searching for Spiral Galaxies
				else if (subChoice == 6)
				{
					//   If P1 chose the Galaxy Type correctly
					if (P2_.getGalaxy().getType() == "Spiral")
					{
						cout << "\n     Player 2's Galaxy is a Spiral!\n" << endl;

						//   Search P1's Galaxy Roster & remove all listings that aren't the guess
						for (int i = 0; i < P1_.getGalaxyRoster().size(); i++)
						{
							if (P1_.getGalaxyRoster()[i].getType() != "Spiral")
							{
								cout << "     " << P1_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P1_.removeGalaxy(i);
								i--;
							}
						}
					}

					//   P1 chose incorrectly
					else
					{
						cout << "\n     Player 2's Galaxy isn't a Spiral!\n" << endl;

						//   Search P1's Galaxy Roster & remove all the listings that are the guess
						for (int i = 0; i < P1_.getGalaxyRoster().size(); i++)
						{
							if (P1_.getGalaxyRoster()[i].getType() == "Spiral")
							{
								cout << "     " << P1_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P1_.removeGalaxy(i);
								i--;
							}
						}
					}
				}

				cout << "\n   ---       ^^^^^^^       ---\n" << endl;
			}

			//   Guessing with Galaxy Size
			else if (choice == 2)
			{
				cout << "\n\n   -------------------------------------------" << endl;
				cout << "   ---      Guessing with Galaxy Size      ---" << endl;
				cout << "   -------------------------------------------\n" << endl;
				cout << "     Enter in the Size of Galaxy to guess with: \n" << endl;
				cout << "     1. Dwarf" << endl;
				cout << "     2. Non-Dwarf" << endl << endl;
				cout << "     Selection: ";
				cin >> subChoice;

				//   Error-checking user input
				while (cin.fail() || subChoice < 1 || subChoice > 2)
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "\n";
					cout << "   !!!       Invalid input entered. Please try again.       !!!\n\n" << endl;
					cout << "     Selection: ";
					cin >> subChoice;
				}

				cout << "\n\n   ---       RESULT:       ---" << endl;

				//   Searching for Dwarf Galaxies
				if (subChoice == 1)
				{
					//   If P1 chose the Galaxy Size correctly
					if (P2_.getGalaxy().getSize() == "Dwarf")
					{
						cout << "\n     Player 2's Galaxy is a Dwarf Galaxy!\n" << endl;

						//   Search P1's Galaxy Roster & remove all listings that aren't the guess
						for (int i = 0; i < P1_.getGalaxyRoster().size(); i++)
						{
							if (P1_.getGalaxyRoster()[i].getSize() != "Dwarf")
							{
								cout << "     " << P1_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P1_.removeGalaxy(i);
								i--;
							}
						}
					}

					//   P1 chose incorrectly
					else
					{
						cout << "\n     Player 2's Galaxy isn't a Dwarf Galaxy!\n" << endl;

						//   Search P1's Galaxy Roster & remove all the listings that are the guess
						for (int i = 0; i < P1_.getGalaxyRoster().size(); i++)
						{
							if (P1_.getGalaxyRoster()[i].getSize() == "Dwarf")
							{
								cout << "     " << P1_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P1_.removeGalaxy(i);
								i--;
							}
						}
					}
				}

				//   Searching for Non-Dwarf Galaxies
				else
				{
					//   If P1 chose the Galaxy Size correctly
					if (P2_.getGalaxy().getSize() == "Non-Dwarf")
					{
						cout << "\n     Player 2's Galaxy is a Non-Dwarf Galaxy!\n" << endl;

						//   Search P1's Galaxy Roster & remove all listings that aren't the guess
						for (int i = 0; i < P1_.getGalaxyRoster().size(); i++)
						{
							if (P1_.getGalaxyRoster()[i].getSize() != "Non-Dwarf")
							{
								cout << "     " << P1_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P1_.removeGalaxy(i);
								i--;
							}
						}
					}

					//   P1 chose incorrectly
					else
					{
						cout << "\n     Player 2's Galaxy isn't a Non-Dwarf Galaxy!\n" << endl;

						//   Search P1's Galaxy Roster & remove all the listings that are the guess
						for (int i = 0; i < P1_.getGalaxyRoster().size(); i++)
						{
							if (P1_.getGalaxyRoster()[i].getSize() == "Non-Dwarf")
							{
								cout << "     " << P1_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P1_.removeGalaxy(i);
								i--;
							}
						}
					}
				}

				cout << "\n   ---       ^^^^^^^       ---\n" << endl;
			}

			//   Guessing with Galaxy Distance
			else if (choice == 3)
			{
				cout << "\n\n   -----------------------------------------------" << endl;
				cout << "   ---      Guessing with Galaxy Distance      ---" << endl;
				cout << "   -----------------------------------------------\n" << endl;
				cout << "     Enter in the Distance from the Milky Way Galaxy to guess with:\n" << endl;
				cout << "     1. 0 - 1 million Light Years" << endl;
				cout << "     2. 1 - 2.5 million Light Years" << endl;
				cout << "     3. 2.5 - 5 million Light Years" << endl << endl;
				cout << "     Selection: ";
				cin >> subChoice;

				//   Error-checking user input
				while (cin.fail() || subChoice < 1 || subChoice > 3)
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "\n";
					cout << "   !!!       Invalid input entered. Please try again.       !!!\n\n" << endl;
					cout << "     Selection: ";
					cin >> subChoice;
				}

				cout << "\n\n   ---       RESULT:       ---" << endl;

				//   Searching for Galaxies from 0 - 1 mly away from Milky Way
				if (subChoice == 1)
				{
					//   If P1 chose the Galaxy Distance correctly
					if (P2_.getGalaxy().getDistFrMW() == "0 - 1 mly")
					{
						cout << "\n     Player 2's Galaxy is 0 - 1 million Light Years from the Milky Way!\n" << endl;

						//   Search P1's Galaxy Roster & remove all listings that aren't the guess
						for (int i = 0; i < P1_.getGalaxyRoster().size(); i++)
						{
							if (P1_.getGalaxyRoster()[i].getDistFrMW() != "0 - 1 mly")
							{
								cout << "     " << P1_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P1_.removeGalaxy(i);
								i--;
							}
						}
					}

					//   P1 chose incorrectly
					else
					{
						cout << "\n     Player 2's Galaxy isn't 0 - 1 million Light Years from the Milky Way!\n" << endl;

						//   Search P1's Galaxy Roster & remove all the listings that are the guess
						for (int i = 0; i < P1_.getGalaxyRoster().size(); i++)
						{
							if (P1_.getGalaxyRoster()[i].getDistFrMW() == "0 - 1 mly")
							{
								cout << "     " << P1_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P1_.removeGalaxy(i);
								i--;
							}
						}
					}
				}

				//   Searching for Galaxies from 1 - 2.5 mly away from Milky Way
				if (subChoice == 2)
				{
					//   If P1 chose the Galaxy Distance correctly
					if (P2_.getGalaxy().getDistFrMW() == "1 - 2.5 mly")
					{
						cout << "\n     Player 2's Galaxy is 1 - 2.5 million Light Years from the Milky Way!\n" << endl;

						//   Search P1's Galaxy Roster & remove all listings that aren't the guess
						for (int i = 0; i < P1_.getGalaxyRoster().size(); i++)
						{
							if (P1_.getGalaxyRoster()[i].getDistFrMW() != "1 - 2.5 mly")
							{
								cout << "     " << P1_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P1_.removeGalaxy(i);
								i--;
							}
						}
					}

					//   P1 chose incorrectly
					else
					{
						cout << "\n     Player 2's Galaxy isn't 1 - 2.5 million Light Years from the Milky Way!\n" << endl;

						//   Search P1's Galaxy Roster & remove all the listings that are the guess
						for (int i = 0; i < P1_.getGalaxyRoster().size(); i++)
						{
							if (P1_.getGalaxyRoster()[i].getDistFrMW() == "1 - 2.5 mly")
							{
								cout << "     " << P1_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P1_.removeGalaxy(i);
								i--;
							}
						}
					}
				}

				//   Searching for Galaxies from 2.5 - 5 mly away from Milky Way
				if (subChoice == 3)
				{
					//   If P1 chose the Galaxy Distance correctly
					if (P2_.getGalaxy().getDistFrMW() == "2.5 - 5 mly")
					{
						cout << "\n     Player 2's Galaxy is 2.5 - 5 million Light Years from the Milky Way!\n" << endl;

						//   Search P1's Galaxy Roster & remove all listings that aren't the guess
						for (int i = 0; i < P1_.getGalaxyRoster().size(); i++)
						{
							if (P1_.getGalaxyRoster()[i].getDistFrMW() != "2.5 - 5 mly")
							{
								cout << "     " << P1_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P1_.removeGalaxy(i);
								i--;
							}
						}
					}

					//   P1 chose incorrectly
					else
					{
						cout << "\n     Player 2's Galaxy isn't 2.5 - 5 million Light Years from the Milky Way!\n" << endl;

						//   Search P1's Galaxy Roster & remove all the listings that are the guess
						for (int i = 0; i < P1_.getGalaxyRoster().size(); i++)
						{
							if (P1_.getGalaxyRoster()[i].getDistFrMW() == "2.5 - 5 mly")
							{
								cout << "     " << P1_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P1_.removeGalaxy(i);
								i--;
							}
						}
					}
				}

				cout << "\n   ---       ^^^^^^^       ---\n" << endl;
			}

			//   Guessing with Galaxy Color
			else if (choice == 4)
			{
			//   Color:	1. White, 2. Lavender, 3. Rainbow, 4. Orange, 5. Purple, 6. Blue, 
			//          7. Brown, 8. Red, 9. Yellow, 10. Unknown
				cout << "\n\n   --------------------------------------------" << endl;
				cout << "   ---      Guessing with Galaxy Color      ---" << endl;
				cout << "   --------------------------------------------\n" << endl;
				cout << "     Enter in the Galaxy Color to guess with:\n" << endl;
				cout << "     1. White" << endl; cout << "     2. Lavender" << endl;
				cout << "     3. Rainbow" << endl; cout << "     4. Orange" << endl;
				cout << "     5. Purple" << endl; cout << "     6. Blue" << endl;
				cout << "     7. Brown" << endl; cout << "     8. Red" << endl;
				cout << "     9. Yellow" << endl; cout << "     10. Unknown" << endl << endl;
				cout << "     Selection: ";
				cin >> subChoice;

				//   Error-checking user input
				while (cin.fail() || subChoice < 1 || subChoice > 10)
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "\n";
					cout << "   !!!       Invalid input entered. Please try again.       !!!\n\n" << endl;
					cout << "     Selection: ";
					cin >> subChoice;
				}

				cout << "\n\n   ---       RESULT:       ---" << endl;

				//   Searching for White Galaxies
				if (subChoice == 1)
				{
					//   If P1 chose the Galaxy Color correctly
					if (P2_.getGalaxy().getColor() == "White")
					{
						cout << "\n     Player 2's Galaxy is White!\n" << endl;

						//   Search P1's Galaxy Roster & remove all listings that aren't the guess
						for (int i = 0; i < P1_.getGalaxyRoster().size(); i++)
						{
							if (P1_.getGalaxyRoster()[i].getColor() != "White")
							{
								cout << "     " << P1_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P1_.removeGalaxy(i);
								i--;
							}
						}
					}

					//   P1 chose incorrectly
					else
					{
						cout << "\n     Player 2's Galaxy isn't White!\n" << endl;

						//   Search P1's Galaxy Roster & remove all the listings that are the guess
						for (int i = 0; i < P1_.getGalaxyRoster().size(); i++)
						{
							if (P1_.getGalaxyRoster()[i].getColor() == "White")
							{
								cout << "     " << P1_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P1_.removeGalaxy(i);
								i--;
							}
						}
					}
				}

				//   Searching for Lavender Galaxies
				if (subChoice == 2)
				{
					//   If P1 chose the Galaxy Color correctly
					if (P2_.getGalaxy().getColor() == "Lavender")
					{
						cout << "\n     Player 2's Galaxy is Lavender!\n" << endl;

						//   Search P1's Galaxy Roster & remove all listings that aren't the guess
						for (int i = 0; i < P1_.getGalaxyRoster().size(); i++)
						{
							if (P1_.getGalaxyRoster()[i].getColor() != "Lavender")
							{
								cout << "     " << P1_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P1_.removeGalaxy(i);
								i--;
							}
						}
					}

					//   P1 chose incorrectly
					else
					{
						cout << "\n     Player 2's Galaxy isn't Lavender!\n" << endl;

						//   Search P1's Galaxy Roster & remove all the listings that are the guess
						for (int i = 0; i < P1_.getGalaxyRoster().size(); i++)
						{
							if (P1_.getGalaxyRoster()[i].getColor() == "Lavender")
							{
								cout << "     " << P1_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P1_.removeGalaxy(i);
								i--;
							}
						}
					}
				}
				
				//   Searching for Rainbow Galaxies
				if (subChoice == 3)
				{
					//   If P1 chose the Galaxy Color correctly
					if (P2_.getGalaxy().getColor() == "Rainbow")
					{
						cout << "\n     Player 2's Galaxy is Rainbow-colored!\n" << endl;

						//   Search P1's Galaxy Roster & remove all listings that aren't the guess
						for (int i = 0; i < P1_.getGalaxyRoster().size(); i++)
						{
							if (P1_.getGalaxyRoster()[i].getColor() != "Rainbow")
							{
								cout << "     " << P1_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P1_.removeGalaxy(i);
								i--;
							}
						}
					}

					//   P1 chose incorrectly
					else
					{
						cout << "\n     Player 2's Galaxy isn't Rainbow-colored!\n" << endl;

						//   Search P1's Galaxy Roster & remove all the listings that are the guess
						for (int i = 0; i < P1_.getGalaxyRoster().size(); i++)
						{
							if (P1_.getGalaxyRoster()[i].getColor() == "Rainbow")
							{
								cout << "     " << P1_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P1_.removeGalaxy(i);
								i--;
							}
						}
					}
				}
				
				//   Searching for Orange Galaxies
				if (subChoice == 4)
				{
					//   If P1 chose the Galaxy Color correctly
					if (P2_.getGalaxy().getColor() == "Orange")
					{
						cout << "\n     Player 2's Galaxy is Orange!\n" << endl;

						//   Search P1's Galaxy Roster & remove all listings that aren't the guess
						for (int i = 0; i < P1_.getGalaxyRoster().size(); i++)
						{
							if (P1_.getGalaxyRoster()[i].getColor() != "Orange")
							{
								cout << "     " << P1_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P1_.removeGalaxy(i);
								i--;
							}
						}
					}

					//   P1 chose incorrectly
					else
					{
						cout << "\n     Player 2's Galaxy isn't Orange!\n" << endl;

						//   Search P1's Galaxy Roster & remove all the listings that are the guess
						for (int i = 0; i < P1_.getGalaxyRoster().size(); i++)
						{
							if (P1_.getGalaxyRoster()[i].getColor() == "Orange")
							{
								cout << "     " << P1_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P1_.removeGalaxy(i);
								i--;
							}
						}
					}
				}
				
				//   Searching for Purple Galaxies
				if (subChoice == 5)
				{
					//   If P1 chose the Galaxy Color correctly
					if (P2_.getGalaxy().getColor() == "Purple")
					{
						cout << "\n     Player 2's Galaxy is Purple!\n" << endl;

						//   Search P1's Galaxy Roster & remove all listings that aren't the guess
						for (int i = 0; i < P1_.getGalaxyRoster().size(); i++)
						{
							if (P1_.getGalaxyRoster()[i].getColor() != "Purple")
							{
								cout << "     " << P1_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P1_.removeGalaxy(i);
								i--;
							}
						}
					}

					//   P1 chose incorrectly
					else
					{
						cout << "\n     Player 2's Galaxy isn't Purple!\n" << endl;

						//   Search P1's Galaxy Roster & remove all the listings that are the guess
						for (int i = 0; i < P1_.getGalaxyRoster().size(); i++)
						{
							if (P1_.getGalaxyRoster()[i].getColor() == "Purple")
							{
								cout << "     " << P1_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P1_.removeGalaxy(i);
								i--;
							}
						}
					}
				}
				
				//   Searching for Blue Galaxies
				if (subChoice == 6)
				{
					//   If P1 chose the Galaxy Color correctly
					if (P2_.getGalaxy().getColor() == "Blue")
					{
						cout << "\n     Player 2's Galaxy is Blue!\n" << endl;

						//   Search P1's Galaxy Roster & remove all listings that aren't the guess
						for (int i = 0; i < P1_.getGalaxyRoster().size(); i++)
						{
							if (P1_.getGalaxyRoster()[i].getColor() != "Blue")
							{
								cout << "     " << P1_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P1_.removeGalaxy(i);
								i--;
							}
						}
					}

					//   P1 chose incorrectly
					else
					{
						cout << "\n     Player 2's Galaxy isn't Blue!\n" << endl;

						//   Search P1's Galaxy Roster & remove all the listings that are the guess
						for (int i = 0; i < P1_.getGalaxyRoster().size(); i++)
						{
							if (P1_.getGalaxyRoster()[i].getColor() == "Blue")
							{
								cout << "     " << P1_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P1_.removeGalaxy(i);
								i--;
							}
						}
					}
				}
				
				//   Searching for Brown Galaxies
				if (subChoice == 7)
				{
					//   If P1 chose the Galaxy Color correctly
					if (P2_.getGalaxy().getColor() == "Brown")
					{
						cout << "\n     Player 2's Galaxy is Brown!\n" << endl;

						//   Search P1's Galaxy Roster & remove all listings that aren't the guess
						for (int i = 0; i < P1_.getGalaxyRoster().size(); i++)
						{
							if (P1_.getGalaxyRoster()[i].getColor() != "Brown")
							{
								cout << "     " << P1_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P1_.removeGalaxy(i);
								i--;
							}
						}
					}

					//   P1 chose incorrectly
					else
					{
						cout << "\n     Player 2's Galaxy isn't Brown!\n" << endl;

						//   Search P1's Galaxy Roster & remove all the listings that are the guess
						for (int i = 0; i < P1_.getGalaxyRoster().size(); i++)
						{
							if (P1_.getGalaxyRoster()[i].getColor() == "Brown")
							{
								cout << "     " << P1_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P1_.removeGalaxy(i);
								i--;
							}
						}
					}
				}
				
				//   Searching for Red Galaxies
				if (subChoice == 8)
				{
					//   If P1 chose the Galaxy Color correctly
					if (P2_.getGalaxy().getColor() == "Red")
					{
						cout << "\n     Player 2's Galaxy is Red!\n" << endl;

						//   Search P1's Galaxy Roster & remove all listings that aren't the guess
						for (int i = 0; i < P1_.getGalaxyRoster().size(); i++)
						{
							if (P1_.getGalaxyRoster()[i].getColor() != "Red")
							{
								cout << "     " << P1_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P1_.removeGalaxy(i);
								i--;
							}
						}
					}

					//   P1 chose incorrectly
					else
					{
						cout << "\n     Player 2's Galaxy isn't Red!\n" << endl;

						//   Search P1's Galaxy Roster & remove all the listings that are the guess
						for (int i = 0; i < P1_.getGalaxyRoster().size(); i++)
						{
							if (P1_.getGalaxyRoster()[i].getColor() == "Red")
							{
								cout << "     " << P1_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P1_.removeGalaxy(i);
								i--;
							}
						}
					}
				}
				
				//   Searching for Yellow Galaxies
				if (subChoice == 9)
				{
					//   If P1 chose the Galaxy Color correctly
					if (P2_.getGalaxy().getColor() == "Yellow")
					{
						cout << "\n     Player 2's Galaxy is Yellow!\n" << endl;

						//   Search P1's Galaxy Roster & remove all listings that aren't the guess
						for (int i = 0; i < P1_.getGalaxyRoster().size(); i++)
						{
							if (P1_.getGalaxyRoster()[i].getColor() != "Yellow")
							{
								cout << "     " << P1_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P1_.removeGalaxy(i);
								i--;
							}
						}
					}

					//   P1 chose incorrectly
					else
					{
						cout << "\n     Player 2's Galaxy isn't Yellow!\n" << endl;

						//   Search P1's Galaxy Roster & remove all the listings that are the guess
						for (int i = 0; i < P1_.getGalaxyRoster().size(); i++)
						{
							if (P1_.getGalaxyRoster()[i].getColor() == "Yellow")
							{
								cout << "     " << P1_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P1_.removeGalaxy(i);
								i--;
							}
						}
					}
				}
				
				//   Searching for Unknown-colored Galaxies
				if (subChoice == 10)
				{
					//   If P1 chose the Galaxy Color correctly
					if (P2_.getGalaxy().getColor() == "Unknown")
					{
						cout << "\n     Player 2's Galaxy is Unknown-colored!\n" << endl;

						//   Search P1's Galaxy Roster & remove all listings that aren't the guess
						for (int i = 0; i < P1_.getGalaxyRoster().size(); i++)
						{
							if (P1_.getGalaxyRoster()[i].getColor() != "Unknown")
							{
								cout << "     " << P1_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P1_.removeGalaxy(i);
								i--;
							}
						}
					}

					//   P1 chose incorrectly
					else
					{
						cout << "\n     Player 2's Galaxy isn't Unknown-colored!\n" << endl;

						//   Search P1's Galaxy Roster & remove all the listings that are the guess
						for (int i = 0; i < P1_.getGalaxyRoster().size(); i++)
						{
							if (P1_.getGalaxyRoster()[i].getColor() == "Unknown")
							{
								cout << "     " << P1_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P1_.removeGalaxy(i);
								i--;
							}
						}
					}
				}

				cout << "\n   ---       ^^^^^^^       ---\n" << endl;
			}

			//   Guessing with Galaxy Sattelite
			else if (choice == 5)
			{
				cout << "\n\n   ------------------------------------------------" << endl;
				cout << "   ---      Guessing with Galaxy Sattelite      ---" << endl;
				cout << "   ------------------------------------------------\n" << endl;
				cout << "     Enter in the Galaxy the opponent's Galaxy orbits around to guess with:\n" << endl;
				cout << "     1. Milky Way" << endl;
				cout << "     2. Andromeda" << endl;
				cout << "     3. Triangulum" << endl;
				cout << "     4. None" << endl << endl;
				cout << "     Selection: ";
				cin >> subChoice;

				//   Error-checking user input
				while (cin.fail() || subChoice < 1 || subChoice > 4)
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "\n";
					cout << "   !!!       Invalid input entered. Please try again.       !!!\n\n" << endl;
					cout << "     Selection: ";
					cin >> subChoice;
				}

				cout << "\n\n   ---       RESULT:       ---" << endl;

				//   Searching for the Milky Way as the galaxy orbitee
				if (subChoice == 1)
				{
					//   If P1 chose the galaxy orbitee correctly
					if (P2_.getGalaxy().getSattlOf() == "Milky Way")
					{
						cout << "\n     Player 2's Galaxy orbits around the Milky Way!\n" << endl;

						//   Search P1's Galaxy Roster & remove all listings that aren't the guess
						for (int i = 0; i < P1_.getGalaxyRoster().size(); i++)
						{
							if (P1_.getGalaxyRoster()[i].getSattlOf() != "Milky Way")
							{
								cout << "     " << P1_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P1_.removeGalaxy(i);
								i--;
							}
						}
					}

					//   P1 chose incorrectly
					else
					{
						cout << "\n     Player 2's Galaxy doesn't orbit around the Milky Way!\n" << endl;

						//   Search P1's Galaxy Roster & remove all the listings that are the guess
						for (int i = 0; i < P1_.getGalaxyRoster().size(); i++)
						{
							if (P1_.getGalaxyRoster()[i].getSattlOf() == "Milky Way")
							{
								cout << "     " << P1_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P1_.removeGalaxy(i);
								i--;
							}
						}
					}
				}

				//   Searching for the Andromeda as the galaxy orbitee
				if (subChoice == 2)
				{
					//   If P1 chose the galaxy orbitee correctly
					if (P2_.getGalaxy().getSattlOf() == "Andromeda")
					{
						cout << "\n     Player 2's Galaxy orbits around Andromeda!\n" << endl;

						//   Search P1's Galaxy Roster & remove all listings that aren't the guess
						for (int i = 0; i < P1_.getGalaxyRoster().size(); i++)
						{
							if (P1_.getGalaxyRoster()[i].getSattlOf() != "Andromeda")
							{
								cout << "     " << P1_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P1_.removeGalaxy(i);
								i--;
							}
						}
					}

					//   P1 chose incorrectly
					else
					{
						cout << "\n     Player 2's Galaxy doesn't orbit around Andromeda!\n" << endl;

						//   Search P1's Galaxy Roster & remove all the listings that are the guess
						for (int i = 0; i < P1_.getGalaxyRoster().size(); i++)
						{
							if (P1_.getGalaxyRoster()[i].getSattlOf() == "Andromeda")
							{
								cout << "     " << P1_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P1_.removeGalaxy(i);
								i--;
							}
						}
					}
				}

				//   Searching for the Triangulum as the galaxy orbitee
				if (subChoice == 3)
				{
					//   If P1 chose the galaxy orbitee correctly
					if (P2_.getGalaxy().getSattlOf() == "Triangulum")
					{
						cout << "\n     Player 2's Galaxy orbits around the Triangulum!\n" << endl;

						//   Search P1's Galaxy Roster & remove all listings that aren't the guess
						for (int i = 0; i < P1_.getGalaxyRoster().size(); i++)
						{
							if (P1_.getGalaxyRoster()[i].getSattlOf() != "Triangulum")
							{
								cout << "     " << P1_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P1_.removeGalaxy(i);
								i--;
							}
						}
					}

					//   P1 chose incorrectly
					else
					{
						cout << "\n     Player 2's Galaxy doesn't orbit around the Triangulum!\n" << endl;

						//   Search P1's Galaxy Roster & remove all the listings that are the guess
						for (int i = 0; i < P1_.getGalaxyRoster().size(); i++)
						{
							if (P1_.getGalaxyRoster()[i].getSattlOf() == "Triangulum")
							{
								cout << "     " << P1_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P1_.removeGalaxy(i);
								i--;
							}
						}
					}
				}

				//   Searching for if the Galaxy doesn't orbit anything
				if (subChoice == 4)
				{
					//   If P1 chose the galaxy orbitee correctly
					if (P2_.getGalaxy().getSattlOf() == "None")
					{
						cout << "\n     Player 2's Galaxy doesn't orbit a galaxy!\n" << endl;

						//   Search P1's Galaxy Roster & remove all listings that aren't the guess
						for (int i = 0; i < P1_.getGalaxyRoster().size(); i++)
						{
							if (P1_.getGalaxyRoster()[i].getSattlOf() != "None")
							{
								cout << "     " << P1_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P1_.removeGalaxy(i);
								i--;
							}
						}
					}

					//   P1 chose incorrectly
					else
					{
						cout << "\n     Player 2's Galaxy does orbit a galaxy!\n" << endl;

						//   Search P1's Galaxy Roster & remove all the listings that are the guess
						for (int i = 0; i < P1_.getGalaxyRoster().size(); i++)
						{
							if (P1_.getGalaxyRoster()[i].getSattlOf() == "None")
							{
								cout << "     " << P1_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P1_.removeGalaxy(i);
								i--;
							}
						}
					}
				}

				cout << "\n   ---       ^^^^^^^       ---\n" << endl;
			}

			endTurn_ = true;
		}

		//   Player Action 3: Perform specific guess on opponent's galaxy
		else if (selectionP1_ == 3)
		{
			//   Warn the player that an incorrect specific guess will cost them the game
			cout << "\n   !!!       WARNING!       !!!       WARNING!       !!!\n" << endl;
			cout << "     An incorrect guess is an immediate loss. Do you wish to continue?" << endl;
			cout << "     Enter in (Y) for Yes, any other key for No:\n" << endl;
			cout << "     > ";
			cin >> finalChoice;

			finalChoice = toupper(finalChoice);

			

			//   Player wishes to continue
			if (finalChoice == 'Y')
			{
				cout << "\n   =============================================" << endl;
				cout << "   ===          Make a Specific Guess        ===" << endl;
				cout << "   =============================================\n" << endl;
				cout << "     Enter in the Galaxy Number of your guess:\n" << endl;
				cout << "     > ";
				cin >> choice;

				//   Error-checking user input
				while (cin.fail() || choice < 1 || choice > 51)
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "\n";
					cout << "   !!!       Invalid input entered. Please try again.       !!!\n\n" << endl;
					cout << "     > ";
					cin >> choice;
				}

				//   Displaying Player's final guess
				for (int i = 0; i < P1_.getGalaxyRoster().size(); i++)
				{
					if (P1_.getGalaxyRoster()[i].getNumber() == choice)
					{subChoice = i;}
				}

				cout << "\n\n     Your guess is:" << endl;
				cout << "   --------------------------------------------------------------------------------------------\n" << endl;
				cout << "     "; P1_.getGalaxyRoster()[subChoice].display(); cout << endl;
				cout << "   --------------------------------------------------------------------------------------------\n" << endl;
				cout << "     Is this your final guess? Enter in Y for Yes, any other key for No:\n" << endl;
				cout << "     > ";
				cin >> finalChoice;

				finalChoice = toupper(finalChoice);

				cout << "\n\n\n\n\n\n\n\n\n\n" << endl;

				//   Confirms final choice
				if (finalChoice == 'Y')
				{
					//   If final choice is opponent's galaxy, Player wins
					if (P1_.getGalaxyRoster()[subChoice].getNumber() == P2_.getGalaxy().getNumber())
					{
						cout << "    /$$$$$$                                                /$$             /$$            /$$   /$$" << endl;
						cout << "   /$$__  $$                                              | $$            | $$           | $$  |__/" << endl;
						cout << "  | $$  \\__/ /$$$$$$  /$$$$$$$  /$$$$$$  /$$$$$$ /$$$$$$ /$$$$$$   /$$  /$| $$ /$$$$$$ /$$$$$$  /$$ /$$$$$$ /$$$$$$$  /$$$$$$$" << endl;
						cout << "  | $$      /$$__  $ | $$__  $$/$$__  $$/$$__  $|____  $|_  $$_/  | $$ | $| $$|____  $|_  $$_/ | $$/$$__  $| $$__  $$/$$_____/" << endl;
						cout << "  | $$     | $$  \\ $ | $$  \\ $| $$  \\ $| $$  \\__//$$$$$$$ | $$    | $$ | $| $$ /$$$$$$$ | $$   | $| $$  \\ $| $$  \\ $|  $$$$$$" << endl;
						cout << "  | $$    $| $$  | $ | $$  | $| $$  | $| $$     /$$__  $$ | $$ /$ | $$ | $| $$/$$__  $$ | $$ /$| $| $$  | $| $$  | $$\\____  $$" << endl;
						cout << "  |  $$$$$$ | $$$$$$ | $$  | $|  $$$$$$| $$    |  $$$$$$$ |  $$$$ | $$$$$$| $|  $$$$$$$ |  $$$$| $|  $$$$$$| $$  | $$/$$$$$$$/" << endl;
						cout << "   \\______ / \\______/|__/  |__ /\\____ $|__/     \\_______/  \\___ / \\______/|__/\\_______/  \\___/ |__/\\______/|__/  |__|_______/" << endl;
						cout << "                                /$$  \\ $$" << endl;
						cout << "                               |  $$$$$$/" << endl;
						cout << "                                \\______/" << endl << endl;
						cout << "\n     Congratulations! Player 1 wins!\n" << endl;
					}

					//   If final choice wasn't opponent's galaxy, opponent wins
					else
					{
						cout << "    /$$$$$$                                       /$$$$$$" << endl;
						cout << "   /$$__  $$                                     /$$__  $$" << endl;
						cout << "  | $$  \\__/ /$$$$$$ /$$$$$$/$$$$  /$$$$$$      | $$  \\ $$/$$    /$$/$$$$$$  /$$$$$$" << endl;
						cout << "  | $$ /$$$$|____  $| $$_  $$_  $$/$$__  $$     | $$  | $|  $$  /$$/$$__  $$/$$__  $$" << endl;
						cout << "  | $$|_  $$ /$$$$$$| $$ \\ $$ \\ $| $$$$$$$$     | $$  | $$\\  $$/$$| $$$$$$$| $$  \\__/" << endl;
						cout << "  | $$  \\ $$/$$__  $| $$ | $$ | $| $$_____/     | $$  | $$ \\  $$$/| $$_____| $$" << endl;
						cout << "  |  $$$$$$|  $$$$$$| $$ | $$ | $| $$$$$$$      |  $$$$$$/  \\  $/ |  $$$$$$| $$" << endl;
						cout << "   \\______/ \\_______|__/ |__/ |__/\\_______/      \\______/    \\_/   \\_______|__/" << endl << endl;
						cout << "\n     Game Over! Player 1 Lost!\n" << endl;
						cout << "     Player 2 wins!\n" << endl;
					}

					//   Ends the game
					endGame_ = true;
					return;
				}

				else
				{cout << "\n" << endl;}
			}

			else
			{cout << "\n" << endl;}
		}
	}

	//   Player 2's Turn
	else if(turn_ == 1)
	{
		//   Player Action 1: Display list of opponent's possible galaxies
		if (selectionP2_ == 1)
		{
			cout << "\n   --------------------------------------------------" << endl;
			cout << "   ---     Display Remaining Possible Galaxies    ---" << endl;
			cout << "   --------------------------------------------------\n" << endl;
			cout << "     Player 1's possible galaxies:" << endl;
			cout << "   ------------------------------------------------------------------------------------------------------------" << endl;
			cout << "     ##  Galaxy Name                Type                Size         Distance from     Color       Sattelite" << endl;
			cout << "                                                                     Milky Way                     of ________\n" << endl;

			P2_.dispAllGalaxies();

			cout << "   ------------------------------------------------------------------------------------------------------------" << endl;

			cout << "\n" << endl;
		}

		//   Player Action 2: Perform general guess on opponent's galaxy
		else if (selectionP2_ == 2)
		{
			cout << "\n   ============================================" << endl;
			cout << "   ===          Make a General Guess        ===" << endl;
			cout << "   ============================================\n" << endl;
			cout << "     Choose a criteria to guess with:\n" << endl;
			cout << "     1. Type" << endl;
			cout << "     2. Size" << endl;
			cout << "     3. Distance from Milky Way" << endl;
			cout << "     4. Color" << endl;
			cout << "     5. Sattelite of _______\n" << endl;
			cout << "     Selection: ";
			cin >> choice;

			//   Error-checking user input
			while (cin.fail() || choice < 1 || choice > 5)
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "\n";
				cout << "   !!!       Invalid input entered. Please try again.       !!!\n\n" << endl;
				cout << "     Selection: ";
				cin >> choice;
			}

			//   Guessing with Galaxy Type
			if (choice == 1)
			{
				cout << "\n\n   -------------------------------------------" << endl;
				cout << "   ---      Guessing with Galaxy Type      ---" << endl;
				cout << "   -------------------------------------------\n" << endl;
				cout << "     Enter in the Type of Galaxy to guess with: \n" << endl;
				cout << "     1. Barred Spiral" << endl;
				cout << "     2. Spheroidal" << endl;
				cout << "     3. Magellanic Spiral" << endl;
				cout << "     4. Elliptical" << endl;
				cout << "     5. Irregular" << endl;
				cout << "     6. Spiral" << endl << endl;
				cout << "     Selection: ";
				cin >> subChoice;

				//   Error-checking user input
				while (cin.fail() || subChoice < 1 || subChoice > 6)
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "\n";
					cout << "   !!!       Invalid input entered. Please try again.       !!!\n\n" << endl;
					cout << "     Selection: ";
					cin >> subChoice;
				}

				cout << "\n\n   ---       RESULT:       ---" << endl;

				//   Searching for Barred Spiral Galaxies
				if (subChoice == 1)
				{
					//   If P2 chose the Galaxy Type correctly
					if (P1_.getGalaxy().getType() == "Barred Spiral")
					{
						cout << "\n     Player 1's Galaxy is a Barred Spiral!\n" << endl;

						//   Search P2's Galaxy Roster & remove all listings that aren't the guess
						for (int i = 0; i < P2_.getGalaxyRoster().size(); i++)
						{
							if (P2_.getGalaxyRoster()[i].getType() != "Barred Spiral")
							{
								cout << "     " << P2_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P2_.removeGalaxy(i);
								i--;
							}
						}
					}

					//   P2 chose incorrectly
					else
					{
						cout << "\n     Player 1's Galaxy isn't a Barred Spiral!\n" << endl;

						//   Search P2's Galaxy Roster & remove all the listings that are the guess
						for (int i = 0; i < P2_.getGalaxyRoster().size(); i++)
						{
							if (P2_.getGalaxyRoster()[i].getType() == "Barred Spiral")
							{
								cout << "     " << P2_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P2_.removeGalaxy(i);
								i--;
							}
						}
					}
				}

				//   Searching for Spheroidal Galaxies
				else if (subChoice == 2)
				{
					//   If P2 chose the Galaxy Type correctly
					if (P1_.getGalaxy().getType() == "Spheroidal")
					{
						cout << "\n     Player 1's Galaxy is a Spheroidal!\n" << endl;

						//   Search P2's Galaxy Roster & remove all listings that aren't the guess
						for (int i = 0; i < P2_.getGalaxyRoster().size(); i++)
						{
							if (P2_.getGalaxyRoster()[i].getType() != "Spheroidal")
							{
								cout << "     " << P2_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P2_.removeGalaxy(i);
								i--;
							}
						}
					}

					//   P2 chose incorrectly
					else
					{
						cout << "\n     Player 1's Galaxy isn't a Spheroidal!\n" << endl;

						//   Search P2's Galaxy Roster & remove all the listings that are the guess
						for (int i = 0; i < P2_.getGalaxyRoster().size(); i++)
						{
							if (P2_.getGalaxyRoster()[i].getType() == "Spheroidal")
							{
								cout << "     " << P2_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P2_.removeGalaxy(i);
								i--;
							}
						}
					}
				}

				//   Searching for Magellanic Spiral Galaxies
				else if (subChoice == 3)
				{
					//   If P2 chose the Galaxy Type correctly
					if (P1_.getGalaxy().getType() == "Magellanic Spiral")
					{
						cout << "\n     Player 1's Galaxy is a Magellanic Spiral!\n" << endl;

						//   Search P2's Galaxy Roster & remove all listings that aren't the guess
						for (int i = 0; i < P2_.getGalaxyRoster().size(); i++)
						{
							if (P2_.getGalaxyRoster()[i].getType() != "Magellanic Spiral")
							{
								cout << "     " << P2_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P2_.removeGalaxy(i);
								i--;
							}
						}
					}

					//   P2 chose incorrectly
					else
					{
						cout << "\n     Player 1's Galaxy isn't a Magellanic Spiral!\n" << endl;

						//   Search P2's Galaxy Roster & remove all the listings that are the guess
						for (int i = 0; i < P2_.getGalaxyRoster().size(); i++)
						{
							if (P2_.getGalaxyRoster()[i].getType() == "Magellanic Spiral")
							{
								cout << "     " << P2_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P2_.removeGalaxy(i);
								i--;
							}
						}
					}
				}

				//   Searching for Elliptical Galaxies
				else if (subChoice == 4)
				{
					//   If P2 chose the Galaxy Type correctly
					if (P1_.getGalaxy().getType() == "Elliptical")
					{
						cout << "\n     Player 1's Galaxy is an Elliptical!\n" << endl;

						//   Search P2's Galaxy Roster & remove all listings that aren't the guess
						for (int i = 0; i < P2_.getGalaxyRoster().size(); i++)
						{
							if (P2_.getGalaxyRoster()[i].getType() != "Elliptical")
							{
								cout << "     " << P2_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P2_.removeGalaxy(i);
								i--;
							}
						}
					}

					//   P2 chose incorrectly
					else
					{
						cout << "\n     Player 1's Galaxy isn't an Elliptical!\n" << endl;

						//   Search P2's Galaxy Roster & remove all the listings that are the guess
						for (int i = 0; i < P2_.getGalaxyRoster().size(); i++)
						{
							if (P2_.getGalaxyRoster()[i].getType() == "Elliptical")
							{
								cout << "     " << P2_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P2_.removeGalaxy(i);
								i--;
							}
						}
					}
				}

				//   Searching for Irregular Galaxies
				else if (subChoice == 5)
				{
					//   If P2 chose the Galaxy Type correctly
					if (P1_.getGalaxy().getType() == "Irregular")
					{
						cout << "\n     Player 1's Galaxy is an Irregular!\n" << endl;

						//   Search P2's Galaxy Roster & remove all listings that aren't the guess
						for (int i = 0; i < P2_.getGalaxyRoster().size(); i++)
						{
							if (P2_.getGalaxyRoster()[i].getType() != "Irregular")
							{
								cout << "     " << P2_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P2_.removeGalaxy(i);
								i--;
							}
						}
					}

					//   P2 chose incorrectly
					else
					{
						cout << "\n     Player 1's Galaxy isn't an Irregular!\n" << endl;

						//   Search P2's Galaxy Roster & remove all the listings that are the guess
						for (int i = 0; i < P2_.getGalaxyRoster().size(); i++)
						{
							if (P2_.getGalaxyRoster()[i].getType() == "Irregular")
							{
								cout << "     " << P2_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P2_.removeGalaxy(i);
								i--;
							}
						}
					}
				}

				//   Searching for Spiral Galaxies
				else if (subChoice == 6)
				{
					//   If P2 chose the Galaxy Type correctly
					if (P1_.getGalaxy().getType() == "Spiral")
					{
						cout << "\n     Player 1's Galaxy is a Spiral!\n" << endl;

						//   Search P2's Galaxy Roster & remove all listings that aren't the guess
						for (int i = 0; i < P2_.getGalaxyRoster().size(); i++)
						{
							if (P2_.getGalaxyRoster()[i].getType() != "Spiral")
							{
								cout << "     " << P2_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P2_.removeGalaxy(i);
								i--;
							}
						}
					}

					//   P2 chose incorrectly
					else
					{
						cout << "\n     Player 1's Galaxy isn't a Spiral!\n" << endl;

						//   Search P2's Galaxy Roster & remove all the listings that are the guess
						for (int i = 0; i < P2_.getGalaxyRoster().size(); i++)
						{
							if (P2_.getGalaxyRoster()[i].getType() == "Spiral")
							{
								cout << "     " << P2_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P2_.removeGalaxy(i);
								i--;
							}
						}
					}
				}

				cout << "\n   ---       ^^^^^^^       ---\n" << endl;
			}

			//   Guessing with Galaxy Size
			else if (choice == 2)
			{
				cout << "\n\n   -------------------------------------------" << endl;
				cout << "   ---      Guessing with Galaxy Size      ---" << endl;
				cout << "   -------------------------------------------\n" << endl;
				cout << "     Enter in the Size of Galaxy to guess with: \n" << endl;
				cout << "     1. Dwarf" << endl;
				cout << "     2. Non-Dwarf" << endl << endl;
				cout << "     Selection: ";
				cin >> subChoice;

				//   Error-checking user input
				while (cin.fail() || subChoice < 1 || subChoice > 2)
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "\n";
					cout << "   !!!       Invalid input entered. Please try again.       !!!\n\n" << endl;
					cout << "     Selection: ";
					cin >> subChoice;
				}

				cout << "\n\n   ---       RESULT:       ---" << endl;

				//   Searching for Dwarf Galaxies
				if (subChoice == 1)
				{
					//   If P2 chose the Galaxy Size correctly
					if (P1_.getGalaxy().getSize() == "Dwarf")
					{
						cout << "\n     Player 1's Galaxy is a Dwarf Galaxy!\n" << endl;

						//   Search P2's Galaxy Roster & remove all listings that aren't the guess
						for (int i = 0; i < P2_.getGalaxyRoster().size(); i++)
						{
							if (P2_.getGalaxyRoster()[i].getSize() != "Dwarf")
							{
								cout << "     " << P2_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P2_.removeGalaxy(i);
								i--;
							}
						}
					}

					//   P2 chose incorrectly
					else
					{
						cout << "\n     Player 1's Galaxy isn't a Dwarf Galaxy!\n" << endl;

						//   Search P2's Galaxy Roster & remove all the listings that are the guess
						for (int i = 0; i < P2_.getGalaxyRoster().size(); i++)
						{
							if (P2_.getGalaxyRoster()[i].getSize() == "Dwarf")
							{
								cout << "     " << P2_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P2_.removeGalaxy(i);
								i--;
							}
						}
					}
				}

				//   Searching for Non-Dwarf Galaxies
				else
				{
					//   If P2 chose the Galaxy Size correctly
					if (P1_.getGalaxy().getSize() == "Non-Dwarf")
					{
						cout << "\n     Player 1's Galaxy is a Non-Dwarf Galaxy!\n" << endl;

						//   Search P2's Galaxy Roster & remove all listings that aren't the guess
						for (int i = 0; i < P2_.getGalaxyRoster().size(); i++)
						{
							if (P2_.getGalaxyRoster()[i].getSize() != "Non-Dwarf")
							{
								cout << "     " << P2_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P2_.removeGalaxy(i);
								i--;
							}
						}
					}

					//   P2 chose incorrectly
					else
					{
						cout << "\n     Player 1's Galaxy isn't a Non-Dwarf Galaxy!\n" << endl;

						//   Search P2's Galaxy Roster & remove all the listings that are the guess
						for (int i = 0; i < P2_.getGalaxyRoster().size(); i++)
						{
							if (P2_.getGalaxyRoster()[i].getSize() == "Non-Dwarf")
							{
								cout << "     " << P2_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P2_.removeGalaxy(i);
								i--;
							}
						}
					}
				}

				cout << "\n   ---       ^^^^^^^       ---\n" << endl;
			}

			//   Guessing with Galaxy Distance
			else if (choice == 3)
			{
				cout << "\n\n   -----------------------------------------------" << endl;
				cout << "   ---      Guessing with Galaxy Distance      ---" << endl;
				cout << "   -----------------------------------------------\n" << endl;
				cout << "     Enter in the Distance from the Milky Way Galaxy to guess with:\n" << endl;
				cout << "     1. 0 - 1 million Light Years" << endl;
				cout << "     2. 1 - 2.5 million Light Years" << endl;
				cout << "     3. 2.5 - 5 million Light Years" << endl << endl;
				cout << "     Selection: ";
				cin >> subChoice;

				//   Error-checking user input
				while (cin.fail() || subChoice < 1 || subChoice > 3)
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "\n";
					cout << "   !!!       Invalid input entered. Please try again.       !!!\n\n" << endl;
					cout << "     Selection: ";
					cin >> subChoice;
				}

				cout << "\n\n   ---       RESULT:       ---" << endl;

				//   Searching for Galaxies from 0 - 1 mly away from Milky Way
				if (subChoice == 1)
				{
					//   If P2 chose the Galaxy Distance correctly
					if (P1_.getGalaxy().getDistFrMW() == "0 - 1 mly")
					{
						cout << "\n     Player 1's Galaxy is 0 - 1 million Light Years from the Milky Way!\n" << endl;

						//   Search P2's Galaxy Roster & remove all listings that aren't the guess
						for (int i = 0; i < P2_.getGalaxyRoster().size(); i++)
						{
							if (P2_.getGalaxyRoster()[i].getDistFrMW() != "0 - 1 mly")
							{
								cout << "     " << P2_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P2_.removeGalaxy(i);
								i--;
							}
						}
					}

					//   P2 chose incorrectly
					else
					{
						cout << "\n     Player 1's Galaxy isn't 0 - 1 million Light Years from the Milky Way!\n" << endl;

						//   Search P2's Galaxy Roster & remove all the listings that are the guess
						for (int i = 0; i < P2_.getGalaxyRoster().size(); i++)
						{
							if (P2_.getGalaxyRoster()[i].getDistFrMW() == "0 - 1 mly")
							{
								cout << "     " << P2_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P2_.removeGalaxy(i);
								i--;
							}
						}
					}
				}

				//   Searching for Galaxies from 1 - 2.5 mly away from Milky Way
				if (subChoice == 2)
				{
					//   If P2 chose the Galaxy Distance correctly
					if (P1_.getGalaxy().getDistFrMW() == "1 - 2.5 mly")
					{
						cout << "\n     Player 1's Galaxy is 1 - 2.5 million Light Years from the Milky Way!\n" << endl;

						//   Search P2's Galaxy Roster & remove all listings that aren't the guess
						for (int i = 0; i < P2_.getGalaxyRoster().size(); i++)
						{
							if (P2_.getGalaxyRoster()[i].getDistFrMW() != "1 - 2.5 mly")
							{
								cout << "     " << P2_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P2_.removeGalaxy(i);
								i--;
							}
						}
					}

					//   P2 chose incorrectly
					else
					{
						cout << "\n     Player 1's Galaxy isn't 1 - 2.5 million Light Years from the Milky Way!\n" << endl;

						//   Search P2's Galaxy Roster & remove all the listings that are the guess
						for (int i = 0; i < P2_.getGalaxyRoster().size(); i++)
						{
							if (P2_.getGalaxyRoster()[i].getDistFrMW() == "1 - 2.5 mly")
							{
								cout << "     " << P2_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P2_.removeGalaxy(i);
								i--;
							}
						}
					}
				}

				//   Searching for Galaxies from 2.5 - 5 mly away from Milky Way
				if (subChoice == 3)
				{
					//   If P2 chose the Galaxy Distance correctly
					if (P1_.getGalaxy().getDistFrMW() == "2.5 - 5 mly")
					{
						cout << "\n     Player 2's Galaxy is 2.5 - 5 million Light Years from the Milky Way!\n" << endl;

						//   Search P2's Galaxy Roster & remove all listings that aren't the guess
						for (int i = 0; i < P2_.getGalaxyRoster().size(); i++)
						{
							if (P2_.getGalaxyRoster()[i].getDistFrMW() != "2.5 - 5 mly")
							{
								cout << "     " << P2_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P2_.removeGalaxy(i);
								i--;
							}
						}
					}

					//   P2 chose incorrectly
					else
					{
						cout << "\n     Player 1's Galaxy isn't 2.5 - 5 million Light Years from the Milky Way!\n" << endl;

						//   Search P2's Galaxy Roster & remove all the listings that are the guess
						for (int i = 0; i < P2_.getGalaxyRoster().size(); i++)
						{
							if (P2_.getGalaxyRoster()[i].getDistFrMW() == "2.5 - 5 mly")
							{
								cout << "     " << P2_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P2_.removeGalaxy(i);
								i--;
							}
						}
					}
				}

				cout << "\n   ---       ^^^^^^^       ---\n" << endl;
			}

			//   Guessing with Galaxy Color
			else if (choice == 4)
			{
				//   Color:	1. White, 2. Lavender, 3. Rainbow, 4. Orange, 5. Purple, 6. Blue, 
				//          7. Brown, 8. Red, 9. Yellow, 10. Unknown
				cout << "\n\n   --------------------------------------------" << endl;
				cout << "   ---      Guessing with Galaxy Color      ---" << endl;
				cout << "   --------------------------------------------\n" << endl;
				cout << "     Enter in the Galaxy Color to guess with:\n" << endl;
				cout << "     1. White" << endl; cout << "     2. Lavender" << endl;
				cout << "     3. Rainbow" << endl; cout << "     4. Orange" << endl;
				cout << "     5. Purple" << endl; cout << "     6. Blue" << endl;
				cout << "     7. Brown" << endl; cout << "     8. Red" << endl;
				cout << "     9. Yellow" << endl; cout << "     10. Unknown" << endl << endl;
				cout << "     Selection: ";
				cin >> subChoice;

				//   Error-checking user input
				while (cin.fail() || subChoice < 1 || subChoice > 10)
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "\n";
					cout << "   !!!       Invalid input entered. Please try again.       !!!\n\n" << endl;
					cout << "     Selection: ";
					cin >> subChoice;
				}

				cout << "\n\n   ---       RESULT:       ---" << endl;

				//   Searching for White Galaxies
				if (subChoice == 1)
				{
					//   If P2 chose the Galaxy Color correctly
					if (P1_.getGalaxy().getColor() == "White")
					{
						cout << "\n     Player 1's Galaxy is White!\n" << endl;

						//   Search P2's Galaxy Roster & remove all listings that aren't the guess
						for (int i = 0; i < P2_.getGalaxyRoster().size(); i++)
						{
							if (P2_.getGalaxyRoster()[i].getColor() != "White")
							{
								cout << "     " << P2_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P2_.removeGalaxy(i);
								i--;
							}
						}
					}

					//   P2 chose incorrectly
					else
					{
						cout << "\n     Player 1's Galaxy isn't White!\n" << endl;

						//   Search P2's Galaxy Roster & remove all the listings that are the guess
						for (int i = 0; i < P2_.getGalaxyRoster().size(); i++)
						{
							if (P2_.getGalaxyRoster()[i].getColor() == "White")
							{
								cout << "     " << P2_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P2_.removeGalaxy(i);
								i--;
							}
						}
					}
				}

				//   Searching for Lavender Galaxies
				if (subChoice == 2)
				{
					//   If P2 chose the Galaxy Color correctly
					if (P1_.getGalaxy().getColor() == "Lavender")
					{
						cout << "\n     Player 1's Galaxy is Lavender!\n" << endl;

						//   Search P2's Galaxy Roster & remove all listings that aren't the guess
						for (int i = 0; i < P2_.getGalaxyRoster().size(); i++)
						{
							if (P2_.getGalaxyRoster()[i].getColor() != "Lavender")
							{
								cout << "     " << P2_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P2_.removeGalaxy(i);
								i--;
							}
						}
					}

					//   P2 chose incorrectly
					else
					{
						cout << "\n     Player 1's Galaxy isn't Lavender!\n" << endl;

						//   Search P2's Galaxy Roster & remove all the listings that are the guess
						for (int i = 0; i < P2_.getGalaxyRoster().size(); i++)
						{
							if (P2_.getGalaxyRoster()[i].getColor() == "Lavender")
							{
								cout << "     " << P2_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P2_.removeGalaxy(i);
								i--;
							}
						}
					}
				}

				//   Searching for Rainbow Galaxies
				if (subChoice == 3)
				{
					//   If P2 chose the Galaxy Color correctly
					if (P1_.getGalaxy().getColor() == "Rainbow")
					{
						cout << "\n     Player 1's Galaxy is Rainbow-colored!\n" << endl;

						//   Search P2's Galaxy Roster & remove all listings that aren't the guess
						for (int i = 0; i < P2_.getGalaxyRoster().size(); i++)
						{
							if (P2_.getGalaxyRoster()[i].getColor() != "Rainbow")
							{
								cout << "     " << P2_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P2_.removeGalaxy(i);
								i--;
							}
						}
					}

					//   P2 chose incorrectly
					else
					{
						cout << "\n     Player 1's Galaxy isn't Rainbow-colored!\n" << endl;

						//   Search P2's Galaxy Roster & remove all the listings that are the guess
						for (int i = 0; i < P2_.getGalaxyRoster().size(); i++)
						{
							if (P2_.getGalaxyRoster()[i].getColor() == "Rainbow")
							{
								cout << "     " << P2_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P2_.removeGalaxy(i);
								i--;
							}
						}
					}
				}

				//   Searching for Orange Galaxies
				if (subChoice == 4)
				{
					//   If P2 chose the Galaxy Color correctly
					if (P1_.getGalaxy().getColor() == "Orange")
					{
						cout << "\n     Player 1's Galaxy is Orange!\n" << endl;

						//   Search P2's Galaxy Roster & remove all listings that aren't the guess
						for (int i = 0; i < P2_.getGalaxyRoster().size(); i++)
						{
							if (P2_.getGalaxyRoster()[i].getColor() != "Orange")
							{
								cout << "     " << P2_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P2_.removeGalaxy(i);
								i--;
							}
						}
					}

					//   P2 chose incorrectly
					else
					{
						cout << "\n     Player 1's Galaxy isn't Orange!\n" << endl;

						//   Search P2's Galaxy Roster & remove all the listings that are the guess
						for (int i = 0; i < P2_.getGalaxyRoster().size(); i++)
						{
							if (P2_.getGalaxyRoster()[i].getColor() == "Orange")
							{
								cout << "     " << P2_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P2_.removeGalaxy(i);
								i--;
							}
						}
					}
				}

				//   Searching for Purple Galaxies
				if (subChoice == 5)
				{
					//   If P2 chose the Galaxy Color correctly
					if (P1_.getGalaxy().getColor() == "Purple")
					{
						cout << "\n     Player 1's Galaxy is Purple!\n" << endl;

						//   Search P2's Galaxy Roster & remove all listings that aren't the guess
						for (int i = 0; i < P2_.getGalaxyRoster().size(); i++)
						{
							if (P2_.getGalaxyRoster()[i].getColor() != "Purple")
							{
								cout << "     " << P2_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P2_.removeGalaxy(i);
								i--;
							}
						}
					}

					//   P2 chose incorrectly
					else
					{
						cout << "\n     Player 1's Galaxy isn't Purple!\n" << endl;

						//   Search P2's Galaxy Roster & remove all the listings that are the guess
						for (int i = 0; i < P2_.getGalaxyRoster().size(); i++)
						{
							if (P2_.getGalaxyRoster()[i].getColor() == "Purple")
							{
								cout << "     " << P2_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P2_.removeGalaxy(i);
								i--;
							}
						}
					}
				}

				//   Searching for Blue Galaxies
				if (subChoice == 6)
				{
					//   If P2 chose the Galaxy Color correctly
					if (P1_.getGalaxy().getColor() == "Blue")
					{
						cout << "\n     Player 1's Galaxy is Blue!\n" << endl;

						//   Search P2's Galaxy Roster & remove all listings that aren't the guess
						for (int i = 0; i < P2_.getGalaxyRoster().size(); i++)
						{
							if (P2_.getGalaxyRoster()[i].getColor() != "Blue")
							{
								cout << "     " << P2_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P2_.removeGalaxy(i);
								i--;
							}
						}
					}

					//   P2 chose incorrectly
					else
					{
						cout << "\n     Player 1's Galaxy isn't Blue!\n" << endl;

						//   Search P2's Galaxy Roster & remove all the listings that are the guess
						for (int i = 0; i < P2_.getGalaxyRoster().size(); i++)
						{
							if (P2_.getGalaxyRoster()[i].getColor() == "Blue")
							{
								cout << "     " << P2_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P2_.removeGalaxy(i);
								i--;
							}
						}
					}
				}

				//   Searching for Brown Galaxies
				if (subChoice == 7)
				{
					//   If P2 chose the Galaxy Color correctly
					if (P1_.getGalaxy().getColor() == "Brown")
					{
						cout << "\n     Player 1's Galaxy is Brown!\n" << endl;

						//   Search P2's Galaxy Roster & remove all listings that aren't the guess
						for (int i = 0; i < P2_.getGalaxyRoster().size(); i++)
						{
							if (P2_.getGalaxyRoster()[i].getColor() != "Brown")
							{
								cout << "     " << P2_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P2_.removeGalaxy(i);
								i--;
							}
						}
					}

					//   P2 chose incorrectly
					else
					{
						cout << "\n     Player 1's Galaxy isn't Brown!\n" << endl;

						//   Search P2's Galaxy Roster & remove all the listings that are the guess
						for (int i = 0; i < P2_.getGalaxyRoster().size(); i++)
						{
							if (P2_.getGalaxyRoster()[i].getColor() == "Brown")
							{
								cout << "     " << P2_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P2_.removeGalaxy(i);
								i--;
							}
						}
					}
				}

				//   Searching for Red Galaxies
				if (subChoice == 8)
				{
					//   If P2 chose the Galaxy Color correctly
					if (P1_.getGalaxy().getColor() == "Red")
					{
						cout << "\n     Player 1's Galaxy is Red!\n" << endl;

						//   Search P2's Galaxy Roster & remove all listings that aren't the guess
						for (int i = 0; i < P2_.getGalaxyRoster().size(); i++)
						{
							if (P2_.getGalaxyRoster()[i].getColor() != "Red")
							{
								cout << "     " << P2_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P2_.removeGalaxy(i);
								i--;
							}
						}
					}

					//   P2 chose incorrectly
					else
					{
						cout << "\n     Player 1's Galaxy isn't Red!\n" << endl;

						//   Search P2's Galaxy Roster & remove all the listings that are the guess
						for (int i = 0; i < P2_.getGalaxyRoster().size(); i++)
						{
							if (P2_.getGalaxyRoster()[i].getColor() == "Red")
							{
								cout << "     " << P2_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P2_.removeGalaxy(i);
								i--;
							}
						}
					}
				}

				//   Searching for Yellow Galaxies
				if (subChoice == 9)
				{
					//   If P2 chose the Galaxy Color correctly
					if (P1_.getGalaxy().getColor() == "Yellow")
					{
						cout << "\n     Player 1's Galaxy is Yellow!\n" << endl;

						//   Search P2's Galaxy Roster & remove all listings that aren't the guess
						for (int i = 0; i < P2_.getGalaxyRoster().size(); i++)
						{
							if (P2_.getGalaxyRoster()[i].getColor() != "Yellow")
							{
								cout << "     " << P2_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P2_.removeGalaxy(i);
								i--;
							}
						}
					}

					//   P2 chose incorrectly
					else
					{
						cout << "\n     Player 1's Galaxy isn't Yellow!\n" << endl;

						//   Search P2's Galaxy Roster & remove all the listings that are the guess
						for (int i = 0; i < P2_.getGalaxyRoster().size(); i++)
						{
							if (P2_.getGalaxyRoster()[i].getColor() == "Yellow")
							{
								cout << "     " << P2_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P2_.removeGalaxy(i);
								i--;
							}
						}
					}
				}

				//   Searching for Unknown-colored Galaxies
				if (subChoice == 10)
				{
					//   If P2 chose the Galaxy Color correctly
					if (P1_.getGalaxy().getColor() == "Unknown")
					{
						cout << "\n     Player 1's Galaxy is Unknown-colored!\n" << endl;

						//   Search P2's Galaxy Roster & remove all listings that aren't the guess
						for (int i = 0; i < P2_.getGalaxyRoster().size(); i++)
						{
							if (P2_.getGalaxyRoster()[i].getColor() != "Unknown")
							{
								cout << "     " << P2_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P2_.removeGalaxy(i);
								i--;
							}
						}
					}

					//   P2 chose incorrectly
					else
					{
						cout << "\n     Player 1's Galaxy isn't Unknown-colored!\n" << endl;

						//   Search P2's Galaxy Roster & remove all the listings that are the guess
						for (int i = 0; i < P2_.getGalaxyRoster().size(); i++)
						{
							if (P2_.getGalaxyRoster()[i].getColor() == "Unknown")
							{
								cout << "     " << P2_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P2_.removeGalaxy(i);
								i--;
							}
						}
					}
				}

				cout << "\n   ---       ^^^^^^^       ---\n" << endl;
			}

			//   Guessing with Galaxy Sattelite
			else
			{
				cout << "\n\n   ------------------------------------------------" << endl;
				cout << "   ---      Guessing with Galaxy Sattelite      ---" << endl;
				cout << "   ------------------------------------------------\n" << endl;
				cout << "     Enter in the Galaxy the opponent's Galaxy orbits around to guess with:\n" << endl;
				cout << "     1. Milky Way" << endl;
				cout << "     2. Andromeda" << endl;
				cout << "     3. Triangulum" << endl;
				cout << "     4. None" << endl << endl;
				cout << "     Selection: ";
				cin >> subChoice;

				//   Error-checking user input
				while (cin.fail() || subChoice < 1 || subChoice > 4)
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "\n";
					cout << "   !!!       Invalid input entered. Please try again.       !!!\n\n" << endl;
					cout << "     Selection: ";
					cin >> subChoice;
				}

				cout << "\n\n   ---       RESULT:       ---" << endl;

				//   Searching for the Milky Way as the galaxy orbitee
				if (subChoice == 1)
				{
					//   If P2 chose the galaxy orbitee correctly
					if (P1_.getGalaxy().getSattlOf() == "Milky Way")
					{
						cout << "\n     Player 1's Galaxy orbits around the Milky Way!\n" << endl;

						//   Search P2's Galaxy Roster & remove all listings that aren't the guess
						for (int i = 0; i < P2_.getGalaxyRoster().size(); i++)
						{
							if (P2_.getGalaxyRoster()[i].getSattlOf() != "Milky Way")
							{
								cout << "     " << P2_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P2_.removeGalaxy(i);
								i--;
							}
						}
					}

					//   P2 chose incorrectly
					else
					{
						cout << "\n     Player 1's Galaxy doesn't orbit around the Milky Way!\n" << endl;

						//   Search P2's Galaxy Roster & remove all the listings that are the guess
						for (int i = 0; i < P2_.getGalaxyRoster().size(); i++)
						{
							if (P2_.getGalaxyRoster()[i].getSattlOf() == "Milky Way")
							{
								cout << "     " << P2_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P2_.removeGalaxy(i);
								i--;
							}
						}
					}
				}

				//   Searching for the Andromeda as the galaxy orbitee
				if (subChoice == 2)
				{
					//   If P2 chose the galaxy orbitee correctly
					if (P1_.getGalaxy().getSattlOf() == "Andromeda")
					{
						cout << "\n     Player 1's Galaxy orbits around Andromeda!\n" << endl;

						//   Search P2's Galaxy Roster & remove all listings that aren't the guess
						for (int i = 0; i < P2_.getGalaxyRoster().size(); i++)
						{
							if (P2_.getGalaxyRoster()[i].getSattlOf() != "Andromeda")
							{
								cout << "     " << P2_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P2_.removeGalaxy(i);
								i--;
							}
						}
					}

					//   P2 chose incorrectly
					else
					{
						cout << "\n     Player 1's Galaxy doesn't orbit around Andromeda!\n" << endl;

						//   Search P2's Galaxy Roster & remove all the listings that are the guess
						for (int i = 0; i < P2_.getGalaxyRoster().size(); i++)
						{
							if (P2_.getGalaxyRoster()[i].getSattlOf() == "Andromeda")
							{
								cout << "     " << P2_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P2_.removeGalaxy(i);
								i--;
							}
						}
					}
				}

				//   Searching for the Triangulum as the galaxy orbitee
				if (subChoice == 3)
				{
					//   If P2 chose the galaxy orbitee correctly
					if (P1_.getGalaxy().getSattlOf() == "Triangulum")
					{
						cout << "\n     Player 1's Galaxy orbits around the Triangulum!\n" << endl;

						//   Search P2's Galaxy Roster & remove all listings that aren't the guess
						for (int i = 0; i < P2_.getGalaxyRoster().size(); i++)
						{
							if (P2_.getGalaxyRoster()[i].getSattlOf() != "Triangulum")
							{
								cout << "     " << P2_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P2_.removeGalaxy(i);
								i--;
							}
						}
					}

					//   P2 chose incorrectly
					else
					{
						cout << "\n     Player 1's Galaxy doesn't orbit around the Triangulum!\n" << endl;

						//   Search P2's Galaxy Roster & remove all the listings that are the guess
						for (int i = 0; i < P2_.getGalaxyRoster().size(); i++)
						{
							if (P2_.getGalaxyRoster()[i].getSattlOf() == "Triangulum")
							{
								cout << "     " << P2_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P2_.removeGalaxy(i);
								i--;
							}
						}
					}
				}

				//   Searching for if the Galaxy doesn't orbit anything
				if (subChoice == 4)
				{
					//   If P2 chose the galaxy orbitee correctly
					if (P1_.getGalaxy().getSattlOf() == "None")
					{
						cout << "\n     Player 1's Galaxy doesn't orbit a galaxy!\n" << endl;

						//   Search P2's Galaxy Roster & remove all listings that aren't the guess
						for (int i = 0; i < P2_.getGalaxyRoster().size(); i++)
						{
							if (P2_.getGalaxyRoster()[i].getSattlOf() != "None")
							{
								cout << "     " << P2_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P2_.removeGalaxy(i);
								i--;
							}
						}
					}

					//   P2 chose incorrectly
					else
					{
						cout << "\n     Player 1's Galaxy does orbit a galaxy!\n" << endl;

						//   Search P2's Galaxy Roster & remove all the listings that are the guess
						for (int i = 0; i < P2_.getGalaxyRoster().size(); i++)
						{
							if (P2_.getGalaxyRoster()[i].getSattlOf() == "None")
							{
								cout << "     " << P2_.getGalaxyRoster()[i].getName() << " removed!" << endl;
								P2_.removeGalaxy(i);
								i--;
							}
						}
					}
				}

				cout << "\n   ---       ^^^^^^^       ---\n" << endl;
			}

			endTurn_ = true;
		}

		//   Player Action 3: Perform specific guess on opponent's galaxy
		else if (selectionP2_ == 3)
		{
		//   Warn the player that an incorrect specific guess will cost them the game
		cout << "\n   !!!       WARNING!       !!!       WARNING!       !!!\n" << endl;
		cout << "     An incorrect guess is an immediate loss. Do you wish to continue?" << endl;
		cout << "     Enter in (Y) for Yes, any other key for No:\n" << endl;
		cout << "     > ";
		cin >> finalChoice;

		finalChoice = toupper(finalChoice);



		//   Player wishes to continue
		if (finalChoice == 'Y')
		{
			cout << "\n   =============================================" << endl;
			cout << "   ===          Make a Specific Guess        ===" << endl;
			cout << "   =============================================\n" << endl;
			cout << "     Enter in the Galaxy Number of your guess:\n" << endl;
			cout << "     > ";
			cin >> choice;

			//   Error-checking user input
			while (cin.fail() || choice < 1 || choice > 51)
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "\n";
				cout << "   !!!       Invalid input entered. Please try again.       !!!\n\n" << endl;
				cout << "     > ";
				cin >> choice;
			}

			//   Displaying Player's final guess
			for (int i = 0; i < P2_.getGalaxyRoster().size(); i++)
			{
				if (P2_.getGalaxyRoster()[i].getNumber() == choice)
				{
					subChoice = i;
				}
			}

			cout << "\n\n     Your guess is:" << endl;
			cout << "   --------------------------------------------------------------------------------------------\n" << endl;
			cout << "     "; P2_.getGalaxyRoster()[subChoice].display(); cout << endl;
			cout << "   --------------------------------------------------------------------------------------------\n" << endl;
			cout << "     Is this your final guess? Enter in Y for Yes, any other key for No:\n" << endl;
			cout << "     > ";
			cin >> finalChoice;

			finalChoice = toupper(finalChoice);

			cout << "\n\n\n\n\n\n\n\n\n\n" << endl;

			//   Confirms final choice
			if (finalChoice == 'Y')
			{
				//   If final choice is opponent's galaxy, Player wins
				if (P2_.getGalaxyRoster()[subChoice].getNumber() == P1_.getGalaxy().getNumber())
				{
					cout << "    /$$$$$$                                                /$$             /$$            /$$   /$$" << endl;
					cout << "   /$$__  $$                                              | $$            | $$           | $$  |__/" << endl;
					cout << "  | $$  \\__/ /$$$$$$  /$$$$$$$  /$$$$$$  /$$$$$$ /$$$$$$ /$$$$$$   /$$  /$| $$ /$$$$$$ /$$$$$$  /$$ /$$$$$$ /$$$$$$$  /$$$$$$$" << endl;
					cout << "  | $$      /$$__  $ | $$__  $$/$$__  $$/$$__  $|____  $|_  $$_/  | $$ | $| $$|____  $|_  $$_/ | $$/$$__  $| $$__  $$/$$_____/" << endl;
					cout << "  | $$     | $$  \\ $ | $$  \\ $| $$  \\ $| $$  \\__//$$$$$$$ | $$    | $$ | $| $$ /$$$$$$$ | $$   | $| $$  \\ $| $$  \\ $|  $$$$$$" << endl;
					cout << "  | $$    $| $$  | $ | $$  | $| $$  | $| $$     /$$__  $$ | $$ /$ | $$ | $| $$/$$__  $$ | $$ /$| $| $$  | $| $$  | $$\\____  $$" << endl;
					cout << "  |  $$$$$$ | $$$$$$ | $$  | $|  $$$$$$| $$    |  $$$$$$$ |  $$$$ | $$$$$$| $|  $$$$$$$ |  $$$$| $|  $$$$$$| $$  | $$/$$$$$$$/" << endl;
					cout << "   \\______ / \\______/|__/  |__ /\\____ $|__/     \\_______/  \\___ / \\______/|__/\\_______/  \\___/ |__/\\______/|__/  |__|_______/" << endl;
					cout << "                                /$$  \\ $$" << endl;
					cout << "                               |  $$$$$$/" << endl;
					cout << "                                \\______/" << endl << endl;
					cout << "\n     Congratulations! Player 2 wins!\n" << endl;
				}

				//   If final choice wasn't opponent's galaxy, opponent wins
				else
				{
					cout << "    /$$$$$$                                       /$$$$$$" << endl;
					cout << "   /$$__  $$                                     /$$__  $$" << endl;
					cout << "  | $$  \\__/ /$$$$$$ /$$$$$$/$$$$  /$$$$$$      | $$  \\ $$/$$    /$$/$$$$$$  /$$$$$$" << endl;
					cout << "  | $$ /$$$$|____  $| $$_  $$_  $$/$$__  $$     | $$  | $|  $$  /$$/$$__  $$/$$__  $$" << endl;
					cout << "  | $$|_  $$ /$$$$$$| $$ \\ $$ \\ $| $$$$$$$$     | $$  | $$\\  $$/$$| $$$$$$$| $$  \\__/" << endl;
					cout << "  | $$  \\ $$/$$__  $| $$ | $$ | $| $$_____/     | $$  | $$ \\  $$$/| $$_____| $$" << endl;
					cout << "  |  $$$$$$|  $$$$$$| $$ | $$ | $| $$$$$$$      |  $$$$$$/  \\  $/ |  $$$$$$| $$" << endl;
					cout << "   \\______/ \\_______|__/ |__/ |__/\\_______/      \\______/    \\_/   \\_______|__/" << endl << endl;
					cout << "\n     Game Over! Player 2 Lost!\n" << endl;
					cout << "     Player 1 wins!\n" << endl;
				}

				//   Ends the game
				endGame_ = true;
				return;
			}

			else
			{cout << "\n" << endl;}
		}

		else
		{cout << "\n" << endl;}

		}
	}
}

//   Displays transitional symbols to signify action progression
void dispTransition()
{
	for (int i = 0; i < 30; i++)
	{
		cout << "============================================================" << endl;
		cout << "============================================================" << endl;
		cout << "     ===============================================" << endl;
		cout << "           ===================================" << endl;
		cout << "             ===============================" << endl;
		cout << "                 =======================" << endl;
		cout << "                   ===================" << endl;
		cout << "                     ===============" << endl;
		cout << "                      =============" << endl;
		cout << "                        =========" << endl;
		cout << "                          =====" << endl;
		cout << "                           ===" << endl;
		cout << "                           ===" << endl;
		cout << "                           ===" << endl;
		cout << "                           ===" << endl;
		cout << "                            =" << endl;
		cout << "                            =" << endl;
		cout << "                            =" << endl;
		cout << "                            =" << endl;
		cout << "                            =" << endl;
		cout << "                            =" << endl;
		cout << "                            =" << endl;
	}

	cout << "\n" << endl;
}


//   Confirms the end of the turn player's turn
void confirmTurnEnd(int& turn_)
{
	string temp;

	if (turn_ == 0)
	{

		cout << "\n\n\n     Player 1, call Player 2 up to the stand & step away from the keyboard.\n" << endl;
		cout << "     No peeking!\n\n" << endl;
		cout << "     Player 2, enter in any character and press Enter to begin your turn...\n" << endl;
		cout << "     > ";
	}

	else
	{
		cout << "\n\n\n     Player 2, call Player 1 up to the stand & step away from the keyboard.\n" << endl;
		cout << "     No peeking!\n\n" << endl;
		cout << "     Player 1, enter in any character and press Enter to begin your turn...\n" << endl;
		cout << "     > ";
	}

	cin >> temp;
	cout << endl;
}