/*
	file:Map.h
*/
#include <vector>

#include ".\Player.h"
#include ".\CGraph.h"
#include ".\Map_CPNT.h"
#include ".\Map_loader.h"


 
using namespace std;

#ifndef MAP_H
#define MAP_H

class Map{
	public:
			//edges of vertex
		
	
	
	
		//constructor
		Map();
		
		//print
		void printMap();
		
	
		bool isOwnBy(Player *p); //return true if a player owns all territories 
		
		
		void setNbArmies(vertex v, int nbOfA);	//Set the nb of army  on a territoriy
		int getNbofArmies(vertex v);	//return the nb of contrie of a territory
			
		
		void setOwner(vertex v, Player *p); //set the owner of a territory
		Player* getOwner(vertex v); //return the owner of a vertex
		
		vector<vertex*> getNbr(vertex v);// return list of neighbours
	
		
		//testing 
		void setwinner(Player *p);
		
		
		
	private:	
		Graph mapG;
		vector<Subgraph> continents;
};

#endif
