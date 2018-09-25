/*
	file: Map_loader.h
*/
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include <vector>
#include ".\Map_CPNT.h"
using namespace std;

class Map_loader{
	public:
	//prompt user for file name/path
	string choose_file();
	
	// open the file_stream
	//close the file_stream
	// parse the the file
	void parser(string file_name);
	//load the diffirent map component
	void loadInfo(string var[5]);
	void loadTerritory(string line);
	void loadContinent(string line);
	
	  
};

