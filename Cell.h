#include <iostream>
using namespace std;

class Cell
{
public: 
	Cell(int xCor, int yCor, bool occupied);
	Cell();
	~Cell();

	//functions:
	int NumNeighbors(GameBoard &board); //id like the cell itself to have the ability to check the amount of neighbors it has

	//member vars
	int numNeighbors;
	int coordinates[2];
	bool isEmpty;

};