/*
Stephen White
002323381
stwhite@chapman.edu
Data Structures Section 1
Assignment 2 Game of Life
*/
#include <iostream>
#include <fstream>

using namespace std;

class FileReader
{
public:
	FileReader(string fileName);

	//functions
	void ReadFile(string fileName);

	//member vars
	int height;
	int width;
	int startPop;
	int** positions;
};