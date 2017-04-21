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
#include <iomanip>
#include <map>

using namespace std;
class human;
class computer;

class board {

public:
	board();
	~board();

	/********************************
	SELECTORS
	********************************/
	//Returns what number is at the row and column in the private games map
	const int getNumAtSpace(int row, int column);

	//Returns the human top die number at the specified row and column
	const int getHumanTop(int row, int column);
	//Returns the human right die number at the specified row and column
	const int getHumanRight(int row, int column);

	//Returns the computer top die number at the specified row and column
	const int getComputerTop(int row, int column);
	//Returns the computer right die number at the specified row and column
	const int getComputerRight(int row, int comlumn);

	//Checks the private games map for a 0 for a space
	const bool isSpace(int row, int column);
	//Checks the private games map for a 1 for comp dice
	const bool isHumanDice(int row, int column);
	//Checks the private games map for a 2 for a human dice
	const bool isComputerDice(int row, int column);

	//Return the row and column of the 1x1 dice of the human
	const int getSpecialHumanDiceRow();
	const int getSpecialHumanDiceColumn();

	//Return the row and column of the 1x1 dice of the computer
	const int getSpecialComputerDiceRow();
	const int getSpecialComputerDiceColumn();

	/********************************
	MUTATORS
	********************************/

	//Initialize the games map with the pieces, 0 for space, 1 for computer, 2 for human
	void initializeGames();
	//Set the initial home row for human (1) with the correct dice structures 
	void initalHumanDice();
	//Set the initial home row for computer (8) with the correct dice structures
	void initialComputerDice();
	//Reset the games map to the orginal home rows and spaces
	//Reset the diceHuman and diceComputer maps with the original die
	void resetGame();

	//Move a human dice to the correct new position
	void moveDiceHuman(human player, int row, int column, int newRow, int newColumn, string firstDirection);
	//Move a computer dice to the correct new position 
	void moveDiceComputer(computer player, int row, int column, int newRow, int newColumn, string firstDirection);

	//Functions which move the human dice in four different directions, frontal, backwards, left, right, 
	//and set what the new nice numbers should be on the top and right depending on which way it is moving.
	void moveFrontalHuman(int row, int column, int spaces);
	void moveBackwardsHuman(int row, int column, int spaces);
	void moveLeftHuman(int row, int column, int spaces);
	void moveRightHuman(int row, int column, int spaces);

	//Functions which move the computer dice in four different directions, frontal, backwards, left, right, 
	//and set what the new nice numbers should be on the top and right depending on which way it is moving.
	void moveFrontalComputer(int row, int column, int spaces);
	void moveBackwardsComputer(int row, int column, int spaces);
	void moveLeftComputer(int row, int column, int spaces);
	void moveRightComputer(int row, int column, int spaces);

	//Update the games map when a computer or human die has been killed by an opponents die
	//Updates a computer (1) with a human (2) or vice versa
	void killComputerDice(int newRow, int newColumn);
	void killHumanDice(int newRow, int newCOlumn);

	//Set the games piece with either a 0 for a space, 1 for a computer, or 2 for a human at the row and column
	void setGamesPiece(int row, int column, int piece);

	//Set the computer dice in the diceComputer map, used for reading in die from serialization
	void setComputerDice(int row, int column, int top, int right);
	//Set the human dice in the diceHuman map, used for reading in die from serialization
	void setHumanDice(int row, int column, int top, int right);

	/********************************
	UTILITY
	********************************/

	//Calculate frontal and lateral movements of the dice from the old row to the new row and old column to new column
	int calculateFront(int row, int newRow);
	int calculateLateral(int column, int newColumn);

	//Struct for creating dice, holds the top and right value of the die along with the row and column it's located at
	struct dice {
		int top;
		int right;

		int row;
		int column;

	};

private:
	//Holds the board in simpel state, 0 is a space, 1 is a computer die, 2 is a human die
	map< int, map<int, int> > games;

	//Holds all the human die strucs
	map< int, map<int, dice> > diceHuman;

	//Holds all the computer die strucs
	map< int, map<int, dice> > diceComputer;
};

