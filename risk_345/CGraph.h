/*
	file:C_Graph.h
*/
#include <string>
#include <vector>
#include ".\Map_CPNT.h"
 
using namespace std;

#ifndef CGRAPH_H
#define CGRAPH_H

class Graph{
	public:
		Graph(){};
		Graph(vector<Territory> myT);
		void printGraph();
		bool isConnected();
		// more will the added when the .cpp class is implimented
	private:
		struct edges{
                        vector<string> list_nbr;
                };		

		struct vertex {
        		string name; 
			edges nbr;
		};

		vector<vertex*> nodes;
		void pushEdges(edges *head, vertex *nbr);
		
};

class Subgraph{
	public:
		Subgraph(vector<Territory> myT, Continent myC);
		void printSubG(){subG.printGraph();};
	private:
		Graph subG;	
};


#endif
