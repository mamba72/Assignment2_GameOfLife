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