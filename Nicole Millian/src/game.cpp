/*
************************************************************
* Name: Nicole Millian                                     *
* Project : Duell - Project 1 C++				           *
* Class : CMPS 366 Organization of Programming Languages   *
* Date : October 21, 2016		                           *
************************************************************
*/
#include "game.h"


game::game() {

}


game::~game() {

}

/* *********************************************************************
Function Name: decideFirstPlayer

Purpose: To figure out whether the computer or human player gets to move
first by generating 2 random numbers between 1-6 to simulate a die roll.

Parameters: roster, an array of player pointers passed by value, to access computer
and human traits.

Return Value: Returns an integer value to represent which player gets to move
first. 0 is for computer player, 1 is for human player.

Assistance Received: none
********************************************************************* */
int game::decideFirstPlayer(player * roster[]) {
	//The die rolls for the human and computer player
	int numberHuman;
	int numberComputer;

	//Set the rand function
	srand(time(NULL));

	//Generate numbers between 1 and 6, keep going untill it's not a draw
	do {
		numberHuman = (rand() % 6) + 1;
		numberComputer = (rand() % 6) + 1;
	} while (numberHuman == numberComputer);

	//Print what each player rolled
	cout << roster[1]->getName() << " rolled " << numberHuman << endl;
	cout << roster[0]->getName() << " rolled " << numberComputer << endl;

	//Decide who won and gets to move first, return 0 if computer won and 1 if human won
	if (numberHuman < numberComputer) {
		cout << roster[0]->getName() << " gets to move first!" << endl;
		return 0;
	}

	else {
		cout << roster[1]->getName() << " gets to move first!" << endl;
		return 1;
	}
}

/* *********************************************************************
Function Name: askForSerialization

Purpose: Asks the user if they want to save and quit or keep playing the
game.

Parameters: Duell, passed by value, the board object which holds all the pieces and tiles
duellTournament, passed by value, which holds the score of the tournament
currentPlayer, passed by value, an ineger which determines whether the computer or
human is playing

Return Value: returns a boolean value. true means the game was serialized.
false means that the game is not going to be serialized.

Local Variables: answer, a string to hold whether or not to save and quit
fileName, the name of the file the saved game should be written to

Algorithm:
1) Ask the player if they want to save and quit
2) If the answer is Y, call gameSerializationOut() in order to save the game and return true.
3) If the answer is N, return false.
4) If the user did not enter Y or N ask the question again untill an appropriate answer is given

Assistance Received: none
********************************************************************* */
bool game::askForSerialization(board Duell, tournament duellTournament, int currentPlayer) {
	//The variable that holds the humans response to if they want to save and quit
	string answer;

	//Holds what the player wants to name the save file
	string fileName;

	cout << "Do you want to save and quit? (Enter Y or N): ";

	//Read in the human player answer
	while (cin >> answer) {
		//Change the variable to not be case sensitive 
		transform(answer.begin(), answer.end(), answer.begin(), toupper);

		//Check what the human player answered
		//Answering Y results in asking for a filename and serializing the file
		if (answer == "Y") {
			cout << "What would you like to name the file? ";
			cin >> fileName;

			//Check if serialization works
			//Seriailization worked
			if (gameSerializationOut(Duell, duellTournament, currentPlayer, fileName) == true) {
				cout << "Serializing and closing game..." << endl;
				return true;
			}

			//Serialization failed
			else {
				cout << "Do you want to save and quit? (Enter Y or N): ";
			}

		}

		//Answer is N, function just returns false
		else if (answer == "N") {
			return false;
		}

		//Human entered something other than a Y or N, repeat the question
		else {
			cout << "Do you want to save and quit? (Enter Y or N): ";
		}
	}
}

/* *********************************************************************
Function Name: gameSerializationIn

Purpose: To read in the save file and correctly assign values to variables in
order to resume the game from a saved state.

Parameters: Duell, a board object passed by reference, which holds the die and spaces of the board
duellTournament, a tournamnet objct, which holds the amount of wins each player has
currentPlayer, an integer passed by reference, dictates which players turn it is, 0 for comp and 1 for human
roster, an array of player objects, used in order to get the human and computer player stats
name, a string, the name of a file to open in order to read from

Return Value: returns a boolean value, true if the file was able to be opened and read, and false
if it was unable to open the file

Local Variables: line, a string, to buffer each line from the file
aliveDieHuman, an integer, used to keep track of the alive human die
aliveDieComp, an integer, used to keep track of the alive comp die
duellFile, an ifstream object, used to open and read from a file
word, a string, used to parse each word in a line
row, an integer, defined as 9 because it's subtracted by 1 while lines are being read in
column, an integer, defined as 0 because it's added by 1 while lines are being read in
top, an integer, the top number of a die
right, an integer, the right number of a die

Algorithm:
1) Open the file and being reading line by line, starting at what would be the 8th row
2) Parse each word in the line to see if the word is Computer, Human, or Next, or if it begins with a C, H, or 0
3) If the word is Computer, Human, or Next parse the next two words on the line.
4) If the word is Computer or Human parse the word into an integer and assign the amount of wins to the player
5) If the word is Next determine whether the it is the human or computer player moving next and either assign a
0 or 1 to the currentPlayer variable pased by reference
6) If the word begins with a C or H parse the next two chars in the word
7) Parse the chars into integers and assign the first integer to the top of the die and the second to the right of the die
8) Set the games map space to either 1 or 2 accordingly whether it was a human or computer die
9) If the char is 0 then no additional parsing is needed and just get the space in the games map to 0

Assistance Received: none
********************************************************************* */
bool game::gameSerializationIn(board &Duell, tournament &duellTournament, int &currentPlayer, player * roster[], string name) {
	//Holds each line that is read in one by one
	string line;

	//Variables to keep track of alive dice
	int aliveDieHuman = 0;
	int aliveDieComp = 0;

	//Append .txt to a file name, do not expect human to enter it
	name.append(".txt");

	//Create a ifstream object to read from the file
	ifstream duellFile(name);

	//Keep track of the rows and columns, the first piece to be read in will be (8, 1)
	//When the file is being read in, row is subtracted by 1 and column is added by 1
	//To counteract, row is one larger and column is one smaller to begin with
	int row = 9;
	int column = 0;

	if (duellFile) {

		//Get each line
		while (getline(duellFile, line)) {
			//Read in each line and then split each line into words
			istringstream iss(line);
			string word;

			//Checking for the board at the top of the file, which should be ignored
			if (line != "Board:") {

				//The column has to be reset to 0 each time when reading in each separate piece
				column = 0;
				//The row is gradually subtracted by 1 
				row = row - 1;

				//Reading in each word from a line
				while (iss >> word) {
					//Add 1 to the column so it begins at 1 and increases each time a piece is read in 
					column = column + 1;

					//If the word is computer, found the number of computer wins
					if (word == "Computer") {
						//The next word is irrelevant, skip it and get the next word which is the number of computer wins
						iss >> word;
						iss >> word;

						//Reading the word into the variable val so it can be converted to an integer
						stringstream val;
						val << word;

						//Converting val to an integer so it can be stored in the integer variable wins
						int wins;
						val >> wins;

						//Updating the number of wins the computer player has
						duellTournament.updateSerialWinsComp(wins);
					}

					//If the word is human, found the number of human wins
					else if (word == "Human") {
						//The next word is irrelevant, skip it and get the next word which is the number of human wins
						iss >> word;
						iss >> word;

						//Reading the word into the variable val so it can be converted to an integer
						stringstream val;
						val << word;

						//Converting val to an integer so it can be stored in the integer variable wins
						int wins;
						val >> wins;

						//Updating the number of wins the human player has
						duellTournament.updateSerialWinsHuman(wins);
					}

					//Found which player should be the current player
					else if (word == "Next") {
						//Next word is irrelevant, skip and get the next word which is the current player
						iss >> word;
						iss >> word;

						//If the word is computer, set the currentPlayer variable to 0
						if (word == "Computer") {
							currentPlayer = 0;
						}
						//If the word is human, set the currentPlayer variable to 1
						else if (word == "Human") {
							currentPlayer = 1;
						}
					}

					//Did not find a full word, so it has to be a game piece
					else {
						//Found a computer piece
						if (word.at(0) == 'C') {
							//Read in the next two chars, which are the top and right of the die
							char value = word.at(1);
							char value2 = word.at(2);

							//Convert the two chars so they can be converted to integers
							stringstream strValue;
							strValue << value;

							stringstream strValue2;
							strValue2 << value2;

							//Convert the top and right of the die to integer values
							int top;
							int right;

							strValue >> top;
							strValue2 >> right;

							//Update the number of alive dice
							aliveDieComp += 1;

							//Mark that there is a computer die at the row and column
							Duell.setGamesPiece(row, column, 1);
							//Set the computer die at the row and column, with the top and right die
							Duell.setComputerDice(row, column, top, right);
						}

						//Found a human die
						else if (word.at(0) == 'H') {
							//Read in the next two chars, which are the top and right of the die
							char value = word.at(1);
							char value2 = word.at(2);

							//Convert the two chars so they can be converted to integers
							stringstream strValue;
							strValue << value;

							stringstream strValue2;
							strValue2 << value2;

							//Convert the top and right of the die to integer values
							int top;
							int right;

							strValue >> top;
							strValue2 >> right;

							//Add 1 to the amount of alive human die 
							aliveDieHuman += 1;

							//Mark that there is a human die at the row and column
							Duell.setGamesPiece(row, column, 2);
							//Set the human die with it's top and right value at the row and column
							Duell.setHumanDice(row, column, top, right);
						}

						//Found a blank space
						else if (word.at(0) == '0') {
							//Mark that there is an open space at this row and column
							Duell.setGamesPiece(row, column, 0);
						}
					}
				}
			}
		}

		//Set the amount of alive die
		roster[0]->setDie(aliveDieComp);
		roster[1]->setDie(aliveDieHuman);

		//Close the file and return successful
		duellFile.close();
		return true;
	}

	//If the filename was invalid return unsuccessful
	else {
		cout << "The filename was invalid." << endl;
		return false;
	}

}

/* *********************************************************************
Function Name: gameSerializationOut

Purpose: To write the state of the game to a save file in order to resume at a
later time.

Parameters: Duell, a board object passed by reference, which holds the die and spaces of the board
duellTournament, a tournamnet objct, which holds the amount of wins each player has
currentPlayer, an integer passed by reference, dictates which players turn it is, 0 for comp and 1 for human
name, a string, the name of a file to write to

Return Value: A boolean value, false means the file could not be written to & true means the file was succesfuly
created.

Local Variables: duellFile, an ofstream object, used to open a file and write to it

Algorithm:
1) Append the string, name, with .txt in order to create a file
2) Open the file and check if the file is worked or failed
3) If the file worked cycle through the board using a nested for loop,
beginning in the to left corner (8,1) and ending at (1, 9)
4) Check what the numbers at each space are, if the number is 0 it's a blank space,
1 means it's a computer number, 2 means it's a human
5) Get the top and right numbers and write them to the file accordingly if the number is 1 or 2
6) Get the computer wins and write them to the file
7) Get the human wins and write them to the file
8) Get the next player and write it to the file
9) Return true

Assistance Received: none
********************************************************************* */

bool game::gameSerializationOut(board Duell, tournament &duellTournament, int &currentPlayer, string name) {
	//Append .txt to the string the human player entered as a name
	name.append(".txt");

	//Create an ofstream to write to the file
	ofstream duellFile;

	//Open the file in order to write to it
	duellFile.open(name);

	//Check if the file was opened if it couldn't be opened return false
	if (duellFile.fail()) {
		cout << "The file could not be written to." << endl;
		return false;
	}

	//The file opened and could be written to
	else {
		duellFile << "Board:" << endl;

		//Go through the board, beginning at the top left corner (8, 1) and write the pieces to the file
		for (int i = 8; i > 0; i--) {
			for (int j = 1; j < 10; j++) {

				//Found a computer die
				if (Duell.getNumAtSpace(i, j) == 1) {
					duellFile << "C" << Duell.getComputerTop(i, j) << Duell.getComputerRight(i, j) << "  ";
				}

				//Found a human die
				else if (Duell.getNumAtSpace(i, j) == 2) {
					duellFile << "H" << Duell.getHumanTop(i, j) << Duell.getHumanRight(i, j) << "  ";
				}

				//Found an empty space
				else {
					duellFile << "  0  ";
				}
			}
			duellFile << endl;
		}

		//Write the wins for each player along with the next player to the file
		duellFile << "Computer wins: " << duellTournament.getComputerWins() << endl;
		duellFile << "Human wins: " << duellTournament.getHumanWins() << endl;
		duellFile << "Next player: ";

		//Current player marked as 0 is the computer, 1 is the human
		if (currentPlayer == 0) {
			duellFile << "Computer" << endl;
		}
		else {
			duellFile << "Human" << endl;
		}

		//Close the file and return true for succcess
		duellFile.close();
		return true;
	}
}

