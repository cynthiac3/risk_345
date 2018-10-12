#include <string>
#include <vector>
#include ".\Map_CPNT.h"
#include <iostream>
using namespace std;

Info::Info(){
	author = "unkown";
	warn = "false";
	wrap = "false";
	image = "no-image";
	scroll = "unkown";	
}

void Info::setAll(string Cauthor, string Cwarn, string Cwrap, string Cimage, string Cscroll){
	author = Cauthor;
	warn = Cwarn;
	wrap = Cwrap;
	image = Cimage;
	scroll = Cscroll; 
}

void Info::printInfo(){
	cout << "INFO:"<< endl;
	cout << "\tAuthor: " << author << endl;
	cout << "\twarn: " << warn << endl;
	cout << "\twrap: " << wrap << endl;
	cout << "\timage: " << image << endl;
	cout << "\tscroll: "<< scroll <<endl; 
}

void Territory::printTerritory(){
	cout << "TERRITORY:" << endl;
	cout << "\tname: " << name << endl;
	cout << "\tcoord x,y : "<< coord[0] << "," << coord[1] << endl;
	cout << "\tmotherland: "<< motherland << endl;
	cout << "\tneighbours: " << endl;
	for (vector<string>::iterator i = nbr_name.begin() ; i != nbr_name.end(); ++i){
		cout << "\t\t" << *i << endl;
	}
}

void Continent::printContinent(){
	cout << "CONTINENT" << endl;
	cout << "\tname: " << name  << endl;
	cout << "\tbonus: " << bonus << endl;
}

Territory::Territory(string Cname, string Ccoord[2], string Cmotherland, vector<string> Cnbr_name){
	name = Cname;
	coord[0] = Ccoord[0];
	coord[1] = Ccoord[1];
	motherland = Cmotherland;
	nbr_name = Cnbr_name;
}

Continent::Continent(string str, string B){
	name = str;
	bonus = B;
}

