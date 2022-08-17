#include <fstream>
#include "functions.h"
#include "gGame.h"
#include "fileReader.h"



vector<object> fullGalaxyList;


int main()
{
	ifstream in;
	in.open("Galaxy_Data.txt");


	if (in.is_open())
	{
		fileReader(in, fullGalaxyList);
		in.close();

		gGame(fullGalaxyList);
	}

	else
	{cout << "\n   !!!       Failed to open Galaxy_Data.txt.       !!!\n" << endl;}

	
	return 0;
}