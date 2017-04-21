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
#include <string>
#include "player.h"

using namespace std;

class tournament {
public:
	tournament();
	~tournament();

	/********************************
	SELECTORS
	********************************/
	//Return the number of humanWins
	const int getHumanWins();
	//Return the number of computerWins
	const int getComputerWins();


	/********************************
	MUTATORS
	********************************/
	//Update the amount of human wins in the private variable humanWins
	void updateHumanWins();
	//Update the amount of computer wins in the private variable computerWines
	void updateComputerWins();

	//Update the amount of wins from the serialization file to the private variable computerWins
	void updateSerialWinsComp(int cWins);
	//Update the amount of wins from the serialization file to the private variable humanWins
	void updateSerialWinsHuman(int hWins);

	//Reset the amount of wins in the humanWins and computerWins variables to 0
	void resetTournament();

	/********************************
	UTILITY
	********************************/
	//Determine which variable, humanWins or computerWins, is larger or if the tournament is a tie
	void determineWinner(player * roster[]);

private:
	//The amount of wins the human player has, initially 0
	int humanWins;
	//The amount of wins the computer player has, initially 0 
	int computerWins;
};

