/*
************************************************************
* Name: Nicole Millian                                     *
* Project : Duell - Project 1 C++				           *
* Class : CMPS 366 Organization of Programming Languages   *
* Date : October 21, 2016		                           *
************************************************************
*/
#pragma once
#include "player.h"
#include "human.h"

#include <string>
using namespace std;

//computer class which inherits from player class and implements all the strategies used by the computer

class computer : public player {
public:
	computer();
	~computer();

	/********************************
	MUTATORS
	********************************/
	//Check if a move to the 1x1 enemy die is possible to win the game
	bool moveToSpecialEnemyDice(board &Duell, player * roster[], computer compPlayer);

	//Check if a move to the special human tile at row 1 col 5 is possible in order to win the game
	bool moveToSpecialEnemyTile(board &Duell, player * roster[], computer compPlayer);

	//Defend the special 1x1 die if possible to prevent losing the game
	bool defendSpecialDice(board &Duell, player * roster[], computer compPlayer, human humanPlayer);

	//Defend a die from being captured
	bool defendComputerDice(board &Duell, player * roster[], computer compPlayer, human humanPlayer);

	//Take a human die by moving to 
	bool killAHumanDice(board &Duell, player * roster[], computer compPlayer, human humanPlayer);

	//After nothing else just move to a space if possible
	bool moveToOpenSpace(board &Duell, player * roster[], computer compPlayer, human humanPlayer);

	/********************************
	UTILITY
	********************************/
	//Used to decide which move the computer should make, determines the best possible move
	string decideMove(board &Duell, player * roster[], computer compPlayer, human humanPlayer);

	//Which direction the die is moving from it's original tile to get to it's new tile
	string movementDirection(int row, int column, int newRow, int newColumn);

	//Checking if there is a collision on the pathway from the old tile to the new tile
	bool checkCollision(board Duell, int row, int column, int newRow, int newColumn, string direction, int lateral, int frontal);

	//Checking if it's a valid movement, the diceTop at the row and column should equal the frontal + lateral movement
	bool isValidMovement(board Duell, int row, int column, int frontal, int lateral);

	//Check if the last path space is a valid movement, an enemy human die, 2, or a space, 0.
	int checkLastPathSpace(board Duell, int newRow, int newColumn);

private:

};

