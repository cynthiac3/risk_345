/*
	file:C_Graph.h
*/
#include <string>
#include <vector>
#include ".\Map_CPNT.h"
#include ".\Player.h"
 
using namespace std;

#ifndef CGRAPH_H
#define CGRAPH_H

class Graph{
	public:
		//constructor
		Graph(){};
		Graph(vector<Territory> myT);
		
		//print
		void printGraph();
		//check if the nodes(vertex) are all connected
		bool isConnected();
		

	private:
		//edges of vertex
		struct edges{
                        vector<string> list_nbr; // list of neighbours
                };		
		
		//vertex of the graph
		struct vertex {
        		string name; // name of country 
			edges nbr; // edges of country
			Player *owner;
		};

		vector<vertex*> nodes; // list of vertex in the graph (does might not be connected)
		
};

//Subgraph of a graph
class Subgraph{
	public:
		//constructor
		Subgraph(vector<Territory> myT, Continent myC);
		//print Subgraph
		void printSubG(){cout << "\n\nSUB "; subG.printGraph();};
		bool isConnected(){return subG.isConnected();}
	private:
		Graph subG;//graph (being a sub graph of a other)	
};


#endif
