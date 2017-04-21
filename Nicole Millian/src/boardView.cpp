
/*
************************************************************
* Name: Nicole Millian                                     *
* Project : Duell - Project 1 C++				           *
* Class : CMPS 366 Organization of Programming Languages   *
* Date : October 21, 2016		                           *
************************************************************
*/
#include "boardView.h"

boardView::boardView() {

}

boardView::boardView(board &Duell) {

}

boardView::~boardView() {

}

/* *********************************************************************
Function Name: displayGameBoard

Purpose: Display the game boad.

Parameters: Duell, a board object, passed by value which holds the die.

Return Value: None.

Local Variables: None

Algorithm:
1) Display the row of column numbers.
2) Go through the games map, starting at (8,1) using two nested for loops
3) At each new row print the row number
3) If the value at games equals 0 then print 0 becuase it’s a space
4) If the value at games equals 1 then print the top and right computer die numbers
5) If the value at games equals 2 then print the top and right human die numbers.

Assistance Received: none
********************************************************************* */
void boardView::displayGameBoard(board Duell) {
	//Display column numbers
	cout << setw(6) << " 1";

	for (int i = 2; i < 10; i++) {
		cout << setw(6) << i;
	}

	cout << endl;

	// Display row and board
	for (int i = 8; i > 0; i--) {
		cout << i;

		for (int j = 1; j < 10; j++) {
			if (Duell.getNumAtSpace(i, j) == 0) {
				cout << setw(5) << Duell.getNumAtSpace(i, j) << " ";
			}

			else if (Duell.getNumAtSpace(i, j) == 2) { //There is a human dice
				cout << setw(4) << "H" << Duell.getHumanTop(i, j) << Duell.getHumanRight(i, j);
			}

			else if (Duell.getNumAtSpace(i, j) == 1) {
				cout << setw(4) << "C" << Duell.getComputerTop(i, j) << Duell.getComputerRight(i, j);
			}
		}
		cout << endl;
	}

	cout << endl;
}


