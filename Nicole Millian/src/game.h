/*
************************************************************
* Name: Nicole Millian                                     *
* Project : Duell - Project 1 C++				           *
* Class : CMPS 366 Organization of Programming Languages   *
* Date : October 21, 2016		                           *
************************************************************
*/
#pragma once
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

#include "board.h"
#include "tournament.h"

using namespace std;

class game {
public:
	game();
	~game();

	/********************************
	UTILITY
	********************************/
	//Decides the first player of the round
	int decideFirstPlayer(player * roster[]);

	//Asks the human player if the want to save and quit or keep playing
	bool askForSerialization(board Duell, tournament duellTournament, int currentPlayer);

	//Handles reading in the saved game state from a file
	bool gameSerializationIn(board &Duell, tournament &duellTournament, int &currentPlayer, player * roster[], string name);

	//Handles saving the current game state to a file
	bool gameSerializationOut(board Duell, tournament &duellTournament, int &currentPlayer, string name);

private:

};

