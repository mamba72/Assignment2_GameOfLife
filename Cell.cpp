#include <iostream>
#include "Cell.h"
#include "GameBoard.h"
using namespace std;

Cell::Cell(int xCor, int yCor, bool occupied)
{
	coordinates[0] = xCor;
	coordinates[1] = yCor;
	this->numNeighbors = numNeighbors;
	isEmpty = occupied;
}

Cell::Cell()
{

}

//destroy the object
Cell::~Cell()
{
	//make sure you delete all the arrays created
	delete[] coordinates;
}

int Cell::NumNeighbors(GameBoard& board)
{
	return 0;
}

