/*
************************************************************
* Name: Nicole Millian                                     *
* Project : Duell - Project 1 C++				           *
* Class : CMPS 366 Organization of Programming Languages   *
* Date : October 21, 2016		                           *
************************************************************
*/
#pragma once
#include <string>
#include "board.h"


using namespace std;

//player class in which playing strategies must be implemented

class player {
public:
	player();
	~player();

	/********************************
	SELECTORS
	********************************/
	//Return the string name
	const string getName();

	//Return the integer alive dice
	const int checkAliveDice();

	//Return the integer dead dice
	const int checkDeadDice();

	/********************************
	MUTATORS
	********************************/

	//Set the private variable name
	void setName(string playerName);

	//Set the private variables for ailveDice and deadDice depending on how many aliveDie are passed in
	void setDie(int aliveDie);

	//Update the amount of alive and dead die by subtracting 1 to the alive die and adding 1 to the dead die
	void updateDeadDice();

	//Reset the aliveDice and deadDice private variables 
	void resetGame();

	/********************************
	UTILITY
	********************************/
	//Decide which move should be made for the human or computer player
	virtual string decideMove(board &Duell, player * roster[], computer compPlayer, human humanPlayer);

private:

	string name;
	int aliveDice;
	int deadDice;

};

