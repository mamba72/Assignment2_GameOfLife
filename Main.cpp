#include <iostream>
//#include "Cell.h"
#include "GameBoard.h"
#include <time.h>

using namespace std;

void NextGeneration(GameBoard& currentGen);

int main(int argc, char** argv)
{
	srand(time(NULL));

	cout << "Hello! Welcome to The Game of Life!" << endl;

	//GameBoard board(3, 3, 1, 0.5);
	GameBoard board("ExampleGrid.txt", 1);

	cout << "Board Height: " << board.dimentions[0] << endl;
	cout << "Board Width: " << board.dimentions[1] << endl;

	board.PrintGrid();

	int** nextGenStarterPos = board.GetNextGeneration();
	int nextGenPopulation = board.GetNextGenerationPopulation();

	GameBoard nextGen(5, 7, 1, nextGenStarterPos, nextGenPopulation);

	nextGen.PrintGrid();

	//GameBoard nextGen2 = NextGeneration(board, nextGen);
	//cout << "Got next generation." << endl;
	//nextGen2.PrintGrid();

	//test the file reading
	/*GameBoard boardFromFile("ExampleGrid.txt", 1);

	cout << "BoardFromFile Height: " << boardFromFile.dimentions[0] << endl;
	cout << "BoardFromFile Width: " << boardFromFile.dimentions[1] << endl;

	boardFromFile.PrintGrid();*/



}

//delete the board in the argument and return the next generation
void NextGeneration(GameBoard &currentGen)
{
	//int numberNext = 0;

	////iterate through the grid counting how many cells will be occupied next generation
	//for (int row = 0; row < currentGen.dimentions[0]; ++row)
	//{
	//	for (int col = 0; col < currentGen.dimentions[1]; ++col)
	//	{
	//		int numberNeighbors = currentGen.grid[row][col].NumNeighbors(currentGen.grid, currentGen.dimentions[0], currentGen.dimentions[1]);
	//		cout << "Number of neighbors: " << numberNeighbors << endl;
	//		if (numberNeighbors == 2)
	//			++numberNext;
	//		else if (numberNeighbors == 3)
	//			++numberNext;
	//	}
	//}

	//cout << "Number of cells in next gen: " << numberNext << endl;

	//nextGen = currentGen.GetNextGeneration();


	//return nextGen;
}