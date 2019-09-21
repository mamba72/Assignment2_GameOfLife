/*
Stephen White
002323381
stwhite@chapman.edu
Data Structures Section 1
Assignment 2 Game of Life
*/
#include <iostream>
//#include "GameBoard.h"
using namespace std;

class Cell
{
public: 
	Cell(int xCor, int yCor, bool occupied, int gameMode);
	Cell();
	~Cell();

	//functions:
	int NumNeighbors(Cell** &board, int height, int width); //id like the cell itself to have the ability to check the amount of neighbors it has
	string GetSymbol();

	bool IsNeighbor(int xCor, int yCor, Cell** &board);
	bool IsAgainstWall();

	//member vars
	int coordinates[2];
	int boardHeight;
	int boardWidth;
	bool isEmpty;
	int gameMode;
};