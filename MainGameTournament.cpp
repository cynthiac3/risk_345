#include "player.h"
#include <iostream>
#include <cmath>
#include <windows.h.>
#include "player.h"
#include "Strategy.h"
#include "Human.h"
#include "Aggressive.h"
#include "Benevolent.h"
#include "Random.h"
#include "Cheater.h"

#include ".\Deck.h"

#include "View.h"

#include ".\Map.h"

#include <string>
#include <vector>
#include <algorithm> 

#include <stdlib.h>
#include <time.h>

using namespace std;

// free functions declaration
void clearInputs();
void checkPlayersEliminated(vector<Player*> * players);

int main() {

	/***********************************************  LOAD MAP **********************************************/
	//Creates as many maps as player wants and creates vector of nodes for each
	int NbMaps;
	cout << "How many maps would you like to play on?" << endl;
	cin >> NbMaps;
	vector<Map> maps(NbMaps);
	vector < vector<vertex*>> tmp_nodesVector(NbMaps);
	for (size_t x = 0; x < maps.size(); x++)
		maps.at(x);
	for (size_t x = 0; x < maps.size(); x++)
		tmp_nodesVector.at(x) = maps.at(x).getNodes();


	bool invalid = true; // boolean use for validation


	/***********************************************   CREATE PLAYERS **********************************************/

	// Input the number of players
	vector<Player*> players;
	int NbPlayers;
	bool validNB = false;


	while (!validNB) {
		cout << "How many players?" << endl;
		cin >> NbPlayers;

		// Type checking the input
		if (cin.fail())
		{
			validNB = false;
			cout << "You did not input a number." << endl;
			cin.clear();
			std::string ignoreLine; //read the invalid input into it
			std::getline(cin, ignoreLine); //read the line till next space
		}
		else {
			if (NbPlayers >= 2 && NbPlayers <= 4) {
				validNB = true;
			}
			else {
				validNB = false;
				cout << "Number of player must be 2,3 or 4" << endl;
			}
		}
	}
	cin.clear();
	validNB = false;



	//Selection of player type
	int playerTypeAmount = NbPlayers;
	int NbAgressivePlayers = 0;
	int NbCheaterPlayers = 0;
	int NbBenevolentPlayers = 0;

	while (!validNB) {
		cout << "How many aggressive players do you want?" << endl;
		cin >> NbAgressivePlayers;
		playerTypeAmount -= NbAgressivePlayers;
		if (playerTypeAmount == 0)
			break;
		cout << "How many cheater players do you want?" << endl;
		cin >> NbCheaterPlayers;
		playerTypeAmount -= NbCheaterPlayers;
		if (playerTypeAmount == 0)
			break;
		cout << "How many benevolent players do you want?" << endl;
		cin >> NbBenevolentPlayers;
		playerTypeAmount -= NbBenevolentPlayers;
		if (playerTypeAmount == 0)
			break;

	}

	///////////////////////////////////////////////////////////////////////////
	for (size_t mapNumber = 0; mapNumber < NbMaps; mapNumber++) {

		// Create a deck for the game
		Deck gameDeck;
		gameDeck.fillDeck(42);
		// Sets up players and their types
		for (int i = 0; i < NbPlayers; i++) {
			players.push_back(new Player()); // create player object
			players.at(i)->setHand(&gameDeck); // assign a hand of cards
			players.at(i)->getHand()->fillHand(gameDeck);
			players.at(i)->getHand()->setDeck(gameDeck);
			if (NbAgressivePlayers != 0) {
				players.at(i)->setStrategy(new Aggressive(players.at(i)));
				NbAgressivePlayers--;
			}
			else if (NbBenevolentPlayers != 0 & NbAgressivePlayers == 0) {
				players.at(i)->setStrategy(new Benevolent(players.at(i)));
				NbBenevolentPlayers--;
			}
			else {
				players.at(i)->setStrategy(new Cheater(players.at(i)));
				NbCheaterPlayers--;
			}
		}
		/******************************************************   ASSIGN NUMBER OF TURNS  ************************************************************/

		int numberOfTurns;

		while (!validNB) {
			cout << "How many turns should each player be given>  (Must be between 3 and 50)" << endl;
			cin >> numberOfTurns;

			// Type checking the input
			if (cin.fail())
			{
				validNB = false;
				cout << "You did not input a number." << endl;
				cin.clear();
				std::string ignoreLine; //read the invalid input into it
				std::getline(cin, ignoreLine); //read the line till next space
			}
			else {
				if (numberOfTurns >= 3 && numberOfTurns <= 50) {
					validNB = true;
				}
				else {
					validNB = false;
					cout << "Number of player must be 2,3 or 4" << endl;
				}
			}
		}

		/***********************************************  ASSIGN COUNTRIES & ARMIES TO PLAYERS **********************************************/
		// Calculate the number of armies for each players (depends on nb of players)
		// Assign their armies to countries so that the player own these countries
		// etc.

		// TODO: add a menu to select game mode




		vector<int> order_of_play;//store the order of play (each index owns a unique index(refference) to the player array)
		int tmp_int = 0; // temporal integer use to store a state 


		srand(time(NULL)); //random input 
		int rindex; //variable to store a random index 
		vector<int> tmp_arr(NbPlayers); // Temproal array to sotre index of players





		//assign randomly contries to player in a round-robin fashion for the players
		// each player are assign to country randomly until all players have at least a coutry, then the process is repeted
		//making sure that the number of country that each players gets if equal
		for (vector<vertex*>::iterator i = tmp_nodesVector.at(mapNumber).begin(); i != tmp_nodesVector.at(mapNumber).end(); ++i) {
			do {//check if a certain player as already gone through this assignment round
				rindex = rand() % NbPlayers;
			} while ((tmp_arr[rindex] == 1) && !(tmp_arr[rindex] == 0));


			maps.at(mapNumber).setOwner((**i), players[rindex]); //set the owner of the current territory 
			tmp_arr[rindex] = 1; //instruct that the player x a pass is turn in that round
			tmp_int++; //increment the temporal varial use to check if all player have pass, meaning that the current round is over

			//if the current round is over, it resets to a new round
			if (tmp_int == NbPlayers) {
				for (int i = 0; i < NbPlayers; i++)tmp_arr[i] = 0;
				tmp_int = 0;
			}
		}




		//generate a random order_of_play 	
		for (int i = 0; i < NbPlayers; i++)tmp_arr[i] = -1;//set the temporal array to  -1 

		invalid = true;// reset invalid to true

		//generate a random order of play
		for (int i = 0; i < NbPlayers; i++) {
			invalid = true;
			do {
				rindex = rand() % NbPlayers;	//generate a random index 
				if (tmp_arr[i] == -1) { //check id the location available 
					invalid = false;
					for (int j = 0; j < NbPlayers; j++) {
						if (tmp_arr[j] == rindex)invalid = true;
					}
				}

			} while (invalid);
			tmp_arr[i] = rindex;
			order_of_play.push_back(rindex);
		}


		int NumberOfamry;
		//switch to check the nb of army in function of the number of player
		switch (NbPlayers) {
		case 2:
			NumberOfamry = 2;
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


		vector<Country*> allC = maps.at(mapNumber).getCountry();


		for (vector<Country*>::iterator i = allC.begin(); i != allC.end(); ++i) {
			(*i)->owner->addCountry(*i);
		}



		/***********************************************   MAIN GAME LOOP **********************************************/
		int numberOfTurnsDuplicate = numberOfTurns;
		bool gameOver = false;
		while (!gameOver && numberOfTurnsDuplicate != 0) {

			// Each player has a turn
			for (int j = 0; j < players.size(); j++) {

				players.at(j)->play();
				cout << endl;
			}

			// pass vector of player to check if one is eliminated from the game
			checkPlayersEliminated(&players);
			// TODO: if all the countries belong to one player, the game is over (Part 3 of assignment)
			numberOfTurnsDuplicate--;
		}
		system("PAUSE");
	}
		// Destory objects to prevent memory leaks
		for (int i = 0; i < players.size(); i++) {
			delete players.at(i);
		return 0;

	}
}






// Clears the user input from the console
void clearInputs() {
	cout << "Not a valid answer." << endl;
	cin.clear();
	std::string ignoreLine; //read the invalid input into it
	std::getline(cin, ignoreLine); //read the line till next space
}

// If a player has no countries left, it is eliminated from the game
// Checked after each player's turn
void checkPlayersEliminated(vector<Player*> * players) {
	for (int i = 0; i < players->size(); i++) {
		if (players->at(i)->myTerritories.size() == 0) {
			cout << endl << "Player " << players->at(i)->name << " has been eliminated from the game. Better luck next time!" << endl;
			delete players->at(i); // deletes memory location of pointer (player object)
			players->erase(players->begin() + i); // removes it from the vector list of active players
		}
	}
}


