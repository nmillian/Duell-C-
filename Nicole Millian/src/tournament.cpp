/*
************************************************************
* Name: Nicole Millian                                     *
* Project : Duell - Project 1 C++				           *
* Class : CMPS 366 Organization of Programming Languages   *
* Date : October 21, 2016		                           *
************************************************************
*/
#include "tournament.h"

tournament::tournament() {

	humanWins = 0;
	computerWins = 0;
}


tournament::~tournament() {

}

/* *********************************************************************
Function Name: updateSerialWinsComp

Purpose: Update the amount of computer wins with the number of wins located in a save file.

Parameters: cWins, an integer, the amount of computer wins from the saved file.

Return Value: None.

Assistance Received: none
********************************************************************* */
void tournament::updateSerialWinsComp(int cWins) {
	computerWins = cWins;

}

/* *********************************************************************
Function Name: updateSerialWinsHuman

Purpose: Update the number of human wins with the number of wins located in a saved file.

Parameters: hWins, an integer, the number of human wins from a saved file.

Return Value: None.

Assistance Received: none
********************************************************************* */
void tournament::updateSerialWinsHuman(int hWins) {
	humanWins = hWins;

}

/* *********************************************************************
Function Name: updateHumanWins

Purpose: Update the amount of human wins in a tournament by
Adding 1 to the humanWins private variable.

Parameters: None.

Return Value: None.

Assistance Received: none
********************************************************************* */
void tournament::updateHumanWins() {
	humanWins = humanWins + 1;
}

/* *********************************************************************
Function Name: updateComputerWins

Purpose: Update the amount of computer wins in a tournament by
Adding 1 to the computerWins private variable.

Parameters: None.

Return Value: None.

Assistance Received: none
********************************************************************* */
void tournament::updateComputerWins() {
	computerWins = computerWins + 1;
}


/* *********************************************************************
Function Name: getHumanWins

Purpose: Gets the number of human wins.

Parameters: None.

Return Value: humanWins, an integer, for the number of rounds a human player won

Assistance Received: none
********************************************************************* */
const int tournament::getHumanWins() {
	return humanWins;
}

/* *********************************************************************
Function Name: getComputerWins

Purpose: Gets the number of computer wins.

Parameters: None.

Return Value: computerWins, an integer, for the number of rounds a computer player won

Assistance Received: none
********************************************************************* */
const int tournament::getComputerWins() {
	return computerWins;
}

/* *********************************************************************
Function Name: determineWinner

Purpose: To determine whether the human or computer player won or if it’s a draw

Parameters: roster[], an array of pointers to player objects, passed by value

Return Value: None.

Local Variables: None.

Algorithm:
1)Check if humansWins > computerWins, if it is print out the human player’s name
2)Check if humanWins < computerWins, if it is print out the computer player’s name
3)If neither of the above cases worked, then print the result as a draw

Assistance Received: none
********************************************************************* */
void tournament::determineWinner(player * roster[]) {
	if (humanWins > computerWins) {
		cout << "Congratulations, " << roster[1]->getName() << " you have won the tournament." << endl;
	}

	else if (humanWins < computerWins) {
		cout << "The computer player, " << roster[0]->getName() << ", won the tournament." << endl;
	}

	else {
		cout << "The tournament ended in a draw. No winner." << endl;
	}
}

/* *********************************************************************
Function Name: resetTournament

Purpose: To reset the tournament variables, humanWins, computerWins, and roundsPlayed, to 0 so another round can be played.

Parameters: None.

Return Value: None.

Assistance Received: none
********************************************************************* */
void tournament::resetTournament() {
	humanWins = 0;
	computerWins = 0;
}