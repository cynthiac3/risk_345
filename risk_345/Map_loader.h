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


#ifndef MAP_LOADER_H
#define MAP_LOADER_H

using namespace std;

class Map_loader{
	public:
	Info myInfo;
        vector<Territory> myTerritories;
        vector<Continent> myContinents;	

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

#endif
