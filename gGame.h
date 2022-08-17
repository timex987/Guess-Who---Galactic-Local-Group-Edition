#pragma once


#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <random>
#include <functional>
#include "object.h"
#include "player.h"
using namespace std;


//   Function to handle main gameplay flow
void gGame(vector<object>& galaxyList_)
{
	int P1choice, P2choice;
	int turn = 0;
	string start;
	bool endTurn = false;
	bool dispTurn = false;
	bool endGame = false;
	default_random_engine generator(time(nullptr));
	uniform_int_distribution<int> distribution(1, galaxyList_.size());

	cout << "\n\n   ================================================================" << endl;
	cout << "   ===          Guess Who: Galactic Local Group Edition         ===" << endl;
	cout << "   ================================================================\n\n" << endl;
	cout << "     Welcome to Guess Who: Galactic Local Group Edition!\n" << endl;
	cout << "     This is a spin-off of the classic game, using the members of the Local Group" << endl;
	cout << "     as the stars of this game!\n" << endl;
	cout << "     To start, enter in any key and press Enter...\n" << endl;
	cout << "     > ";
	cin >> start;

	dispTransition();


	//   Enables simple use of randomNumber() function
	auto randomNumber = bind(distribution, generator);


	//   Assigning players a random Galaxy
	P1choice = randomNumber();
	P2choice = randomNumber();
	
	while (P2choice == P1choice)
	{P2choice = randomNumber();}

	player P1(galaxyList_[P1choice - 1], galaxyList_);
	player P2(galaxyList_[P2choice - 1], galaxyList_);


	while (true)
	{
		endTurn = false;
		dispTurn = false;
		
		while (!endTurn)
		{
			playerMenu(turn, P1choice, P2choice, dispTurn);

			performAction(turn, P1, P1choice, P2, P2choice, endTurn, endGame);

			if (endGame)
			{break;}
		}

		if (endGame)
		{break;}

		confirmTurnEnd(turn);

		dispTransition();

		P1choice = 0;
		P2choice = 0;


		//   Ends the turn and progresses game flow to the next player
		if (turn == 0)
		{turn++;}

		else
		{turn--;}
	}

	cout << "\n\n     Enter in any key to close the game...\n" << endl;
	cout << "     > ";
	cin >> turn;
}

