/*
	file: Map_loader.h
*/
#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include ".\Map_CPNT.cpp"
#include ".\Map_loader.h"
using namespace std;
	
Info myInfo;
vector<Territory> myTerritories;
vector<Continent> myContinents;


string Map_loader::choose_file(){
	string str;
	cout << "Please enter the name of the map file in the current directory:" << endl;
	cin >> str;
	return str;	
}

 
void Map_loader::loadInfo(string var[5]){
	string author;
	string warn;
	string wrap;
	string image;
	string scroll;	
	
	for(int i = 0; i<5; i++){
			
		if(!var[i].substr(0,var[i].find("=")).compare("author")){
			author = var[i].substr(var[i].find("=")+1,var[i].length()-1);

		}else if(!var[i].substr(0,var[i].find("=")).compare("warn")){
                        warn = var[i].substr(var[i].find("=")+1,var[i].length()-1);

		}else if(!var[i].substr(0,var[i].find("=")).compare("wrap")){
                        wrap = var[i].substr(var[i].find("=")+1,var[i].length()-1);

		}else if(!var[i].substr(0,var[i].find("=")).compare("image")){
                        image = var[i].substr(var[i].find("=")+1,var[i].length()-1);

		}else if(!var[i].substr(0,var[i].find("=")).compare("scroll")){
                        scroll = var[i].substr(var[i].find("=")+1,var[i].length()-1);
		}
	};
	myInfo.setAll(author, warn, wrap, image, scroll);
}

void Map_loader::loadTerritory(string line){
	string name;
	string coord[2];
	string motherland;	
	vector<string> nbr_name;
	
	int i =0;
	name = line.substr(i, line.find(",",i));
	i =  line.find(",",i)+1;
	
	coord[0] = line.substr(i, line.find(",",i+1)-i);
	i =  line.find(",",i)+1;
	
	coord[1] = line.substr(i, line.find(",",i+1)-i);
        i =  line.find(",",i)+1;	

	motherland = line.substr(i, line.find(",",i+1)-i);
        i =  line.find(",",i)+1;
	
	while ((line.find(",",i-1) != string::npos)){ 
		nbr_name.push_back(line.substr(i, line.find(",",i+1)-i));
		i =  line.find(",",i)+1;
	}

	myTerritories.push_back(Territory(name, coord, motherland, nbr_name));
}

void Map_loader::loadContinent(string line){
	string name;
	string bonus;

	name = line.substr(0, line.find("="));
	bonus = line.substr(line.find("=")+1);
	
	myContinents.push_back(Continent(name, bonus));
}

void Map_loader::parser(string file_name){
	string line;
	ifstream file;
	file.open(file_name);
	if (file.is_open()){
		cout << "\nThe map file was succesfully open" << endl;
	}else{
		cout << "\nAn error occured will oppening the file, program will terminat" << endl;
		exit(0);
 	}
	
	string field_type;
	bool field = false;
	string map_var[5];
	int i = 0;
	int x = 0;
	while ( getline (file,line) ){
		if(!line.empty()){
		field = false;
		if((!line.substr(0,1).compare("[")) && (!line.substr(line.length()-1).compare("]"))){
			field = true;
			}else{
				field = false;
			}
		if(field == true){
			field_type = line.substr(1, line.length()-2);
		}else{
			if(!field_type.compare("Map")){
				if(5>x++)map_var[i++] = line;
			}else if(!field_type.compare("Continents")){
				loadContinent(line);
			}else if(!field_type.compare("Territories")){
				loadTerritory(line);
			}
		}
		}
	}
	loadInfo(map_var);
	file.close();
}


int main(){
	Map_loader Ml;
	Ml.parser(Ml.choose_file());
	myInfo.printInfo();
	myTerritories[12].printTerritory();
	myContinents[3].printContinent();
}
