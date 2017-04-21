/*
************************************************************
* Name: Nicole Millian                                     *
* Project : Duell - Project 1 C++				           *
* Class : CMPS 366 Organization of Programming Languages   *
* Date : October 21, 2016		                           *
************************************************************
*/
#include "board.h"
#include <iostream>

using namespace std;

class boardView {

public:
	boardView();
	boardView(board &Duell);

	~boardView();

	/********************************
	UTILITY
	********************************/
	//Prints out the Duell board starting at the top left (8,1) ending at (1, 9)
	void displayGameBoard(board Duell);

};

