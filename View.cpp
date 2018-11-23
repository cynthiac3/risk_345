
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#include "View.h"
#include "Map.h"
#include "TextTable.h" //imported library that build table

 
using namespace std;

//default constructor for the View
View::View(){};

//parameter construct for the View
View::View(Map *s){
	_subject = s;
	_subject->Attach(this);	
	
	system("start logger.exe");
	
};

//destructor for the view
View::~View(){
	//close the logger use to display data on the Second Screen
	system("taskkill -im logger.exe -f");
}

//Update the talbe 
void View::Update(){
	display();	//display the table 
}

void View::display(){

	int nbOfCountry = 0; //int to store the number of country
	int country[6] = {0,0,0,0,0,0}; //array to store the current number of country own by each palyer 
	int armies[6] = {0,0,0,0,0,0};//array to store the current number of armies own by each palyer 
	int nbOfplayer = 1; //array to store the number of player 

	string player[6] {"_","_","_","_","_","_"}; //array of string to store the number of player 
	bool Notplace; //bool use to check if a player as already been place in the array
	bool complete = false;	//bool use to check if the max number of player as been reach

	vector<vertex*> info = _subject->getNodes();//get the map data
	
	player[0] = (*info.begin())->owner->getName(); //set player one as the first player in the map data 

	//algorithm use to extract the data from the vector of vertex
	for (vector<vertex*>::iterator i = info.begin() ; i != info.end(); ++i){
		Notplace = true;
                nbOfCountry++;
		for(int j =0; j <= nbOfplayer; j++){ //update number of army and country of a palyer after reading the country 
			if( player[j].compare((*i)->owner->getName()) == 0){
				Notplace = false;
				armies[j] += (*i)->nbOfArmies;
				country[j] += 1;
			}else{ // update and set player that havent been add to the player array yet 
				if((Notplace) && (player[j].compare("_") == 0)){
					Notplace = false;
					if(nbOfplayer <5 ){ nbOfplayer++;}else{ complete = true; }
					player[j] = (*i)->owner->getName();
					armies[j] += (*i)->nbOfArmies;
                    country[j] += 1;
				}
			}
		}

	}

	//instantiate  the talbe 
	TextTable t( '-', '|', '+' );	

	//add the to row (label) of the table 
    t.add( "Player" );
    t.add( "percentage of the world" );
	t.add( "Number of countries" );
    t.add( "Number of armies" );
	t.endOfRow();

	if(!complete)nbOfplayer--;
	
	// for each palyer adds a row to the table with the updated information about them
	for(int i = 0; i <= nbOfplayer; i++){
		double perc = ((double)country[i]/(double)nbOfCountry);
		t.add(player[i]);
        	t.add(to_string(perc));
		t.add(to_string(country[i]));
        	t.add(to_string(armies[i]));			
		t.endOfRow();
	
	}
	
	//alligne the table for printing 
	t.setAlignment( 2, TextTable::Alignment::RIGHT );
	
	//make a string stream to store the table
	stringstream strs;
	//store the table in the string stream
	strs << t;
	
	//update the log file so that the information get updated on the second screen
	ofstream logFile;
	logFile.open("./log.txt");
	logFile << strs.rdbuf();
	logFile << "\nTotal number of Country: " << nbOfCountry << endl;
	
	if(nbOfplayer == 0){
		logFile << "\n\nCONGRATULATION YOU HAVE WON THE GAME :" << player[0]<< endl;	
	}
	
	logFile.close();
}









