/*
************************************************************
* Name: Nicole Millian                                     *
* Project : Duell - Project 1 C++				           *
* Class : CMPS 366 Organization of Programming Languages   *
* Date : October 21, 2016		                           *
************************************************************
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <string>
#include <algorithm>
#include "board.h"
#include "boardView.h"
#include "player.h"
#include "computer.h"
#include "human.h"
#include "game.h"
#include "tournament.h"

using namespace std;

void getHumanInput(string line, int &val);
void printReasoning(string move);
bool askToPlayAgain(board &Duell, player * roster[], tournament duellTournament);

/* *********************************************************************
Function Name: main

Purpose: To call functions necessary in order to play the game and control the flow of the
game between the human and the computer player.

Parameters: None

Return Value: None

Local Variables: playerName, a string, the name of the human player
computerName, a string, the name of the computer player, which is Computer
roster, an array of pointers to player objects, used in order to access player functions for human and comptuer objects
humanPlayer, a human object, used to suggest movement to the human and check for valid movements
computerPlayer, a computer object, used for moving computer die and checking for valid movement
duellGame, a game object, used in order to serialize the game and decide which player is playing first
duellTournamnet, a tournament object, used in order to keep track of the number of round wins of the human and computer
Duell, a board object, used in order to keep track of the spaces and die on the board and their movement
duellBoard, a boardView object, used in order to display the game board to the console window
currentPlayer, an integer, the integer determines what player is playing 1 for human 0 for computer
gameChoice, a string, holds whether the human wants to start a new game or from a save
direction, a string, whether the human would like to move laterally or frontally first
line, a string, used as a buffer to check if human input was a number for row, column, newRow, and newColumn
row, an integer, the row of the die to move
column, an integer, the column of the die to move
newRow, an integer, the row to move a die to
newColumn, an integer, the column to move a die to
movementForward, an integer, how many tiles forward a die will be moving
movementLateral, an integer, how many tiles laterally a die will be moving
collision, a boolean, true means that there was a collision and false means there was no collision
validMoveSpaces, an boolean, whether or not the number of tiles moved is the same as the top die number true for they are the same, false when they are not the same
lastSpace, a boolean, what is contained at the last space of a path a die is taking
moveReason, a string, decides what the reason was behind the computer making a move or suggesting a human move
action, a string, whether or not the human wants to make a move or asked for help
serial, a string, whether or not the human wants to exercise the option to save
playAgain, a string, whether or not the human wans to continue playing or end the game

Algorithm:
1) Ask the human player what name they would like to be called
2) Ask the human if they would like to start a new game or resume an old game
3) If they answer resume from a saved game ask for the name of the file to read from
3) Display the game board and decide which player, the human or computer, gets to move first
4) Go back and forth between players moving die untill either player captures the special tile or die
5) After each move ask the human player if they would like to save and quit or continue playing
6) When the round is won by either player ask the human if they want to keep playing or end the game
7) If the human wants to keep playing reset the board and play again
8) If the humans wants to end the game, declare the winner of the tournament and exit the game

Assistance Received: none
********************************************************************* */
int main() {

	//The player name and the computer name
	string playerName;
	string computerName = "Computer";

	cout << "Welcome to Duell!" << endl;

	//Get what the playerName should be set to 
	cout << "Please enter your name: ";
	getline(cin, playerName);
	cout << endl;

	//Set up the player roster as an array of pointers to player object, size 2
	player * roster[2];

	//The human and computer player object declarations 
	human humanPlayer;
	computer compPlayer;

	//Making pointers to the human and computer objects
	player * pointHuman = &humanPlayer;
	player * pointComp = &compPlayer;

	//Assign the human and computer pointers to the player array
	roster[0] = pointComp;
	roster[1] = pointHuman;

	//set the computer
	roster[0]->setName(computerName);
	//set the player
	roster[1]->setName(playerName);

	//Create a game and tournament object to keep track of the game and round wins
	game duellGame;
	tournament duellTournament;

	//Create a board and boardView object to keep track of the die and print the board to screen
	board Duell;
	boardView duellBoard;

	//The player currently making a move, 0 is computer, 1 is human
	int currentPlayer;

	//Ask for a new or saved game from the human player
	string gameChoice;
	cout << "Would you like to start a game from a save or new (Enter save or new)? ";

	while (cin >> gameChoice) {
		//Make it not case sensitive
		transform(gameChoice.begin(), gameChoice.end(), gameChoice.begin(), toupper);

		//Start the game from a save file
		if (gameChoice == "SAVE") {
			string fileName;

			cout << "What is the file name? (Do not add .txt to file name) ";
			cin >> fileName;

			if (duellGame.gameSerializationIn(Duell, duellTournament, currentPlayer, roster, fileName) == true) {
				break;
			}
			else {
				cout << "Would you like to start a game from a save or new (Enter save or new)? ";
			}
		}

		//Start a new game and decide which player gets to go first
		else if (gameChoice == "NEW") {
			cout << "Deciding which player gets to go first.." << endl;
			currentPlayer = duellGame.decideFirstPlayer(roster);

			break;
		}

		//User did not enter save or new
		else {
			cout << "Would you like to start a game from a save or new (Enter save or new)? ";
		}
	}

	//Display the game board to the screen
	duellBoard.displayGameBoard(Duell);

	//The variable to hold whether the human wants to make a move frontally or laterally first
	string direction;

	//Line is used to buffer human input as a string, and to check if a human entered a number for rows and columns
	string line;

	//The row and column of the die to be moved
	int row;
	int column;

	//The row and column of the final destination
	int newRow;
	int newColumn;

	//The total amount of movement in the frontal and lateral directions
	int movementForward;
	int movementLateral;

	//Variables to check for collision, the number of moves, and if the last space is a valid tile
	bool collision;
	bool validMoveSpaces;
	int lastSpace;

	//Used to decide what reason should be printed 
	string moveReason;

	//What action the human player wants to take after making a move
	string action;
	bool serial;
	bool playAgain;

	//Begin playing the game
	while (true) {
		//Which player is currently playing
		// 0 = Computer player is playing
		// 1 = Human player is playing 

		//Print out how many alive die each player has
		cout << "Current alive dice: " << endl;
		cout << roster[0]->getName() << ": " << roster[0]->checkAliveDice() << endl;
		cout << roster[1]->getName() << ": " << roster[1]->checkAliveDice() << endl;

		//Human player is currently playing if currentPlayer == 1
		if (currentPlayer == 1) {
			cout << roster[1]->getName() << " is now playing." << endl;

			//Ask whether to suggest a move or just make a move
			cout << "Do you want help or make a move (Enter H or M): ";

			while (cin >> action) {
				//Make it non case sensitive 
				transform(action.begin(), action.end(), action.begin(), toupper);

				//Suggest a move for the human player and print out the reasoning behind it
				if (action == "H") {
					moveReason = roster[1]->decideMove(Duell, roster, compPlayer, humanPlayer);
					printReasoning(moveReason);
					break;
				}

				//Make a move so exit the loop
				else if (action == "M") {
					break;
				}

				//Didn't enter an H or an M repeat the question
				else {
					cout << "Do you want help or make a move (Enter H or M): ";
				}
			}

			//Making a move to a new tile
			cout << "Which dice would you like to move?" << endl;

			//Pick the row an column where the die being moved is located at and verify that the human entered numbers
			cout << "Row: ";
			getHumanInput(line, row);
			cout << endl;

			cout << "Column: ";
			getHumanInput(line, column);
			cout << endl;

			//Ask which direction to move first before asking for destination
			cout << "Which direction do you want to move first? Enter frontal or lateral: ";
			cin >> direction;
			cout << endl;

			//Player picked a human die to move
			if (Duell.isHumanDice(row, column) == true) {
				//Asking for the new row and column to move to
				cout << "Move to which row: ";
				getHumanInput(line, newRow);
				cout << endl;

				cout << "Move to which column: ";
				getHumanInput(line, newColumn);
				cout << endl;

				//Total movement in the forward and lateral directions
				movementForward = Duell.calculateFront(row, newRow);
				movementLateral = Duell.calculateLateral(column, newColumn);

				//Check if there is a collision on the path, doesn't check the last space
				collision = humanPlayer.checkCollision(Duell, row, column, newRow, newColumn, direction, movementLateral, movementForward);

				//Check if the frontal and lateral movement added together match the top of the die
				validMoveSpaces = humanPlayer.isValidMovement(Duell, row, column, movementForward, movementLateral);

				//There's no collision and the amount of movement sapces are valid 
				if (collision == false && validMoveSpaces == true) {
					//Check what is at the last space of the path
					lastSpace = humanPlayer.checkLastPathSpace(Duell, newRow, newColumn);

					//Free space, 0, at the end of the path, move normally
					if (lastSpace == 0) {
						Duell.moveDiceHuman(humanPlayer, row, column, newRow, newColumn, direction);

						//set the current player to the computer
						currentPlayer = 0;

					}

					//A regular computer die at the end of the path, kill it. 
					else if (lastSpace == 1) {
						//Captured an enemy die, move to the space
						cout << "You captured an enemy die." << endl;
						roster[0]->updateDeadDice();
						Duell.killComputerDice(newRow, newColumn);
						Duell.moveDiceHuman(humanPlayer, row, column, newRow, newColumn, direction);

						currentPlayer = 0;

					}

					//Captured the key piece, won the game
					else if (lastSpace == 3) {
						
						//Move to the 1x1 die space
						Duell.moveDiceHuman(humanPlayer, row, column, newRow, newColumn, direction);
						duellBoard.displayGameBoard(Duell);

						//Declare the winner and update the human wins
						cout << "You win the round! You captured the special die." << endl;
						duellTournament.updateHumanWins();

						//Ask if the human wants to playe another round
						playAgain = askToPlayAgain(Duell, roster, duellTournament);
						if (playAgain == true) {
							cout << "Deciding which player gets to go first.." << endl;
							currentPlayer = duellGame.decideFirstPlayer(roster);

						}
						else {
							system("pause");
							return 0;
						}
					}

					//The special tile with an enemy die on it, won the game if landed on key piece
					else if (lastSpace == 4) {

						//Special die on key tile
						if (Duell.getHumanTop(row, column) == 1 && Duell.getHumanRight(row, column) == 1) {
							//Move to the special tile 
							roster[0]->updateDeadDice();
							Duell.killComputerDice(newRow, newColumn);
							Duell.moveDiceHuman(humanPlayer, row, column, newRow, newColumn, direction);
							duellBoard.displayGameBoard(Duell);

							//Killed an enemy die
							cout << "You captured an enemy die." << endl;
							//Declare the winner and update the human wins
							cout << "You win! You captured the special tile." << endl;
							duellTournament.updateHumanWins();

							//Ask if the human player wants to play another round 
							playAgain = askToPlayAgain(Duell, roster, duellTournament);
							if (playAgain == true) {
								cout << "Deciding which player gets to go first.." << endl;
								currentPlayer = duellGame.decideFirstPlayer(roster);

							}
							else {
								system("pause");
								return 0;
							}
						}

						//Killed a regular die on the tile
						else {
							cout << "You captured an enemy die." << endl;
							roster[0]->updateDeadDice();
							Duell.killComputerDice(newRow, newColumn);
							Duell.moveDiceHuman(humanPlayer, row, column, newRow, newColumn, direction);

							currentPlayer = 0;
						}
					}

					//Empty special tile
					else if (lastSpace == 5) {
						//Move to the key piece to the special tile 
						if (Duell.getHumanTop(row, column) == 1 && Duell.getHumanRight(row, column) == 1) {
							
							Duell.moveDiceHuman(humanPlayer, row, column, newRow, newColumn, direction);
							duellBoard.displayGameBoard(Duell);

							//Declare the winner and update the human wins
							cout << "You win! You captured the special tile." << endl;
							duellTournament.updateHumanWins();

							//Ask if the human player wants to play another round 
							playAgain = askToPlayAgain(Duell, roster, duellTournament);
							if (playAgain == true) {
								cout << "Deciding which player gets to go first.." << endl;
								currentPlayer = duellGame.decideFirstPlayer(roster);

							}
							else {
								system("pause");
								return 0;
							}
						}

						//Did not move the key piece to the special tile 
						else {
							Duell.moveDiceHuman(humanPlayer, row, column, newRow, newColumn, direction);

							//set the current player to the computer
							currentPlayer = 0;
						}
					}

					//The human player tried to move to a die that was their own, which is an invalid move
					else if (lastSpace == 2) {
						cout << "The move ended on your own die, not vaild. Try again." << endl;
					}

				}

				//There was a collision or the frontal + lateral movement did not match the top die number
				else {
					cout << "The move was not a valid path. Try again." << endl;
				}
			}

			//Player chose a blank space to move, which is not a valid move
			else if (Duell.isSpace(row, column)) {
				cout << "You selected an invalid tile to move. Try again." << endl;
				//Allows the player to make a correct move
				currentPlayer = 1;
			}

			//Player chose an opponents die to move, which is not a valid move
			else if (Duell.isHumanDice(row, column) == false) {
				cout << "Invalid move, you selected an opponents dice. Try again." << endl;
				//Allows the player to make a correct move
				currentPlayer = 1;
			}

			//Display the game board and ask if the human player would like to save and quit after making a move
			duellBoard.displayGameBoard(Duell);
			serial = duellGame.askForSerialization(Duell, duellTournament, currentPlayer);
			if (serial == true) {
				return 0;
			}
		}

		//The computer player is making a move
		else if (currentPlayer == 0) {
			//Computer player is now playing 
			cout << roster[0]->getName() << " is now playing." << endl;

			//Decide which move to make & make the move
			//decideMove returns a string which defines why the move was made
			moveReason = roster[0]->decideMove(Duell, roster, compPlayer, humanPlayer);

			//Special circumstances for making a move

			//Winning the game by claiming the special die
			if (moveReason == "specialdie") {
				//Print the reasoning behind moving, which is that it was to win the game
				printReasoning(moveReason);
				duellBoard.displayGameBoard(Duell);

				cout << "The computer won the round! You lost." << endl;

				//Update the number of computer wins
				duellTournament.updateComputerWins();

				//Ask the human if they would like to play again or stop and determine the winner
				playAgain = askToPlayAgain(Duell, roster, duellTournament);
				if (playAgain == true) {
					cout << "Deciding which player gets to go first.." << endl;
					currentPlayer = duellGame.decideFirstPlayer(roster);

					duellBoard.displayGameBoard(Duell);
				}
				else {
					system("pause");
					return 0;
				}
			}

			//Winning the game by claiming the special enemy tile
			else if (moveReason == "specialtile") {
				//Print the reasoning behind moving, which is that it was to win the game
				printReasoning(moveReason);
				duellBoard.displayGameBoard(Duell);

				cout << "The computer won the round! You lost." << endl;

				//Update the number of computer wins
				duellTournament.updateComputerWins();

				//Ask the human if they would like to play again or stop and determine the winner
				playAgain = askToPlayAgain(Duell, roster, duellTournament);
				if (playAgain == true) {
					cout << "Deciding which player gets to go first.." << endl;
					currentPlayer = duellGame.decideFirstPlayer(roster);

					duellBoard.displayGameBoard(Duell);
				}
				else {
					system("pause");
					return 0;
				}
			}

			//Killed a regular die, defended a die, or moved to an open space
			else {
				//Print reasoning for the move
				printReasoning(moveReason);
				duellBoard.displayGameBoard(Duell);

				//Set it back to the human
				currentPlayer = 1;
			}

			//Ask if the human would like to save the game and quit
			serial = duellGame.askForSerialization(Duell, duellTournament, currentPlayer);
			if (serial == true) {
				return 0;
			}
		}

	}
}


/* *********************************************************************
Function Name: getHumanInput

Purpose: To verify that when asking a human for input, the human inputs the correct data type,
in this case a number.

Parameters: line, a string, what the human enetered on the console
val, an integer, passed by reference, if the string can be converted to an integer it
is stored in val

Return Value: None

Assistance Received: none
********************************************************************* */
void getHumanInput(string line, int &val) {

	while (cin >> line) {

		try {
			val = stoi(line);
			return;
		}

		catch (invalid_argument) {
			cout << "That was not a number, please enter a number: ";
		}

	}

}


/* *********************************************************************
Function Name: printReasoning

Purpose: To print the reasoning for the human and computer making a move

Parameters: move, a string, which determines which type of move was made

Return Value: None.

Assistance Received: None.
********************************************************************* */
void printReasoning(string move) {
	if (move == "specialdie") {
		cout << "Winning by claiming the opponent's special dice." << endl;
	}

	else if (move == "specialtile") {
		cout << "Winning the game by claiming the opponent's special tile." << endl;
	}

	else if (move == "defendspecialdie") {
		cout << "Defending special die from being captured." << endl;
	}

	else if (move == "defendregular") {
		cout << "Defending a die from being captured." << endl;
	}

	else if (move == "killdice") {
		cout << "Capturing an enemy die." << endl;
	}

	else if (move == "openspace") {
		cout << "Possible move to an open space. " << endl;
	}

	else {
		cout << "No suitable move." << endl;
	}
}


/* *********************************************************************
Function Name: askToPlayAgain

Purpose: To ask the player if they want to continue playing or stop playing.

Parameters: Duell, a board object, passed by reference, holds the die of the board
roster, an array of player object pointers, used to call functions in relation to the human and computer
duellTournament, a tournament object, used in order to keep track of wins for the computer and human

Return Value: A boolean, true if playing again, false if not playing again.

Assistance Received: none
********************************************************************* */
bool askToPlayAgain(board &Duell, player * roster[], tournament duellTournament) {
	string playAgain;

	cout << "Do you want to play again? (Enter Y or N): ";

	while (cin >> playAgain) {
		//Make it not case sensitive
		transform(playAgain.begin(), playAgain.end(), playAgain.begin(), toupper);

		//If playing again reset the game
		if (playAgain == "Y") {
			Duell.resetGame();
			roster[0]->resetGame();
			roster[1]->resetGame();

			return true;
		}

		//If not playing again, find the winner of the tournament and print it out
		else if (playAgain == "N") {
			cout << "Human wins: " << duellTournament.getHumanWins() << endl;
			cout << "Computer wins: " << duellTournament.getComputerWins() << endl;

			duellTournament.determineWinner(roster);

			return false;
		}

		//Didn't enter a Y or N
		else {
			cout << "Do you want to play again? ";
		}

	}
}
