/*
Stephen White
002323381
stwhite@chapman.edu
Data Structures Section 1
Assignment 2 Game of Life
*/
#include "FileReader.h"

using namespace std;

FileReader::FileReader(string fileName)
{
	ReadFile(fileName);
}

//read all the info from the file
void FileReader::ReadFile(string fileName)
{
	ifstream file;
	file.open(fileName);

	if (!file)
	{
		throw runtime_error("Couldn't open file named " + fileName);
	}

	//count how many lines there are
	string line;
	int lineCount = 0;
	while (getline(file, line))
	{
		++lineCount;
	}
	file.clear();
	file.seekg(0);//reset the stream to position 0

	//create an array that houses all the lines from the file
	string* fileLines = new string[lineCount];

	//put all the lines into the array
	int counter = 0;
	while (getline(file, line))
	{
		fileLines[counter] = line;
		++counter;
	}
	file.clear();
	file.seekg(0);//reset the stream to position 0

	file.close();

	//ERROR CHECKING. MAKE SURE ITS A NUMBER. IF NOT, THROW EXCEPTION
	//now that we have all the lines, parse the first two lines into integers
	//line 1 is height, two is width. Everything after that is part of the grid
	this->height = stoi((string)fileLines[0]); //parse height. Both functions will throw exceptions if it cannot be parsed
	this->width = stoi((string)fileLines[1]); //parse width. 

	if (this->height != lineCount - 2 || IsWidthCorrect(fileLines, lineCount, width))
	{
		throw runtime_error("The file does not follow the correct standard layout.");
	}

	//now read how many cells are in the provided grid
	int totalPop = 0;
	for (int i = 2; i < lineCount; ++i)
	{
		for (int index = 0; index < fileLines[i].length(); ++index)
		{
			if (fileLines[i][index] == 'X')
				++totalPop;
		}
	}

	//now determine the coordinates of each starter cell
	//initialize the 2D array
	positions = new int* [totalPop];
	for (int i = 0; i < totalPop; ++i)
	{
		positions[i] = new int[2];
	}

	this->startPop = totalPop;

	//now iterate through the lines recording their positions
	int currentCell = 0;
	for (int row = 2; row < lineCount; ++row)
	{
		for (int col = 0; col < fileLines[row].length(); ++col)
		{
			if (fileLines[row][col] == 'X')
			{
				positions[currentCell][0] = row-2;
				positions[currentCell][1] = col;

				++currentCell;
				if (currentCell >= totalPop)
				{
					return;
				}
					
			}
		}
	}
	
	
}

//determines if all the lines in the file are the correct width
bool FileReader::IsWidthCorrect(string* &fileLines, int lineCount, int width)
{
	for (int i = 2; i < lineCount; ++i)
	{
		if (fileLines[i].length() != width)
			return false;
	}

	return true;
}

void FileReader::WriteToFile(string fileName, string strToWrite)
{
	ofstream outFile;

	outFile.open(fileName, ofstream::app);

	if (!outFile)
		throw runtime_error("Cannot open output file.");

	outFile << strToWrite << endl;

	outFile.close();
}