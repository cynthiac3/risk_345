
/*
        file:C_Graph.h
*/
#include <string>
#include <vector>
#include <algorithm> 
#include <iostream>
#include ".\CGraph.h"
#include ".\Map_CPNT.h"


using namespace std;
	
//Constructor, takes the vector of territories genereted by the map loader
Graph::Graph(vector<Territory> myT){
	//iterate trough the vector of terrytory constructed by the map_load and generates a graph
	for (vector<Territory>::iterator i = myT.begin() ; i != myT.end(); ++i){
		nodes.push_back(new vertex());// creats a new vertex
		nodes.back()->name = i->getName(); // set the name
		nodes.back()->nbr.list_nbr = i->getNbr();// set its neighbours
        }
}

//tester for the connected map (test if the map is actualy connected)
bool Graph::isConnected(){
	/*
		This algorithm work taking the first stored node and its edges and adding them 
		to the 'visited' list. Then for every other node, if the node it self 
		or any of it edges are containe in the visited list the node and its edges also
		added to the visited list. This verification of the tail need to happen n*n times
		to make sure every path possible are loaded.
	*/

	vector<string> visited; // list of visited nodes
	vector<string> edges; // list of currently check edges  
		
	//adding the first node and it edges to the visited list
	visited.push_back((*nodes.begin())->name);
	visited.insert(visited.end(), nodes[0]->nbr.list_nbr.begin(), nodes[0]->nbr.list_nbr.end());	

	//nested loop of every node for every node since the algorithm need to be run N*N times
	for (vector<vertex*>::iterator z = nodes.begin() ; z != nodes.end(); ++z){ // for every node
		for (vector<vertex*>::iterator i = nodes.begin() ; i != nodes.end(); ++i){ // for every node
			
			edges = (*i)->nbr.list_nbr;//set the current list of edges in function of the current node being check
			
			//If the node it self as been visited, then it its push as well as its egdes to the visited list
			if(find(visited.begin(), visited.end(), (*i)->name) != visited.end()){
				visited.push_back((*i)->name); // push the name of the node to the visited list 
				visited.insert(visited.end(), (*i)->nbr.list_nbr.begin(), (*i)->nbr.list_nbr.end()); //append the edges of the node to the visited list
			}else{
			// check if one of its edges are in the visited list
				for (vector<string>::iterator k = edges.begin() ; k != edges.end(); ++k){
					if(find(visited.begin(), visited.end(), (*k))!= visited.end()){
						visited.push_back((*i)->name);// push the name of the node to the visited list
        	                		visited.insert(visited.end(), (*i)->nbr.list_nbr.begin(), (*i)->nbr.list_nbr.end());//append the edges of the node to the visited list
					}
				}
			}
			sort( visited.begin(), visited.end() ); // sort the visited list
			visited.erase( unique( visited.begin(), visited.end() ), visited.end() ); // deleted duplicate that have form
		}
	}
	//check result of the algorithm 
	//if the Graph is indeed a connected graph, the visited list will be of the same size of the actual number of nodes in the graph
	if(visited.size() == nodes.size()){
		return true;
	}else{
		return false;
	}	
}

//Check if the map is owned  by a player 
bool Graph::isOwnBy(Player *p){

	for (vector<vertex*>::iterator i = nodes.begin() ; i != nodes.end(); ++i){
		if ( (*i)->owner != p ) return false;
	}
	return true;
}

//Set the nb of army  on a territoriy
void Graph::setNbArmies(vertex v, int nbOfA){
	for (vector<vertex*>::iterator i = nodes.begin() ; i != nodes.end(); ++i){
		if ( (*i)->name.compare(v.name) == 0 ){
			(*i)->nbOfArmies = nbOfA;
		}
	}
				
}	//Set the nb of army  on a territoriy
int Graph::getNbofArmies(vertex v){
	for (vector<vertex*>::iterator i = nodes.begin() ; i != nodes.end(); ++i){
		if ( (*i)->name.compare(v.name) == 0 ){
			return (*i)->nbOfArmies;
		}
	}
}

//set the owner of a territory
void Graph::setOwner(vertex v, Player *p){
	for (vector<vertex*>::iterator i = nodes.begin() ; i != nodes.end(); ++i){
		if ( (*i)->name.compare(v.name) == 0 ){
			(*i)->owner = p;
		}
	}
}
//return the owner of a vertex
Player* Graph::getOwner(vertex v){
	for (vector<vertex*>::iterator i = nodes.begin() ; i != nodes.end(); ++i){
		if ( (*i)->name.compare(v.name) == 0 ){
			return v.owner;
		}
	}
}

vector<vertex*> Graph::getNbr(vertex v){
	vector<vertex*> itsNBR;
			
			for (vector<string>::iterator j = v.nbr.list_nbr.begin() ; j != v.nbr.list_nbr.end(); ++j){
				
				for (vector<vertex*>::iterator i = nodes.begin() ; i != nodes.end(); ++i){
					if ( (*i)->name.compare((*j)) == 0 ){
						itsNBR.push_back(*i);
					}
				}
			}
	
	return itsNBR;
}
		

//simple function to print the Connected graph
void Graph::printGraph(){
	cout << "GRAPH: \n\n" << endl;//Print the header 

	for (vector<vertex*>::iterator i = nodes.begin() ; i != nodes.end(); ++i){
		cout << "\tTERITORY: " << (*i)->name << " NEIGHBOURS:" << endl; // print the country
		//print its neighbours
		for (vector<string>::iterator k = (*i)->nbr.list_nbr.begin() ; k != (*i)->nbr.list_nbr.end(); ++k){
			cout << "\t\t" << *k << endl;
        	}
        }	
}


//stesting
void Graph::setAll(Player *p){
	for (vector<vertex*>::iterator i = nodes.begin() ; i != nodes.end(); ++i){
		(*i)->owner = p;
		(*i)->nbOfArmies = 1;
	}
}


//creates a sub graph. takes in the vector of territory and the continent for which the subgraph is being created 
Subgraph::Subgraph(vector<Territory> myT, Continent myC){
	vector<Territory> tmp_T;//temporal vector for a the territories
	vector<string>	tmp_nbg;//temporal vector for the neighbour
	vector<string> it_nbg; //vector for the neighbour being iterate
	
	//iterat throught the territory
	for (vector<Territory>::iterator i = myT.begin() ; i != myT.end(); ++i){
		if(i->getM().compare(myC.getName()) == 0 ){ //check if the territory being check belongs to the continent
			//if it does belong to the continent it the node is added to the graph
			tmp_T.push_back(Territory());
			tmp_T.back().setName(i->getName());
			it_nbg = i->getNbr();
			//then is neighbours are check and only does that also bolongs to the continent are added as neighbours
			for (vector<string>::iterator k = it_nbg.begin(); k != it_nbg.end(); ++k){
				for (vector<Territory>::iterator j = myT.begin() ; j != myT.end(); ++j){	
					if(((*k).compare(j->getName()) == 0) && (j->getM().compare(myC.getName()) == 0)){
						tmp_nbg.push_back((*k));
						break;
					}
				}		
			}
			tmp_T.back().setNbr(tmp_nbg);
			tmp_nbg.clear(); 
		}
	}
	// a graph is created (being a subgraph of the original set)
	Graph G(tmp_T);
	subG = G;
}


