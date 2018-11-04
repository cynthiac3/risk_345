/*
	file: Map_CPNT.h
*/
#include <string>
#include <vector>
using namespace std;

#ifndef MAP_CPNT_H
#define MAP_CPNT_H

//Info
class Info{
	public:
		Info();//constructor
		void setAll(string Cauthor, string Cwarn, string Cwrap, string Cimage, string Cscroll);//setter
		void printInfo();//print Info
	private:
		string author; 
		string warn;
		string wrap;
		string image; 
		string scroll;	
};


//Territory
class Territory{
	public:
		// constructor
		Territory(){};
		Territory(string Cname, string Ccoord[2], string Cmotherland, vector<string> Cnbr_name);

		//getter
		string getName(){return name;};
		string getM(){return motherland;};
		vector<string> getNbr(){return nbr_name;};
		int getArmies() {return nbArmies;};

		//setter
		void setName(string str){name = str; };
		void setNbr(vector<string> n){nbr_name = n;};
		
	private:
		string name;	//name of territory
		string coord[2]; // (x,y) coordinate of pixel on the image of the map
		string motherland; //continent
		vector<string> nbr_name; // neighbours
		int nbArmies;
};

//Continent
class Continent{
	public:
		//constructor	
		Continent(string str, string B);
		
		//getter
		string getName(){return name;};
		string getBonus(){return bonus;};	
	private:
		string name;// name of continent
		string bonus;// continent bonus
};
	

#endif
