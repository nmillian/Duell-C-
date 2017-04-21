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
#include "player.h"
#include "computer.h"

using namespace std;

//human class which inherits from player class and implements all the validation of input from the human player

class human : public player {

public:
	human();
	human(string playerName);
	~human();

	/********************************
	UTILITY
	********************************/
	//Used to give the human player advice, determines the best possible move the human can make
	string decideMove(board &Duell, player * roster[], computer compPlayer, human humanPlayer);

	//Checking if there is a collision on the pathway from the old tile to the new tile
	bool checkCollision(board Duell, int row, int column, int newRow, int newColumn, string direction, int lateral, int frontal);

	//Which direction the die is moving from it's original tile to get to it's new tile
	string movementDirection(int row, int column, int newRow, int newColumn);

	//Checking if it's a valid movement, the diceTop at the row and column should equal the frontal + lateral movement
	bool isValidMovement(board Duell, int row, int column, int frontal, int lateral);

	//Check if the last path space is a valid movement, an enemy computer die, 1, or a space, 0.
	int checkLastPathSpace(board Duell, int newRow, int newColumn);

	//Check if a move to the 1x1 enemy die is possible to win the game
	bool moveToSpecialEnemyDice(board &Duell, player * roster[], human humanPlayer);

	//Check if a move to the special computer tile at row 8 col 5 is possible in order to win the game
	bool moveToSpecialEnemyTile(board &Duell, player * roster[], human humanPlayer);

	//Defend the special 1x1 die if possible to prevent losing the game
	bool defendSpecialDice(board &Duell, player * roster[], computer compPlayer, human humanPlayer);

	//Defend a die from being captured by the enemy
	bool defendHumanDice(board &Duell, player * roster[], computer compPlayer, human humanPlayer);

	//Kill an enemy die by moving to it
	bool killAComputerDice(board &Duell, player * roster[], computer compPlayer, human humanPlayer);

	//Move to an open available space
	bool moveToOpenSpace(board &Duell, player * roster[], computer compPlayer, human humanPlayer);

private:

};

