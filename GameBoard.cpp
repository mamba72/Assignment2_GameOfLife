#include <iostream>
#include "GameBoard.h"
using namespace std;

GameBoard::GameBoard(int height, int width, int gameMode)
{
	dimentions[0] = height;
	dimentions[1] = width;
	this->gameMode = gameMode;
}

GameBoard::GameBoard(string fileName, int gameMode)
{
	this->gameMode = gameMode;
}

GameBoard::~GameBoard()
{
	//destroy the 2D array
	for (int row = 0; row < dimentions[0]; ++row)
	{
		delete[] grid[row];
	}
}

void GameBoard::RandomizeStartPositions(float initDensity)
{

}

void GameBoard::InitializeGrid()
{
	grid = new Cell * [dimentions[0]];
	//create the inner arrays
	for (int row = 0; row < dimentions[0]; ++row)
	{

		grid[row] = new Cell[dimentions[1]];
		//populate all the cells with the required info

	}
}