#include <string>
#include <vector>
#include ".\Map_CPNT.h"
#include <iostream>
using namespace std;

//Info constructor 
Info::Info(){
	author = "unkown";
	warn = "false";
	wrap = "false";
	image = "no-image";
	scroll = "unkown";	
}

//set Info
void Info::setAll(string Cauthor, string Cwarn, string Cwrap, string Cimage, string Cscroll){
	author = Cauthor;
	warn = Cwarn;
	wrap = Cwrap;
	image = Cimage;
	scroll = Cscroll; 
}

//print info
void Info::printInfo(){
	cout << "INFO:"<< endl;
	cout << "\tAuthor: " << author << endl;
	cout << "\twarn: " << warn << endl;
	cout << "\twrap: " << wrap << endl;
	cout << "\timage: " << image << endl;
	cout << "\tscroll: "<< scroll <<endl; 
}

//Territory constructor
Territory::Territory(string Cname, string Ccoord[2], string Cmotherland, vector<string> Cnbr_name){
	name = Cname;
	coord[0] = Ccoord[0];
	coord[1] = Ccoord[1];
	motherland = Cmotherland;
	nbr_name = Cnbr_name;
	nbArmies = 0;
}

//Continent constructor
Continent::Continent(string str, string B){
	name = str;
	bonus = B;
}
