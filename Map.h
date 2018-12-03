/*
	file:Map.h
*/
#pragma once


#include <vector>

#include "Subject.h"
#include ".\Player.h"
#include ".\CGraph.h"
#include ".\Map_CPNT.h"
#include ".\Map_loader.h"


 
using namespace std;



class Map : public Subject {
	public:
			//edges of vertex
		
	
	
	
		//constructor
		Map();
		
		//print
		void printMap();
		
	
		bool isOwnBy(Player *p); //return true if a player owns all territories 
		
		void update(vector<Country*> allC);
		void setNbArmies(vertex v, int nbOfA);	//Set the nb of army  on a territoriy
		int getNbofArmies(vertex v);	//return the nb of army of a territory
			
		vertex* getVertex(string name);
		
		void setOwner(vertex v, Player *p); //set the owner of a territory
		Player* getOwner(vertex v); //return the owner of a vertex
		
		vector<vertex*> getNbr(vertex v);// return list of neighbours
		
		bool isContOwnBy(string cont_name, Player *p);
		
		//testing 
		void setwinner(Player *p);
		void steal(Player *t,Player *v);
		
		vector<Country*> getCountry();
		vector<Continent*> getContinent();
		
		int getNbOfT(){ return mapG.getNbOfNode();}
		vector<string> getContName(){return continents_name;};
		vector<vertex*> getNodes(){return mapG.getNodes();};
		
	private:	
		Graph mapG;
		vector<Subgraph> continents;
		vector<string> continents_name;
		vector<int> continents_bonus;
};

