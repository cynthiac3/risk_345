
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
	
//Constructor 
Graph::Graph(vector<Territory> myT){
	string name;
	for (vector<Territory>::iterator i = myT.begin() ; i != myT.end(); ++i){
		nodes.push_back(new vertex());
		nodes.back()->name = i->getName();
		nodes.back()->nbr.list_nbr = i->getNbr();
        }
}

//tester for the connected map (test if the map is actualy connected)
bool Graph::isConnected(){
	/*
		This algorithm work taking the first stored node and its edges and adding them 
		to the 'visited' list. Then for every other node, if the node it self 
		or any of it edges are containe in the visited list the node and its edges also
		added to the visited list.
	*/

	vector<string> visited;
	vector<string> list_nbr;	
	
	visited.push_back((*nodes.begin())->name);
	visited.insert(visited.end(), nodes[0]->nbr.list_nbr.begin(), nodes[0]->nbr.list_nbr.end());	

	for (vector<vertex*>::iterator z = nodes.begin() ; z != nodes.end(); ++z){
		for (vector<vertex*>::iterator i = nodes.begin() ; i != nodes.end(); ++i){
			list_nbr = (*i)->nbr.list_nbr;
			if(find(visited.begin(), visited.end(), (*i)->name) != visited.end()){
				visited.push_back((*i)->name);
				visited.insert(visited.end(), (*i)->nbr.list_nbr.begin(), (*i) ->nbr.list_nbr.end());
			}else{
				for (vector<string>::iterator k = list_nbr.begin() ; k != list_nbr.end(); ++k){
					if(find(visited.begin(), visited.end(), (*k))!= visited.end()){
						visited.push_back((*i)->name);
        	                		visited.insert(visited.end(), (*i)->nbr.list_nbr.begin(), (*i) ->nbr.list_nbr.end());
					}
				}
			}
			sort( visited.begin(), visited.end() );
			visited.erase( unique( visited.begin(), visited.end() ), visited.end() );
		}
	}
	if(visited.size() == nodes.size()){
		return true;
	}else{
		return false;
	}	
}

void Graph::printGraph(){
	for (vector<vertex*>::iterator i = nodes.begin() ; i != nodes.end(); ++i){
		cout << "Territory: " << (*i)->name << " Nbr:" << endl;
		for (vector<string>::iterator k = (*i)->nbr.list_nbr.begin() ; k != (*i)->nbr.list_nbr.end(); ++k){
			cout << "\t" << *k << endl;
        	}
        }	
}

Subgraph::Subgraph(vector<Territory> myT, Continent myC){
	vector<Territory> tmp_T;
	vector<string>	tmp_nbg;
	vector<string> it_nbg;
	
	for (vector<Territory>::iterator i = myT.begin() ; i != myT.end(); ++i){
		if(i->getM().compare(myC.getName()) == 0 ){
			tmp_T.push_back(Territory());
			tmp_T.back().setName(i->getName());
			it_nbg = i->getNbr();
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
	Graph G(tmp_T);
	subG = G;
}


