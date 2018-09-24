/*
	file: Map_loader.h
*/
#include <ifstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <.\Map_CPNT.h>
using namespace std;
	
Info myInfo();
vector<Territory> myTerritories;
vector<Continent> myContinents;

string enum{
	Map = 0,
	Continents = 1,
	Territories = 2;	
}

string Map_loader::choose_file(){
	string str;
	cout << "Please enter the name of the map file in the current directory:" << endl;
	cin >> str;
	return str;	
}

void Map_loader::close_file(ifstream file){
	file.close();	
} 

ifstream Map_loader::read_file(string file_name){	
	string line;
	ifstream file (file_name);
	if (myfile.is_open()){
		cout << "\nThe map file was succesfully open" << endl;
	}else{
		cout << "\nAn error occured will oppening the file, program will terminat" << endl;
		exit(0);
 	}
	return file;
}


Info Map_loader::loadInfo(string var[5]){
	string author;
	bool warn;
	bool wrap;
	string image;
	string scroll;	

	for(int i = 0; i<5; i++){
		if(!var[i].substring(0,line.find("=")).compare("author")){
			author = var[i].substring(line.find("="),line.length()-1);
		}else if(!var[i].substring(0,line.find("=")).compare("warn")){
                        warn = var[i].substring(line.find("="),line.length()-1);
		}else if(!var[i].substring(0,line.find("=")).compare("wrap")){
                        wrap = var[i].substring(line.find("="),line.length()-1);
		}else if(!var[i].substring(0,line.find("=")).compare("image")){
                        image = var[i].substring(line.find("="),line.length()-1);
		}else if(!var[i].substring(0,line.find("=")).compare("scroll")){
                        scroll = var[i].substring(line.find("="),line.length()-1);
		}
	}
	myInfo setAll(author, warn, wrap, image, scroll);
}
Territory* Map_loader::loadTerritory(string line){
	string name;
	int coord[2];
	string motherland;	
	vector<string> nbr_name;
	
	int i =0;
	name = line.substring(i, line.find(",",i));
	i =  line.find(",",i)+1;

	coord[0] = line.substring(i, line.find(",",i+1)-i);
	i =  line.find(",",i)+1;
	
	coord[1] = line.substring(i, line.find(",",i+1)-i);
        i =  line.find(",",i)+1;	

	motherland = line.substring(i, line.find(",",i+1)-i);
        i =  line.find(",",i)+1;
	
	while ((line.find(",",i-1) != string::npos)){ // this condition doesnt hold
		nbr_name.push_back(line.substring(i, line.find(",",i+1)-I));
	}
	
}
Continent* Map_loader::loadContinet(string line){
	
}

Map_loader::parser(ifstream file){
	string field_type;
	string line; 
	bool field = false;
	string map_var[5];
	int i = 0;
	while ( getline (file,line) ){
		field = false;
		if((!line.front().compare("[")) && (!line.back().compare("]"))){
			field = true;
			}else{
				field = false;
			}
		if(field == true){
			field_type = line.substring(1, str.length()-2);
		}else{
			if(!field_type.compare("Map")){
				map_var[i++] = line;
			}else if(!field_type.compare("Continents")){
				 loadTerritory(line);
			}else if(!field_type.compare("Territories")){
				loadContinent(line);
			}
		}
		
	}
	loadInfo(map_var);
}


int main{
	ifstream file;
	file = read_file(choose_file());
	parser(file);
	
	close_file(file);

}

