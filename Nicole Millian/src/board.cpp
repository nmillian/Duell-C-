/*
************************************************************
* Name: Nicole Millian                                     *
* Project : Duell - Project 1 C++				           *
* Class : CMPS 366 Organization of Programming Languages   *
* Date : October 21, 2016		                           *
************************************************************
*/
#pragma once
#include "board.h"
#include "boardView.h"

#include "computer.h"
#include "human.h"

board::board() {
	initializeGames();
	initalHumanDice();
	initialComputerDice();
}


board::~board() {

}

/* *********************************************************************
Function Name: initializeGames

Purpose: Initialize the games map with numbers determinging if it's a space,
human, or computer die. Space is 0, computer is 1, human is 2.

Parameters: None

Return Value: None

Local Variables: None

Algorithm:
1) Using a nested for loop that beings at (8,1) and ends at (1,9) to go through the map.
2) Assign values based on what the original board should look like, with two home rows.
3) Row 8 is the computers home row, so assign a 1 to all row 8 die.
3) Row 1 is the human home row, so assign a 2 to all the row 1 die.
4) The rest of the rows are assigned a 0 to stand for a space.

Assistance Received: none
********************************************************************* */
void board::initializeGames() {
	//Initialize the board
	for (int i = 8; i > 0; i--) {
		for (int j = 1; j < 10; j++) {

			//Computer dice is 1
			if (i == 8) {
				games[i][j] = 1;
			}

			//Human dice is 2
			else if (i == 1) {
				games[i][j] = 2;
			}

			//Blank spaces
			else {
				games[i][j] = 0;
			}
		}

	}
}

/* *********************************************************************
Function Name: initialHumanDice

Purpose: Initialize the human dice in the diceHuman map.

Parameters: None

Return Value: None

Local Variables: None

Algorithm:
1) Create 9 dice structs.
2) Assign each dice struct a top and right die number as per the rules.
3) Assign the dice row and dice column as per the rules.
4) Add the dice struct to the diceHuman map using the row and column as keys.

Assistance Received: none
********************************************************************* */
void board::initalHumanDice() {
	//First dice for human player
	dice dice1;
	dice1.top = 5;
	dice1.right = 6;

	dice1.row = 1;
	dice1.column = 1;

	diceHuman[1][1] = dice1;

	//Second dice for human player
	dice dice2;
	dice2.top = 1;
	dice2.right = 5;

	dice2.row = 1;
	dice2.column = 2;

	diceHuman[1][2] = dice2;

	//Third dice for human player
	dice dice3;
	dice3.top = 2;
	dice3.right = 1;

	dice3.row = 1;
	dice3.column = 3;

	diceHuman[1][3] = dice3;

	//Fourth dice for human player
	dice dice4;
	dice4.top = 6;
	dice4.right = 2;

	dice4.row = 1;
	dice4.column = 4;

	diceHuman[1][4] = dice4;

	//Fifth dice for human player
	dice dice5;
	dice5.top = 1;
	dice5.right = 1;

	dice5.row = 1;
	dice5.column = 5;

	diceHuman[1][5] = dice5;

	//Sixth dice for human player
	dice dice6;
	dice6.top = 6;
	dice6.right = 2;

	dice6.row = 1;
	dice6.column = 6;

	diceHuman[1][6] = dice6;

	//Seventh dice for human player
	dice dice7;
	dice7.top = 2;
	dice7.right = 1;

	dice7.row = 1;
	dice7.column = 7;

	diceHuman[1][7] = dice7;

	//Eigth dice for human player
	dice dice8;
	dice8.top = 1;
	dice8.right = 5;

	dice8.row = 1;
	dice8.column = 8;

	diceHuman[1][8] = dice8;

	//Ninth dice for human player
	dice dice9;
	dice9.top = 5;
	dice9.right = 6;

	dice9.row = 1;
	dice9.column = 9;

	diceHuman[1][9] = dice9;

}

/* *********************************************************************
Function Name: initialComputerDice

Purpose: Initialize the computer dice in the diceComputer map.

Parameters: None

Return Value: None

Local Variables: None

Algorithm:
1) Create 9 dice structs.
2) Assign each dice struct a top and right die number as per the rules.
3) Assign the dice row and dice column as per the rules.
4) Add the dice struct to the computerDice map using the row and column as keys.

Assistance Received: none
********************************************************************* */
void board::initialComputerDice() {
	//First dice for human player
	dice dice1;
	dice1.top = 5;
	dice1.right = 6;

	dice1.row = 8;
	dice1.column = 1;

	diceComputer[8][1] = dice1;

	//Second dice for human player
	dice dice2;
	dice2.top = 1;
	dice2.right = 5;

	dice2.row = 8;
	dice2.column = 2;

	diceComputer[8][2] = dice2;

	//Third dice for human player
	dice dice3;
	dice3.top = 2;
	dice3.right = 1;

	dice3.row = 8;
	dice3.column = 3;

	diceComputer[8][3] = dice3;

	//Fourth dice for human player
	dice dice4;
	dice4.top = 6;
	dice4.right = 2;

	dice4.row = 8;
	dice4.column = 4;

	diceComputer[8][4] = dice4;

	//Fifth dice for human player
	dice dice5;
	dice5.top = 1;
	dice5.right = 1;

	dice5.row = 8;
	dice5.column = 5;

	diceComputer[8][5] = dice5;

	//Sixth dice for human player
	dice dice6;
	dice6.top = 6;
	dice6.right = 2;

	dice6.row = 8;
	dice6.column = 6;

	diceComputer[8][6] = dice6;

	//Seventh dice for human player
	dice dice7;
	dice7.top = 2;
	dice7.right = 1;

	dice7.row = 8;
	dice7.column = 7;

	diceComputer[8][7] = dice7;

	//Eigth dice for human player
	dice dice8;
	dice8.top = 1;
	dice8.right = 5;

	dice8.row = 8;
	dice8.column = 8;

	diceComputer[8][8] = dice8;

	//Ninth dice for human player
	dice dice9;
	dice9.top = 5;
	dice9.right = 6;

	dice9.row = 8;
	dice9.column = 9;

	diceComputer[8][9] = dice9;
}

/* *********************************************************************
Function Name: getNumAtSpace

Purpose: Return which number is being stored in the games map to identify what
type of die it is on the board. 0 for space, 1 for computer, 2 for human.

Parameters: None

Return Value: None

Assistance Received: none
********************************************************************* */
const int board::getNumAtSpace(int row, int column) {
	return games[row][column];
}

/* *********************************************************************
Function Name: isSpace

Purpose: Return whether or not a tile in the games map is a space, 0.

Parameters: None

Return Value: True if it is a space. False if it is not a space.

Assistance Received: none
********************************************************************* */
const bool board::isSpace(int row, int column) {
	
	int num = games[row][column];

	if (num == 0) {
		return true;
	}
	else {
		return false;
	}
}

/* *********************************************************************
Function Name: isHumanDice

Purpose: Return whether or not a tile in the games map is a human die, 2.

Parameters: None

Return Value: True if it is a human die. False if it is not a human die.

Assistance Received: none
********************************************************************* */
const bool board::isHumanDice(int row, int column) {
	if (games[row][column] == 2) {
		return true;
	}
	else {
		return false;
	}
}


/* *********************************************************************
Function Name: isComputerDice

Purpose: Return whether or not a tile in the games map is a computer die, 1.

Parameters: None

Return Value: True if it is a comp die. False if it is not a comp die.

Assistance Received: none
********************************************************************* */
const bool board::isComputerDice(int row, int column) {
	if (games[row][column] == 1) {
		return true;
	}
	else {
		return false;
	}
}

/* *********************************************************************
Function Name: calculateFront

Purpose: To calculate the amount of spaces being moved in the vertical direction,
for either front or back.

Parameters: row, an integer, the row where the die is originally
newRow, an integer, the row where the die will end up

Return Value: An integer, either (row - newRow) or (newRow - row)

Assistance Received: none
********************************************************************* */
int board::calculateFront(int row, int newRow) {

	if (newRow == 0) {
		return 0;
	}
	else if (row > newRow) {
		return row - newRow;
	}
	else {
		return newRow - row;
	}
}


/* *********************************************************************
Function Name: calculateLateral

Purpose: To calculate the amount of spaces being moved in the lateral direction,
for either left or right

Parameters: column, an integer, the column where the die is originally
newColumn, an integer, the column where the die will end up

Return Value: An integer, either (column - newColumn) or (newColumn - column)

Assistance Received: none
********************************************************************* */
int board::calculateLateral(int column, int newColumn) {

	if (newColumn == 0) {
		return 0;
	}
	else if (column > newColumn) {
		return column - newColumn;
	}
	else {
		return newColumn - column;
	}
}

/* *********************************************************************
Function Name: getHumanTop

Purpose: Return which number is being stored in the diceHuman map as the top die number.

Parameters: None

Return Value: None

Assistance Received: none
********************************************************************* */
const int board::getHumanTop(int row, int column) {
	return diceHuman[row][column].top;
}

/* *********************************************************************
Function Name: getHumanRight

Purpose: Return which number is being stored in the diceHuman map as the right die number.

Parameters: None

Return Value: None

Assistance Received: none
********************************************************************* */
const int board::getHumanRight(int row, int column) {
	return diceHuman[row][column].right;
}

/* *********************************************************************
Function Name: getComputerTop

Purpose: Return which number is being stored in the diceComputer map as the top die number.

Parameters: None

Return Value: None

Assistance Received: none
********************************************************************* */
const int board::getComputerTop(int row, int column) {
	return diceComputer[row][column].top;
}

/* *********************************************************************
Function Name: getComputerRight

Purpose: Return which number is being stored in the diceComputer map as the right die number.

Parameters: None

Return Value: None

Assistance Received: none
********************************************************************* */
const int board::getComputerRight(int row, int column) {
	return diceComputer[row][column].right;
}


/* *********************************************************************
Function Name: moveDiceHuman

Purpose: To move the human dice to the appropriate spot with the appropriate new
die numbers.

Parameters: player, a human object passed by value, used to get the movement direction
row, an integer, used to represent the row of the die player wants to move
column, an integer, used to represent the column of the die the player wants to move
newRow, an integer, the location of the row where the die should move to
newColumn, an integer, the location of the column where the die should move to
firstDirection, a string, whether the die should be moving frontally or laterally first

Return Value: None

Local Variables: oldGames, an integer, to hold the number that was at the original space
oldDice, a dice struct, used to hold the old dice that was at the original space
frontalSpaces, an integer, used to calculate the number of horizontal movement spaces
lateralSpaces, an integer, used to calculate the number of lateral movement spaces
direction, a string, used to hold which direction the dice is moving

Algorithm:
1) Store the current dice in the oldDice variable
2) Store the current piece number in the oldGames variable
3) Get the direction in which the die is going to be moving
4) Go through if statements in order to see if the direction matches any movements
5) If a match is found, set the games[newRow][newColumn] to the oldGames variable
6) If a match is found, set the diceHuman[newRow][newColumn] to the oldDice variable
7) Change the diceHuman stored row and column appropriately
8) Calculate the movement fontally and laterally
9) Call the appropriate movement functions depending on which direction is in the string firstDirection

Assistance Received: none
********************************************************************* */
void board::moveDiceHuman(human player, int row, int column, int newRow, int newColumn, string firstDirection) {
	int oldGames;
	dice oldDice;

	oldDice = diceHuman[row][column];
	oldGames = games[row][column];

	int frontalSpaces = 0;
	int lateralSpaces = 0;

	string direction;
	direction = player.movementDirection(row, column, newRow, newColumn);

	if (direction == "F") {
		//Set games and dicehuman correctly
		games[newRow][column] = oldGames;
		diceHuman[newRow][column] = oldDice;
		diceHuman[newRow][column].row = newRow;

		//Move dice
		//Calculate the number of spaces being moved forward
		frontalSpaces = calculateFront(row, newRow);
		//Calculate the dice movement using the new row/column
		moveFrontalHuman(newRow, column, frontalSpaces);
	}

	else if (direction == "B") {
		//Set games and dicehuman correctly
		games[newRow][column] = oldGames;
		diceHuman[newRow][column] = oldDice;
		diceHuman[newRow][column].row = newRow;

		//Move dice
		//Calculate the number of spaces being moved forward
		frontalSpaces = calculateFront(row, newRow);
		//Calculate the dice movement using the new row/column
		moveBackwardsHuman(newRow, column, frontalSpaces);
	}

	else if (direction == "L") {
		games[row][newColumn] = oldGames;
		diceHuman[row][newColumn] = oldDice;
		diceHuman[row][newColumn].column = newColumn;

		lateralSpaces = calculateLateral(column, newColumn);
		moveLeftHuman(newRow, newColumn, lateralSpaces);
	}

	else if (direction == "R") {
		games[row][newColumn] = oldGames;
		diceHuman[row][newColumn] = oldDice;
		diceHuman[row][newColumn].column = newColumn;

		lateralSpaces = calculateLateral(column, newColumn);
		moveRightHuman(newRow, newColumn, lateralSpaces);
	}

	else if (direction == "FL") {
		games[newRow][newColumn] = oldGames;
		diceHuman[newRow][newColumn] = oldDice;
		diceHuman[newRow][newColumn].column = newColumn;
		diceHuman[newRow][newColumn].row = newRow;

		//Calculate the number of spaces being moved
		frontalSpaces = calculateFront(row, newRow);
		lateralSpaces = calculateLateral(column, newColumn);
		//Calculate the dice movement using the new row/column
		if (firstDirection == "frontal") {
			moveFrontalHuman(newRow, newColumn, frontalSpaces);
			moveLeftHuman(newRow, newColumn, lateralSpaces);
		}
		else if (firstDirection == "lateral") {
			moveLeftHuman(newRow, newColumn, lateralSpaces);
			moveFrontalHuman(newRow, newColumn, frontalSpaces);
		}
	}

	else if (direction == "FR") {
		games[newRow][newColumn] = oldGames;
		diceHuman[newRow][newColumn] = oldDice;
		diceHuman[newRow][newColumn].column = newColumn;
		diceHuman[newRow][newColumn].row = newRow;

		//Calculate the number of spaces being moved
		frontalSpaces = calculateFront(row, newRow);
		lateralSpaces = calculateLateral(column, newColumn);
		//Calculate the dice movement using the new row/column

		if (firstDirection == "frontal") {
			moveFrontalHuman(newRow, newColumn, frontalSpaces);
			moveRightHuman(newRow, newColumn, lateralSpaces);
		}
		else if (firstDirection == "lateral") {
			moveRightHuman(newRow, newColumn, lateralSpaces);
			moveFrontalHuman(newRow, newColumn, frontalSpaces);
		}

	}

	else if (direction == "BL") {
		games[newRow][newColumn] = oldGames;
		diceHuman[newRow][newColumn] = oldDice;
		diceHuman[newRow][newColumn].column = newColumn;
		diceHuman[newRow][newColumn].row = newRow;

		//Move dice
		//Calculate the number of spaces being moved forward
		frontalSpaces = calculateFront(row, newRow);
		lateralSpaces = calculateLateral(column, newColumn);
		//Calculate the dice movement using the new row/column
		if (firstDirection == "frontal") {
			moveBackwardsHuman(newRow, newColumn, frontalSpaces);
			moveLeftHuman(newRow, newColumn, lateralSpaces);
		}
		else if (firstDirection == "lateral") {
			moveLeftHuman(newRow, newColumn, lateralSpaces);
			moveBackwardsHuman(newRow, column, frontalSpaces);
		}

	}

	else if (direction == "BR") {
		games[newRow][newColumn] = oldGames;
		diceHuman[newRow][newColumn] = oldDice;
		diceHuman[newRow][newColumn].column = newColumn;
		diceHuman[newRow][newColumn].row = newRow;

		//Move dice
		//Calculate the number of spaces being moved forward
		frontalSpaces = calculateFront(row, newRow);
		lateralSpaces = calculateLateral(column, newColumn);
		//Calculate the dice movement using the new row/column
		if (firstDirection == "frontal") {
			moveBackwardsHuman(newRow, newColumn, frontalSpaces);
			moveRightHuman(newRow, newColumn, lateralSpaces);
		}
		else if (firstDirection == "lateral") {
			moveRightHuman(newRow, newColumn, lateralSpaces);
			moveBackwardsHuman(newRow, newColumn, frontalSpaces);
		}
	}

	else {
		cout << "THIS IS INVALID" << endl;
	}

	games[row][column] = 0;

	diceHuman[row][column].top = 0;
	diceHuman[row][column].right = 0;
	diceHuman[row][column].row = 0;
	diceHuman[row][column].column = 0;

}


/* *********************************************************************
Function Name: moveFrontalHuman

Purpose: To set the correct top die when moving forwards. At this point the
die struct is already at the appropriate row & column and the top die has to be updated.

Parameters: row, an integer, the row where the die will end up moving to
column, an integer, the column where the die will end up moving to
spaces, an integer, the number of spaces the die will be moved frontally

Return Value: None.

Local Variables: None.

Algorithm:
1) Inside a for loop, loop untill the number of spaces moved has been met
2) In each iteration find the top and right die that matches the current one
3) Update only the top die with a new number, as it is moving forward the right stays the same

Assistance Received: none
********************************************************************* */
void board::moveFrontalHuman(int row, int column, int spaces) {

	for (int i = 0; i < spaces; i++) {
		//If the 1 is on top
		if (diceHuman[row][column].top == 1 && diceHuman[row][column].right == 5) {
			diceHuman[row][column].top = 3;
		}
		else if (diceHuman[row][column].top == 1 && diceHuman[row][column].right == 3) {
			diceHuman[row][column].top = 2;
		}
		else if (diceHuman[row][column].top == 1 && diceHuman[row][column].right == 2) {
			diceHuman[row][column].top = 4;
		}
		else if (diceHuman[row][column].top == 1 && diceHuman[row][column].right == 4) {
			diceHuman[row][column].top = 5;
		}

		//If the two is on top
		else if (diceHuman[row][column].top == 2 && diceHuman[row][column].right == 1) {
			diceHuman[row][column].top = 3;
		}
		else if (diceHuman[row][column].top == 2 && diceHuman[row][column].right == 3) {
			diceHuman[row][column].top = 6;
		}
		else if (diceHuman[row][column].top == 2 && diceHuman[row][column].right == 6) {
			diceHuman[row][column].top = 4;
		}
		else if (diceHuman[row][column].top == 2 && diceHuman[row][column].right == 4) {
			diceHuman[row][column].top = 1;
		}

		else if (diceHuman[row][column].top == 3 && diceHuman[row][column].right == 2) {
			diceHuman[row][column].top = 1;
		}
		else if (diceHuman[row][column].top == 3 && diceHuman[row][column].right == 1) {
			diceHuman[row][column].top = 5;
		}
		else if (diceHuman[row][column].top == 3 && diceHuman[row][column].right == 5) {
			diceHuman[row][column].top = 6;
		}
		else if (diceHuman[row][column].top == 3 && diceHuman[row][column].right == 6) {
			diceHuman[row][column].top = 2;
		}

		else if (diceHuman[row][column].top == 4 && diceHuman[row][column].right == 2) {
			diceHuman[row][column].top = 6;
		}
		else if (diceHuman[row][column].top == 4 && diceHuman[row][column].right == 6) {
			diceHuman[row][column].top = 5;
		}
		else if (diceHuman[row][column].top == 4 && diceHuman[row][column].right == 5) {
			diceHuman[row][column].top = 1;
		}
		else if (diceHuman[row][column].top == 4 && diceHuman[row][column].right == 1) {
			diceHuman[row][column].top = 2;
		}

		else if (diceHuman[row][column].top == 5 && diceHuman[row][column].right == 6) {
			diceHuman[row][column].top = 3;
		}
		else if (diceHuman[row][column].top == 5 && diceHuman[row][column].right == 3) {
			diceHuman[row][column].top = 1;
		}
		else if (diceHuman[row][column].top == 5 && diceHuman[row][column].right == 1) {
			diceHuman[row][column].top = 4;
		}
		else if (diceHuman[row][column].top == 5 && diceHuman[row][column].right == 4) {
			diceHuman[row][column].top = 6;
		}

		else if (diceHuman[row][column].top == 6 && diceHuman[row][column].right == 2) {
			diceHuman[row][column].top = 3;
		}
		else if (diceHuman[row][column].top == 6 && diceHuman[row][column].right == 3) {
			diceHuman[row][column].top = 5;
		}
		else if (diceHuman[row][column].top == 6 && diceHuman[row][column].right == 5) {
			diceHuman[row][column].top = 4;
		}
		else if (diceHuman[row][column].top == 6 && diceHuman[row][column].right == 4) {
			diceHuman[row][column].top = 2;
		}
	}
}

/* *********************************************************************
Function Name: moveBackwardsHuman

Purpose: To set the correct top die when moving backwards. At this point the
die struct is already at the appropriate row & column and the top die has to be updated.

Parameters: row, an integer, the row where the die will end up moving to
column, an integer, the column where the die will end up moving to
spaces, an integer, the number of spaces the die will be moved backwards

Return Value: None.

Local Variables: None.

Algorithm:
1) Inside a for loop, loop untill the number of spaces moved has been met
2) In each iteration find the top and right die that matches the current one
3) Update only the top die with a new number, as it is moving backwards the right stays the same

Assistance Received: none
********************************************************************* */
void board::moveBackwardsHuman(int row, int column, int spaces) {

	for (int i = 0; i < spaces; i++) {
		//If the 1 is on top
		if (diceHuman[row][column].top == 1 && diceHuman[row][column].right == 5) {
			diceHuman[row][column].top = 4;
		}
		else if (diceHuman[row][column].top == 1 && diceHuman[row][column].right == 3) {
			diceHuman[row][column].top = 5;
		}
		else if (diceHuman[row][column].top == 1 && diceHuman[row][column].right == 2) {
			diceHuman[row][column].top = 3;
		}
		else if (diceHuman[row][column].top == 1 && diceHuman[row][column].right == 4) {
			diceHuman[row][column].top = 2;
		}

		//If the two is on top
		else if (diceHuman[row][column].top == 2 && diceHuman[row][column].right == 1) {
			diceHuman[row][column].top = 4;
		}
		else if (diceHuman[row][column].top == 2 && diceHuman[row][column].right == 3) {
			diceHuman[row][column].top = 1;
		}
		else if (diceHuman[row][column].top == 2 && diceHuman[row][column].right == 6) {
			diceHuman[row][column].top = 3;
		}
		else if (diceHuman[row][column].top == 2 && diceHuman[row][column].right == 4) {
			diceHuman[row][column].top = 6;
		}

		else if (diceHuman[row][column].top == 3 && diceHuman[row][column].right == 2) {
			diceHuman[row][column].top = 6;
		}
		else if (diceHuman[row][column].top == 3 && diceHuman[row][column].right == 1) {
			diceHuman[row][column].top = 2;
		}
		else if (diceHuman[row][column].top == 3 && diceHuman[row][column].right == 5) {
			diceHuman[row][column].top = 1;
		}
		else if (diceHuman[row][column].top == 3 && diceHuman[row][column].right == 6) {
			diceHuman[row][column].top = 5;
		}

		else if (diceHuman[row][column].top == 4 && diceHuman[row][column].right == 2) {
			diceHuman[row][column].top = 1;
		}
		else if (diceHuman[row][column].top == 4 && diceHuman[row][column].right == 6) {
			diceHuman[row][column].top = 2;
		}
		else if (diceHuman[row][column].top == 4 && diceHuman[row][column].right == 5) {
			diceHuman[row][column].top = 6;
		}
		else if (diceHuman[row][column].top == 4 && diceHuman[row][column].right == 1) {
			diceHuman[row][column].top = 5;
		}

		else if (diceHuman[row][column].top == 5 && diceHuman[row][column].right == 6) {
			diceHuman[row][column].top = 4;
		}
		else if (diceHuman[row][column].top == 5 && diceHuman[row][column].right == 3) {
			diceHuman[row][column].top = 6;
		}
		else if (diceHuman[row][column].top == 5 && diceHuman[row][column].right == 1) {
			diceHuman[row][column].top = 3;
		}
		else if (diceHuman[row][column].top == 5 && diceHuman[row][column].right == 4) {
			diceHuman[row][column].top = 1;
		}

		else if (diceHuman[row][column].top == 6 && diceHuman[row][column].right == 2) {
			diceHuman[row][column].top = 4;
		}
		else if (diceHuman[row][column].top == 6 && diceHuman[row][column].right == 3) {
			diceHuman[row][column].top = 2;
		}
		else if (diceHuman[row][column].top == 6 && diceHuman[row][column].right == 5) {
			diceHuman[row][column].top = 3;
		}
		else if (diceHuman[row][column].top == 6 && diceHuman[row][column].right == 4) {
			diceHuman[row][column].top = 5;
		}

	}
}

/* *********************************************************************
Function Name: moveLeftHuman

Purpose: To set the correct top die when moving left. At this point the
die struct is already at the appropriate row & column and the top and left of the die has to be updated.

Parameters: row, an integer, the row where the die will end up moving to
column, an integer, the column where the die will end up moving to
spaces, an integer, the number of spaces the die will be moved to the left

Return Value: None.

Local Variables: None.

Algorithm:
1) Inside a for loop, loop untill the number of spaces moved has been met
2) In each iteration find the top and right die that matches the current one
3) Update the top die and right with the appropriate number

Assistance Received: none
********************************************************************* */
void board::moveLeftHuman(int row, int column, int spaces) {

	for (int i = 0; i < spaces; i++) {
		//If the 1 is on top
		if (diceHuman[row][column].top == 1 && diceHuman[row][column].right == 5) {
			diceHuman[row][column].top = 5;
			diceHuman[row][column].right = 6;
		}
		else if (diceHuman[row][column].top == 1 && diceHuman[row][column].right == 3) {
			diceHuman[row][column].top = 3;
			diceHuman[row][column].right = 6;
		}
		else if (diceHuman[row][column].top == 1 && diceHuman[row][column].right == 2) {
			diceHuman[row][column].top = 2;
			diceHuman[row][column].right = 6;
		}
		else if (diceHuman[row][column].top == 1 && diceHuman[row][column].right == 4) {
			diceHuman[row][column].top = 4;
			diceHuman[row][column].right = 6;
		}

		//If the two is on top
		else if (diceHuman[row][column].top == 2 && diceHuman[row][column].right == 1) {
			diceHuman[row][column].top = 1;
			diceHuman[row][column].right = 5;
		}
		else if (diceHuman[row][column].top == 2 && diceHuman[row][column].right == 3) {
			diceHuman[row][column].top = 3;
			diceHuman[row][column].right = 5;
		}
		else if (diceHuman[row][column].top == 2 && diceHuman[row][column].right == 6) {
			diceHuman[row][column].top = 6;
			diceHuman[row][column].right = 5;
		}
		else if (diceHuman[row][column].top == 2 && diceHuman[row][column].right == 4) {
			diceHuman[row][column].top = 4;
			diceHuman[row][column].right = 5;
		}

		else if (diceHuman[row][column].top == 3 && diceHuman[row][column].right == 2) {
			diceHuman[row][column].top = 2;
			diceHuman[row][column].right = 4;
		}
		else if (diceHuman[row][column].top == 3 && diceHuman[row][column].right == 1) {
			diceHuman[row][column].top = 1;
			diceHuman[row][column].right = 4;
		}
		else if (diceHuman[row][column].top == 3 && diceHuman[row][column].right == 5) {
			diceHuman[row][column].top = 5;
			diceHuman[row][column].right = 4;
		}
		else if (diceHuman[row][column].top == 3 && diceHuman[row][column].right == 6) {
			diceHuman[row][column].top = 6;
			diceHuman[row][column].right = 4;
		}

		else if (diceHuman[row][column].top == 4 && diceHuman[row][column].right == 2) {
			diceHuman[row][column].top = 2;
			diceHuman[row][column].right = 3;
		}
		else if (diceHuman[row][column].top == 4 && diceHuman[row][column].right == 6) {
			diceHuman[row][column].top = 6;
			diceHuman[row][column].right = 3;
		}
		else if (diceHuman[row][column].top == 4 && diceHuman[row][column].right == 5) {
			diceHuman[row][column].top = 5;
			diceHuman[row][column].right = 3;
		}
		else if (diceHuman[row][column].top == 4 && diceHuman[row][column].right == 1) {
			diceHuman[row][column].top = 1;
			diceHuman[row][column].right = 3;
		}

		else if (diceHuman[row][column].top == 5 && diceHuman[row][column].right == 6) {
			diceHuman[row][column].top = 6;
			diceHuman[row][column].right = 2;
		}
		else if (diceHuman[row][column].top == 5 && diceHuman[row][column].right == 3) {
			diceHuman[row][column].top = 3;
			diceHuman[row][column].right = 2;
		}
		else if (diceHuman[row][column].top == 5 && diceHuman[row][column].right == 1) {
			diceHuman[row][column].top = 1;
			diceHuman[row][column].right = 2;
		}
		else if (diceHuman[row][column].top == 5 && diceHuman[row][column].right == 4) {
			diceHuman[row][column].top = 4;
			diceHuman[row][column].right = 2;
		}

		else if (diceHuman[row][column].top == 6 && diceHuman[row][column].right == 2) {
			diceHuman[row][column].top = 2;
			diceHuman[row][column].right = 1;
		}
		else if (diceHuman[row][column].top == 6 && diceHuman[row][column].right == 3) {
			diceHuman[row][column].top = 3;
			diceHuman[row][column].right = 1;
		}
		else if (diceHuman[row][column].top == 6 && diceHuman[row][column].right == 5) {
			diceHuman[row][column].top = 5;
			diceHuman[row][column].right = 1;
		}
		else if (diceHuman[row][column].top == 6 && diceHuman[row][column].right == 4) {
			diceHuman[row][column].top = 4;
			diceHuman[row][column].right = 1;
		}
	}
}

/* *********************************************************************
Function Name: moveRightHuman

Purpose: To set the correct top die when moving right. At this point the
die struct is already at the appropriate row & column and the top and right of the die has to be updated.

Parameters: row, an integer, the row where the die will end up moving to
column, an integer, the column where the die will end up moving to
spaces, an integer, the number of spaces the die will be moved to the right

Return Value: None.

Local Variables: None.

Algorithm:
1) Inside a for loop, loop untill the number of spaces moved has been met
2) In each iteration find the top and right die that matches the current one
3) Update the top die and right with the appropriate number

Assistance Received: none
********************************************************************* */
void board::moveRightHuman(int row, int column, int spaces) {

	for (int i = 0; i < spaces; i++) {
		//If the 1 is on top
		if (diceHuman[row][column].top == 1 && diceHuman[row][column].right == 5) {
			diceHuman[row][column].top = 2;
			diceHuman[row][column].right = 1;
		}
		else if (diceHuman[row][column].top == 1 && diceHuman[row][column].right == 3) {
			diceHuman[row][column].top = 4;
			diceHuman[row][column].right = 1;
		}
		else if (diceHuman[row][column].top == 1 && diceHuman[row][column].right == 2) {
			diceHuman[row][column].top = 5;
			diceHuman[row][column].right = 1;
		}
		else if (diceHuman[row][column].top == 1 && diceHuman[row][column].right == 4) {
			diceHuman[row][column].top = 3;
			diceHuman[row][column].right = 1;
		}

		//If the two is on top
		else if (diceHuman[row][column].top == 2 && diceHuman[row][column].right == 1) {
			diceHuman[row][column].top = 6;
			diceHuman[row][column].right = 2;
		}
		else if (diceHuman[row][column].top == 2 && diceHuman[row][column].right == 3) {
			diceHuman[row][column].top = 4;
			diceHuman[row][column].right = 2;
		}
		else if (diceHuman[row][column].top == 2 && diceHuman[row][column].right == 6) {
			diceHuman[row][column].top = 1;
			diceHuman[row][column].right = 2;
		}
		else if (diceHuman[row][column].top == 2 && diceHuman[row][column].right == 4) {
			diceHuman[row][column].top = 3;
			diceHuman[row][column].right = 2;
		}

		else if (diceHuman[row][column].top == 3 && diceHuman[row][column].right == 2) {
			diceHuman[row][column].top = 5;
			diceHuman[row][column].right = 3;
		}
		else if (diceHuman[row][column].top == 3 && diceHuman[row][column].right == 1) {
			diceHuman[row][column].top = 6;
			diceHuman[row][column].right = 3;
		}
		else if (diceHuman[row][column].top == 3 && diceHuman[row][column].right == 5) {
			diceHuman[row][column].top = 2;
			diceHuman[row][column].right = 3;
		}
		else if (diceHuman[row][column].top == 3 && diceHuman[row][column].right == 6) {
			diceHuman[row][column].top = 1;
			diceHuman[row][column].right = 3;
		}

		else if (diceHuman[row][column].top == 4 && diceHuman[row][column].right == 2) {
			diceHuman[row][column].top = 5;
			diceHuman[row][column].right = 4;
		}
		else if (diceHuman[row][column].top == 4 && diceHuman[row][column].right == 6) {
			diceHuman[row][column].top = 1;
			diceHuman[row][column].right = 4;
		}
		else if (diceHuman[row][column].top == 4 && diceHuman[row][column].right == 5) {
			diceHuman[row][column].top = 2;
			diceHuman[row][column].right = 4;
		}
		else if (diceHuman[row][column].top == 4 && diceHuman[row][column].right == 1) {
			diceHuman[row][column].top = 6;
			diceHuman[row][column].right = 4;
		}

		else if (diceHuman[row][column].top == 5 && diceHuman[row][column].right == 6) {
			diceHuman[row][column].top = 1;
			diceHuman[row][column].right = 5;
		}
		else if (diceHuman[row][column].top == 5 && diceHuman[row][column].right == 3) {
			diceHuman[row][column].top = 4;
			diceHuman[row][column].right = 5;
		}
		else if (diceHuman[row][column].top == 5 && diceHuman[row][column].right == 1) {
			diceHuman[row][column].top = 6;
			diceHuman[row][column].right = 5;
		}
		else if (diceHuman[row][column].top == 5 && diceHuman[row][column].right == 4) {
			diceHuman[row][column].top = 3;
			diceHuman[row][column].right = 5;
		}

		else if (diceHuman[row][column].top == 6 && diceHuman[row][column].right == 2) {
			diceHuman[row][column].top = 5;
			diceHuman[row][column].right = 6;
		}
		else if (diceHuman[row][column].top == 6 && diceHuman[row][column].right == 3) {
			diceHuman[row][column].top = 4;
			diceHuman[row][column].right = 6;
		}
		else if (diceHuman[row][column].top == 6 && diceHuman[row][column].right == 5) {
			diceHuman[row][column].top = 2;
			diceHuman[row][column].right = 6;
		}
		else if (diceHuman[row][column].top == 6 && diceHuman[row][column].right == 4) {
			diceHuman[row][column].top = 3;
			diceHuman[row][column].right = 6;
		}

	}
}

/* *********************************************************************
Function Name: killComputerDice

Purpose: To set the space that used to be a 1 in the games map to a 0.

Parameters: newRow, an integer, that describes the row of where a die will move to
newColumn, an integer, that describes the column of where a die will move to

Return Value:None.

Assistance Received: none
********************************************************************* */
void board::killComputerDice(int newRow, int newColumn) {
	//kill it in the games map
	games[newRow][newColumn] = 2;
}

//**********************************
//******************************
//**************************





/* *********************************************************************
Function Name: moveDiceComputer

Purpose: To move the computer dice to the appropriate spot with the appropriate new
die numbers.

Parameters: player, a computer object passed by value, used to get the movement direction
row, an integer, used to represent the row of the die player wants to move
column, an integer, used to represent the column of the die the player wants to move
newRow, an integer, the location of the row where the die should move to
newColumn, an integer, the location of the column where the die should move to
firstDirection, a string, whether the die should be moving frontally or laterally first

Return Value: None

Local Variables: oldGames, an integer, to hold the number that was at the original space
oldDice, a dice struct, used to hold the old dice that was at the original space
frontalSpaces, an integer, used to calculate the number of horizontal movement spaces
lateralSpaces, an integer, used to calculate the number of lateral movement spaces
direction, a string, used to hold which direction the dice is moving

Algorithm:
1) Store the current dice in the oldDice variable
2) Store the current piece number in the oldGames variable
3) Get the direction in which the die is going to be moving
4) Go through if statements in order to see if the direction matches any movements
5) If a match is found, set the games[newRow][newColumn] to the oldGames variable
6) If a match is found, set the diceHuman[newRow][newColumn] to the oldDice variable
7) Change the diceHuman stored row and column appropriately
8) Calculate the movement fontally and laterally
9) Call the appropriate movement functions depending on which direction is in the string firstDirection

Assistance Received: none
********************************************************************* */
void board::moveDiceComputer(computer player, int row, int column, int newRow, int newColumn, string firstDirection) {
	int oldGames;
	dice oldDice;

	oldDice = diceComputer[row][column];
	oldGames = games[row][column];

	int frontalSpaces = 0;
	int lateralSpaces = 0;

	string direction;
	direction = player.movementDirection(row, column, newRow, newColumn);

	if (direction == "F") {

		//Set games and dicehuman correctly
		games[newRow][column] = oldGames;
		diceComputer[newRow][column] = oldDice;
		diceComputer[newRow][column].row = newRow;

		//Move dice
		//Calculate the number of spaces being moved forward
		frontalSpaces = calculateFront(row, newRow);
		//Calculate the dice movement using the new row/column
		moveFrontalComputer(newRow, column, frontalSpaces);
	}

	else if (direction == "B") {
		//Set games and dicehuman correctly
		games[newRow][column] = oldGames;
		diceComputer[newRow][column] = oldDice;
		diceComputer[newRow][column].row = newRow;

		//Move dice
		//Calculate the number of spaces being moved forward
		frontalSpaces = calculateFront(row, newRow);
		//Calculate the dice movement using the new row/column
		moveBackwardsComputer(newRow, column, frontalSpaces);
	}

	else if (direction == "L") {
		games[row][newColumn] = oldGames;
		diceComputer[row][newColumn] = oldDice;
		diceComputer[row][newColumn].column = newColumn;

		lateralSpaces = calculateLateral(column, newColumn);
		moveLeftComputer(newRow, newColumn, lateralSpaces);
	}

	else if (direction == "R") {
		games[row][newColumn] = oldGames;
		diceComputer[row][newColumn] = oldDice;
		diceComputer[row][newColumn].column = newColumn;

		lateralSpaces = calculateLateral(column, newColumn);
		moveRightComputer(newRow, newColumn, lateralSpaces);
	}

	else if (direction == "FL") {
		games[newRow][newColumn] = oldGames;
		diceComputer[newRow][newColumn] = oldDice;
		diceComputer[newRow][newColumn].column = newColumn;
		diceComputer[newRow][newColumn].row = newRow;

		//Calculate the number of spaces being moved
		frontalSpaces = calculateFront(row, newRow);
		lateralSpaces = calculateLateral(column, newColumn);

		//Calculate the dice movement using the new row/column
		if (firstDirection == "frontal") {
			moveFrontalComputer(newRow, newColumn, frontalSpaces);
			moveLeftComputer(newRow, newColumn, lateralSpaces);
		}
		else if (firstDirection == "lateral") {
			moveLeftComputer(newRow, newColumn, lateralSpaces);
			moveFrontalComputer(newRow, newColumn, frontalSpaces);
		}
	}

	else if (direction == "FR") {
		games[newRow][newColumn] = oldGames;
		diceComputer[newRow][newColumn] = oldDice;
		diceComputer[newRow][newColumn].column = newColumn;
		diceComputer[newRow][newColumn].row = newRow;

		//Calculate the number of spaces being moved
		frontalSpaces = calculateFront(row, newRow);
		lateralSpaces = calculateLateral(column, newColumn);
		//Calculate the dice movement using the new row/column

		if (firstDirection == "frontal") {
			moveFrontalComputer(newRow, newColumn, frontalSpaces);
			moveRightComputer(newRow, newColumn, lateralSpaces);
		}
		else if (firstDirection == "lateral") {
			moveRightComputer(newRow, newColumn, lateralSpaces);
			moveFrontalComputer(newRow, newColumn, frontalSpaces);
		}

	}

	else if (direction == "BL") {
		games[newRow][newColumn] = oldGames;
		diceComputer[newRow][newColumn] = oldDice;
		diceComputer[newRow][newColumn].column = newColumn;
		diceComputer[newRow][newColumn].row = newRow;

		//Move dice
		//Calculate the number of spaces being moved forward
		frontalSpaces = calculateFront(row, newRow);
		lateralSpaces = calculateLateral(column, newColumn);
		//Calculate the dice movement using the new row/column
		if (firstDirection == "frontal") {
			moveBackwardsComputer(newRow, newColumn, frontalSpaces);
			moveLeftComputer(newRow, newColumn, lateralSpaces);
		}
		else if (firstDirection == "lateral") {
			moveLeftComputer(newRow, newColumn, lateralSpaces);
			moveBackwardsComputer(newRow, newColumn, frontalSpaces);
		}

	}

	else if (direction == "BR") {
		games[newRow][newColumn] = oldGames;
		diceComputer[newRow][newColumn] = oldDice;
		diceComputer[newRow][newColumn].column = newColumn;
		diceComputer[newRow][newColumn].row = newRow;

		//Move dice
		//Calculate the number of spaces being moved forward
		frontalSpaces = calculateFront(row, newRow);
		lateralSpaces = calculateLateral(column, newColumn);
		//Calculate the dice movement using the new row/column
		if (firstDirection == "frontal") {
			moveBackwardsComputer(newRow, newColumn, frontalSpaces);
			moveRightComputer(newRow, newColumn, lateralSpaces);
		}
		else if (firstDirection == "lateral") {
			moveRightComputer(newRow, newColumn, lateralSpaces);
			moveBackwardsComputer(newRow, newColumn, frontalSpaces);
		}
	}

	else {
		cout << "THIS IS INVALID" << endl;
	}

	games[row][column] = 0;
}


/* *********************************************************************
Function Name: moveFrontalComputer

Purpose: To set the correct top die when moving forwards. At this point the
die struct is already at the appropriate row & column and the top die has to be updated.

Parameters: row, an integer, the row where the die will end up moving to
column, an integer, the column where the die will end up moving to
spaces, an integer, the number of spaces the die will be moved frontally

Return Value: None.

Local Variables: None.

Algorithm:
1) Inside a for loop, loop untill the number of spaces moved has been met
2) In each iteration find the top and right die that matches the current one
3) Update only the top die with a new number, as it is moving forward the right stays the same

Assistance Received: none
********************************************************************* */
void board::moveFrontalComputer(int row, int column, int spaces) {

	for (int i = 0; i < spaces; i++) {
		//If the 1 is on top
		if (diceComputer[row][column].top == 1 && diceComputer[row][column].right == 5) {
			diceComputer[row][column].top = 3;
		}
		else if (diceComputer[row][column].top == 1 && diceComputer[row][column].right == 3) {
			diceComputer[row][column].top = 2;
		}
		else if (diceComputer[row][column].top == 1 && diceComputer[row][column].right == 2) {
			diceComputer[row][column].top = 4;
		}
		else if (diceComputer[row][column].top == 1 && diceComputer[row][column].right == 4) {
			diceComputer[row][column].top = 5;
		}

		//If the two is on top
		else if (diceComputer[row][column].top == 2 && diceComputer[row][column].right == 1) {
			diceComputer[row][column].top = 3;
		}
		else if (diceComputer[row][column].top == 2 && diceComputer[row][column].right == 3) {
			diceComputer[row][column].top = 6;
		}
		else if (diceComputer[row][column].top == 2 && diceComputer[row][column].right == 6) {
			diceComputer[row][column].top = 4;
		}
		else if (diceComputer[row][column].top == 2 && diceComputer[row][column].right == 4) {
			diceComputer[row][column].top = 1;
		}

		else if (diceComputer[row][column].top == 3 && diceComputer[row][column].right == 2) {
			diceComputer[row][column].top = 1;
		}
		else if (diceComputer[row][column].top == 3 && diceComputer[row][column].right == 1) {
			diceComputer[row][column].top = 5;
		}
		else if (diceComputer[row][column].top == 3 && diceComputer[row][column].right == 5) {
			diceComputer[row][column].top = 6;
		}
		else if (diceComputer[row][column].top == 3 && diceComputer[row][column].right == 6) {
			diceComputer[row][column].top = 2;
		}

		else if (diceComputer[row][column].top == 4 && diceComputer[row][column].right == 2) {
			diceComputer[row][column].top = 6;
		}
		else if (diceComputer[row][column].top == 4 && diceComputer[row][column].right == 6) {
			diceComputer[row][column].top = 5;
		}
		else if (diceComputer[row][column].top == 4 && diceComputer[row][column].right == 5) {
			diceComputer[row][column].top = 1;
		}
		else if (diceComputer[row][column].top == 4 && diceComputer[row][column].right == 1) {
			diceComputer[row][column].top = 2;
		}

		else if (diceComputer[row][column].top == 5 && diceComputer[row][column].right == 6) {
			diceComputer[row][column].top = 3;
		}
		else if (diceComputer[row][column].top == 5 && diceComputer[row][column].right == 3) {
			diceComputer[row][column].top = 1;
		}
		else if (diceComputer[row][column].top == 5 && diceComputer[row][column].right == 1) {
			diceComputer[row][column].top = 4;
		}
		else if (diceComputer[row][column].top == 5 && diceComputer[row][column].right == 4) {
			diceComputer[row][column].top = 6;
		}

		else if (diceComputer[row][column].top == 6 && diceComputer[row][column].right == 2) {
			diceComputer[row][column].top = 3;
		}
		else if (diceComputer[row][column].top == 6 && diceComputer[row][column].right == 3) {
			diceComputer[row][column].top = 5;
		}
		else if (diceComputer[row][column].top == 6 && diceComputer[row][column].right == 5) {
			diceComputer[row][column].top = 4;
		}
		else if (diceComputer[row][column].top == 6 && diceComputer[row][column].right == 4) {
			diceComputer[row][column].top = 2;
		}
	}
}

/* *********************************************************************
Function Name: moveBackwardsComputer

Purpose: To set the correct top die when moving backwards. At this point the
die struct is already at the appropriate row & column and the top die has to be updated.

Parameters: row, an integer, the row where the die will end up moving to
column, an integer, the column where the die will end up moving to
spaces, an integer, the number of spaces the die will be moved backwards

Return Value: None.

Local Variables: None.

Algorithm:
1) Inside a for loop, loop untill the number of spaces moved has been met
2) In each iteration find the top and right die that matches the current one
3) Update only the top die with a new number, as it is moving backwards the right stays the same

Assistance Received: none
********************************************************************* */
void board::moveBackwardsComputer(int row, int column, int spaces) {

	for (int i = 0; i < spaces; i++) {
		//If the 1 is on top
		if (diceComputer[row][column].top == 1 && diceComputer[row][column].right == 5) {
			diceComputer[row][column].top = 4;
		}
		else if (diceComputer[row][column].top == 1 && diceComputer[row][column].right == 3) {
			diceComputer[row][column].top = 5;
		}
		else if (diceComputer[row][column].top == 1 && diceComputer[row][column].right == 2) {
			diceComputer[row][column].top = 3;
		}
		else if (diceComputer[row][column].top == 1 && diceComputer[row][column].right == 4) {
			diceComputer[row][column].top = 2;
		}

		//If the two is on top
		else if (diceComputer[row][column].top == 2 && diceComputer[row][column].right == 1) {
			diceComputer[row][column].top = 4;
		}
		else if (diceComputer[row][column].top == 2 && diceComputer[row][column].right == 3) {
			diceComputer[row][column].top = 1;
		}
		else if (diceComputer[row][column].top == 2 && diceComputer[row][column].right == 6) {
			diceComputer[row][column].top = 3;
		}
		else if (diceComputer[row][column].top == 2 && diceComputer[row][column].right == 4) {
			diceComputer[row][column].top = 6;
		}

		else if (diceComputer[row][column].top == 3 && diceComputer[row][column].right == 2) {
			diceComputer[row][column].top = 6;
		}
		else if (diceComputer[row][column].top == 3 && diceComputer[row][column].right == 1) {
			diceComputer[row][column].top = 2;
		}
		else if (diceComputer[row][column].top == 3 && diceComputer[row][column].right == 5) {
			diceComputer[row][column].top = 1;
		}
		else if (diceComputer[row][column].top == 3 && diceComputer[row][column].right == 6) {
			diceComputer[row][column].top = 5;
		}

		else if (diceComputer[row][column].top == 4 && diceComputer[row][column].right == 2) {
			diceComputer[row][column].top = 1;
		}
		else if (diceComputer[row][column].top == 4 && diceComputer[row][column].right == 6) {
			diceComputer[row][column].top = 2;
		}
		else if (diceComputer[row][column].top == 4 && diceComputer[row][column].right == 5) {
			diceComputer[row][column].top = 6;
		}
		else if (diceComputer[row][column].top == 4 && diceComputer[row][column].right == 1) {
			diceComputer[row][column].top = 5;
		}

		else if (diceComputer[row][column].top == 5 && diceComputer[row][column].right == 6) {
			diceComputer[row][column].top = 4;
		}
		else if (diceComputer[row][column].top == 5 && diceComputer[row][column].right == 3) {
			diceComputer[row][column].top = 6;
		}
		else if (diceComputer[row][column].top == 5 && diceComputer[row][column].right == 1) {
			diceComputer[row][column].top = 3;
		}
		else if (diceComputer[row][column].top == 5 && diceComputer[row][column].right == 4) {
			diceComputer[row][column].top = 1;
		}

		else if (diceComputer[row][column].top == 6 && diceComputer[row][column].right == 2) {
			diceComputer[row][column].top = 4;
		}
		else if (diceComputer[row][column].top == 6 && diceComputer[row][column].right == 3) {
			diceComputer[row][column].top = 2;
		}
		else if (diceComputer[row][column].top == 6 && diceComputer[row][column].right == 5) {
			diceComputer[row][column].top = 3;
		}
		else if (diceComputer[row][column].top == 6 && diceComputer[row][column].right == 4) {
			diceComputer[row][column].top = 5;
		}

	}
}

/* *********************************************************************
Function Name: moveLeftComputer

Purpose: To set the correct top die when moving left. At this point the
die struct is already at the appropriate row & column and the top and left of the die has to be updated.

Parameters: row, an integer, the row where the die will end up moving to
column, an integer, the column where the die will end up moving to
spaces, an integer, the number of spaces the die will be moved to the left

Return Value: None.

Local Variables: None.

Algorithm:
1) Inside a for loop, loop untill the number of spaces moved has been met
2) In each iteration find the top and right die that matches the current one
3) Update the top die and right with the appropriate number

Assistance Received: none
********************************************************************* */
void board::moveLeftComputer(int row, int column, int spaces) {

	for (int i = 0; i < spaces; i++) {
		//If the 1 is on top
		if (diceComputer[row][column].top == 1 && diceComputer[row][column].right == 5) {
			diceComputer[row][column].top = 5;
			diceComputer[row][column].right = 6;
		}
		else if (diceComputer[row][column].top == 1 && diceComputer[row][column].right == 3) {
			diceComputer[row][column].top = 3;
			diceComputer[row][column].right = 6;
		}
		else if (diceComputer[row][column].top == 1 && diceComputer[row][column].right == 2) {
			diceComputer[row][column].top = 2;
			diceComputer[row][column].right = 6;
		}
		else if (diceComputer[row][column].top == 1 && diceComputer[row][column].right == 4) {
			diceComputer[row][column].top = 4;
			diceComputer[row][column].right = 6;
		}

		//If the two is on top
		else if (diceComputer[row][column].top == 2 && diceComputer[row][column].right == 1) {
			diceComputer[row][column].top = 1;
			diceComputer[row][column].right = 5;
		}
		else if (diceComputer[row][column].top == 2 && diceComputer[row][column].right == 3) {
			diceComputer[row][column].top = 3;
			diceComputer[row][column].right = 5;
		}
		else if (diceComputer[row][column].top == 2 && diceComputer[row][column].right == 6) {
			diceComputer[row][column].top = 6;
			diceComputer[row][column].right = 5;
		}
		else if (diceComputer[row][column].top == 2 && diceComputer[row][column].right == 4) {
			diceComputer[row][column].top = 4;
			diceComputer[row][column].right = 5;
		}

		else if (diceComputer[row][column].top == 3 && diceComputer[row][column].right == 2) {
			diceComputer[row][column].top = 2;
			diceComputer[row][column].right = 4;
		}
		else if (diceComputer[row][column].top == 3 && diceComputer[row][column].right == 1) {
			diceComputer[row][column].top = 1;
			diceComputer[row][column].right = 4;
		}
		else if (diceComputer[row][column].top == 3 && diceComputer[row][column].right == 5) {
			diceComputer[row][column].top = 5;
			diceComputer[row][column].right = 4;
		}
		else if (diceComputer[row][column].top == 3 && diceComputer[row][column].right == 6) {
			diceComputer[row][column].top = 6;
			diceComputer[row][column].right = 4;
		}

		else if (diceComputer[row][column].top == 4 && diceComputer[row][column].right == 2) {
			diceComputer[row][column].top = 2;
			diceComputer[row][column].right = 3;
		}
		else if (diceComputer[row][column].top == 4 && diceComputer[row][column].right == 6) {
			diceComputer[row][column].top = 6;
			diceComputer[row][column].right = 3;
		}
		else if (diceComputer[row][column].top == 4 && diceComputer[row][column].right == 5) {
			diceComputer[row][column].top = 5;
			diceComputer[row][column].right = 3;
		}
		else if (diceComputer[row][column].top == 4 && diceComputer[row][column].right == 1) {
			diceComputer[row][column].top = 1;
			diceComputer[row][column].right = 3;
		}

		else if (diceComputer[row][column].top == 5 && diceComputer[row][column].right == 6) {
			diceComputer[row][column].top = 6;
			diceComputer[row][column].right = 2;
		}
		else if (diceComputer[row][column].top == 5 && diceComputer[row][column].right == 3) {
			diceComputer[row][column].top = 3;
			diceComputer[row][column].right = 2;
		}
		else if (diceComputer[row][column].top == 5 && diceComputer[row][column].right == 1) {
			diceComputer[row][column].top = 1;
			diceComputer[row][column].right = 2;
		}
		else if (diceComputer[row][column].top == 5 && diceComputer[row][column].right == 4) {
			diceComputer[row][column].top = 4;
			diceComputer[row][column].right = 2;
		}

		else if (diceComputer[row][column].top == 6 && diceComputer[row][column].right == 2) {
			diceComputer[row][column].top = 2;
			diceComputer[row][column].right = 1;
		}
		else if (diceComputer[row][column].top == 6 && diceComputer[row][column].right == 3) {
			diceComputer[row][column].top = 3;
			diceComputer[row][column].right = 1;
		}
		else if (diceComputer[row][column].top == 6 && diceComputer[row][column].right == 5) {
			diceComputer[row][column].top = 5;
			diceComputer[row][column].right = 1;
		}
		else if (diceComputer[row][column].top == 6 && diceComputer[row][column].right == 4) {
			diceComputer[row][column].top = 4;
			diceComputer[row][column].right = 1;
		}

	}
}

/* *********************************************************************
Function Name: moveRightComputer

Purpose: To set the correct top die when moving right. At this point the
die struct is already at the appropriate row & column and the top and right of the die has to be updated.

Parameters: row, an integer, the row where the die will end up moving to
column, an integer, the column where the die will end up moving to
spaces, an integer, the number of spaces the die will be moved to the right

Return Value: None.

Local Variables: None.

Algorithm:
1) Inside a for loop, loop untill the number of spaces moved has been met
2) In each iteration find the top and right die that matches the current one
3) Update the top die and right with the appropriate number

Assistance Received: none
********************************************************************* */
void board::moveRightComputer(int row, int column, int spaces) {

	for (int i = 0; i < spaces; i++) {
		//If the 1 is on top
		if (diceComputer[row][column].top == 1 && diceComputer[row][column].right == 5) {
			diceComputer[row][column].top = 2;
			diceComputer[row][column].right = 1;
		}
		else if (diceComputer[row][column].top == 1 && diceComputer[row][column].right == 3) {
			diceComputer[row][column].top = 4;
			diceComputer[row][column].right = 1;
		}
		else if (diceComputer[row][column].top == 1 && diceComputer[row][column].right == 2) {
			diceComputer[row][column].top = 5;
			diceComputer[row][column].right = 1;
		}
		else if (diceComputer[row][column].top == 1 && diceComputer[row][column].right == 4) {
			diceComputer[row][column].top = 3;
			diceComputer[row][column].right = 1;
		}

		//If the two is on top
		else if (diceComputer[row][column].top == 2 && diceComputer[row][column].right == 1) {
			diceComputer[row][column].top = 6;
			diceComputer[row][column].right = 2;
		}
		else if (diceComputer[row][column].top == 2 && diceComputer[row][column].right == 3) {
			diceComputer[row][column].top = 4;
			diceComputer[row][column].right = 2;
		}
		else if (diceComputer[row][column].top == 2 && diceComputer[row][column].right == 6) {
			diceComputer[row][column].top = 1;
			diceComputer[row][column].right = 2;
		}
		else if (diceComputer[row][column].top == 2 && diceComputer[row][column].right == 4) {
			diceComputer[row][column].top = 3;
			diceComputer[row][column].right = 2;
		}

		else if (diceComputer[row][column].top == 3 && diceComputer[row][column].right == 2) {
			diceComputer[row][column].top = 5;
			diceComputer[row][column].right = 3;
		}
		else if (diceComputer[row][column].top == 3 && diceComputer[row][column].right == 1) {
			diceComputer[row][column].top = 6;
			diceComputer[row][column].right = 3;
		}
		else if (diceComputer[row][column].top == 3 && diceComputer[row][column].right == 5) {
			diceComputer[row][column].top = 2;
			diceComputer[row][column].right = 3;
		}
		else if (diceComputer[row][column].top == 3 && diceComputer[row][column].right == 6) {
			diceComputer[row][column].top = 1;
			diceComputer[row][column].right = 3;
		}

		else if (diceComputer[row][column].top == 4 && diceComputer[row][column].right == 2) {
			diceComputer[row][column].top = 5;
			diceComputer[row][column].right = 4;
		}
		else if (diceComputer[row][column].top == 4 && diceComputer[row][column].right == 6) {
			diceComputer[row][column].top = 1;
			diceComputer[row][column].right = 4;
		}
		else if (diceComputer[row][column].top == 4 && diceComputer[row][column].right == 5) {
			diceComputer[row][column].top = 2;
			diceComputer[row][column].right = 4;
		}
		else if (diceComputer[row][column].top == 4 && diceComputer[row][column].right == 1) {
			diceComputer[row][column].top = 6;
			diceComputer[row][column].right = 4;
		}

		else if (diceComputer[row][column].top == 5 && diceComputer[row][column].right == 6) {
			diceComputer[row][column].top = 1;
			diceComputer[row][column].right = 5;
		}
		else if (diceComputer[row][column].top == 5 && diceComputer[row][column].right == 3) {
			diceComputer[row][column].top = 4;
			diceComputer[row][column].right = 5;
		}
		else if (diceComputer[row][column].top == 5 && diceComputer[row][column].right == 1) {
			diceComputer[row][column].top = 6;
			diceComputer[row][column].right = 5;
		}
		else if (diceComputer[row][column].top == 5 && diceComputer[row][column].right == 4) {
			diceComputer[row][column].top = 3;
			diceComputer[row][column].right = 5;
		}

		else if (diceComputer[row][column].top == 6 && diceComputer[row][column].right == 2) {
			diceComputer[row][column].top = 5;
			diceComputer[row][column].right = 6;
		}
		else if (diceComputer[row][column].top == 6 && diceComputer[row][column].right == 3) {
			diceComputer[row][column].top = 4;
			diceComputer[row][column].right = 6;
		}
		else if (diceComputer[row][column].top == 6 && diceComputer[row][column].right == 5) {
			diceComputer[row][column].top = 2;
			diceComputer[row][column].right = 6;
		}
		else if (diceComputer[row][column].top == 6 && diceComputer[row][column].right == 4) {
			diceComputer[row][column].top = 3;
			diceComputer[row][column].right = 6;
		}
	}
}


/* *********************************************************************
Function Name: killHumanDice

Purpose: To set the space that used to be a 2 in the games map to a 0.

Parameters: newRow, an integer, that describes the row of where a die will move to
newColumn, an integer, that describes the column of where a die will move to

Return Value:None.

Assistance Received: none
********************************************************************* */
void board::killHumanDice(int newRow, int newColumn) {
	//kill it in the games map
	games[newRow][newColumn] = 1;
}

/* *********************************************************************
Function Name: getSpecialHumanDiceRow

Purpose: To return the row of the special human die.

Parameters: None

Return Value: An integer, i, the row where the special die was found.

Assistance Received: none
********************************************************************* */
const int board::getSpecialHumanDiceRow() {
	for (int i = 8; i > 0; i--) {
		for (int j = 1; j < 10; j++) {
			if (games[i][j] == 2) {
				if (diceHuman[i][j].top == 1 && diceHuman[i][j].right == 1) {
					return i;
				}
			}
		}
	}
}

/* *********************************************************************
Function Name: getSpecialHumanDiceColumn

Purpose: To return the column of the special human die.

Parameters: None

Return Value: An integer, j, the column where the special die was found.

Assistance Received: none
********************************************************************* */
const int board::getSpecialHumanDiceColumn() {
	for (int i = 8; i > 0; i--) {
		for (int j = 1; j < 10; j++) {
			if (games[i][j] == 2) {
				if (diceHuman[i][j].top == 1 && diceHuman[i][j].right == 1) {
					return j;
				}
			}
		}
	}
}

/* *********************************************************************
Function Name: getSpecialComputerDiceRow

Purpose: To return the row of the special computer die.

Parameters: None

Return Value: An integer, i, the row where the special die was found.

Assistance Received: none
********************************************************************* */
const int board::getSpecialComputerDiceRow() {
	for (int i = 8; i > 0; i--) {
		for (int j = 1; j < 10; j++) {
			if (games[i][j] == 1) {
				if (diceComputer[i][j].top == 1 && diceComputer[i][j].right == 1) {
					return i;
				}
			}
		}
	}
}

/* *********************************************************************
Function Name: getSpecialComputerDiceColumn

Purpose: To return the column of the special computer die.

Parameters: None

Return Value: An integer, j, the column where the special die was found.

Assistance Received: none
********************************************************************* */
const int board::getSpecialComputerDiceColumn() {
	for (int i = 8; i > 0; i--) {
		for (int j = 1; j < 10; j++) {
			if (games[i][j] == 1) {
				if (diceComputer[i][j].top == 1 && diceComputer[i][j].right == 1) {
					return j;
				}
			}
		}
	}
}


/* *********************************************************************
Function Name: setGamesPiece

Purpose: To set a games piece from a serialization file

Parameters: row, an integer, that describes the row of the piece
column, an integer, that describes the column of the piece
piece, an integer, whether it should be a space 0, computer 1, or human die 2

Return Value:None.

Assistance Received: none
********************************************************************* */
void board::setGamesPiece(int row, int column, int piece) {
	games[row][column] = piece;
}

/* *********************************************************************
Function Name: setComputerDice

Purpose: To set a computer die in the diceComputer map.

Parameters: row, an integer, that describes the row of the piece
column, an integer, that describes the column of the piece
top, an integer, the top number of a die
right, an integer, the right number of a die

Return Value:None.

Assistance Received: none
********************************************************************* */
void board::setComputerDice(int row, int column, int top, int right) {
	diceComputer[row][column].row = row;
	diceComputer[row][column].column = column;

	diceComputer[row][column].top = top;
	diceComputer[row][column].right = right;
}

/* *********************************************************************
Function Name: setHumanDice

Purpose: To set a human die in the diceHuman map.

Parameters: row, an integer, that describes the row of the piece
column, an integer, that describes the column of the piece
top, an integer, the top number of a die
right, an integer, the right number of a die

Return Value:None.

Assistance Received: None
********************************************************************* */
void board::setHumanDice(int row, int column, int top, int right) {
	diceHuman[row][column].row = row;
	diceHuman[row][column].column = column;

	diceHuman[row][column].top = top;
	diceHuman[row][column].right = right;
}

/* *********************************************************************
Function Name: resetGame

Purpose: To clear the games, diceHuman, and diceComputer maps and reinitialize them
to their original states.

Parameters: None.

Return Value:None.

Assistance Received: None.
********************************************************************* */
void board::resetGame() {
	initializeGames();

	diceHuman.clear();
	initalHumanDice();

	diceComputer.clear();
	initialComputerDice();
}
