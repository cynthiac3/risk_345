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
		Info();
		void setAll(string Cauthor, string Cwarn, string Cwrap, string Cimage, string Cscroll);
		void printInfo();
	private:
		string author; 
		string warn;
		string wrap;
		string image; 
		string scroll;	
};


class Territory{
	public:
		Territory(string Cname, string Ccoord[2], string Cmotherland, vector<string> Cnbr_name);
		string getName(){return name;};
		void printTerritory();	
	private:
		string name;
		string coord[2]; // (x,y) coordinate of pixel on the image of the map
		string motherland; //continent
		vector<string> nbr_name;
};

class Continent{
	public:
		void printContinent();
		Continent(string str, string B);
		string getName(){return name;};
		string getBonus(){return bonus;};	
				

	private:
		string name;
		string bonus;
};
	

#endif


