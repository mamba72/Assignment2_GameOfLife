/*
Stephen White
002323381
stwhite@chapman.edu
Data Structures Section 1
Assignment 2 Game of Life
*/
#include <iostream>
#include "Cell.h"

using namespace std;

Cell::Cell(int xCor, int yCor, bool occupied, int gameMode)
{
	coordinates[0] = xCor;
	coordinates[1] = yCor;
	//this->numNeighbors = numNeighbors;
	isEmpty = occupied;
	this->gameMode = gameMode;
}

Cell::Cell()
{
	isEmpty = true;
}

//destroy the object
Cell::~Cell()
{
	//make sure you delete all the arrays created
}

int Cell::NumNeighbors(Cell** &board, int height, int width)
{
	int totalNeighbors = 0;
		//check straight right
		if (IsNeighbor(coordinates[0], coordinates[1] + 1, board))
		{
			totalNeighbors++;
		}
		//right and up
		if (IsNeighbor(coordinates[0] + 1, coordinates[1] + 1, board))
		{
			totalNeighbors++;
		}

		//directly up
		if (IsNeighbor(coordinates[0] + 1, coordinates[1], board))
			totalNeighbors++;

		//up and left
		if (IsNeighbor(coordinates[0] + 1, coordinates[1] - 1, board))
			totalNeighbors++;

		//directly left
		if (IsNeighbor(coordinates[0], coordinates[1]-1, board))
			totalNeighbors++;

		//left and down
		if (IsNeighbor(coordinates[0] - 1, coordinates[1] - 1, board));
			totalNeighbors++;

		//directly down
		if (IsNeighbor(coordinates[0]-1, coordinates[1], board))
			totalNeighbors++;

		//right and down
		if (IsNeighbor(coordinates[0] - 1, coordinates[1] + 1, board))
			totalNeighbors++;
	//}
	

	return totalNeighbors;
}

string Cell::GetSymbol()
{
	if (isEmpty == true)
		return "-";
	else
		return "X";
}

bool Cell::IsNeighbor(int xCor, int yCor, Cell** &board)
{

	int coordToCheck[2] = { xCor, yCor };
	//cout << "\tCoordinates to check: (" << coordToCheck[0] << ", " << coordToCheck[1] << ")\n";
	//classic is 1
	if (gameMode == 1)
	{
		//if the coord to check is out of bounds, do nothing
		if (coordToCheck[0] < 0 || coordToCheck[0] >= boardHeight || coordToCheck[1] < 0 || coordToCheck[1] >= boardWidth)
		{
			//cout << "Found a corner at coordinates (" << coordToCheck[0] << ", " << coordToCheck[1] << ")" << endl;
			return false;
		}
		else if (board[coordToCheck[0]][coordToCheck[1]].isEmpty == false)
			return true;
		return false;
	}
	//doughnut mode
	else if (gameMode == 2)
	{
		//if its not against the wall, you dont need to do these checks
		if (IsAgainstWall())
		{
			//if the coordinates would be out of bounds, check the other side of the grid
			//check the height and adjust as necessary 
			if (coordToCheck[0] < 0)
				coordToCheck[0] = (boardHeight - 1);
			else if (coordToCheck[0] >= boardHeight)
				coordToCheck[0] = 0;

			//now check the width and adjust as necessary
			if (coordToCheck[1] < 0)
				coordToCheck[1] = (boardWidth - 1);
			else if (coordToCheck[1] >= boardWidth)
				coordToCheck[1] = 0;
		}
		//cout << "\t\tCoordinates to check: " << coordToCheck[0] << ", " << coordToCheck[1] << endl;
		if(board[coordToCheck[0]][coordToCheck[1]].isEmpty == false)
			return true;
			
	}
	//mirror
	else if (gameMode == 3)
	{
		//if its not against the wall, you dont need these checks
		if (IsAgainstWall())
		{
			if (coordToCheck[0] < 0)
				coordToCheck[0] = 0;
			else if (coordToCheck[0] >= boardHeight)
				coordToCheck[0] = (boardHeight - 1);

			if (coordToCheck[1] < 0)
				coordToCheck[1] = 0;
			else if (coordToCheck[1] >= boardWidth)
				coordToCheck[1] = (boardWidth - 1);
		}
		//cout << "\t\tCoordinates to check: " << coordToCheck[0] << ", " << coordToCheck[1] << endl;
		if (board[coordToCheck[0]][coordToCheck[1]].isEmpty == false)
			return true;
	}
	return false;
}

//this function determines if the current cell is against a wall
bool Cell::IsAgainstWall()
{
	//cout << "\tCoordinates: " << coordinates[0] << ", " << coordinates[1] << endl;
	if (coordinates[0] == 0)
		return true;
	else if (coordinates[0] == boardHeight - 1)
		return true;

	if (coordinates[1] == 0)
		return true;
	else if (coordinates[1] == (boardWidth - 1))
		return true;

	return false;
}
