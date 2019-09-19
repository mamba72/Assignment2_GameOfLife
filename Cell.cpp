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
	//1 is classic mode
	if (gameMode == 1)
	{
		cout << "Cell's coordinates: (" << coordinates[1] << ", " << coordinates[0] << ")\n";

		//check straight right
		if (IsNeighbor(coordinates[0], coordinates[1] + 1, board, height, width))
		{
			totalNeighbors++;
			cout << "\tFound a neighbor stright right at coordinates " << coordinates[1] << ", " << coordinates[0] - 1 << endl;
		}
			

		//right and up
		if (IsNeighbor(coordinates[0] + 1, coordinates[1] + 1, board, height, width))
		{
			totalNeighbors++;
			cout << "\tFound a neighbor right and up at coordinates " << coordinates[1]+1 << ", " << coordinates[0]-1 << endl;
		}

		//directly up
		if (IsNeighbor(coordinates[0] + 1, coordinates[1], board, height, width))
			totalNeighbors++;

		//up and left
		if (IsNeighbor(coordinates[0] + 1, coordinates[1] - 1, board, height, width))
			totalNeighbors++;

		//directly left
		if (IsNeighbor(coordinates[0], coordinates[1]-1, board, height, width))
			totalNeighbors++;

		//left and down
		if (IsNeighbor(coordinates[0] - 1, coordinates[1] - 1, board, height, width))
			totalNeighbors++;

		//directly down
		if (IsNeighbor(coordinates[0]-1, coordinates[1], board, height, width))
			totalNeighbors++;

		//right and down
		if (IsNeighbor(coordinates[0] - 1, coordinates[1] + 1, board, height, width))
			totalNeighbors++;
	}
	

	return totalNeighbors;
}

string Cell::GetSymbol()
{
	if (isEmpty == true)
		return "-";
	else
		return "X";
}

bool Cell::IsNeighbor(int xCor, int yCor, Cell** &board, int height, int width)
{

	int coordToCheck[2] = { xCor, yCor };
	//cout << "\tCoordinates to check: (" << coordToCheck[0] << ", " << coordToCheck[1] << ")\n";
	//classic is 1
	if (gameMode == 1)
	{
		if (coordToCheck[0] < 0 || coordToCheck[0] >= height || coordToCheck[1] < 0 || coordToCheck[1] >= width)
		{
			//cout << "Found a corner at coordinates (" << coordToCheck[0] << ", " << coordToCheck[1] << ")" << endl;
			return false;
		}
		else if (board[coordToCheck[0]][coordToCheck[1]].isEmpty == false)
			return true;
		return false;
	}
	else if (gameMode == 2)
	{

	}
	else if (gameMode == 3)
	{

	}

	return false;
	
}

//this function determines if the current cell is in a corner
bool Cell::IsInCorner(int height, int width)
{
	if (coordinates[0] == 0)
	{
		if (coordinates[1] == 0)
			return true;
		else if (coordinates[1] == width - 1)
			return true;
	}
}
