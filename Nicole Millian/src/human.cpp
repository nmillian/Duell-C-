/*
************************************************************
* Name: Nicole Millian                                     *
* Project : Duell - Project 1 C++				           *
* Class : CMPS 366 Organization of Programming Languages   *
* Date : October 21, 2016		                           *
************************************************************
*/
#pragma once
#include "human.h"


human::human() {

}

human::human(string playerName) {
	this->setName(playerName);
}

human::~human() {

}

/* *********************************************************************
Function Name: decideMove

Purpose: To determine what move the human should make.

Parameters:Duell, a board object passed by reference, which stores the die
roster, an array of player object pointers, passed by value, used to access the 2 players of the game
compPlayer, a computer object, passed by value, used to access the computer functions
humanPlayer, a human object,  passed by value, used to access human functions

Return Value: A string determining which move was made.

Local Variables: None

Algorithm:
1) Check if it's possible to win via moving to the enemy 1x1 die or the special tile
2) Check if it's possible to defend the special die or special tile
3) Check if it's possible to defend a normal die
4) Check if it's possible to kill an enemy die
5) Check if it's possible to move any of the die to an open space
6) If none of the above work it's not possible to make a move

Assistance Received: none
********************************************************************* */
string human::decideMove(board &Duell, player * roster[], computer compPlayer, human humanPlayer) {
	//Decide which move to suggest to the human player
	//Return a string specifiying which move should be made
	if (humanPlayer.moveToSpecialEnemyDice(Duell, roster, humanPlayer) == true) {
		return "specialdie";
	}
	else if (humanPlayer.moveToSpecialEnemyTile(Duell, roster, humanPlayer) == true) {
		return "specialtile";
	}
	else if (humanPlayer.defendSpecialDice(Duell, roster, compPlayer, humanPlayer) == true) {
		return "defendspecialdie";
	}
	else if (humanPlayer.defendHumanDice(Duell, roster, compPlayer, humanPlayer) == true) {
		return "defendregular";
	}
	else if (humanPlayer.killAComputerDice(Duell, roster, compPlayer, humanPlayer) == true) {
		return "killdice";
	}
	else if (humanPlayer.moveToOpenSpace(Duell, roster, compPlayer, humanPlayer) == true) {
		return "openspace";
	}
	else {
		return "nomove";
	}
}


/* *********************************************************************
Function Name: movetoSpecialEnemyDice

Purpose: To determine if it is possible to capture the special 1x1 enemy die and if so make the move.

Parameters:Duell, a board object passed by reference which stores the die
roster, an array of player object pointers, passed by value, used to access the 2 players of the game
humanPlayer, a human object,  passed by value, which is used to access the computer functions

Return Value: A boolean value, true if it is possible to move to an enemy die, false if it is not possible to move to the special die.

Local Variables:  top, an integer, the top number of a die
right, an integer, the right number of a die
frontal, an integer, the total number of spaces moved frontally
lateral, an integer, the total number of spaces moved laterally
specialRow, an integer, the row where the 1x1 die is located
specialColumn, an integer, the column where the 1x1 die is located
collision, a boolean, which holds true if there was a collision or false if there was none
lastSpace, an integer, which holds what value was at the last space

Algorithm:
1) Get the row and column of the special die
2) Go through and see if it’s possible for a computer die to move to the special die by calculating the frontal and lateral movement and checking if it’s equal to the top of the die.
3) If it’s equal call the checkCollision and checkLastPathSpace function to test if the path works, checking moving frontally first then laterally.
4) If a die that can capture the special die is found, print out what movement the die will make and return true.
5) If no die can capture the special die, return false.

Assistance Received: none
********************************************************************* */
bool human::moveToSpecialEnemyDice(board &Duell, player * roster[], human humanPlayer) {
	//Top dice, right
	int top;
	int right;

	//Fronal and lateral space movement
	int frontal;
	int lateral;

	bool collision;
	int lastSpace;

	//find out where the comp special dice is
	int specialRow = Duell.getSpecialComputerDiceRow();
	int specialColumn = Duell.getSpecialComputerDiceColumn();

	//Start at the top left
	//Checking to see if a die can kill the special die of the human
	for (int i = 8; i > 0; i--) {

		for (int j = 1; j < 10; j++) {

			if (Duell.getNumAtSpace(i, j) == 2) {
				//Get the top and the right
				top = Duell.getHumanTop(i, j);
				right = Duell.getHumanRight(i, j);

				frontal = Duell.calculateFront(i, specialRow);
				lateral = Duell.calculateLateral(j, specialColumn);

				//Can move the correct number of spaces to get to the dice
				if (frontal + lateral == top) {

					//Check the path moving frontally first
					collision = checkCollision(Duell, i, j, specialRow, specialColumn, "frontal", lateral, frontal);
					lastSpace = checkLastPathSpace(Duell, specialRow, specialColumn);

					//Check if there were no collisions and the last space is a valid tile
					if (collision == false && lastSpace != 1) {
						cout << "H" << top << right << " can be rolled frontally first from square (" << i << ", " << j << ") horizontally by " << frontal
							<< " and laterally by " << lateral << ". It will end up on (" << specialRow << ", " << specialColumn << ")." << endl;

						return true;
					}

					//Check moving laterally first if moving frontally fails
					else {
						collision = checkCollision(Duell, i, j, specialRow, specialColumn, "lateral", lateral, frontal);
						lastSpace = checkLastPathSpace(Duell, specialRow, specialColumn);

						//Check if there were no collisions and the last space is a valid tile
						if (collision == false && lastSpace != 1) {

							cout << "H" << top << right << " can be rolled laterally first from square (" << i << ", " << j << ") "
								<< "laterally by " << lateral << " and horizontally by " << frontal <<
								". It will up on (" << specialRow << ", " << specialColumn << ")." << endl;
							return true;
						}
					}
				}
			}
		}
	}

	//Couldn't kill the enemy 1x1 die with any human dice
	return false;
}

/* *********************************************************************
Function Name: movetoSpecialEnemyTile

Purpose: To determine if it is possible to capture the special tile with the 1x1 die.

Parameters:Duell, a board object passed by reference, which stores the die
Roster, an array of player object pointers, passed by value, used to access the 2 players of the game
humanPlayer, a human object,  passed by value, which is used to access the computer functions

Return Value: A boolean value, true if it is possible to move to the enemy tile, false if it is not possible to move to the tile.

Local Variables:  top, an integer, the top number of a die
right, an integer, the right number of a die
specialDieRow, an integer, the row the 1x1 die is located at
specialDieCol, an integer, the column the 1x1 die is located at
frontal, an integer, the total number of spaces moved frontally
lateral, an integer, the total number of spaces moved laterally
winningTileRow, the winning tile row for the computer, row 8
winningTileColumn, the winning tile column for the computer, column 5
collision, a boolean, which holds true if there was a collision or false if there was none
lastSpace, an integer, which holds what value was at the last space

Algorithm:
1) Go through and see if it’s possible for the 1x1 die to move to the special tile by calculating the frontal and lateral movement and checking if it’s equal to the top of the die.
2) If it’s equal call the checkCollision and checkLastPathSpace function to test if the path works, checking moving frontally first then laterally.
3) If the 1x1 can capture the tile print out what movement the die will make and return true.
4) If the die can not capture the special tile, return false.

Assistance Received: none
********************************************************************* */
bool human::moveToSpecialEnemyTile(board &Duell, player * roster[], human humanPlayer) {

	//Top and right of the special die which are constant
	const int top = 1;
	const int right = 1;

	//The location of the special human die
	int specialDieRow = Duell.getSpecialHumanDiceRow();
	int specialDieCol = Duell.getSpecialHumanDiceColumn();

	//The special tiles location for the computer, which is always the same
	const int winningTileRow = 8;
	const int winningTileColumn = 5;

	//Frontal and lateral space movement
	int frontal;
	int lateral;

	//Whether the path is valid and the final tile is able to be landed on
	bool collision;
	int lastSpace;

	//The frontal movement from the current die row to the destination row
	frontal = Duell.calculateFront(specialDieRow, winningTileRow);
	//The lateral movement from the current die column to the destination column
	lateral = Duell.calculateLateral(specialDieCol, winningTileColumn);

	//Can move the correct number of spaces to get to the dice
	if (frontal + lateral == top) {
		//Check the path moving frontally first
		collision = checkCollision(Duell, specialDieRow, specialDieCol, winningTileRow, winningTileColumn, "frontal", lateral, frontal);
		lastSpace = checkLastPathSpace(Duell, winningTileRow, winningTileColumn);

		//Check if the path is valid and the last space is a valid tile
		if (collision == false && lastSpace != 1) {

			cout << "H" << top << right << " can be rolled frontally first from square (" << specialDieRow << ", " << specialDieCol << ") horizontally by " << frontal
				<< " and laterally by " << lateral << ". It end up on (" << winningTileRow << ", " << winningTileColumn << ")." << endl;

			return true;
		}

		//If moving fronatally first fails, check moving laterally first
		else {
			collision = checkCollision(Duell, specialDieRow, specialDieCol, winningTileRow, winningTileColumn, "lateral", lateral, frontal);
			lastSpace = checkLastPathSpace(Duell, winningTileRow, winningTileColumn);

			//Check if the path is valid and the last space is a valid tile
			if (collision == false && lastSpace != 1) {

				cout << "H" << top << right << " can be rolled laterally first from square (" << specialDieRow << ", " << specialDieCol << ") "
					<< "laterally by " << lateral << " and horizontally by " << frontal << ". It will end up on (" << winningTileRow << ", " << winningTileColumn << ")." << endl;

				return true;
			}
		}
	}

	//Can't move to the special computer tile, 8,5 , with any human die
	return false;
}

/* *********************************************************************
Function Name: defendSpecialDice

Purpose: To determine if it is possible to defend the special die with another die.

Parameters:Duell, a board object passed by reference, which stores the die
roster, an array of player object pointers, passed by value, used to access the 2 players of the game
compPlayer, a computer object, passed by value, used to access the computer functions
humanPlayer, a human object,  passed by value, used to access human functions

Return Value: A boolean value, true if it is possible to defend the special die, false if it is not possible to defend the die.

Local Variables: currentHumanDice, a map, which maps coordinates to the top of the die
currentComputerDice, a map, which maps coordinates to the top of the die
computerMovement, a map, which holds coordinates of where the computer die will move to capture the human tile
humanRow2, an integer, the row the human die is located at
humanCol2, an integer, the column the human die is located at
humanTop2, an integer, the top number of a die
computerRow, an integer, the row the computer die is located at
computerCol, an integer, the column the computer die is located at
computerTop, an integer, the top number of a die
pathRow, an integer, the row of a tile the die will be moving to
pathCol, an integer, the column of a tile the die will be moving to
specialRow, an integer, the row where the special tile is, 8
specialCol, an integer, the column where the special tile is, 5
totalMoves, an integer, the total number of spaces moved
frontal, an integer, the total number of spaces moved frontally
lateral, an integer, the total number of spaces moved laterally
collision, a boolean, which holds true if there was a collision or false if there was none
lastSpace, an integer, which holds what value was at the last space


Algorithm:
1) Go through and see if it’s possible for a computer die to attack the human special die.
2) Calculate the frontal and lateral movement and checking if it’s equal to the top of the die.
3) If it’s equal call the checkCollision and checkLastPathSpace function to test if the path works, checking moving frontally first then laterally.
4) If a die that can capture the special die is found, go through and track the path the die will take in computerMovement.
5) Go through the currentHumanDice map and see if there is a die that can block the pathway of the attacking die
6) If a die can block, return true and print out it’s movement
7) If no die can block, return false.

Assistance Received: none
********************************************************************* */
bool human::defendSpecialDice(board &Duell, player * roster[], computer compPlayer, human humanPlayer) {

	//Store the current human dice
	map< int, map<int, int> > currentHumanDice;
	//Store the current comptuer dice
	map< int, map<int, int> > currentComputerDice;

	//Get the path the computer die will move to try to get to a human die
	map< int, map<int, int> > computerMovement;

	//The current computer row, column, and top die 
	int computerRow;
	int computerCol;
	int computerTop;

	//Get the column and row of where the special 1x1 human die is located
	int specialRow = Duell.getSpecialHumanDiceRow();
	int specialCol = Duell.getSpecialHumanDiceColumn();

	//The total frontal and lateral movement 
	int frontal;
	int lateral;

	//Collision and lastSpace verify that a path is valid 
	bool collision;
	int lastSpace;

	//Get all the human dice
	for (int i = 8; i > 0; i--) {
		for (int j = 1; j < 10; j++) {
			//found a human die
			if (Duell.getNumAtSpace(i, j) == 2) {
				//Store the huamn die top number at the coords it was found
				currentHumanDice[i][j] = Duell.getHumanTop(i, j);
			}
		}
	}

	//Get the computer dice
	for (int i = 8; i > 0; i--) {
		for (int j = 1; j < 10; j++) {
			//found a computer die
			if (Duell.getNumAtSpace(i, j) == 1) {
				//Store the computer die top number at the coords it was found
				currentComputerDice[i][j] = Duell.getComputerTop(i, j);
			}
		}
	}

	//Go through all the current computer die and see if any of them can reach the special human die
	for (auto const &compRow : currentComputerDice) {

		for (auto const &compCol : compRow.second) {
			computerRow = compRow.first;
			computerCol = compCol.first;
			computerTop = compCol.second;

			frontal = Duell.calculateFront(computerRow, specialRow);
			lateral = Duell.calculateLateral(computerCol, specialCol);

			//The computer die can move the correct number of spaces to get to the die
			if (frontal + lateral == computerTop) {
				int finalRow;

				//Check if the path works moving frontally first
				collision = compPlayer.checkCollision(Duell, computerRow, computerCol, specialRow, specialCol, "frontal", lateral, frontal);
				lastSpace = compPlayer.checkLastPathSpace(Duell, specialRow, specialCol);

				//***************************************
				//The path works moving frontally first
				if (collision == false && lastSpace != 1) {

					//Get the frontal or backwards movement first
					if (computerRow <= specialRow) {
						finalRow = computerRow + frontal;

						//computer moving backwards + to the row
						for (int i = computerRow; i <= finalRow; i++) {
							computerMovement[i][computerCol] = 999;
						}

					}

					else if (computerRow >= specialRow) {
						//computer moving forwards - to the row
						finalRow = computerRow - frontal;

						for (int i = computerRow; i >= finalRow; i--) {
							computerMovement[i][computerCol] = 999;
						}
					}

					//Get the left or right movement second
					if (computerCol <= specialCol) {
						//computer moving left + to the column
						for (int i = computerCol; i <= computerCol + lateral; i++) {
							computerMovement[finalRow][i] = 999;
						}

					}

					else if (computerCol >= specialCol) {
						//computer moving right - to the column
						for (int i = computerCol; i >= computerCol - lateral; i--) {
							computerMovement[finalRow][i] = 999;
						}

					}

					//Go through the human die and see if any of them can block the pathway
					for (int i = 8; i > 0; i--) {
						for (int j = 1; j < 10; j++) {
							//Found a human die
							if (Duell.getNumAtSpace(i, j) == 2) {
								//Get the row, column, top, and right of the die attempting to block
								int humanRow2 = i;
								int humanCol2 = j;
								int humanTop2 = Duell.getHumanTop(i, j);
								int right = Duell.getHumanRight(i, j);

								//Go through the path and see if the human die can move to any of the spaces
								for (auto const &movement : computerMovement) {
									for (auto const &movement2 : movement.second) {
										int pathRow = movement.first;
										int pathCol = movement2.first;

										frontal = Duell.calculateFront(humanRow2, pathRow);
										lateral = Duell.calculateLateral(humanCol2, pathCol);

										//Can move the correct number of spaces
										if (frontal + lateral == humanTop2) {
											//Checking moving frontally first
											collision = checkCollision(Duell, humanRow2, humanCol2, pathRow, pathCol, "frontal", lateral, frontal);
											lastSpace = checkLastPathSpace(Duell, pathRow, pathCol);

											if (collision == false && lastSpace != 2) {
												cout << "H" << humanTop2 << right << " can be rolled frontally first from square (" << humanRow2 << ", " << humanCol2 << ") horizontally by " << frontal
													<< " and laterally by " << lateral << ". It will up on (" << pathRow << ", " << pathCol << ")." << endl;
												return true;
											}

											//If moving frontally first fails, check moving laterally first
											collision = checkCollision(Duell, humanRow2, humanCol2, pathRow, pathCol, "lateral", lateral, frontal);
											lastSpace = checkLastPathSpace(Duell, pathRow, pathCol);

											if (collision == false && lastSpace != 2) {
												cout << "H" << humanTop2 << right << " can be rolled laterally first from square (" << humanRow2 << ", " << humanCol2 << ") Laterally by " << lateral <<
													" and horizontally by " << frontal << ". It will end up on (" << pathRow << ", " << pathCol << ")." << endl;
												return true;
											}

										}
									}
								}
							}
						}
					}
				}

				//****************************************

				//Check if the computer die can get to the special die moving laterally first if moving frontally fails
				collision = compPlayer.checkCollision(Duell, computerRow, computerCol, specialRow, specialCol, "lateral", lateral, frontal);
				lastSpace = compPlayer.checkLastPathSpace(Duell, specialRow, specialCol);

				frontal = Duell.calculateFront(computerRow, specialRow);
				lateral = Duell.calculateLateral(computerCol, specialCol);

				//The path works moving laterally
				if (collision == false && lastSpace != 1) {

					int finalCol;

					//The left or right movement first
					if (computerCol <= specialCol) {
						finalCol = computerCol + lateral;
						//computer moving left +
						for (int i = computerCol; i <= finalCol; i++) {
							computerMovement[computerRow][i] = 999;
						}

					}

					else if (computerCol >= specialCol) {
						finalCol = computerCol - lateral;
						//computer moving right -
						for (int i = computerCol; i >= finalCol; i--) {
							computerMovement[computerRow][i] = 999;
						}

					}

					//The front and backwards movement
					if (computerRow <= specialRow) {
						//computer moving backwards +
						for (int i = computerRow; i <= computerRow + frontal; i++) {
							computerMovement[i][finalCol] = 999;
						}

					}

					else if (computerRow >= specialRow) {
						//computer moving forwards -

						for (int i = computerRow; i >= computerRow - frontal; i--) {
							computerMovement[i][finalCol] = 999;
						}
					}

					//Go through and see if a human die can block at any of the spaces the computer die will be moving
					for (int i = 8; i > 0; i--) {
						for (int j = 1; j < 10; j++) {
							//Found a human die
							if (Duell.getNumAtSpace(i, j) == 2) {
								//Get the row, column, top, and right of the die attempting to block the computer die
								int humanRow2 = i;
								int humanCol2 = j;
								int humanTop2 = Duell.getHumanTop(i, j);
								int right = Duell.getHumanRight(i, j);

								//Check the pathway for a tile the human die could block at
								for (auto const &movement : computerMovement) {
									for (auto const &movement2 : movement.second) {
										int pathRow = movement.first;
										int pathCol = movement2.first;

										frontal = Duell.calculateFront(humanRow2, pathRow);
										lateral = Duell.calculateLateral(humanCol2, pathCol);

										//Check if the human die can block moving frontally first
										if (frontal + lateral == humanTop2) {
											collision = checkCollision(Duell, humanRow2, humanCol2, pathRow, pathCol, "frontal", lateral, frontal);
											lastSpace = checkLastPathSpace(Duell, pathRow, pathCol);

											if (collision == false && lastSpace != 2) {
												cout << "H" << humanTop2 << right << " can be rolled frontally first from square (" << humanRow2 << ", " << humanCol2 << ") horizontally by " << frontal
													<< " and laterally by " << lateral << ". It will up on (" << pathRow << ", " << pathCol << ")." << endl;
												return true;
											}

											//Check if the human die can block moving laterally if moving frontally fails
											collision = checkCollision(Duell, humanRow2, humanCol2, pathRow, pathCol, "lateral", lateral, frontal);
											lastSpace = checkLastPathSpace(Duell, pathRow, pathCol);

											if (collision == false && lastSpace != 2) {
												cout << "H" << humanTop2 << right << " can be rolled laterally first from square (" << humanRow2 << ", " << humanCol2 << ") Laterally by " << lateral <<
													" and horizontally by " << frontal << ". It will end up on (" << pathRow << ", " << pathCol << ")." << endl;
												return true;
											}

										}

									}
								}
							}
						}
					}
				}
			}
		}
	}

	//Not possible to block using any of the human die 
	return false;
}

/* *********************************************************************
Function Name: defendHumanDice

Purpose: To determine if it is possible to defend a human dice.

Parameters:Duell, a board object passed by reference, which stores the die
roster, an array of player object pointers, passed by value, used to access the 2 players of the game
compPlayer, a computer object, passed by value, used to access the computer functions
humanPlayer, a human object,  passed by value, used to access human functions

Return Value: A boolean value, true if it is possible to defend a die, false if it is not possible to defend a die.

Local Variables: currentHumanDice, a map, which maps coordinates to the top of the die
currentComputerDice, a map, which maps coordinates to the top of the die
computerMovement, a map, which holds coordinates of where the human die will move to capture the computer tile
humanRow, an integer, the row the human die is located at
humanCol, an integer, the column the human die is located at
humanTop, an integer, the top number of a die
computerRow, an integer, the row the computer die is located at
computerCol, an integer, the column the computer die is located at
computerTop, an integer, the top number of a die
pathRow, an integer, the row of a tile the die will be moving to
pathCol, an integer, the column of a tile the die will be moving to
specialRow, an integer, the row where the special tile is, 8
specialCol, an integer, the column where the special tile is, 5
totalMoves, an integer, the total number of spaces moved
frontal, an integer, the total number of spaces moved frontally
lateral, an integer, the total number of spaces moved laterally
collision, a boolean, which holds true if there was a collision or false if there was none
lastSpace, an integer, which holds what value was at the last space


Algorithm:
1) Go through and see if it’s possible for a copmuter die to attack a human die.
2) Calculate the frontal and lateral movement and checking if it’s equal to the top of the die.
3) If it’s equal call the checkCollision and checkLastPathSpace function to test if the path works, checking moving frontally first then laterally.
4) If a die that can capture a human die is found, go through and track the path the die will take in computerMovement.
5) Go through the human map and see if there is a die that can block the pathway of the attacking die
6) If a die can block, return true and print out it’s movement
7) If no die can block, return false.

Assistance Received: none
********************************************************************* */
bool human::defendHumanDice(board &Duell, player * roster[], computer compPlayer, human humanPlayer) {
	//Store the current human dice
	map< int, map<int, int> > currentHumanDice;
	//Store the current comptuer dice
	map< int, map<int, int> > currentComputerDice;

	//Get the path the computer die will move to try to get to a human die
	map< int, map<int, int> > computerMovement;

	//The current human row, column, and top number
	int humanRow;
	int humanCol;
	int humanTop;

	//The current computer row, column, and top number
	int computerRow;
	int computerCol;
	int computerTop;

	//frontal and lateral movement
	int frontal;
	int lateral;

	//Collision and lastSpace verify that a path is valid 
	bool collision;
	int lastSpace;

	//Get all the human dice
	for (int i = 8; i > 0; i--) {
		for (int j = 1; j < 10; j++) {
			//found a human die
			if (Duell.getNumAtSpace(i, j) == 2) {
				//Store the huamn die top number at the coords it was found
				currentHumanDice[i][j] = Duell.getHumanTop(i, j);
			}
		}
	}

	//Get the computer dice
	for (int i = 8; i > 0; i--) {
		for (int j = 1; j < 10; j++) {
			//found a computer die
			if (Duell.getNumAtSpace(i, j) == 1) {
				//Store the computer die top number at the coords it was found
				currentComputerDice[i][j] = Duell.getComputerTop(i, j);
			}
		}
	}

	//Go through all the current computer die and see if any of them can get to a human die
	for (auto const &compRow : currentComputerDice) {
		for (auto const &compCol : compRow.second) {
			//Get the current computer row, column, and top
			computerRow = compRow.first;
			computerCol = compCol.first;
			computerTop = compCol.second;

			for (auto const &row : currentHumanDice) {
				for (auto const &col : row.second) {
					//Get the current human row, column, and top
					humanRow = row.first;
					humanCol = col.first;
					humanTop = col.second;

					frontal = Duell.calculateFront(computerRow, humanRow);
					lateral = Duell.calculateLateral(computerCol, humanCol);

					//The computer die can move the correct number of spaces to get to a die
					if (frontal + lateral == computerTop) {
						int finalRow;

						//Check if the path is valid moving frontally first
						collision = compPlayer.checkCollision(Duell, computerRow, computerCol, humanRow, humanCol, "frontal", lateral, frontal);
						lastSpace = compPlayer.checkLastPathSpace(Duell, humanRow, humanCol);

						if (collision == false && lastSpace != 1) {

							//Get the front or backwards movement first
							if (computerRow <= humanRow) {
								finalRow = computerRow + frontal;

								//computer moving backwards +
								for (int i = computerRow; i <= finalRow; i++) {
									computerMovement[i][computerCol] = 999;
								}

							}

							else if (computerRow >= humanRow) {
								//computer moving forwards -
								finalRow = computerRow - frontal;

								for (int i = computerRow; i >= finalRow; i--) {
									computerMovement[i][computerCol] = 999;
								}
							}

							//Get the left or right movement
							if (computerCol <= humanCol) {
								//computer moving left + 
								for (int i = computerCol; i <= computerCol + lateral; i++) {
									computerMovement[finalRow][i] = 999;
								}

							}

							else if (computerCol >= humanCol) {
								//computer moving right -
								for (int i = computerCol; i >= computerCol - lateral; i--) {
									computerMovement[finalRow][i] = 999;
								}

							}

							//Go through all the human die and see if any of them can block the computer die's pathway
							for (int i = 8; i > 0; i--) {
								for (int j = 1; j < 10; j++) {
									//Found a human die
									if (Duell.getNumAtSpace(i, j) == 2) {
										//Get the row, column, top, and right of the human die currently testing
										int humanRow2 = i;
										int humanCol2 = j;
										int humanTop2 = Duell.getHumanTop(i, j);
										int right = Duell.getHumanRight(i, j);

										//See if the human die can block at any of the computer path spaces
										for (auto const &movement : computerMovement) {
											for (auto const &movement2 : movement.second) {
												int pathRow = movement.first;
												int pathCol = movement2.first;

												frontal = Duell.calculateFront(humanRow2, pathRow);
												lateral = Duell.calculateLateral(humanCol2, pathCol);

												//Check if the human die can move the correct number of spaces
												if (frontal + lateral == humanTop2) {

													//Check if the path works moving frontally first
													collision = checkCollision(Duell, humanRow2, humanCol2, pathRow, pathCol, "frontal", lateral, frontal);
													lastSpace = checkLastPathSpace(Duell, pathRow, pathCol);

													if (collision == false && lastSpace != 2) {
														cout << "H" << humanTop2 << right << " can be rolled frontally first from square (" << humanRow2 << ", " << humanCol2 << ") horizontally by " << frontal
															<< " and laterally by " << lateral << ". It will up on (" << pathRow << ", " << pathCol << ")." << endl;
														return true;
													}

													//Check moving laterally if moving frontally fails
													collision = checkCollision(Duell, humanRow2, humanCol2, pathRow, pathCol, "lateral", lateral, frontal);
													lastSpace = checkLastPathSpace(Duell, pathRow, pathCol);

													if (collision == false && lastSpace != 2) {
														cout << "H" << humanTop2 << right << " can be rolled laterally first from square (" << humanRow2 << ", " << humanCol2 << ") Laterally by " << lateral <<
															" and horizontally by " << frontal << ". It will end up on (" << pathRow << ", " << pathCol << ")." << endl;
														return true;
													}

												}
											}
										}
									}
								}
							}
						}

						//****************************************
						//Check if a computer die can reach a human die moving laterally first if moving frontally failed
						frontal = Duell.calculateFront(computerRow, humanRow);
						lateral = Duell.calculateLateral(computerCol, humanCol);

						collision = compPlayer.checkCollision(Duell, computerRow, computerCol, humanRow, humanCol, "lateral", lateral, frontal);
						lastSpace = compPlayer.checkLastPathSpace(Duell, humanRow, humanCol);

						//The path works moving laterally first
						if (collision == false && lastSpace != 1) {

							int finalCol;

							//Get the left or right movement
							if (computerCol <= humanCol) {
								finalCol = computerCol + lateral;

								//computer moving left + 
								for (int i = computerCol; i <= finalCol; i++) {
									computerMovement[computerRow][i] = 999;
								}

							}

							else if (computerCol >= humanCol) {
								finalCol = computerCol - lateral;

								//computer moving right -
								for (int i = computerCol; i >= finalCol; i--) {
									computerMovement[computerRow][i] = 999;
								}

							}

							//Get the front or backwards movement
							if (computerRow <= humanRow) {
								//computer moving backwards +
								for (int i = computerRow; i <= computerRow + frontal; i++) {
									computerMovement[i][finalCol] = 999;
								}

							}

							else if (computerRow >= humanRow) {
								//computer moving forwards -

								for (int i = computerRow; i >= computerRow - frontal; i--) {
									computerMovement[i][finalCol] = 999;
								}
							}

							//Go trhough all the current human dice and see if any of them can block the pathway
							for (int i = 8; i > 0; i--) {
								for (int j = 1; j < 10; j++) {
									//Found a human die
									if (Duell.getNumAtSpace(i, j) == 2) {
										//Get the human row, col, top, and right 
										int humanRow2 = i;
										int humanCol2 = j;
										int humanTop2 = Duell.getHumanTop(i, j);
										int right = Duell.getHumanRight(i, j);

										//Go through the computer path and see if the human die can block any of the tiles
										for (auto const &movement : computerMovement) {
											for (auto const &movement2 : movement.second) {
												int pathRow = movement.first;
												int pathCol = movement2.first;

												frontal = Duell.calculateFront(humanRow2, pathRow);
												lateral = Duell.calculateLateral(humanCol2, pathCol);

												//The die can move the correct number of spaces to get to the tile to block
												if (frontal + lateral == humanTop2) {
													//Check the path moving frontally first
													collision = checkCollision(Duell, humanRow2, humanCol2, pathRow, pathCol, "frontal", lateral, frontal);
													lastSpace = checkLastPathSpace(Duell, pathRow, pathCol);

													if (collision == false && lastSpace != 2) {
														cout << "H" << humanTop2 << right << " can be rolled frontally first from square (" << humanRow2 << ", " << humanCol2 << ") horizontally by " << frontal
															<< " and laterally by " << lateral << ". It will up on (" << pathRow << ", " << pathCol << ")." << endl;
														return true;
													}

													//If moving frontally fails check moving laterally first
													collision = checkCollision(Duell, humanRow2, humanCol2, pathRow, pathCol, "lateral", lateral, frontal);
													lastSpace = checkLastPathSpace(Duell, pathRow, pathCol);

													if (collision == false && lastSpace != 2) {
														cout << "H" << humanTop2 << right << " can be rolled laterally first from square (" << humanRow2 << ", " << humanCol2 << ") Laterally by " << lateral <<
															" and horizontally by " << frontal << ". It will end up on (" << pathRow << ", " << pathCol << ")." << endl;
														return true;
													}

												}

											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	//Could not use any of the human die to block a die from being captured by the comptuer player
	return false;
}

/* *********************************************************************
Function Name: killAComputerDice

Purpose: To determine if it is possible to attack a computer die.

Parameters:Duell, a board object passed by reference, which stores the die
roster, an array of player object pointers, passed by value, used to access the 2 players of the game
compPlayer, a computer object, passed by value, used to access the computer functions
humanPlayer, a human object,  passed by value, used to access human functions

Return Value: A boolean value, true if it is possible to attack, false if it is not possible to attack.

Local Variables: currentHumanDice, a map, which maps coordinates to the top of the die
currentComputerDice, a map, which maps coordinates to the top of the die
humanRow, an integer, the row the human die is located at
humanCol, an integer, the column the human die is located at
humanTop, an integer, the top number of a die
computerRow, an integer, the row the computer die is located at
computerCol, an integer, the column the computer die is located at
computerTop, an integer, the top number of a die
specialRow, an integer, the row where the special tile is, 8
specialCol, an integer, the column where the special tile is, 5
totalMoves, an integer, the total number of spaces moved
frontal, an integer, the total number of spaces moved frontally
lateral, an integer, the total number of spaces moved laterally
collision, a boolean, which holds true if there was a collision or false if there was none
lastSpace, an integer, which holds what value was at the last space

Algorithm:
1) Go through and see if it’s possible for a human die to attack any of the computer die.
2) Calculate the frontal and lateral movement and checking if it’s equal to the top of the die.
3) If it’s equal call the checkCollision and checkLastPathSpace function to test if the path works, checking moving frontally first then laterally.
4) If a die can attack a computer die make the move and move to the space of the computer die.
5) Return true if a computer die can be attacked.
6) Return false if a computer die can't be attacked.

Assistance Received: none
********************************************************************* */
bool human::killAComputerDice(board &Duell, player * roster[], computer compPlayer, human humanPlayer) {
	//Store the current human dice
	map< int, map<int, int> > currentHumanDice;
	//Store the current comptuer dice
	map< int, map<int, int> > currentComputerDice;

	//The current human row, column, and top number
	int humanRow;
	int humanCol;
	int humanTop;

	//The current computer row, column, and top number
	int computerRow;
	int computerCol;
	int computerTop;

	//frontal and lateral movement
	int frontal;
	int lateral;

	//Collision and lastSpace verify that a path is valid 
	bool collision;
	int lastSpace;

	//Get all the human dice
	for (int i = 8; i > 0; i--) {
		for (int j = 1; j < 10; j++) {
			//found a human die
			if (Duell.getNumAtSpace(i, j) == 2) {
				//Store the huamn die top number at the coords it was found
				currentHumanDice[i][j] = Duell.getHumanTop(i, j);
			}
		}
	}

	//Get the computer dice
	for (int i = 8; i > 0; i--) {
		for (int j = 1; j < 10; j++) {
			//found a computer die
			if (Duell.getNumAtSpace(i, j) == 1) {
				//Store the computer die top number at the coords it was found
				currentComputerDice[i][j] = Duell.getComputerTop(i, j);
			}
		}
	}

	//Go through all the current human die and see if any of them can get to an enemy die
	for (auto const &row : currentHumanDice) {
		for (auto const &col : row.second) {
			//Get the row, column, top, and right of the human die currently testing
			humanRow = row.first;
			humanCol = col.first;
			humanTop = col.second;
			int right = Duell.getHumanRight(humanRow, humanCol);

			//Go through all the computer die and test if a human die can get to it
			for (auto const &compRow : currentComputerDice) {
				for (auto const &compCol : compRow.second) {
					//Get the row, column, top, and right of the computer die being tested
					computerRow = compRow.first;
					computerCol = compCol.first;
					computerTop = compCol.second;

					frontal = Duell.calculateFront(humanRow, computerRow);
					lateral = Duell.calculateLateral(humanCol, computerCol);

					//The human die can move the correct number of spaces to get to the dice
					if (frontal + lateral == humanTop) {

						//Check path moving frontally first
						collision = humanPlayer.checkCollision(Duell, humanRow, humanCol, computerRow, computerCol, "frontal", lateral, frontal);
						lastSpace = humanPlayer.checkLastPathSpace(Duell, computerRow, computerCol);

						if (collision == false && lastSpace != 2) {

							cout << "H" << humanTop << right << " can be rolled frontally first from square (" << humanRow << ", " << humanCol << ") horizontally by " << frontal
								<< " and laterally by " << lateral << ". It will end up on (" << computerRow << ", " << computerCol << ")" << endl;

							return true;
						}

						//Check the path moving laterally first if moving frontally failed
						else {
							collision = humanPlayer.checkCollision(Duell, humanRow, humanCol, computerRow, computerCol, "lateral", lateral, frontal);
							lastSpace = humanPlayer.checkLastPathSpace(Duell, computerRow, computerCol);

							if (collision == false && lastSpace != 2) {

								cout << "H" << humanTop << right << " can be rolled laterally first from square (" << humanRow << ", " << humanCol << ") "
									<< "laterally by " << lateral << " and horizontally by " << frontal << ". It will up on (" << computerRow << ", " << computerCol << ")" << endl;

								return true;
							}
						}
					}
				}
			}
		}
	}

	//Couldn't move any of the human die to capture a computer die
	return false;
}

/* *********************************************************************
Function Name: moveToOpenSpace

Purpose: To determine if it is possible for a die to move to an open space.

Parameters:Duell, a board object passed by reference, which stores the die
Roster, an array of player object pointers, passed by value, used to access the 2 players of the game
compPlayer, a computer object, passed by value, used to access the computer functions
humanPlayer, a human object,  passed by value, used to access human functions

Return Value: A boolean value, true if it is possible to move a die. False if it is not possible to move a die.

Local Variables:
currentHumanDice, a map, which maps coordinates to the top of the die
computerRow, an integer, the row the computer die is located at
computerCol, an integer, the column the computer die is located at
computerTop, an integer, the top number of a die
specialRow, an integer, the row where the special tile is, 8
specialCol, an integer, the column where the special tile is, 5
totalMoves, an integer, the total number of spaces moved
frontal, an integer, the total number of spaces moved frontally
lateral, an integer, the total number of spaces moved laterally
collision, a boolean, which holds true if there was a collision or false if there was none
lastSpace, an integer, which holds what value was at the last space

Algorithm:
1) Go through the currentHumanDice map.
2) Calculate the frontal and lateral movement and checking if it’s equal to the top of the die.
3) If it’s equal call the checkCollision and checkLastPathSpace function to test if the path works, checking moving frontally first then laterally.
4) If a die can make a move, make the movement and return true.
5) If no die can make a move, return false.

Assistance Received: none
********************************************************************* */
bool human::moveToOpenSpace(board &Duell, player * roster[], computer compPlayer, human humanPlayer) {
	//Get all the current human dice
	map< int, map<int, int> > currentHumanDice;

	//The current die's row, column, and top number
	int humanRow;
	int humanCol;
	int humanTop;

	//The frontal and lateral movement
	int frontal;
	int lateral;

	//Collision and lastSpace verify that a path is valid 
	bool collision;
	int lastSpace;

	//Get all the human dice
	for (int i = 8; i > 0; i--) {
		for (int j = 1; j < 10; j++) {
			//found a human die
			if (Duell.getNumAtSpace(i, j) == 2) {
				//Store the huamn die top number at the coords it was found
				currentHumanDice[i][j] = Duell.getHumanTop(i, j);
			}
		}
	}

	//Go through all the human die and see if it's possible to move to any space
	for (auto const &row : currentHumanDice) {
		for (auto const &col : row.second) {
			humanRow = row.first;
			humanCol = col.first;
			humanTop = col.second;
			int right = Duell.getHumanRight(humanRow, humanCol);

			//Staring at the top left, (8, 1)
			for (int i = 8; i > 0; i--) {
				for (int j = 1; j < 10; j++) {

					frontal = Duell.calculateFront(humanRow, i);
					lateral = Duell.calculateLateral(humanCol, j);

					//It can move the correct number of spaces 
					if (frontal + lateral == humanTop) {
						//Check the path moving frontally first
						collision = checkCollision(Duell, humanRow, humanCol, i, j, "frontal", lateral, frontal);
						lastSpace = checkLastPathSpace(Duell, i, j);

						//Check the path and last space
						if (collision == false && lastSpace == 0) {

							cout << "H" << humanTop << right << " can be rolled frontally first from square (" << humanRow << ", " << humanCol << ") horizontally by " << frontal
								<< " and laterally by " << lateral << ". It will end up on (" << i << ", " << j << ")" << endl;

							return true;
						}

						//If the path does not work moving frontally first, check laterally
						else {
							collision = checkCollision(Duell, humanRow, humanCol, i, j, "lateral", lateral, frontal);
							lastSpace = checkLastPathSpace(Duell, i, j);

							//Check the path and last space
							if (collision == false && lastSpace == 0) {

								cout << "H" << humanTop << right << " can be rolled laterally first from square (" << humanRow << ", " << humanCol << ") "
									<< "laterally by " << lateral << " and horizontally by " << frontal << ". It will end up on (" << i << ", " << j << ")" << endl;

								return true;
							}
						}
					}
				}
			}
		}
	}
	//Couldn't find an open space to move to
	return false;
}


/* *********************************************************************
Function Name: checkCollision

Purpose: To determine if there is a collision on the pathway the die will take.

Parameters:Duell, a board object passed by value, which stores the die
row, an integer, the row the die is starting at
column, an integer, the column the die is starting at
newRow, an integer, the row where the die will end up
newColumn, an integer, the column where the die will end up
direction, a string, which determines which way the die will move first
lateral, an integer, the number of spaces being moved laterally
frontal, an integer, the number of spaces beng moved frontally

Return Value: A boolean value, true means there was a collision, false means there was no collision

Local Variables: movement, a string, which holds the movement direction of the die

Algorithm:
1) Get the movement of the die by calling the movementDirection function
2) If the diretion is frontal first check the pathway moving frontally first before moving laterally
3) If the direction is lateral first check the pathway moving laterally first before moving frontally
4) Depending on what movement represents, check the pathway.
5) If a collision is found the function returns true
6) If no collision is found the function returns false

Assistance Received: none
********************************************************************* */
bool human::checkCollision(board Duell, int row, int column, int newRow, int newColumn, string direction, int lateral, int frontal) {

	//Check which movement direction the die will be moving, frontal or lateral first 
	string movement = movementDirection(row, column, newRow, newColumn);

	//Moving forward first before going lateral
	if (direction == "frontal") {
		//Only forward
		if (movement == "F") {
			//Checking up from the original point
			for (int i = row + 1; i < newRow; i++) {
				if (Duell.getNumAtSpace(i, column) == 1 || Duell.getNumAtSpace(i, column) == 2) {
					return true;
				}
			}
		}

		//Only backwards
		else if (movement == "B") {
			//Backwards
			for (int i = row - 1; i > newRow; i--) {
				if (Duell.getNumAtSpace(i, column) == 1 || Duell.getNumAtSpace(i, column) == 2) {
					return true;
				}
			}
		}

		//Only left
		else if (movement == "L") {
			//Left
			for (int i = column - 1; i > newColumn; i--) {
				if (Duell.getNumAtSpace(newRow, i) == 1 || Duell.getNumAtSpace(newRow, i) == 2) {
					return true;
				}
			}
		}

		//Only right
		else if (movement == "R") {
			//Right
			for (int i = column + 1; i < newColumn; i++) {
				if (Duell.getNumAtSpace(newRow, i) == 1 || Duell.getNumAtSpace(newRow, i) == 2) {
					return true;
				}
			}
		}

		//Front and left
		else if (movement == "FL") {
			//Front
			for (int i = row + 1; i <= newRow; i++) {
				if (Duell.getNumAtSpace(i, column) == 1 || Duell.getNumAtSpace(i, column) == 2) {
					return true;
				}
			}

			//Left
			for (int i = column - 1; i > newColumn; i--) {
				if (Duell.getNumAtSpace(newRow, i) == 1 || Duell.getNumAtSpace(newRow, i) == 2) {
					return true;
				}
			}

		}

		//Front and right
		else if (movement == "FR") {
			//Front
			for (int i = row + 1; i <= newRow; i++) {
				if (Duell.getNumAtSpace(i, column) == 1 || Duell.getNumAtSpace(i, column) == 2) {
					return true;
				}
			}

			//Right
			for (int i = column + 1; i < newColumn; i++) {
				if (Duell.getNumAtSpace(newRow, i) == 1 || Duell.getNumAtSpace(newRow, i) == 2) {
					return true;
				}
			}
		}

		//Back and left
		else if (movement == "BL") {
			//Backwards
			for (int i = row - 1; i >= newRow; i--) {
				if (Duell.getNumAtSpace(i, column) == 1 || Duell.getNumAtSpace(i, column) == 2) {
					return true;
				}
			}

			//Left
			for (int i = column - 1; i > newColumn; i--) {
				if (Duell.getNumAtSpace(newRow, i) == 1 || Duell.getNumAtSpace(newRow, i) == 2) {
					return true;
				}
			}
		}

		//Back and right
		else if (movement == "BR") {
			//Backwards
			for (int i = row - 1; i >= newRow; i--) {
				if (Duell.getNumAtSpace(i, column) == 1 || Duell.getNumAtSpace(i, column) == 2) {
					return true;
				}
			}

			//Right
			for (int i = column + 1; i < newColumn; i++) {
				if (Duell.getNumAtSpace(newRow, i) == 1 || Duell.getNumAtSpace(newRow, i) == 2) {
					return true;
				}
			}
		}

		//Found a path that works don't have to check anymore
		//If we didn't find a path have to check other path can't return yet
		//return false if found no collisions
		return false;
	}

	//Check the lateral directions before the frontal
	else if (direction == "lateral") {

		//Only forward
		if (movement == "F") {
			//Checking up
			for (int i = row + 1; i < newRow; i++) {
				if (Duell.getNumAtSpace(i, column) == 1 || Duell.getNumAtSpace(i, column) == 2) {
					return true;
				}
			}

		}

		//Only backwards
		else if (movement == "B") {
			//Checking backwards
			for (int i = row - 1; i > newRow; i--) {
				if (Duell.getNumAtSpace(i, column) == 1 || Duell.getNumAtSpace(i, column) == 2) {
					return true;
				}
			}
		}

		//Only left
		else if (movement == "L") {
			//Left
			for (int i = column - 1; i > newColumn; i--) {
				if (Duell.getNumAtSpace(newRow, i) == 1 || Duell.getNumAtSpace(newRow, i) == 2) {
					return true;
				}
			}


		}

		//Only right
		else if (movement == "R") {
			//Right
			for (int i = column + 1; i < newColumn; i++) {
				if (Duell.getNumAtSpace(newRow, i) == 1 || Duell.getNumAtSpace(newRow, i) == 2) {
					return true;
				}
			}
		}

		//Front and left
		else if (movement == "FL") {
			//Left
			for (int i = column - 1; i >= newColumn; i--) {
				if (Duell.getNumAtSpace(row, i) == 1 || Duell.getNumAtSpace(row, i) == 2) {
					return true;
				}
			}

			//Front
			for (int i = row + 1; i < newRow; i++) {
				if (Duell.getNumAtSpace(i, newColumn) == 1 || Duell.getNumAtSpace(i, newColumn) == 2) {
					return true;
				}
			}


		}

		//Front and right
		else if (movement == "FR") {
			//Right
			for (int i = column + 1; i <= newColumn; i++) {
				if (Duell.getNumAtSpace(row, i) == 1 || Duell.getNumAtSpace(row, i) == 2) {
					return true;
				}
			}
			//Front
			for (int i = row + 1; i < newRow; i++) {
				if (Duell.getNumAtSpace(i, newColumn) == 1 || Duell.getNumAtSpace(i, newColumn) == 2) {
					return true;
				}
			}


		}

		//Back and left
		else if (movement == "BL") {
			//Left
			for (int i = column - 1; i >= newColumn; i--) {
				if (Duell.getNumAtSpace(row, i) == 1 || Duell.getNumAtSpace(row, i) == 2) {
					return true;
				}
			}
			//Backwards
			for (int i = row - 1; i > newRow; i--) {
				if (Duell.getNumAtSpace(i, newColumn) == 1 || Duell.getNumAtSpace(i, newColumn) == 2) {
					return true;
				}
			}
		}

		//Back and right
		else if (movement == "BR") {
			//Right
			for (int i = column + 1; i <= newColumn; i++) {
				if (Duell.getNumAtSpace(row, i) == 1 || Duell.getNumAtSpace(row, i) == 2) {
					return true;
				}
			}

			//Backwards
			for (int i = row - 1; i > newRow; i--) {
				if (Duell.getNumAtSpace(i, newColumn) == 1 || Duell.getNumAtSpace(i, newColumn) == 2) {
					return true;
				}
			}

		}
		//Return false found no collision
		return false;
	}

}

/* *********************************************************************
Function Name: movementDirection

Purpose: To figure out which way the die will be movnig to get to it's destination.

Parameters: row, an integer, the row the die is starting at
column, an integer, the column the die is starting at
newRow, an integer, the row where the die will end up
newColumn, an integer, the column where the die will end up

Return Value: A string, which stands for the movement direction.

Local Variables: None.

Algorithm:
1) Go through and check if the die is moving forwards or backwards, depending
on if the newRow is smaller or greater than the row.
2) Go through and check if the die is moving left or right, depending on if the newColumn
is smaller or greater than the column
3) If the newRow and row are equal or the newColumn and column are equal the die is
only being moved in one direction.
4) Return when a direction has been found.

Assistance Received: none
********************************************************************* */
string human::movementDirection(int row, int column, int newRow, int newColumn) {

	//Only forward
	if (newRow > row && column == newColumn) {
		return "F";
	}

	//Only backwards
	else if (newRow < row && column == newColumn) {
		return "B";
	}

	//Only left
	else if (newColumn < column && row == newRow) {
		return "L";
	}

	//Only right
	else if (newColumn > column && row == newRow) {
		return "R";
	}

	//Front and left
	else if (newRow > row && newColumn < column) {
		return "FL";
	}

	//Front and right
	else if (newRow > row && newColumn > column) {
		return "FR";
	}

	//Back and left
	else if (newRow < row && newColumn < column) {
		return "BL";
	}

	//Back and right
	else if (newRow < row && newColumn > column) {
		return "BR";
	}

	else {
		return "INVALID";
	}
}



/* *********************************************************************
Function Name: isValidMovement

Purpose: To determine if the number of movement spaces is equal to the
number on the top of the die

Parameters:Duell, a board object passed by value, which stores the die
row, an integer, the row the die is starting at
column, an integer, the column the die is starting at
lateral, an integer, the number of spaces being moved laterally
frontal, an integer, the number of spaces beng moved frontally

Return Value: A boolean value, true means that the top of the die is equal to the total movement spaces,
false means that they were not equal

Assistance Received: none
********************************************************************* */
bool human::isValidMovement(board Duell, int row, int column, int frontal, int lateral) {
	//Total moves is the total of the frontal and lateral movement, which should match the top of the die trying to move
	int totalMoves = frontal + lateral;
	int diceTop = Duell.getHumanTop(row, column);

	if (totalMoves == diceTop) {
		return true;
	}
	else {
		return false;
	}
}

/* *********************************************************************
Function Name: checkLastPathSpace

Purpose: To check what is located at the last space being moved to, a space, human, computer,
special die, or special space.

Parameters:Duell, a board object passed by value, which stores the die
newRow, an integer, the row the die will end up at
newColumn, an integer, the column the die will end up at

Return Value: An integer, representing which type the last space is.
0, a space
1, a computer die
2, a human die
3, the special die
4, the special space

Local Variables: None.

Algorithm:
1) Check if the last space has an enemy die
2) If it has an enemy die, check if it's the special die, on the special space, or a normal die
3) Check if it's your die, which will be a collision
4) Check if it's the special space, the game will be over
5) Check if it's an empty space

Assistance Received: none
********************************************************************* */
int human::checkLastPathSpace(board Duell, int newRow, int newColumn) {

	//Enemy piece on the last tile
	if (Duell.getNumAtSpace(newRow, newColumn) == 1) {
		if (Duell.getComputerTop(newRow, newColumn) == 1 && Duell.getComputerTop(newRow, newColumn) == 1) {
			//Captured the special die, game is over
			return 3;
		}

		else if (newRow == 8 && newColumn == 5) {
			//This is the special space with an enemy die on it
			return 4;
		}

		else {
			//Killed a normal dice
			return 1;
		}

	}

	else if (Duell.getNumAtSpace(newRow, newColumn) == 2) {
		//Collision, would land on own human die
		return 2;
	}

	else if (newRow == 8 && newColumn == 5) {
		//This is the special space, no enemy die on it
		return 5;
	}

	else if (Duell.getNumAtSpace(newRow, newColumn) == 0) {
		//Landed on an empty space
		return 0;
	}

}