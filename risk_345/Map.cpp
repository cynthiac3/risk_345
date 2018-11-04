
/*
        file:Map.cpp
*/
#include <string>
#include <vector>
#include <algorithm> 
#include <iostream>

#include ".\Player.h"
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

//return true if a player owns all territories 
bool Map::isOwnBy(Player *p){ 
	return mapG.isOwnBy(p);
} 
		
//Set the nb of army  on a territoriy
void Map::setNbArmies(vertex v, int nbOfA){
	mapG.setNbArmies(v, nbOfA);
}	

//return the nb of contrie of a territory
int Map::getNbofArmies(vertex v){
	return mapG.getNbofArmies(v);
}
			
//set the owner of a territory	
void Map::setOwner(vertex v, Player *p){
	mapG.setOwner(v,p);
}

//return the owner of a vertex
Player* Map::getOwner(vertex v){
	return mapG.getOwner(v);
}

vector<vertex*> Map::getNbr(vertex v){
	return mapG.getNbr(v);
}

//testing 

void Map::setwinner(Player *p){
	mapG.setAll(p);
}


//driver for the map
int main(){
	Map map;
	//map.printMap();
	
	Player p1; //creates player1
	
	map.setwinner(&p1); // set player winner 
	
	cout << map.isOwnBy(&p1) << endl; // check if player own the map (return true)

	Player p2;// creates 
	
	//making country A1 for testing on EB.map
	vector<string> nbr;
	nbr.push_back("a2");
	nbr.push_back("a4");
	nbr.push_back("a5");
	
	vertex country = {"a1", nbr, &p1, 1};
	
	//set the owner of country A1 to p2
	map.setOwner(country, &p2);
	
	cout << map.isOwnBy(&p1) << endl; // check if player two owns the map (return false since p2 owns 1 country)
	
	map.setNbArmies(country, 10); // set the nb of army of p2 on A1 to 10

	cout << map.getNbofArmies(country) << endl;
	
	vector<vertex*> nbr_ofp2; // vector of vertex of A1
	nbr_ofp2 = map.getNbr(country);
	
	for (vector<vertex*>::iterator i = nbr_ofp2.begin() ; i != nbr_ofp2.end(); ++i){
		cout << (*i)->name <<endl;
		
	}
}




