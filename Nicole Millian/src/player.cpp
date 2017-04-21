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
#include "computer.h"
#include "human.h"

player::player() {
	aliveDice = 9;
	deadDice = 0;
	name = "DEFUALT";
}

player::~player() {

}

/* *********************************************************************
Function Name: setName

Purpose: Sets the name of the player

Parameters: playerName, a string, used to set the name variable

Return Value: None.

Assistance Received: none
********************************************************************* */
void player::setName(string playerName) {
	name = playerName;
}

/* *********************************************************************
Function Name: getName

Purpose: Gets the name of a player.

Parameters: None.

Return Value: name, a string, which is a name of the player

Assistance Received: none
********************************************************************* */
const string player::getName() {
	return name;
}

/* *********************************************************************
Function Name: checkAliveDice

Purpose: Get the number of aliveDice of the player

Parameters: None.

Return Value: aliveDice, an integer, the number of alive dice

Assistance Received: none
********************************************************************* */
const int player::checkAliveDice() {
	return aliveDice;
}

/* *********************************************************************
Function Name: checkDeadDice

Purpose: Get the number of deadDice of the player

Parameters: None.

Return Value: deadDice, an integer, the number of dead dice

Assistance Received: none
********************************************************************* */
const int player::checkDeadDice() {
	return deadDice;
}

/* *********************************************************************
Function Name: setDie

Purpose: Update the number of deadDice and aliveDice, used to only update
from a save file.

Parameters: aliveDie, an integer, the amount of dice currently alive

Return Value: None

Assistance Received: none
********************************************************************* */
void player::setDie(int aliveDie) {
	aliveDice = aliveDie;
	deadDice = 9 - aliveDie;
}

/* *********************************************************************
Function Name: updateDeadDice

Purpose: Update the number of deadDice by adding 1 and update the number of aliveDice by subtracting 1

Parameters: None.

Return Value: None

Assistance Received: none
********************************************************************* */
void player::updateDeadDice() {
	deadDice = (deadDice + 1);
	aliveDice = (aliveDice - 1);
}

/* *********************************************************************
Function Name: resetGame

Purpose: Update the number of deadDice to 0, the original amount, and the
number of aliveDice to 9, the original amount.

Parameters: None.

Return Value: None

Assistance Received: none
********************************************************************* */
void player::resetGame() {
	aliveDice = 9;
	deadDice = 0;
}

/* *********************************************************************
Function Name: decideMove

Purpose: To determine what move the human or computer should make.

Parameters:Duell, a board object passed by reference, which stores the die
roster, an array of player object pointers, passed by value, used to access the 2 players of the game
compPlayer, a computer object, passed by value, used to access the computer functions
humanPlayer, a human object,  passed by value, used to access human functions

Return Value: A string determining which move was made.

Assistance Received: none
********************************************************************* */
string player::decideMove(board &Duell, player * roster[], computer compPlayer, human humanPlayer) {
	return "Wrong";
}

