/*
	file:Map.h
*/
#include <vector>
#include ".\CGraph.h"
#include ".\Map_loader.h"
 
using namespace std;

#ifndef MAP_H
#define MAP_H

class Map{
	public:
		//constructor
		Map();
		
		//print
		void printMap();
		
		//check if connected.

	private:	
		Graph mapG;
		vector<Subgraph> continents;
};

#endif
