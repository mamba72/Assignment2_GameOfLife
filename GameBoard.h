/*
Stephen White
002323381
stwhite@chapman.edu
Data Structures Section 1
Assignment 2 Game of Life
*/
#include <iostream>
#include "Cell.h"
#include "FileReader.h"

using namespace std;

class GameBoard
{
public:
	//consider taking out the gameMode?
	GameBoard(int height, int width, int gameMode, float initDensity);
	GameBoard(int height, int width, int gameMode, int** &startingPos, int startingPop);
	GameBoard(string fileName, int gameMode);
	~GameBoard();

	//functions
	//void LoadBoardFromFile(string fileName);
	
	string PrintGrid();
	int** GetNextGeneration();
	int GetNextGenerationPopulation();

	//member vars
	Cell** grid;
	int dimentions[2];
	int gameMode;
	int totalCells;

private:

	//functions
	int RandomizeStartPositions(float initDensity, int** &startCoords);
	void InitializeGridRandomly(float initDensity);
	bool IsPositionEmpty(int xCor, int yCor);
	void InitializeGrid(int**& startCoords, int startPop);
};