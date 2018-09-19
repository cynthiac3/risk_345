/*
	file: Map_CPNT.h
*/
#include <string>
#include <vector>
using namespace std;

#ifndef MAPC_H
#define MAPC_H

class Info{
	public:
		Info(string Cauthor = "unknown", bool Cwarn = false, bool Cwrap = false, string Cimage = "no-image", string Cscroll = "none");
		string getAuthor();
	private:
		string author; 
		bool warn;
		bool wrap;
		string image; 
		string scroll;	
};


class Territorie{
	public:
		Territorie(string name, int coord[2],int nb_nbr, string motherland);
		string getName(){return name;};
		
	private:
		int nb_nbr;
		string name;
		int coord[2]; // (x,y) coordinate of pixel on the image of the map
		string motherland; //continent
		vector<Territorie*> nbr;
};

class Continent{
	public:
		Continent(string str, int B);
		string getName(){return name;};
		int getBonus(){return bonus;};	
				

	private:
		string name;
		int bonus;
		vector<Territorie*> ptr; // pointer towards her territories		
}; 

#endif


