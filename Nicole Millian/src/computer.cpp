/*
************************************************************
* Name: Nicole Millian                                     *
* Project : Duell - Project 1 C++				           *
* Class : CMPS 366 Organization of Programming Languages   *
* Date : October 21, 2016		                           *
************************************************************
*/
#pragma once
#include "computer.h"


computer::computer() {


}


computer::~computer() {

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
string computer::decideMove(board &Duell, player * roster[], computer compPlayer, human humanPlayer) {
	//See which function returns true, they are checked in the order of importance
	//If a function returns true, then return the string describing what move took place
	if (compPlayer.moveToSpecialEnemyDice(Duell, roster, compPlayer) == true) {
		return "specialdie";
	}

	else if (compPlayer.moveToSpecialEnemyTile(Duell, roster, compPlayer) == true) {
		return "specialtile";
	}

	else if (compPlayer.defendSpecialDice(Duell, roster, compPlayer, humanPlayer) == true) {
		return "defendspecialdie";
	}

	else if (compPlayer.defendComputerDice(Duell, roster, compPlayer, humanPlayer) == true) {
		return "defendregular";
	}

	else if (compPlayer.killAHumanDice(Duell, roster, compPlayer, humanPlayer) == true) {
		return "killdice";
	}

	else if (compPlayer.moveToOpenSpace(Duell, roster, compPlayer, humanPlayer) == true) {
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
compPlayer, a computer object,  passed by value, which is used to access the computer functions

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
bool computer::moveToSpecialEnemyDice(board &Duell, player * roster[], computer compPlayer) {
	//Top dice, right
	int top;
	int right;

	//Fronal and lateral space movement
	int frontal;
	int lateral;

	//Checking if the pathway is valid and what is at the last tile 
	bool collision;
	int lastSpace;

	//Find out where the human special dice is
	int specialRow = Duell.getSpecialHumanDiceRow();
	int specialColumn = Duell.getSpecialHumanDiceColumn();

	//Start at the top left
	//Checking to see if a die can kill the special die of the human
	for (int i = 8; i > 0; i--) {

		for (int j = 1; j < 10; j++) {
			//Found a computer dice
			if (Duell.getNumAtSpace(i, j) == 1) {
				//Get the top and the right
				top = Duell.getComputerTop(i, j);
				right = Duell.getComputerRight(i, j);

				//Calculate the movement distance
				frontal = Duell.calculateFront(i, specialRow);
				lateral = Duell.calculateLateral(j, specialColumn);

				//Can move the correct number of spaces to get to the dice
				if (frontal + lateral == top) {
					//Check the front path then to the side
					collision = checkCollision(Duell, i, j, specialRow, specialColumn, "frontal", lateral, frontal);
					lastSpace = checkLastPathSpace(Duell, specialRow, specialColumn);

					//Rhe path works moving frontally first
					if (collision == false && lastSpace != 1) {
						Duell.moveDiceComputer(compPlayer, i, j, specialRow, specialColumn, "frontal");
						cout << "C" << top << right << " was rolled frontally first from square (" << i << ", " << j << ") horizontally by " << frontal
							<< " and laterally by " << lateral << ". It ended up on (" << specialRow << ", " << specialColumn << ")" <<
							" the die is now C" << Duell.getComputerTop(specialRow, specialColumn) << Duell.getComputerRight(specialRow, specialColumn) << endl;

						//Found a valid move so return
						return true;
					}

					//Check the path moving laterally first
					else {
						collision = checkCollision(Duell, i, j, specialRow, specialColumn, "lateral", lateral, frontal);
						lastSpace = checkLastPathSpace(Duell, specialRow, specialColumn);

						if (collision == false && lastSpace != 1) {
							Duell.moveDiceComputer(compPlayer, i, j, specialRow, specialColumn, "lateral");
							cout << "C" << top << right << " was rolled laterally first from square (" << i << ", " << j << ") "
								<< "laterally by " << lateral << " and horizontally by " << frontal << ". It ended up on (" << specialRow << ", " << specialColumn << ")" <<
								" the die is now C" << Duell.getComputerTop(specialRow, specialColumn) << Duell.getComputerRight(specialRow, specialColumn) << endl;

							//Found a valid move so return
							return true;
						}
					}
				}
			}
		}
	}

	//Couldn't kill the special die so return false
	return false;
}

/* *********************************************************************
Function Name: movetoSpecialEnemyTile

Purpose: To determine if it is possible to capture the special tile with the 1x1 die

Parameters:Duell, a board object passed by reference, which stores the die
Roster, an array of player object pointers, passed by value, used to access the 2 players of the game
compPlayer, a computer object,  passed by value, which is used to access the computer functions

Return Value: A boolean value, true if it is possible to move to the enemy tile, false if it is not possible to move to the tile.

Local Variables:  top, an integer, the top number of a die
right, an integer, the right number of a die
specialDieRow, an integer, the row the 1x1 die is located at
specialDieCol, an integer, the column the 1x1 die is located at
frontal, an integer, the total number of spaces moved frontally
lateral, an integer, the total number of spaces moved laterally
winningTileRow, the winning tile row for the human, row 1
winningTileColumn, the winning tile column for the human, column 5
collision, a boolean, which holds true if there was a collision or false if there was none
lastSpace, an integer, which holds what value was at the last space

Algorithm:
1) Go through and see if it’s possible for the 1x1 die to move to the special tile by calculating the frontal and lateral movement and checking if it’s equal to the top of the die.
2) If it’s equal call the checkCollision and checkLastPathSpace function to test if the path works, checking moving frontally first then laterally.
3) If the 1x1 can capture the tile print out what movement the die will make and make the move and return true.
4) If the die can't capture the special tile, return false.

Assistance Received: none
********************************************************************* */
bool computer::moveToSpecialEnemyTile(board &Duell, player * roster[], computer compPlayer) {

	//Top and right of the special die which are constant
	const int top = 1;
	const int right = 1;

	//The location of the special computer die
	int specialDieRow = Duell.getSpecialComputerDiceRow();
	int specialDieCol = Duell.getSpecialComputerDiceColumn();

	//Special tiles are always the same, for the human it's 1,5
	const int winningTileRow = 1;
	const int winningTileColumn = 5;

	//Fronal and lateral space movement
	int frontal;
	int lateral;

	//Whether the path is valid and the final tile is able to be landed on
	bool collision;
	int lastSpace;

	//The tile is static
	int specialRow = 1;
	int specialColumn = 5;

	//The frontal movement from the current die row to the destination row
	frontal = Duell.calculateFront(specialDieRow, specialRow);
	//The lateral movement from the current die column to the destination column
	lateral = Duell.calculateLateral(specialDieCol, specialColumn);

	//You can move the correct number of spaces to get to the tile
	if (frontal + lateral == top) {
		//Check the path moving frontally then laterally, looking for a collision and what's on the last space
		collision = checkCollision(Duell, specialDieRow, specialDieCol, winningTileRow, winningTileColumn, "frontal", lateral, frontal);
		lastSpace = checkLastPathSpace(Duell, winningTileRow, winningTileColumn);

		//Check if the path worked moving frontally first
		if (collision == false && lastSpace != 1) {
			Duell.moveDiceComputer(compPlayer, specialDieRow, specialDieCol, winningTileRow, winningTileColumn, "frontal");
			cout << "C" << top << right << " was rolled frontally first from square (" << specialDieRow << ", " << specialDieCol << ") horizontally by " << frontal
				<< " and laterally by " << lateral << ". It ended up on (" << winningTileRow << ", " << winningTileColumn << ")" <<
				" the die is now C" << Duell.getComputerTop(winningTileRow, winningTileColumn) << Duell.getComputerRight(winningTileRow, winningTileColumn) << endl;

			//Made a move so return from the function
			return true;
		}

		//Chec moving laterally first 
		else {
			collision = checkCollision(Duell, specialDieRow, specialDieCol, winningTileRow, winningTileColumn, "lateral", lateral, frontal);
			lastSpace = checkLastPathSpace(Duell, winningTileRow, winningTileColumn);

			if (collision == false && lastSpace != 1) {
				Duell.moveDiceComputer(compPlayer, specialDieRow, specialDieCol, winningTileRow, winningTileColumn, "lateral");
				cout << "C" << top << right << " was rolled laterally first from square (" << specialDieRow << ", " << specialDieCol << ") "
					<< "laterally by " << lateral << " and horizontally by " << frontal << ". It ended up on (" << winningTileRow << ", " << winningTileColumn << ")" <<
					" the die is now C" << Duell.getComputerTop(winningTileRow, winningTileColumn) << Duell.getComputerRight(winningTileRow, winningTileColumn) << endl;

				//Made a move so return from the function
				return true;
			}
		}
	}

	//can't move to the tile
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
humanMovement, a map, which holds coordinates of where the human die will move to capture the computer tile
humanRow, an integer, the row the human die is located at
humanCol, an integer, the column the human die is located at
humanTop, an integer, the top number of a die
comRow2, an integer, the row the computer die is located at
compCol2, an integer, the column the computer die is located at
compTop2, an integer, the top number of a die
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
1) Go through and see if it’s possible for a human die to attack the special computer die.
2) Calculate the frontal and lateral movement and checking if it’s equal to the top of the die.
3) If it’s equal call the checkCollision and checkLastPathSpace function to test if the path works, checking moving frontally first then laterally.
4) If a die that can capture the special die is found, go through and track the path the die will take in humanMovement
5) Go through the computer map and see if there is a die that can block the pathway of the attacking die
6) If a die can block, return true and print out it’s movement
7) If no die can block, return false.

Assistance Received: none
********************************************************************* */
bool computer::defendSpecialDice(board &Duell, player * roster[], computer compPlayer, human humanPlayer) {
	//Defend the computer 1x1 die

	//Store the current human dice and the top number
	map< int, map<int, int> > currentHumanDice;
	//Store the current comptuer dice and the top number
	map< int, map<int, int> > currentComputerDice;

	//Store the coordinates the human will be moving to get to the die
	map< int, map<int, int> > humanMovement;

	//The human row, column, and top, used to check if it can kill the computer special die
	int humanRow;
	int humanCol;
	int humanTop;

	//Get the comp special dice row and col
	int specialRow = Duell.getSpecialComputerDiceRow();
	int specialCol = Duell.getSpecialComputerDiceColumn();

	//Stores the total frontal and lateral movement
	int frontal;
	int lateral;

	//Check if there was a collision or the last space is not valid
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
				//Store the huamn die top number at the coords it was found
				currentComputerDice[i][j] = Duell.getComputerTop(i, j);
			}
		}
	}

	//Go through the human die and see if any of them are capable of successfuly moving to the 1x1 computer die
	for (auto const &row : currentHumanDice) {
		for (auto const &col : row.second) {
			humanRow = row.first;
			humanCol = col.first;
			humanTop = col.second;

			frontal = Duell.calculateFront(humanRow, specialRow);
			lateral = Duell.calculateLateral(humanCol, specialCol);

			//The human die can move the correct number of spaces to get to the 1x1 die
			if (frontal + lateral == humanTop) {
				int finalRow;

				//Check the front path then to the side
				collision = humanPlayer.checkCollision(Duell, humanRow, humanCol, specialRow, specialCol, "frontal", lateral, frontal);
				lastSpace = humanPlayer.checkLastPathSpace(Duell, specialRow, specialCol);

				//***************************************
				//the path works moving frontally first...
				if (collision == false && lastSpace != 2) {

					//Get all of the spaces it will be moving to

					//the front and backwards movement

					//Forwards to kill it
					if (humanRow <= specialRow) {
						finalRow = humanRow + frontal;

						for (int i = humanRow; i <= finalRow; i++) {
							humanMovement[i][humanCol] = 999;
						}

					}

					//Backwards
					else if (humanRow >= specialRow) {
						// moving backwards
						finalRow = humanRow - frontal;

						for (int i = humanRow; i >= finalRow; i--) {
							humanMovement[i][humanCol] = 999;
						}
					}

					//the left or right movement
					if (humanCol <= specialCol) {
						//moving right
						for (int i = humanCol; i <= humanCol + lateral; i++) {
							humanMovement[finalRow][i] = 999;
						}

					}

					else if (humanCol >= specialCol) {
						//moving left
						for (int i = humanCol; i >= humanCol - lateral; i--) {
							humanMovement[finalRow][i] = 999;
						}

					}


					//Go through and see if there is a computer die that can block, starting at 8,1 
					for (int i = 8; i > 0; i--) {
						for (int j = 1; j < 10; j++) {
							//Found a computer die, i is row, j is column, get the right and top of the die using i and j
							if (Duell.getNumAtSpace(i, j) == 1) {
								int compRow2 = i;
								int compCol2 = j;
								int compTop2 = Duell.getComputerTop(i, j);
								int right = Duell.getComputerRight(i, j);

								//Go through and see if it can block on one of the path spaces
								for (auto const &movement : humanMovement) {

									for (auto const &movement2 : movement.second) {
										int pathRow = movement.first;
										int pathCol = movement2.first;

										frontal = Duell.calculateFront(compRow2, pathRow);
										lateral = Duell.calculateLateral(compCol2, pathCol);

										//Checking path frontally first
										if (frontal + lateral == compTop2) {
											collision = compPlayer.checkCollision(Duell, compRow2, compCol2, pathRow, pathCol, "frontal", lateral, frontal);
											lastSpace = compPlayer.checkLastPathSpace(Duell, pathRow, pathCol);

											if (collision == false && lastSpace != 1) {
												Duell.moveDiceComputer(compPlayer, compRow2, compCol2, pathRow, pathCol, "frontal");

												cout << "C" << compTop2 << right << " was rolled frontally first from square (" << compRow2 << ", " << compCol2 << ") horizontally by " << frontal
													<< " and laterally by " << lateral << ". It ended up on (" << pathRow << ", " << pathCol << ")" <<
													" the die is now C" << Duell.getComputerTop(pathRow, pathCol) << Duell.getComputerRight(pathRow, pathCol) << endl;

												if (lastSpace == 2) {
													roster[1]->updateDeadDice();
													Duell.setGamesPiece(pathRow, pathCol, 1);
												}
												return true;
											}

											collision = compPlayer.checkCollision(Duell, compRow2, compCol2, pathRow, pathCol, "lateral", lateral, frontal);
											lastSpace = compPlayer.checkLastPathSpace(Duell, pathRow, pathCol);

											//Checking the path moving laterally first
											if (collision == false && lastSpace != 1) {
												Duell.moveDiceComputer(compPlayer, compRow2, compCol2, pathRow, pathCol, "lateral");

												cout << "C" << compTop2 << right << " was rolled laterally first from square (" << compRow2 << ", " << compCol2 << ") Laterally by " << lateral <<
													" and horizontally by " << frontal << ". It ended up on (" << pathRow << ", " << pathCol << ")" <<
													" the die is now C" << Duell.getComputerTop(pathRow, pathCol) << Duell.getComputerRight(pathRow, pathCol) << endl;

												if (lastSpace == 2) {
													roster[1]->updateDeadDice();
													Duell.setGamesPiece(pathRow, pathCol, 1);
												}
												return true;
											}
										}
									}
								}
							}
						}
					}
					//****************************************

					collision = humanPlayer.checkCollision(Duell, humanRow, humanCol, specialRow, specialCol, "lateral", lateral, frontal);
					lastSpace = humanPlayer.checkLastPathSpace(Duell, specialRow, specialCol);

					frontal = Duell.calculateFront(humanRow, specialRow);
					lateral = Duell.calculateLateral(humanCol, specialCol);

					//Check if a human die can reach by moving laterally first
					if (collision == false && lastSpace != 2) {

						int finalCol;

						//The left or right movement first
						if (humanCol <= specialCol) {
							finalCol = humanCol + lateral;
							//moving right
							for (int i = humanCol; i <= finalCol; i++) {
								humanMovement[humanRow][i] = 999;
							}

						}

						else if (humanCol >= specialCol) {
							finalCol = humanCol - lateral;
							//moving left
							for (int i = humanCol; i >= finalCol; i--) {
								humanMovement[humanRow][i] = 999;
							}

						}

						//The front and backwards movement
						if (humanRow <= specialRow) {

							for (int i = humanRow; i <= humanRow + frontal; i++) {
								humanMovement[i][finalCol] = 999;
							}

						}

						else if (humanRow >= specialRow) {
							// moving backwards
							for (int i = humanRow; i >= humanRow - frontal; i--) {
								humanMovement[i][finalCol] = 999;
							}
						}


						//Go through and see if a computer die can block a space in the path
						for (int i = 8; i > 0; i--) {
							for (int j = 1; j < 10; j++) {

								//i is the row, j is the column, use i and j to get the computer top and right number
								if (Duell.getNumAtSpace(i, j) == 1) {
									int compRow2 = i;
									int compCol2 = j;
									int computerTop2 = Duell.getComputerTop(i, j); //the top die
									int right = Duell.getComputerRight(i, j);

									//Go through the path and see if it's possible to block
									for (auto const &movement : humanMovement) {

										for (auto const &movement2 : movement.second) {
											int pathRow = movement.first;
											int pathCol = movement2.first;

											frontal = Duell.calculateFront(compRow2, pathRow);
											lateral = Duell.calculateLateral(compCol2, pathCol);

											//Possible to make the movement
											if (frontal + lateral == computerTop2) {
												//Check the path moving frontally first
												collision = compPlayer.checkCollision(Duell, compRow2, compCol2, pathRow, pathCol, "frontal", lateral, frontal);
												lastSpace = compPlayer.checkLastPathSpace(Duell, pathRow, pathCol);

												if (collision == false && lastSpace != 1) {
													Duell.moveDiceComputer(compPlayer, compRow2, compCol2, pathRow, pathCol, "frontal");

													cout << "C" << computerTop2 << right << " was rolled frontally first from square (" << compRow2 << ", " << compCol2 << ") horizontally by " << frontal
														<< " and laterally by " << lateral << ". It ended up on (" << pathRow << ", " << pathCol << ")" <<
														" the die is now C" << Duell.getComputerTop(pathRow, pathCol) << Duell.getComputerRight(pathRow, pathCol) << endl;

													if (lastSpace == 2) {
														roster[1]->updateDeadDice();
														Duell.setGamesPiece(pathRow, pathCol, 1);
													}
													return true;
												}

												//Check the path moving laterally if frontally fails
												collision = compPlayer.checkCollision(Duell, compRow2, compCol2, pathRow, pathCol, "lateral", lateral, frontal);
												lastSpace = compPlayer.checkLastPathSpace(Duell, pathRow, pathCol);

												if (collision == false && lastSpace != 1) {
													Duell.moveDiceComputer(compPlayer, compRow2, compCol2, pathRow, pathCol, "lateral");

													cout << "C" << computerTop2 << right << " was rolled laterally first from square (" << compRow2 << ", " << compCol2 << ") Laterally by " << lateral <<
														" and horizontally by " << frontal << ". It ended up on (" << pathRow << ", " << pathCol << ")" <<
														" the die is now C" << Duell.getComputerTop(pathRow, pathCol) << Duell.getComputerRight(pathRow, pathCol) << endl;

													if (lastSpace == 2) {
														roster[1]->updateDeadDice();
														Duell.setGamesPiece(pathRow, pathCol, 1);
													}
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
	//Couldn't find a piece that could block
	return false;
}

/* *********************************************************************
Function Name: defendComputerDice

Purpose: To determine if it is possible to defend a computer dice.

Parameters:Duell, a board object passed by reference, which stores the die
roster, an array of player object pointers, passed by value, used to access the 2 players of the game
compPlayer, a computer object, passed by value, used to access the computer functions
humanPlayer, a human object,  passed by value, used to access human functions

Return Value: A boolean value, true if it is possible to defend a die, false if it is not possible to defend a die.

Local Variables: currentHumanDice, a map, which maps coordinates to the top of the die
currentComputerDice, a map, which maps coordinates to the top of the die
humanMovement, a map, which holds coordinates of where the human die will move to capture the computer tile
humanRow, an integer, the row the human die is located at
humanCol, an integer, the column the human die is located at
humanTop, an integer, the top number of a die
computerRow, an integer, the row the computer die is located at
computerCol, an integer, the column the computer die is located at
computerTop, an integer, the top number of a die
comRow2, an integer, the row the computer die is located at
compCol2, an integer, the column the computer die is located at
compTop2, an integer, the top number of a die
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
1) Go through and see if it’s possible for a human die to attack a computer die.
2) Calculate the frontal and lateral movement and checking if it’s equal to the top of the die.
3) If it’s equal call the checkCollision and checkLastPathSpace function to test if the path works, checking moving frontally first then laterally.
4) If a die that can capture a computer die is found, go through and track the path the die will take in humanMovement
5) Go through the computer map and see if there is a die that can block the pathway of the attacking die
6) If a die can block, return true and print out it’s movement
7) If no die can block, return false.

Assistance Received: none
********************************************************************* */
bool computer::defendComputerDice(board &Duell, player * roster[], computer compPlayer, human humanPlayer) {
	//Store the current human dice
	map< int, map<int, int> > currentHumanDice;
	//Store the current comptuer dice
	map< int, map<int, int> > currentComputerDice;

	//Storing the pathway the human die will take to the computer die
	map< int, map<int, int> > humanMovement;

	//The row, col, and top of the human die trying to get to the computer die
	int humanRow;
	int humanCol;
	int humanTop;

	//The row, col, and top of the comp die that will potentailyl block
	int computerRow;
	int computerCol;
	int computerTop;

	//frontal and lateral movement
	int frontal;
	int lateral;

	//Collision and lastspace determine if a path is valid
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
				//Store the huamn die top number at the coords it was found
				currentComputerDice[i][j] = Duell.getComputerTop(i, j);
			}
		}
	}

	//Go through the human die and see if they can kill any of the computer die
	for (auto const &row : currentHumanDice) {
		for (auto const &col : row.second) {
			humanRow = row.first;//first key
			humanCol = col.first;//second key
			humanTop = col.second; //the top die

								   //Going through each computer die
			for (auto const &compRow : currentComputerDice) {
				for (auto const &compCol : compRow.second) {
					computerRow = compRow.first;
					computerCol = compCol.first;
					computerTop = compCol.second;

					frontal = Duell.calculateFront(humanRow, computerRow);
					lateral = Duell.calculateLateral(humanCol, computerCol);

					//The human die can move the correct number of spaces to get to a computer die
					if (frontal + lateral == humanTop) {
						int finalRow;

						collision = humanPlayer.checkCollision(Duell, humanRow, humanCol, computerRow, computerCol, "frontal", lateral, frontal);
						lastSpace = humanPlayer.checkLastPathSpace(Duell, computerRow, computerCol);

						//***************************************
						//the path works moving frontally first...
						if (collision == false && lastSpace != 2) {

							//The front or backwards movement
							if (humanRow <= computerRow) {
								finalRow = humanRow + frontal;

								//moving forwards to kill it
								for (int i = humanRow; i <= finalRow; i++) {
									humanMovement[i][humanCol] = 999;
								}

							}

							else if (humanRow >= computerRow) {
								// moving backwards
								finalRow = humanRow - frontal;

								for (int i = humanRow; i >= finalRow; i--) {
									humanMovement[i][humanCol] = 999;
								}
							}

							//The left or right movement
							if (humanCol <= computerCol) {
								//moving right
								for (int i = humanCol; i <= humanCol + lateral; i++) {
									humanMovement[finalRow][i] = 999;
								}

							}

							else if (humanCol >= computerCol) {
								//moving left
								for (int i = humanCol; i >= humanCol - lateral; i--) {
									humanMovement[finalRow][i] = 999;
								}

							}


							//Go through and see if a computer die can block it from being captured
							for (int i = 8; i > 0; i--) {
								for (int j = 1; j < 10; j++) {
									//Found a comp die
									if (Duell.getNumAtSpace(i, j) == 1) {
										int compRow2 = i;
										int compCol2 = j;
										int compTop2 = Duell.getComputerTop(i, j);
										int right = Duell.getComputerRight(i, j);

										//Go through and see if a computer die can move to one of the path spaces
										for (auto const &movement : humanMovement) {
											for (auto const &movement2 : movement.second) {
												int pathRow = movement.first;
												int pathCol = movement2.first;

												frontal = Duell.calculateFront(compRow2, pathRow);
												lateral = Duell.calculateLateral(compCol2, pathCol);

												//Check frontally first
												if (frontal + lateral == compTop2) {
													collision = compPlayer.checkCollision(Duell, compRow2, compCol2, pathRow, pathCol, "frontal", lateral, frontal);
													lastSpace = compPlayer.checkLastPathSpace(Duell, pathRow, pathCol);

													if (collision == false && lastSpace != 1) {
														Duell.moveDiceComputer(compPlayer, compRow2, compCol2, pathRow, pathCol, "frontal");

														cout << "C" << compTop2 << right << " was rolled frontally first from square (" << compRow2 << ", " << compCol2 << ") horizontally by " << frontal
															<< " and laterally by " << lateral << ". It ended up on (" << pathRow << ", " << pathCol << ")" <<
															" the die is now C" << Duell.getComputerTop(pathRow, pathCol) << Duell.getComputerRight(pathRow, pathCol) << endl;

														if (lastSpace == 2) {
															roster[1]->updateDeadDice();
															Duell.setGamesPiece(pathRow, pathCol, 1);
														}
														return true;
													}

													//Check laterally if frontal fails
													collision = compPlayer.checkCollision(Duell, compRow2, compCol2, pathRow, pathCol, "lateral", lateral, frontal);
													lastSpace = compPlayer.checkLastPathSpace(Duell, pathRow, pathCol);


													if (collision == false && lastSpace != 1) {
														Duell.moveDiceComputer(compPlayer, compRow2, compCol2, pathRow, pathCol, "lateral");

														cout << "C" << compTop2 << right << " was rolled laterally first from square (" << compRow2 << ", " << compCol2 << ") Laterally by " << lateral <<
															" and horizontally by " << frontal << ". It ended up on (" << pathRow << ", " << pathCol << ")" <<
															" the die is now C" << Duell.getComputerTop(pathRow, pathCol) << Duell.getComputerRight(pathRow, pathCol) << endl;

														if (lastSpace == 2) {
															roster[1]->updateDeadDice();
															Duell.setGamesPiece(pathRow, pathCol, 1);
														}
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

						//Check if the human die can reach the computer die moving frontally first
						collision = humanPlayer.checkCollision(Duell, humanRow, humanCol, computerRow, computerCol, "lateral", lateral, frontal);
						lastSpace = humanPlayer.checkLastPathSpace(Duell, computerRow, computerCol);

						frontal = Duell.calculateFront(humanRow, computerRow);
						lateral = Duell.calculateLateral(humanCol, computerCol);
						//The path works moving laterally first....
						if (collision == false && lastSpace != 2) {
							int finalCol;

							//the left or right movement
							if (humanCol <= computerCol) {
								finalCol = humanCol + lateral;
								//moving right
								for (int i = humanCol; i <= finalCol; i++) {
									humanMovement[humanRow][i] = 999;
								}

							}

							else if (humanCol >= computerCol) {
								finalCol = humanCol - lateral;
								//moving left
								for (int i = humanCol; i >= finalCol; i--) {
									humanMovement[humanRow][i] = 999;
								}

							}

							//the frontal movement
							if (humanRow <= computerRow) {

								//moving forwards to kill it
								for (int i = humanRow; i <= humanRow + frontal; i++) {
									humanMovement[i][finalCol] = 999;
								}

							}

							else if (humanRow >= computerRow) {
								// moving backwards
								for (int i = humanRow; i >= humanRow - frontal; i--) {
									humanMovement[i][finalCol] = 999;
								}
							}

							//Go through starting at 8,1 and see if a computer die can block
							for (int i = 8; i > 0; i--) {
								for (int j = 1; j < 10; j++) {
									//Found a computer die
									if (Duell.getNumAtSpace(i, j) == 1) {
										int compRow2 = i;
										int compCol2 = j;
										int computerTop2 = Duell.getComputerTop(i, j);
										int right = Duell.getComputerRight(i, j);

										//Go through the path and see if the computer die can block 
										for (auto const &movement : humanMovement) {
											for (auto const &movement2 : movement.second) {
												int pathRow = movement.first;
												int pathCol = movement2.first;

												frontal = Duell.calculateFront(compRow2, pathRow);
												lateral = Duell.calculateLateral(compCol2, pathCol);

												//Check if it can block moving frontally first
												if (frontal + lateral == computerTop2) {
													collision = compPlayer.checkCollision(Duell, compRow2, compCol2, pathRow, pathCol, "frontal", lateral, frontal);
													lastSpace = compPlayer.checkLastPathSpace(Duell, pathRow, pathCol);

													if (collision == false && lastSpace != 1) {
														Duell.moveDiceComputer(compPlayer, compRow2, compCol2, pathRow, pathCol, "frontal");

														cout << "C" << computerTop2 << right << " was rolled frontally first from square (" << compRow2 << ", " << compCol2 << ") horizontally by " << frontal
															<< " and laterally by " << lateral << ". It ended up on (" << pathRow << ", " << pathCol << ")" <<
															" the die is now C" << Duell.getComputerTop(pathRow, pathCol) << Duell.getComputerRight(pathRow, pathCol) << endl;

														if (lastSpace == 2) {
															roster[1]->updateDeadDice();
															Duell.setGamesPiece(pathRow, pathCol, 1);
														}
														return true;
													}

													//If moving frontally fails, check if moving laterally will work
													collision = compPlayer.checkCollision(Duell, compRow2, compCol2, pathRow, pathCol, "lateral", lateral, frontal);
													lastSpace = compPlayer.checkLastPathSpace(Duell, pathRow, pathCol);

													if (collision == false && lastSpace != 1) {
														Duell.moveDiceComputer(compPlayer, compRow2, compCol2, pathRow, pathCol, "lateral");

														cout << "C" << computerTop2 << right << " was rolled laterally first from square (" << compRow2 << ", " << compCol2 << ") Laterally by " << lateral <<
															" and horizontally by " << frontal << ". It ended up on (" << pathRow << ", " << pathCol << ")" <<
															" the die is now C" << Duell.getComputerTop(pathRow, pathCol) << Duell.getComputerRight(pathRow, pathCol) << endl;

														if (lastSpace == 2) {
															roster[1]->updateDeadDice();
															Duell.setGamesPiece(pathRow, pathCol, 1);
														}
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

	//Couldn't find any die to block, return false
	return false;
}

/* *********************************************************************
Function Name: killAHumanDice

Purpose: To determine if it is possible to attack a human die

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
1) Go through and see if it’s possible for a computer die to attack any of the human die.
2) Calculate the frontal and lateral movement and checking if it’s equal to the top of the die.
3) If it’s equal call the checkCollision and checkLastPathSpace function to test if the path works, checking moving frontally first then laterally.
4) If a die can attack a human die make the move and move to the space of the human die.
5) Return true if a human die can be attacked.
6) Return false if a human die can't be attacked.

Assistance Received: none
********************************************************************* */
bool computer::killAHumanDice(board &Duell, player * roster[], computer compPlayer, human humanPlayer) {
	//Store the current human dice
	map< int, map<int, int> > currentHumanDice;
	//Store the current comptuer dice
	map< int, map<int, int> > currentComputerDice;

	//The row, col, and top for each human die
	int humanRow;
	int humanCol;
	int humanTop;

	//The row, col, and top for each computer die
	int computerRow;
	int computerCol;
	int computerTop;

	//The frontal and lateral movement
	int frontal;
	int lateral;

	//Collision and lastspace used to check if a path movement is valid
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
			//found a human die
			if (Duell.getNumAtSpace(i, j) == 1) {
				//Store the huamn die top number at the coords it was found
				currentComputerDice[i][j] = Duell.getComputerTop(i, j);
			}
		}
	}

	//Go through all the computer die one by one and check if it's possible to reach any of the human die
	for (auto const &compRow : currentComputerDice) {
		for (auto const &compCol : compRow.second) {
			computerRow = compRow.first;
			computerCol = compCol.first;
			computerTop = compCol.second;
			int right = Duell.getComputerRight(computerRow, computerCol);

			//Go through the human die and see if it's possible to reach any using the current computer die
			for (auto const &row : currentHumanDice) {
				for (auto const &col : row.second) {
					humanRow = row.first;
					humanCol = col.first;
					humanTop = col.second;

					frontal = Duell.calculateFront(computerRow, humanRow);
					lateral = Duell.calculateLateral(computerCol, humanCol);

					//It can move the correct number of spaces to get to the dice
					if (frontal + lateral == computerTop) {
						//Check the front path first 
						collision = compPlayer.checkCollision(Duell, computerRow, computerCol, humanRow, humanCol, "frontal", lateral, frontal);
						lastSpace = compPlayer.checkLastPathSpace(Duell, humanRow, humanCol);

						//the path works moving frontally first make the move
						if (collision == false && lastSpace != 1) {
							Duell.moveDiceComputer(compPlayer, computerRow, computerCol, humanRow, humanCol, "frontal");

							cout << "C" << computerTop << right << " was rolled frontally first from square (" << computerRow << ", " << computerCol << ") horizontally by " << frontal
								<< " and laterally by " << lateral << ". It ended up on (" << humanRow << ", " << humanCol << ")" <<
								" the die is now C" << Duell.getComputerTop(humanRow, humanCol) << Duell.getComputerRight(humanRow, humanCol) << endl;

							roster[1]->updateDeadDice();
							Duell.killHumanDice(humanRow, humanCol);
							return true;
						}

						//Try the pathway moving laterally if frontally fails
						else {
							collision = compPlayer.checkCollision(Duell, computerRow, computerCol, humanRow, humanCol, "lateral", lateral, frontal);
							lastSpace = compPlayer.checkLastPathSpace(Duell, humanRow, humanCol);

							if (collision == false && lastSpace != 1) {
								Duell.moveDiceComputer(compPlayer, computerRow, computerCol, humanRow, humanCol, "lateral");

								cout << "C" << computerTop << right << " was rolled laterally first from square (" << computerRow << ", " << computerCol << ") "
									<< "laterally by " << lateral << " and horizontally by " << frontal << ". It ended up on (" << humanRow << ", " << humanCol << ")" <<
									" the die is now C" << Duell.getComputerTop(humanRow, humanCol) << Duell.getComputerRight(humanRow, humanCol) << endl;

								roster[1]->updateDeadDice();
								Duell.killHumanDice(humanRow, humanCol);
								return true;
							}
						}
					}
				}
			}
		}
	}

	//Couldn't move any of the computer die to kill a human die
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
currentComputerDice, a map, which maps coordinates to the top of the die
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
1) Go through the currentComputerDice map.
2) Calculate the frontal and lateral movement and checking if it’s equal to the top of the die.
3) If it’s equal call the checkCollision and checkLastPathSpace function to test if the path works, checking moving frontally first then laterally.
4) If a die can make a move, make the movement and return true.
5) If no die can make a move, return false.

Assistance Received: none
********************************************************************* */
bool computer::moveToOpenSpace(board &Duell, player * roster[], computer compPlayer, human humanPlayer) {

	//Store the current comptuer dice
	map< int, map<int, int> > currentComputerDice;

	//The row, col, and top of the current computer die
	int computerRow;
	int computerCol;
	int computerTop;

	//Frontal and lateral movement
	int frontal;
	int lateral;

	//Used to determine if a pathway is valid
	bool collision;
	int lastSpace;

	//Get all the computer dice
	for (int i = 8; i > 0; i--) {
		for (int j = 1; j < 10; j++) {
			if (Duell.getNumAtSpace(i, j) == 1) {
				//Store the computer die top number at the coords it was found
				currentComputerDice[i][j] = Duell.getComputerTop(i, j);
			}
		}
	}


	//Go through all the computer die and see if it's possible for it to move
	for (auto const &compRow : currentComputerDice) {

		for (auto const &compCol : compRow.second) {
			computerRow = compRow.first;//first key
			computerCol = compCol.first;//second key
			computerTop = compCol.second; //the top die
			int right = Duell.getComputerRight(computerRow, computerCol);

			//Go through the board and see if it's possible for a computer die to make a move to any space
			for (int i = 1; i < 9; i++) {
				for (int j = 1; j < 10; j++) {

					frontal = Duell.calculateFront(computerRow, i);
					lateral = Duell.calculateLateral(computerCol, j);

					//It can move the correct number of spaces to get to the dice
					if (frontal + lateral == computerTop) {
						//Check the path moving frontally first
						collision = compPlayer.checkCollision(Duell, computerRow, computerCol, i, j, "frontal", lateral, frontal);
						lastSpace = compPlayer.checkLastPathSpace(Duell, i, j);

						//If the path works moving frontally first
						if (collision == false && lastSpace == 0) {
							Duell.moveDiceComputer(compPlayer, computerRow, computerCol, i, j, "frontal");

							cout << "C" << computerTop << right << " was rolled frontally first from square (" << computerRow << ", " << computerCol << ") horizontally by " << frontal
								<< " and laterally by " << lateral << ". It ended up on (" << i << ", " << j << ")" <<
								" the die is now C" << Duell.getComputerTop(i, j) << Duell.getComputerRight(i, j) << endl;

							return true;
						}

						//If moving frontally first fails, check moving laterally first
						else {
							collision = compPlayer.checkCollision(Duell, computerRow, computerCol, i, j, "lateral", lateral, frontal);
							lastSpace = compPlayer.checkLastPathSpace(Duell, i, j);

							if (collision == false && lastSpace == 0) {
								Duell.moveDiceComputer(compPlayer, computerRow, computerCol, i, j, "lateral");

								cout << "C" << computerTop << right << " was rolled laterally first from square (" << computerRow << ", " << computerCol << ") "
									<< "laterally by " << lateral << " and horizontally by " << frontal << ". It ended up on (" << i << ", " << j << ")" <<
									" the die is now C" << Duell.getComputerTop(i, j) << Duell.getComputerRight(i, j) << endl;

								return true;
							}
						}
					}
				}
			}
		}
	}
	//Couldn't move to an open space
	return false;
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
string computer::movementDirection(int row, int column, int newRow, int newColumn) {
	//Only forward
	if (newRow < row && column == newColumn) {
		return "F";
	}

	//Only backwards
	else if (newRow > row && column == newColumn) {
		return "B";
	}

	//Only left
	else if (newColumn > column && row == newRow) {
		return "L";
	}

	//Only right
	else if (newColumn < column && row == newRow) {
		return "R";
	}

	//Front and left
	else if (newRow < row && newColumn > column) {
		return "FL";
	}

	//Front and right
	else if (newRow < row && newColumn < column) {
		return "FR";
	}

	//Back and left
	else if (newRow > row && newColumn > column) {
		return "BL";
	}

	//Back and right
	else if (newRow > row && newColumn < column) {
		return "BR";
	}

	//An invalid movement
	else {
		return "INVALID";
	}
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
bool computer::checkCollision(board Duell, int row, int column, int newRow, int newColumn, string direction, int lateral, int frontal) {
	//Does not check the last position, checked in another function

	//Get which way the die will be travelling
	string movement = movementDirection(row, column, newRow, newColumn);

	//Moving forward first
	if (direction == "frontal") {
		//Only forward
		if (movement == "F") {
			for (int i = row - 1; i > newRow; i--) {
				if (Duell.getNumAtSpace(i, column) || Duell.getNumAtSpace(i, column) == 2) {
					return true;
				}
			}
		}

		//Only backwards
		else if (movement == "B") {
			for (int i = row + 1; i < newRow; i++) {
				if (Duell.getNumAtSpace(i, column) == 1 || Duell.getNumAtSpace(i, column) == 2) {
					return true;
				}
			}
		}

		//Only left
		else if (movement == "L") {
			for (int i = column + 1; i < newColumn; i++) {
				if (Duell.getNumAtSpace(newRow, i) == 1 || Duell.getNumAtSpace(newRow, i) == 2) {
					return true;
				}
			}
		}

		//Only right
		else if (movement == "R") {
			for (int i = column - 1; i > newColumn; i--) {
				if (Duell.getNumAtSpace(newRow, i) == 1 || Duell.getNumAtSpace(newRow, i) == 2) {
					return true;
				}
			}
		}

		//Front and left
		else if (movement == "FL") {
			//Checking front first then left
			for (int i = row - 1; i >= newRow; i--) {
				if (Duell.getNumAtSpace(i, column) == 1 || Duell.getNumAtSpace(i, column) == 2) {
					return true;
				}
			}

			//Will already be at the new row when moving laterally
			for (int i = column; i < newColumn; i++) {
				if (Duell.getNumAtSpace(newRow, i) == 1 || Duell.getNumAtSpace(newRow, i) == 2) {
					return true;
				}
			}

		}

		//Front and right
		else if (movement == "FR") {
			//Checking front then right
			for (int i = row - 1; i >= newRow; i--) {
				if (Duell.getNumAtSpace(i, column) == 1 || Duell.getNumAtSpace(i, column) == 2) {
					return true;
				}
			}

			//Will already be at the new row when moving laterally
			for (int i = column; i > newColumn; i--) {
				if (Duell.getNumAtSpace(newRow, i) == 1 || Duell.getNumAtSpace(newRow, i) == 2) {
					return true;
				}
			}
		}

		//Back and left
		else if (movement == "BL") {
			//Checking backwards then left
			for (int i = row + 1; i <= newRow; i++) {
				if (Duell.getNumAtSpace(i, column) == 1 || Duell.getNumAtSpace(i, column) == 2) {
					return true;
				}
			}

			//Will already be at the new row when moving laterally
			for (int i = column; i < newColumn; i++) {
				if (Duell.getNumAtSpace(newRow, i) == 1 || Duell.getNumAtSpace(newRow, i) == 2) {
					return true;
				}
			}
		}

		//Back and right
		else if (movement == "BR") {
			//Checking backwards then right
			for (int i = row + 1; i <= newRow; i++) {
				if (Duell.getNumAtSpace(i, column) == 1 || Duell.getNumAtSpace(i, column) == 2) {
					return true;
				}
			}

			//Will already be at the new row when moving laterally
			for (int i = column; i > newColumn; i--) {
				if (Duell.getNumAtSpace(newRow, i) == 1 || Duell.getNumAtSpace(newRow, i) == 2) {
					return true;
				}
			}
		}

		//Found a path that works don't have to check anymore
		//If we didn't find a path have to check other path can't return yet
		//return false found no collisions
		return false;
	}

	//Check the lateral directions before the front and back
	else if (direction == "lateral") {

		//Only forward
		if (movement == "F") {
			for (int i = row - 1; i > newRow; i--) {
				if (Duell.getNumAtSpace(i, column) == 1 || Duell.getNumAtSpace(i, column) == 2) {
					return true;
				}
			}
		}

		//Only backwards
		else if (movement == "B") {
			for (int i = row + 1; i < newRow; i++) {
				if (Duell.getNumAtSpace(i, column) == 1 || Duell.getNumAtSpace(i, column) == 2) {
					return true;
				}
			}
		}

		//Only left
		else if (movement == "L") {
			for (int i = column + 1; i < newColumn; i++) {
				if (Duell.getNumAtSpace(newRow, i) == 1 || Duell.getNumAtSpace(newRow, i) == 2) {
					return true;
				}
			}
		}

		//Only right
		else if (movement == "R") {
			for (int i = column - 1; i > newColumn; i--) {
				if (Duell.getNumAtSpace(newRow, i) == 1 || Duell.getNumAtSpace(newRow, i) == 2) {
					return true;
				}
			}
		}

		//Front and left
		else if (movement == "FL") {
			//Checking left before moving frontally
			for (int i = column + 1; i <= newColumn; i++) {
				if (Duell.getNumAtSpace(row, i) == 1 || Duell.getNumAtSpace(row, i) == 2) {
					return true;
				}
			}

			//Already at the new column before moving frontally
			for (int i = row - 1; i > newRow; i--) {
				if (Duell.getNumAtSpace(i, newColumn) == 1 || Duell.getNumAtSpace(i, newColumn) == 2) {
					return true;
				}
			}

		}

		//Front and right
		else if (movement == "FR") {
			//Right before moving frontally 
			for (int i = column - 1; i >= newColumn; i--) {
				if (Duell.getNumAtSpace(row, i) == 1 || Duell.getNumAtSpace(row, i) == 2) {
					return true;
				}
			}

			//Already at the new column before moving frontally
			for (int i = row - 1; i > newRow; i--) {
				if (Duell.getNumAtSpace(i, newColumn) == 1 || Duell.getNumAtSpace(i, newColumn) == 2) {
					return true;
				}
			}

		}

		//Back and left
		else if (movement == "BL") {
			//Left before moving backwards
			for (int i = column + 1; i <= newColumn; i++) {
				if (Duell.getNumAtSpace(row, i) == 1 || Duell.getNumAtSpace(row, i) == 2) {
					return true;
				}
			}

			//Already at the new column before moving frontally
			for (int i = row + 1; i < newRow; i++) {
				if (Duell.getNumAtSpace(i, newColumn) == 1 || Duell.getNumAtSpace(i, newColumn) == 2) {
					return true;
				}
			}
		}

		//Back and right
		else if (movement == "BR") {
			//Right before moving backwards
			for (int i = column - 1; i >= newColumn; i--) {
				if (Duell.getNumAtSpace(row, i) == 1 || Duell.getNumAtSpace(row, i) == 2) {
					return true;
				}
			}

			//Already at the new column before moving frontally
			for (int i = row + 1; i < newRow; i++) {
				if (Duell.getNumAtSpace(i, newColumn) == 1 || Duell.getNumAtSpace(i, newColumn) == 2) {
					return true;
				}
			}

		}
		//Return false if no collision was found
		return false;
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
bool computer::isValidMovement(board Duell, int row, int column, int frontal, int lateral) {
	//Check if the total of frontal + lateral is equal to the top of the die being moved, a rule of the game
	int totalMoves = frontal + lateral;
	int diceTop = Duell.getComputerTop(row, column);

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
int computer::checkLastPathSpace(board Duell, int newRow, int newColumn) {
	//Checking the last path space on the path to the new row and column

	//The last space was an enemy die of some type
	if (Duell.getNumAtSpace(newRow, newColumn) == 2) {
		if (Duell.getHumanTop(newRow, newColumn) == 1 && Duell.getHumanRight(newRow, newColumn) == 1) {
			//Captured the special die, game is over
			return 3;
		}
		else if (newRow == 1 && newColumn == 5) {
			//This is the special space, with an enemy die on it
			return 4;
		}
		else {
			//Killed a normal dice
			return 2;
		}

	}

	//This would be invalid and a collision, because finding a 1 would mean finding a Fe, which is your own ide
	else if (Duell.getNumAtSpace(newRow, newColumn) == 1) {
		return 1;
	}

	//Landed on the special tile, nothing on the tile
	else if (newRow == 1 && newColumn == 5) {
		return 5;
	}

	//Landed on an empty space
	else if (Duell.getNumAtSpace(newRow, newColumn) == 0) {
		return 0;
	}

}

