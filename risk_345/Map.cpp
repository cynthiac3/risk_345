
/*
        file:Map.cpp
*/
#include <string>
#include <vector>
#include <algorithm> 
#include <iostream>
#include ".\CGraph.h"
#include ".\Map_CPNT.h"
#include ".\Map_loader.h"
#include ".\Map.h"

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
	for (vector<Continent>::iterator i = m.myContinents.begin() ; i != m.myContinents.end(); ++i){
		continents.push_back(Subgraph(m.myTerritories, (*i)));
	}
	
}

//print the map
void Map::printMap(){
	cout << "\n\nConnected: " << mapG.isConnected() <<endl;
	mapG.printGraph();
	for (vector<Subgraph>::iterator i = continents.begin(); i != continents.end(); ++i){
		cout << "\n\nConnected: " << (*i).isConnected();
		i->printSubG();
	} 
}




//driver for the map
int main(){
	Map map;
	map.printMap();

}


