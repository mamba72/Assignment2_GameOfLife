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

	bool IsNeighbor(int xCor, int yCor, Cell** &board, int height, int width);
	bool IsInCorner(int height, int width);

	//member vars
	int coordinates[2];
	bool isEmpty;
	int gameMode;
};