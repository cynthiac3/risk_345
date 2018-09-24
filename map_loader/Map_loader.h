/*
	file: Map_loader.h
*/
#include <ifstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include <vector>
#include ".\Map_CPNT.h"
using namespace std;

class Map_loader{
	//prompt user for file name/path
	string choose_file();
	
	// open the file_stream
	ifstream read_file(string file_name);
	//close the file_stream
	void close_file(ifstream file);	

	// parse the the file
	parser(ifstream file);
	//load the diffirent map component
	Info loadInfo(string var[5]);
	Territory* loadTerritory(string line);
	Contitnent* loadContinent(string line);
	
	  
}

