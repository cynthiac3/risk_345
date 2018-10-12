/*
	file: Map_CPNT.h
*/
#include <string>
#include <vector>
using namespace std;

#ifndef MAP_CPNT_H
#define MAP_CPNT_H

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
		Territory(){};
		Territory(string Cname, string Ccoord[2], string Cmotherland, vector<string> Cnbr_name);
		string getName(){return name;};
		void setName(string str){name = str; };
		vector<string> getNbr(){return nbr_name;};
		void setNbr(vector<string> n){nbr_name = n;};
		void printTerritory();
		string getM(){return motherland;};	
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


