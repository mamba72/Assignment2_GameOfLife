#include <iostream>
#include "Cell.h"

using namespace std;

class GameBoard
{
public:
	GameBoard(int height, int width, int gameMode);
	GameBoard(string fileName, int gameMode);
	~GameBoard();

	//functions
	//void LoadBoardFromFile(string fileName);
	void RandomizeStartPositions(float initDensity);
	

	//member vars
	Cell** grid;
	int dimentions[2];
	int gameMode;

private:

	//functions
	void InitializeGrid();
};