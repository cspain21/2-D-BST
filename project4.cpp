//Project 4 Spring 2021 Data Structures Connor Spain

#include <iostream>
#include "BinarySearchTree.h"



int main() {

	//xTree
	BinarySearchTree<int>* xTree = new BinarySearchTree<int>();

	//Reads input from file
	while (!cin.eof()) {
		char c;
		cin.get(c);

		//Chooses function to perform on xTree object depending on the input command given
		switch (c) {

		//Insert
		case 'I':
			//Takes input of x, y, and id to be inserted
			int xVal;
			int yVal;
			int ID;
			cin >> xVal >> yVal >> ID;

			//Inserts the xVal first
			xTree->insert(xVal);

			//Uses modified _insert to insert a y value and id at the given x Coordinate
			xTree->_insert(xVal, yVal, ID);

			break;

		//Print
		case 'P':

			//Outputs the xTree object in inorder and in preorder
			cout << "Print" << endl;
			cout << *xTree << endl;
			break;

		//Range Search
		case 'S':
			cout << "Range search " << endl;

			//Takes input of the x range and y range
			int xLow;
			int xHigh;
			int yLow;
			int yHigh;
			cin >> xLow >> xHigh >> yLow >> yHigh;

			//Outputs the ranges to be searched
			cout << xLow << " " << xHigh << " " << yLow << " " << yHigh << endl;

			//Calls modified _rangeSearch
			xTree->_rangeSearch(xLow, xHigh, yLow, yHigh);
			break;

		//Remove
		case 'R':

			//Takes input of xCoordinate and yCoordinate
			int xCoordinate;
			int yCoordinate;
			cin >> xCoordinate >> yCoordinate;

			//Prints coordinates to attempt remove on
			cout << "Remove: " << xCoordinate << " " << yCoordinate << endl;

			//Calls modified _remove function
			xTree->_remove(xCoordinate, yCoordinate);
			break;

		//Y tree Balance
		case 'Y':
			
			//Takes input of xLocation
			int xLocation;
			cin >> xLocation;

			//Prints the xTree that will have its yTree balanced
			cout << "Y tree balance" << endl;
			cout << xLocation << endl;

			//Calls yBalance
			xTree->yBalance(xLocation);

			break;

		//Find
		case 'F':

			//Takes input for x and y value to find
			int xFind;
			int yFind;
			cin >> xFind >> yFind;

			//Prints the values that will be attempted to be found
			cout << "Find: " << xFind << " " << yFind << endl;

			//Calls find 
			xTree->find(xFind, yFind);
			break;
			
		}
	}

	//Calls destructor
	delete xTree;
	return 0;
}
