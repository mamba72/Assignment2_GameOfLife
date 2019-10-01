/*
Stephen White
002323381
stwhite@chapman.edu
Data Structures Section 1
Assignment 2 Game of Life
*/
#include <chrono>//is required for pause to give me the number of seconds i want
#include <thread>//to pause/sleep the thread
#include <fstream>
#include <iostream>
#include "GameBoard.h"
#include <time.h>

using namespace std::this_thread;
using namespace std::chrono; // nanoseconds, system_clock, seconds

using namespace std;

bool KeepRunning(GameBoard*& curGen, GameBoard*& nextGen);

//global var
int stabalizedGens = 0;
//this will maintain the last 3 generation strings. (to help know if it has stabalized)
string prevGenStrings[3];

int main(int argc, char** argv)
{

	string my = string(1, '0');
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
	//ofstream outputFile;
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

	cout << "To watch each generation you have 3 options:\n1. A short pause in between.\n2. Pressing enter between each generation.\n3. Just run and then output to a file.\n";
	cout << "(you must enter the number of your choice)\n";
	int nextGenChoice = 0;
	cin >> answer;
	try
	{
		nextGenChoice = stoi(answer);

		if (nextGenChoice < 1 || nextGenChoice > 3)
			throw runtime_error("That was not an option.");
	}
	catch (...)
	{
		cout << "That was not an option. I'm going to select the option to view every generation.\n";
		nextGenChoice = 2;
	}
	//ask for the file
	string outputFileName = "";
	if (nextGenChoice == 3)
	{
		cout << "What would you like the output file to be called?\n";
		cin >> outputFileName;

		try
		{
			FileReader::WriteToFile(outputFileName, "Beginning of Simulation.");
		}
		catch (...)
		{
			cout << "There was a problem opening your output file. Make sure you input a file that isnt in use.";
			return 1;
		}
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
			cout << "You must enter a valid file name.\n";
			cout << "Your error message: " << e.what() << endl;
			cout << "This could also occur if the file did not follow the standard layout.\n";
			return 1;
		}
	}
	
	//now start all the generation jazz

	int currentGenPopulation = curBoard->totalCells;
	int nextGenPop = 0;
	cin.get();//because there seems to already be an enter in the cin buffer?
	int generationCounter = 0;
	do
	{
		currentGenPopulation = curBoard->totalCells;
		//the program will alway print the generation number so the user knows it is still running
		cout << "Generation Number: " << generationCounter << endl;
		if (nextGenChoice == 3)
		{
			string outStr = "Generation Number: " + to_string(generationCounter);
			FileReader::WriteToFile(outputFileName, outStr);
			outStr = curBoard->PrintGrid();
			FileReader::WriteToFile(outputFileName, outStr);
		}
		else if(nextGenChoice == 2 || nextGenChoice == 1)
			cout << curBoard->PrintGrid() << endl;

		
		//get the starter coordinates of the next generation
		int** nextGenStarterPos = curBoard->GetNextGeneration();
		//get the number of occupied cells in the next generation (also the length of the array gathered on the previous line)
		nextGenPop = curBoard->GetNextGenerationPopulation();
		//instantiate the next gameboard with the same dimentions, but the new starter positions
		nextGen = new GameBoard(curBoard->dimentions[0], curBoard->dimentions[1], gameMode, nextGenStarterPos, nextGenPop);
		
		if (nextGenChoice == 3)
		{
			string outStr = "Next Generation Population: " + to_string(nextGenPop);
			FileReader::WriteToFile(outputFileName, outStr);
		}
		else if(nextGenChoice == 2 || nextGenChoice == 1)
			cout << "Next Generation Population: " << nextGenPop << endl;

		//place the last couple generation strings into the array
		prevGenStrings[generationCounter % 3] = curBoard->PrintGrid();
		prevGenStrings[(generationCounter + 1) % 3] = nextGen->PrintGrid();


		keepRunning = KeepRunning(curBoard, nextGen);

		curBoard->~GameBoard();//deconstruct the previous generation. (because memory reasons)
		//reassign the variables
		curBoard = nextGen;

		//this is to wait for user input if they select the option to press enter every time
		if (nextGenChoice == 2)
		{
			cout << "Press ENTER to continue to next generation.\n";
			cin.get();
		}
		//sleep for 2 seconds if the option was selected
		if (nextGenChoice == 1)
		{
			sleep_for(seconds(2));
		}

		++generationCounter;
	} while (keepRunning);

	//print the last generation
	if (nextGenChoice == 3)
	{
		string outStr = "Generation Number: " + to_string(generationCounter);
		FileReader::WriteToFile(outputFileName, outStr);
		outStr = curBoard->PrintGrid();
		FileReader::WriteToFile(outputFileName, outStr);
		FileReader::WriteToFile(outputFileName, "Simulation Finished");
	}
	cout << "Generation Number: " << generationCounter << endl;
	cout << curBoard->PrintGrid() << endl;
	cout << "This is the last generation.\n";

	cout << "Press ENTER to exit the program...\n";
	cin.get();

	cout << "Goodbye! :)\n";
}

/*this will determine whether the game should keep runnning.
It will return false if the grid from the previous gen is identical to the current gen 
or if the current gen's population is 0.*/
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

	//if the simulation has the same amonut of cells for 4 generations, it has stabalized.
	if (curGen->totalCells == nextGen->totalCells)
	{
		stabalizedGens++;
		if (stabalizedGens > 4)
			return false;
	}
	else
		stabalizedGens = 0;

	//iterate through the prevGenStrings to ensure that we dont have a duplicate
	//if we have a duplicate, the program has stabilized.
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			//skip this iteratation to make sure we arent comparing the exact same generation.
			if (i == j)
				continue;
			//if it finds 2 generation strings that are equal, then we have a repeating simulation.
			if (prevGenStrings[i] == prevGenStrings[j])
				return false;
		}
	}


	return true;
}