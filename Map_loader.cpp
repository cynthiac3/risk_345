/*
	file: Map_loader.h
*/
	
#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include ".\Map_loader.h"
#include ".\Map_CPNT.h"
#include ".\CGraph.h"
using namespace std;
	

//Prompt for the map file to load
string Map_loader::choose_file(){
	string str;
	cout << "Please enter the name of the map file in the current directory:" << endl;
	cin >> str;
	return str;	
}

//load information of the map
void Map_loader::loadInfo(string lines[5]){
	//variable of the Info class  
	string author; 
	string warn;
	string wrap;
	string image;
	string scroll;
	
	
	try{

		//parser to retrieve the imformation from the txt line
		for(int i = 0; i<5; i++){
			//retrive author
			if(!lines[i].substr(0,lines[i].find("=")).compare("author")){
				author = lines[i].substr(lines[i].find("=")+1,lines[i].length()-1);
			//retrive warn value
			}else if(!lines[i].substr(0,lines[i].find("=")).compare("warn")){
        	                warn = lines[i].substr(lines[i].find("=")+1,lines[i].length()-1);
			//retrive wrap value
			}else if(!lines[i].substr(0,lines[i].find("=")).compare("wrap")){
        	                wrap = lines[i].substr(lines[i].find("=")+1,lines[i].length()-1);
			//retrive image path
			}else if(!lines[i].substr(0,lines[i].find("=")).compare("image")){
        	                image = lines[i].substr(lines[i].find("=")+1,lines[i].length()-1);
			//retrive scroll value
			}else if(!lines[i].substr(0,lines[i].find("=")).compare("scroll")){
        	                scroll = lines[i].substr(lines[i].find("=")+1,lines[i].length()-1);
			}
		}
	}catch (...){
                cout<< "invalid Map declaration, program will terminat" << endl;
                exit(0);
        }
	//set the map info variables
	myInfo.setAll(author, warn, wrap, image, scroll);
}

//load a territory in the map_load vector of teritories
void Map_loader::loadTerritory(string line){
	string name; // name of territory
	string coord[2];	// pixel coord (of the  map image)  of the country 
	string motherland;//Continent which the belongs too 	
	vector<string> nbr_name;//list of the territory neighbours
	

	try{
	
		int i =0;// variable to store index in a string
		// retrive name
		name = line.substr(i, line.find(",",i));
		i =  line.find(",",i)+1;
		//retrive x coord
		coord[0] = line.substr(i, line.find(",",i+1)-i);
		i =  line.find(",",i)+1;
		//retrive y coord
		coord[1] = line.substr(i, line.find(",",i+1)-i);
	        i =  line.find(",",i)+1;	
		//retrive continent
		motherland = line.substr(i, line.find(",",i+1)-i);
	        i =  line.find(",",i)+1;
		//retrive neighbours
		if ((line.find(",",i-1) == string::npos)){throw 1;}
		while ((line.find(",",i-1) != string::npos)){ 
			nbr_name.push_back(line.substr(i, line.find(",",i+1)-i));
			i =  line.find(",",i)+1;
		}
	}catch (...){
		cout<< "invalid Territory declaration, program will terminat" << endl;
                exit(0);
  	}
	
	//push a new territory to the vector of territories
	myTerritories.push_back(Territory(name, coord, motherland, nbr_name));
}

//load a continent in the vector of Continents
void Map_loader::loadContinent(string line){
	string name;//name of the continent
	string bonus;//bonus of the contient
	
	if(line.find("=")==string::npos ){
                cout<< "invalid Continent declaration, program will terminat" << endl;
                exit(0);
        }

	//retrieve the name
	name = line.substr(0, line.find("="));
	//retrieve the bonus
	bonus = line.substr(line.find("=")+1);
	
	//push the continent to the vector of Continents
	myContinents.push_back(_Continent(name, bonus));
}

//parse the map file line by line, take a file name frome the current directory
void Map_loader::parser(string file_name){
	string line;//current line being read 
	ifstream file; //ifstream object for file reading
	
	//opening the file
	file.open(file_name);
	//checkingif file is open 
	if (file.is_open()){
		cout << "\nThe map file was succesfully open" << endl;
	}else{
		cout << "\nAn error occured while oppening the file, program will terminat" << endl;
		exit(0);
 	}
	

	string field_type; //string to store the filed_type (info, contient and territory)
	bool field = false; //bool use when checking if a line is a field header
	string map_info[5];// string to store the line when the info field is strigger
	int i = 0;// integer use in line counting 
	int x = 0;// integer use in line counting

	bool info_loaded = false; // boolean to check if map map info are loaded 
	bool continent_loaded = false; // boolean to check if continent are loaded
	bool territory_loaded = false; // boolean to check ig the territory are loaded  

	while ( getline (file,line) ){
		if(!line.empty()){//skip empty line
		field = false;
		//field detector
		if((!line.substr(0,1).compare("[")) && (!line.substr(line.length()-1).compare("]"))){
			field = true;
			}else{
				field = false;
			}
		//if field was found set the field type
		if(field == true){	
			field_type = line.substr(1, line.length()-2);
		}else{
			//check the filed type
			if(!field_type.compare("Map")){	// get the lines with the map info
				if(5>x++)map_info[i++] = line;
				info_loaded = true;
			}else if(!field_type.compare("Continents")){ // get a continent info 
				loadContinent(line);// send the line to the continent loader
				continent_loaded = true;
			}else if(!field_type.compare("Territories")){// get a territory info
				loadTerritory(line);// send the line to the territory loader
				territory_loaded = true;
			}
		}
		}
	}
	
	//check if all the field where loaded
	if(!(territory_loaded && continent_loaded && info_loaded)){
		cout << "\nInvalid map missing field, program will terminat" << endl;
                exit(0);	
	}

				
	loadInfo(map_info);//loads information
	file.close();// close the file
	map_loaded = Graph(myTerritories);
	
	
}


