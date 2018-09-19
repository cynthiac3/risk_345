/*
	file:C_Graph.h
*/
#include <string>
#include <vector>
#include ".\Map_CPNT.h"
 
using namespace std;

#ifndef MAPC_H
#define MAPC_H

class graph{
	public:
		graph();
		// more will the added when the .cpp class is implimented
		getNb_vertices();
		Territorie* getVertices();// retrieve vertices by name 
		vector<vertex*> getEdges(string vertex_name); 
		boolean isConnected(string vertex_name, vertex_name);
	protected:
		struct vertex {
        	Territorie *node; 
			edges nbr;
		};

		struct edges{
			vector<vertex*> edges_connection; // the vector to sotre [pointers] towards neighbouring territory. 
		};

	private:
		int nb_vertices; 
		vertex<Territorie> (*vertices)[nb_vertices] = NULL;
};

class subgraph: public graph{
	public:
		subgraph(graph* mainGraph, vector<vertex*> sub_vertices, vector<edges*> sub_edges);
	private:
		string name;
		graph sub_G;
}

class Map : public Info : public Territorie : public Continent : public graph : public subgraph{
	public:
		Map();
	private:
		
};

#endif
