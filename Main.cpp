/*
Stephen White
002323381
stwhite@chapman.edu
Data Structures Section 1
Assignment 2 Game of Life
*/
#include <fstream>
#include <iostream>
//#include "Cell.h"
#include "GameBoard.h"
#include <time.h>


using namespace std;

bool KeepRunning(GameBoard*& curGen, GameBoard*& nextGen);

int main(int argc, char** argv)
{
	//this is to ensure that the random numbers are actually random by seeding the number with the current time
	srand(time(NULL));

	cout << "Hello! Welcome to The Game of Life!" << endl;

	//get the user input
	cout << "Would you like to input a file name or randomly generate the population?" <<
		"\n(Please enter the number of your cooresponding answer)\n";

	cout << "1. Random\n2. File Name\n";
	string answer = "";
	cin >> answer;

	bool isRandom;
	if (answer == "1")
		isRandom = true;
	else if (answer == "2")
		isRandom = false;

	/*NOTE::::: if the user does something stupid, quit the program.
	If the user cant follow simple instructions, then they dont deserve to play.*/
	else
	{
		cout << "That was not an option. Ending the program.\n";
		return 1;
	}

	int height = 0;
	int width = 0;
	float density = 0;
	string filePath = "";
	ofstream outputFile;
	if (isRandom)
	{
		cout << "What should the dimentions of the world be?\n";
		cout << "Height: ";
		cin >> answer;
		try
		{
			height = stoi(answer);//parse the string to an int
		}
		catch (...)
		{
			cout << "That was not a number.\n";
			return 1;
		}
		
		if (height <= 0)
		{
			cout << "That is not a valid height.\n";
			return 1;
		}

		cout << "Width: ";
		cin >> answer;
		try
		{
			width = stoi(answer);//parse the string to an int
		}
		catch (...)
		{
			cout << "That was not a number.\n";
			return 1;
		}
		if (width <= 0)
		{
			cout << "That is not a valid width.\n";
			return 1;
		}

		cout << "What should the initial population density be?\n(must be 0 < density <= 1)\n";
		cin >> answer;
		try
		{
			density = stof(answer);//parse the string to an int
		}
		catch (...)
		{
			cout << "That was not a number.\n";
			return 1;
		}
		if (density < 0 || density > 1)
		{
			cout << "That was not a valid density. (Make sure you follow the rules)\n";
			return 1;
		}


		cout << "Input summary:\n";
		cout << "Height: " << height << endl;
		cout << "Width: " << width << endl;
		cout << "Density: " << density << endl;
	}//end is random
	else//get filePath
	{
		cout << "Please enter the file path or name of the file. (it must be a txt)\n";
		cin >> filePath;
	}

	cout << "What game mode would you like to run? (please enter the number of the option)\n";
	cout << "1. Classic\n2. Doughnut\n3. Mirror\n";
	cin >> answer;
	int gameMode = 0;
	try
	{
		gameMode = stoi(answer);
		if (gameMode < 1 || gameMode > 3)
			throw runtime_error("That was not a valid mode.");
	}
	catch (...)
	{
		cout << "That was not a valid mode. Since entering numbers is hard for you, I'm going to make the mode Classic.\n";
		gameMode = 1;
	}

	bool stepByStep = false;
	cout << "Would you like to slow the program down so you can see each step? (y/n)\n";
	cout << "(This means you will have to press ENTER between every generation)\n";
	cin >> answer;
	if (answer == "y")
		stepByStep = true;
	else if (answer == "n")
		stepByStep = false;
	else
		cout << "That was not an option. Seeing that you struggle to type in single letters,\nyou dont care to watch every generation.\n";

	string outputFileName = "";
	if (stepByStep == false)
	{
		cout << "What would you like the output file to be called?\n";
		cin >> outputFileName;
		outputFile.open(outputFileName);
	}
	//done gathering user input

	//now run the simulation
	
	
	GameBoard* curBoard;
	GameBoard* nextGen;
	bool keepRunning = false;

	if (isRandom)
		curBoard = new GameBoard(height, width, gameMode, density);
	else
	{
		try
		{
			curBoard = new GameBoard(filePath, gameMode);
		}
		catch (runtime_error e)
		{
			cout << "There was a problem. Your error message: " << e.what() << endl;
			return 1;
		}
	}
		

	int currentGenPopulation = curBoard->totalCells;
	int nextGenPop = 0;
	cin.get();//because there seems to already be an enter in the cin buffer?
	int generationCounter = 0;
	do
	{
		currentGenPopulation = curBoard->totalCells;
		//the program will alway print the generation number so the user knows it is still running
		cout << "Generation Number: " << generationCounter << endl;
		if (stepByStep == false)
		{
			outputFile << "Generation Number: " << generationCounter << endl;
			outputFile << curBoard->PrintGrid() << endl;
		}
		else
			cout << curBoard->PrintGrid() << endl;

		

		int** nextGenStarterPos = curBoard->GetNextGeneration();
		nextGenPop = curBoard->GetNextGenerationPopulation();
		nextGen = new GameBoard(curBoard->dimentions[0], curBoard->dimentions[1], gameMode, nextGenStarterPos, nextGenPop);
		
		if (stepByStep == false)
			outputFile << "Next Generation Population: " << nextGenPop << endl;
		else
			cout << "Next Generation Population: " << nextGenPop << endl;

		keepRunning = KeepRunning(curBoard, nextGen);

		curBoard->~GameBoard();

		curBoard = nextGen;
		if(stepByStep)
			cout << "Keep running to next generation: " << keepRunning << endl;

		if (stepByStep)
		{
			string throwAway;
			cout << "Press ENTER to continue to next generation.\n";
			cin.get();
		}

		++generationCounter;
	} while (keepRunning);

	//print the last generation
	if (stepByStep == false)
	{
		outputFile << "Generation Number: " << generationCounter << endl;
		outputFile << curBoard->PrintGrid() << endl;

		outputFile << "This is the last generation.\n";

		outputFile.close();
	}
	cout << "Generation Number: " << generationCounter << endl;
	cout << curBoard->PrintGrid() << endl;
	cout << "This is the last generation.\n";

	cout << "Press ENTER to exit the program...\n";
	cin.get();

	cout << "Goodbye! :)\n";
}

//this will determine whether the game should keep runnning.
bool KeepRunning(GameBoard*& curGen, GameBoard*& nextGen)
{
	//check to see if the nextGen's population is empty
	if (nextGen->totalCells == 0)
		return false;

	//if the grids are equal, then the program has stagnated.
	bool areGridsEqual = true;
	for (int row = 0; row < curGen->dimentions[0]; ++row)
	{
		for (int col = 0; col < curGen->dimentions[1]; ++col)
		{
			if (curGen->grid[row][col].isEmpty != nextGen->grid[row][col].isEmpty)
			{
				//if the grids arent equal, break.
				areGridsEqual = false;
				break;
			}
		}
		if (areGridsEqual == false)
			break;
	}

	if (areGridsEqual)
		return false;



	return true;
}