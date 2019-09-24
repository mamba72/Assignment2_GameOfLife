/*
Stephen White
002323381
stwhite@chapman.edu
Data Structures Section 1
Assignment 2 Game of Life
*/
#include <iostream>
#include "GameBoard.h"
using namespace std;

GameBoard::GameBoard(int height, int width, int gameMode, float initDensity)
{
	//THROW AN EXCEPTION IF HEIGHT AND WIDTH ARE TOO LOW
	//OR IF GAMEMODE ISNT A VALID SELECTION
	//OR IF INITDENSITY IS GREATER THAN ONE OR LESS THAN OR EQUAL TO 0
	dimentions[0] = height;
	dimentions[1] = width;
	this->gameMode = gameMode;

	InitializeGridRandomly(initDensity);
}

GameBoard::GameBoard(string fileName, int gameMode)
{
	this->gameMode = gameMode;

	FileReader reader(fileName);

	this->dimentions[0] = reader.height;
	this->dimentions[1] = reader.width;

	this->totalCells = reader.startPop;

	InitializeGrid(reader.positions, totalCells);
}

GameBoard::GameBoard(int height, int width, int gameMode, int**& startingPos, int startingPop)
{
	this->dimentions[0] = height;
	this->dimentions[1] = width;
	this->gameMode = gameMode;
	
	InitializeGrid(startingPos, startingPop);
}

//destructor
GameBoard::~GameBoard()
{
	//destroy the 2D array
	for (int row = 0; row < dimentions[0]; ++row)
	{
		delete[] grid[row];
	}
	delete[] grid;
}

//returns the amount of starters and creates an array in place and fills it with the starting positions
int GameBoard::RandomizeStartPositions(float initDensity, int** &startCoords)
{
	//total spots is height * width (area)
	int totalSpots = dimentions[0] * dimentions[1];
	int startPop = totalSpots * initDensity;
	startCoords = new int* [startPop];

	//now generate all the random positions for the occupied cells. 
	//ensure that if that cell is already taken, find a different spot
	for (int i = 0; i < startPop;)
	{
		startCoords[i] = new int[2];

		int randX = rand() % (dimentions[0]); //this will get a random number between 0 and the length of the board
		int randY = rand() % (dimentions[1]);

		bool isFree = false;
		//now ensure that that position isnt already taken
		for (int index = 0; index < startPop; ++index)
		{
			//if those x and y coordinates are already taken, then break
			if (startCoords[i][0] == randX && startCoords[i][1] == randY)
			{
				isFree = false;
				break;
			}
			else
			{
				isFree = true;
			}
		}

		//if that spot was free and everything is good to go, then occupy that spot and move on.
		if (isFree == true)
		{
			startCoords[i][0] = randX;
			startCoords[i][1] = randY;
			++i;
		}
	}

	return startPop;
}

//fills in the grid with empty cells and then places all the occupied ones
void GameBoard::InitializeGridRandomly(float initDensity)
{
	int** starterPos;
	int startPop = RandomizeStartPositions(initDensity, starterPos);

	InitializeGrid(starterPos, startPop);
}

/*This takes in the coordinates of the starting coordinates and that arrays length*/
void GameBoard::InitializeGrid(int**& startCoords, int startPop)
{
	this->totalCells = startPop;
	grid = new Cell * [dimentions[0]];
	//create the inner arrays
	for (int row = 0; row < dimentions[0]; ++row)
	{
		//just initilize the grid with a bunch of empty cells
		grid[row] = new Cell[dimentions[1]];

		for (int col = 0; col < dimentions[1]; ++col)
		{
			//initialize the cells to the default values
			grid[row][col].coordinates[0] = row;
			grid[row][col].coordinates[1] = col;
			grid[row][col].gameMode = this->gameMode;
			grid[row][col].isEmpty = true;
			grid[row][col].boardHeight = dimentions[0];
			grid[row][col].boardWidth = dimentions[1];
		}
	}

	//now that the grid is ready for info, place all the cells in their specified place
	for (int i = 0; i < startPop; ++i)
	{

		int x = startCoords[i][0];
		int y = startCoords[i][1];
		//initialize the cell's coordinates
		grid[x][y].coordinates[0] = x;
		grid[x][y].coordinates[1] = y;
		grid[x][y].isEmpty = false;
		grid[x][y].gameMode = this->gameMode;
	}

	//destroy the starterPos array
	for (int i = 0; i < startPop; ++i)
	{
		delete[] startCoords[i];
	}
	delete[] startCoords;
}

//returns whether the cell at that position is unoccupied
bool GameBoard::IsPositionEmpty(int xCor, int yCor)
{
	return grid[xCor][yCor].isEmpty;
}

//this function simply prints the whole board
string GameBoard::PrintGrid()
{
	string outputStr = "";
	for (int row = 0; row < dimentions[0]; ++row)
	{
		for (int col = 0; col < dimentions[1]; ++col)
		{
			outputStr += grid[row][col].GetSymbol() + " ";
		}

		outputStr += "\n";
	}

	return outputStr;
}

//go through the grid and gather up the coordinates of all the cells that will be in the next generation
int** GameBoard::GetNextGeneration()
{
	int numberNext = GetNextGenerationPopulation();

	//now go through the grid finding all the coordinates of the next generation's occupied cells
	int** nextStarterPos = new int* [numberNext];
	for (int i = 0; i < numberNext; ++i)
	{
		nextStarterPos[i] = new int[2];
	}

	int cellCounter = 0;
	//go through the grid and gather up the coordinates of all the cells that will be in the next generation
	for (int row = 0; row < dimentions[0]; ++row)
	{
		for (int col = 0; col < dimentions[1]; ++col)
		{
			int numberNeighbors = grid[row][col].NumNeighbors(grid, dimentions[0], dimentions[1]);
			if (numberNeighbors == 2 && grid[row][col].isEmpty == false)
			{
				nextStarterPos[cellCounter][0] = row;
				nextStarterPos[cellCounter][1] = col;
				++cellCounter;
			}
				
			else if (numberNeighbors == 3)
			{
				nextStarterPos[cellCounter][0] = row;
				nextStarterPos[cellCounter][1] = col;
				++cellCounter;
			}
		}
	}

	return nextStarterPos;
}

/*Get the population of the next generation.*/
int GameBoard::GetNextGenerationPopulation()
{
	int numberNext = 0;

	//iterate through the grid counting how many cells will be occupied next generation
	for (int row = 0; row < dimentions[0]; ++row)
	{
		for (int col = 0; col < dimentions[1]; ++col)
		{
			int numberNeighbors = grid[row][col].NumNeighbors(grid, dimentions[0], dimentions[1]);
			if (numberNeighbors == 2 && grid[row][col].isEmpty == false)
				++numberNext;
			else if (numberNeighbors == 3)
				++numberNext;
		}
	}

	return numberNext;
}