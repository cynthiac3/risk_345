
/*
        file:Map.cpp
*/
#include <string>
#include <vector>
#include <algorithm> 
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include ".\Player.h"
#include ".\Map.h"
#include ".\Deck.h"

using namespace std;
	
Map::Map(){
	//call the map loaded to load a map file.
	Map_loader m;
	
	m.parser(m.choose_file());
	//check if map is valid, verify that a territory is loaded only once
	for (vector<Territory>::iterator k  = m.myTerritories.begin() ; k != m.myTerritories.end(); ++k){
		for (vector<Territory>::iterator j  = m.myTerritories.begin() ; j != m.myTerritories.end(); ++j){
			//exit if a territory is already loaded 
			if((k->getName().compare(j->getName()) == 0)&& (k != j) ){
				cout << "Territory " << j->getName()<<" already exist, the map is invalid, program will terminate"<< endl;
				exit(0);
			}
		}
	}

	// set the map graph	
	mapG = m.map_loaded;
	
	// check if the map is connected and terminate if not
	if(!mapG.isConnected()){
		cout << "The map is not connected, program will terminat" <<endl;
		exit(0); 
        }
	
	//make the continent subgraph
	for (vector<_Continent>::iterator i = m.myContinents.begin() ; i != m.myContinents.end(); ++i){
		continents_name.push_back((*i).getName());
		continents.push_back(Subgraph(m.myTerritories, (*i)));
	}
	
}

//print the map
void Map::printMap(){
	cout << "\n\nConnected: " << mapG.isConnected() <<endl;
	mapG.printGraph();
	//for (vector<Subgraph>::iterator i = continents.begin(); i != continents.end(); ++i){
	//	cout << "\n\nConnected: " << (*i).isConnected();
	//	i->printSubG();
	//} 
}


vector<Country*> Map::getCountry(){
	return mapG.getCountry();
}

//return true if a player owns all territories 
bool Map::isOwnBy(Player *p){ 
	return mapG.isOwnBy(p);
} 
		
//Set the nb of army  on a territoriy
void Map::setNbArmies(vertex v, int nbOfA){
	mapG.setNbArmies(v, nbOfA);
	Notify();
}	

//return the nb of contrie of a territory
int Map::getNbofArmies(vertex v){
	return mapG.getNbofArmies(v);
}
			
//set the owner of a territory	
void Map::setOwner(vertex v, Player *p){
	mapG.setOwner(v,p);
	Notify();
}

//return the owner of a vertex
Player* Map::getOwner(vertex v){
	return mapG.getOwner(v);
}

//get the neighbours of a vertex
vector<vertex*> Map::getNbr(vertex v){
	return mapG.getNbr(v);
}

vertex* Map::getVertex(string name){
	return mapG.getVertex(name);
}



void Map::setwinner(Player *p){
	mapG.setAll(p);
	Notify();
}

void Map::steal(Player *t, Player *v){
	mapG.steal(t,v);
	Notify();
}

bool Map::isContOwnBy(string cont_name, Player *p){
	int index = -1;
	for(int i = 0; i < continents_name.size(); i++){
		if(cont_name.compare(continents_name[i]) == 0){
			index = i;
		}
	}
	
	if(index  == -1){
		return false;
	}else{
		return continents[index].isOwnBy(p);
	}
}


//driver for the map




