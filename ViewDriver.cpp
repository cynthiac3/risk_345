
/*
        file:Map.cpp
*/
#include <string>
#include <vector>
#include <algorithm> 
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "View.h"
#include ".\Player.h"
#include ".\Map.h"
#include ".\Deck.h"

using namespace std;
	

//driver for the map
/*
int main(){
	//creats a map 
	Map map;
	
	int nbPlayer; // int to store the number of players
	bool invalid = true; // boolean use for validation
	

	vector<vertex*> tmp_nodes = map.getNodes(); // list of territories to assign a them a owners

	
	nbPlayer = 2;
	
	Player player[nbPlayer]; // array of players 
	string tmp_name; //temporal variable to sotre a name
	int order_of_play[nbPlayer];//store the order of play (each index owns a unique index(refference) to the player array)
	int tmp_int=0; // temporal integer use to store a state 
	
		
	srand (time(NULL)); //random input 
	int rindex; //varialbe to store a random index 
	int tmp_arr[nbPlayer]; // Temproal array to sotre index of palyers
	
	//read the name of each player and assign it to them
	for(int i = 0; i < nbPlayer; i++){
		cout << "type the name of player " << i+1 << endl;
		cin >> tmp_name;
		player[i].setName(tmp_name);
	}
	
	
	
	Deck gameDeck;
	gameDeck.fillDeck(42);

	// Create new players in a vector
	for (int i = 0; i < nbPlayer; i++) {
		player[i].setHand(&gameDeck); // assign a hand of cards
	}
	
	
	
	//assign randomly contries to player in a round-robin fashion for the players
	// each player are assign to country randomly until all players have at least a coutry, then the process is repeted
	//making sure that the number of country that each players gets if equal
	for (vector<vertex*>::iterator i = tmp_nodes.begin() ; i != tmp_nodes.end(); ++i){
		do{//check if a certain player as already gone trough thi assignment round
			rindex = rand() % nbPlayer;
		}while((tmp_arr[rindex] == 1)&& !(tmp_arr[rindex] == 0));
		
		
		map.setOwner((**i), &player[rindex]); //set the owner of the current territory 
		tmp_arr[rindex] = 1; //instruct that the player x a pass is turn in that round
		tmp_int++; //increment the temporal varial use to check if all player have pass, meaning that the current round is over
	
		//if the current round is over, it resets to a new round
		if(tmp_int == nbPlayer){
			for(int i =0; i< nbPlayer; i++)tmp_arr[i] =0;
			tmp_int =0;
		}
	}
	
	
	//generate a random order_of_play 
	
	for(int i =0; i< nbPlayer; i++)tmp_arr[i] =-1;//set the temporal array to  -1 
	
	invalid = true;// reset invalid to true
	
	//generate a random order of play
	for(int i =0; i< nbPlayer; i++){
		invalid = true;
		do{
			rindex = rand() % nbPlayer;	//generate a random index 
			if(tmp_arr[i] == -1){ //check id the location available 
				invalid = false;
				for(int j =0; j<nbPlayer; j++){
					if(tmp_arr[j] == rindex)invalid = true;
				}
			}
			
		}while(invalid);
		tmp_arr[i] = rindex;
		order_of_play[i] = rindex;
	}

	
	
	map.printMap();
	
	View *table = new View(&map);
	
	int NumberOfamry;
	//switch to check the nb of army in function of the number of player
	switch(nbPlayer){
		case 2:
			NumberOfamry =  2;
			break;
		case 3: 
			NumberOfamry = 2;
			break;
		case 4:
			NumberOfamry = 2;
			break;
		case 5:
			NumberOfamry = 2;
			break;
		case 6:
			NumberOfamry = 2;
			break;
	}
	
	
	invalid = true;//reset invalid to true 
	
	//in a  round-robin fashion each player place a army on territories they owns 
	do{
		for(int i = 0; i < nbPlayer; i++){
			cout << player[order_of_play[i]].getName() << " type your territoriy that you wish to place an army on: " << endl;
			while(invalid){
				cin >> tmp_name;
			if (map.getVertex(tmp_name) == NULL){// check if the territories exist 
				cout << "This territory doesnt exist, please chose again: "  << endl;
			}
			else if( &player[order_of_play[i]] == map.getOwner(*map.getVertex(tmp_name))){ //exit loop if player owns the contry
				invalid = false;
				
			}else{
				cout << "you dont own that territory, please chose again: "  << endl; //informe the player that he does own the country
				}
			}
			invalid = true;
			map.setNbArmies(*map.getVertex(tmp_name), map.getNbofArmies(*map.getVertex(tmp_name))+1 ); // set the new amount of armies on a givien country
		}
		NumberOfamry--;
	}while(NumberOfamry != 0);
	
	
	vector<Country*> allC = map.getCountry();
	
	
	for (vector<Country*>::iterator i = allC.begin() ; i != allC.end(); ++i){
		(*i)->owner->addCountry(*i);
	}
	player[1].getCountries();
	
	//each player steal from a other 
	for(int i = 0; i < nbPlayer; i++){
			cout << player[order_of_play[i]].getName() << " type your territoriy that you wish steal: " << endl;
			while(invalid){
				cin >> tmp_name;
			if (map.getVertex(tmp_name) == NULL){// check if the territories exist 
				cout << "This territory doesnt exist, please chose again: "  << endl;
			}
			else if( &player[order_of_play[i]] != map.getOwner(*map.getVertex(tmp_name))){ //exit loop if player owns the contry
				invalid = false;
				
			}else{
				cout << "you own that territory, please chose again: "  << endl; //informe the player that he own the country
				}
			}
			invalid = true;
			map.setOwner(*map.getVertex(tmp_name), &player[order_of_play[i]] ); // set the new own
	}	
	
	
	
	
	
	system("pause");	
	//give ownership of all country of a player to a other 
	cout << player[1].getName() << " is giving ownership to " << player[0].getName() << endl;
	
	map.steal(&player[0],&player[1]);
	
	system("pause");
		
	//set a player winner 
	map.setwinner(&player[0]);
	cout << endl;
	cout << "Map is own by the first player:" << map.isOwnBy(&player[0]) <<endl;
		
	system("pause");
	map.printMap();
		
	//delete the view 	
	delete table;
}
	
	*/






