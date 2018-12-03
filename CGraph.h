/*
	file:C_Graph.h
*/
#pragma once

#include <string>
#include <vector>
#include ".\Map_CPNT.h"
#include ".\Player.h"

 
using namespace std;



	//edges of vertex
		struct edges{
                        vector<string> list_nbr; // list of neighbours
                };	
		
		//vertex of the graph
		struct vertex {
        	string name; // name of country 
			edges nbr; // edges of country
			Player *owner;
			int nbOfArmies;
			friend class Map;
		};

class Graph{
	public:
		//constructor
		Graph(){};
		Graph(vector<Territory> myT);
		
		//print
		void printGraph();
		//check if the nodes(vertex) are all connected
		bool isConnected();

		vector<Country*> getCountry();
		
		//set & get
		void update(vector<Country*> allC);
		bool isOwnBy(Player* p); //return true if a player owns all territories 
		void setNbArmies(vertex v, int nbOfA);	//Set the nb of army  on a territoriy
		int getNbofArmies(vertex v);	//return the nb of contrie of a territory
		void setOwner(vertex v, Player* p); //set the owner of a territory
		Player* getOwner(vertex v); //return the owner of a vertex
		
		vector<vertex*> getNbr(vertex v);// return a vector of neighbours
		
		vertex* getVertex(string name);//retrun a vertex by name 
		
		void setAll(Player *p);
		
		int getNbOfNode(){return nodes.size();};
		friend class Map;
		vector<vertex*> getNodes(){return nodes;}
		
		void steal(Player *t,Player *v);
		
		private:
		
		vector<vertex*> nodes; // list of vertex in the graph (does might not be connected)
		
};

//Subgraph of a graph
class Subgraph{
	public:
		//constructor
		Player* getOwner(Graph * map);
		Subgraph(vector<Territory> myT, _Continent myC);
		//print Subgraph
		//void printSubG(){ cout << "\n\nSUB "; subG.printGraph();};
		bool isConnected(){return subG.isConnected();};
		bool isOwnBy(Player *p){ return subG.isOwnBy(p);};
	private:
	
		Graph subG;//graph (being a sub graph of a other)	
};


