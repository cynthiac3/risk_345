#include <iostream>
#include <cmath>
#include <windows.h.>
//#include "Player.h" // already included in Header
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
//#include <vector> // already included in Header
#include <algorithm> 

#include <stdlib.h>
#include <time.h>
#include "MainGameTournament.h"


using namespace std;

void runTournament() {

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
	//vector<Player*> players;
	int NbPlayers;
	bool validNB = false;


	while (!validNB) {
		cout << "How many players? (2, 3 or 4)" << endl;
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

	while (playerTypeAmount>0) {
		cout << endl << "You have " << playerTypeAmount << " player types to choose." << endl;

		if (NbAgressivePlayers == 0) {
			cout << "Enter 1 if you want an aggressive player..." << endl;
			cin >> NbAgressivePlayers;
			if (NbAgressivePlayers == 1)
				playerTypeAmount--;
			else
				NbAgressivePlayers = 0;
			if (playerTypeAmount == 0)
				break;
		}
		if (NbCheaterPlayers == 0) {
			cout << "Enter 1 if you want an cheater player..." << endl;
			cin >> NbCheaterPlayers;
			if (NbCheaterPlayers == 1)
				playerTypeAmount--;
			else
				NbCheaterPlayers = 0;
			if (playerTypeAmount == 0)
				break;
		}
		if (NbBenevolentPlayers==0) {
			cout << "Enter 1 if you want an benevolent player..." << endl;
			cin >> NbBenevolentPlayers;
			if (NbBenevolentPlayers == 1)
				playerTypeAmount--;
			else
				NbBenevolentPlayers = 0;
			if (playerTypeAmount == 0)
				break;
		}
	}

	vector<string>playerTypes;
	for (int x = 0; x < NbAgressivePlayers; x++) 
		playerTypes.push_back("Aggressive");

	for (int x = 0; x < NbCheaterPlayers; x++) 
		playerTypes.push_back("Cheater");
	
	for (int x = 0; x < NbBenevolentPlayers; x++)
		playerTypes.push_back("Benevolent");


	/******************************************************   ASSIGN NUMBER OF TURNS  ************************************************************/

	int numberOfTurns; 

	while (!validNB) {
		cout << "How many turns should each player be given?  (Must be between 3 and 50)" << endl;
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
	validNB = false;



	/******************************************************   ASSIGN NUMBER OF GAMES  ************************************************************/

	int numberOfGames;

	while (!validNB) {
		cout << "How many games should be played on each map (Must be between 1 and 5)" << endl;
		cin >> numberOfGames;

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
			if (numberOfGames >= 1 && numberOfGames <= 5) {
				validNB = true;
			}
			else {
				validNB = false;
				cout << "Number of games must be 1,2,3,4 or 5" << endl;
			}
		}
	}

	// Vector of vectors that holds the type of Strategy for winner of each game.  In same order as table that will be printed.
	vector<vector<string>> winners(NbMaps, vector<string>(numberOfGames));


	//*************************************************************FOR EACH MAP*******************************************************//
	//Beginning of loop that will run through all maps selected for however many games were selected for each map
	for (size_t mapNumber = 0; mapNumber < NbMaps; mapNumber++) //for each map loop
	{
		for (size_t gameNumber = 0; gameNumber < numberOfGames; gameNumber++) //for each game loop
		{
			vector<Player*> players;
			// Create a deck for the game
			Deck gameDeck;
			gameDeck.fillDeck(42);
			// Sets up players and their types.  These are used for each game loop cycle to recreate the right amount of each strategy type
			int NbAggressivePlayersholder = NbAgressivePlayers;
			int NbBenevolentPlayersholder = NbBenevolentPlayers;
			int NbCheaterPlayersholder = NbCheaterPlayers;
		
			for (int i = 0; i < NbPlayers; i++) {
				players.push_back(new Player()); // create player object
				players.at(i)->setHand(&gameDeck); // assign a hand of cards
				players.at(i)->getHand()->fillHand(gameDeck);
				players.at(i)->getHand()->setDeck(gameDeck);

				//Sets right amount of strategy types selected by user for each player object
				if (NbAggressivePlayersholder != 0) {
					players.at(i)->setStrategy(new Aggressive(players.at(i)));
					NbAggressivePlayersholder--;
					players.at(i)->setName("Aggressive");
					cout << "AGRESSIVE" << endl;
				}
				else if (NbBenevolentPlayersholder != 0 & NbAggressivePlayersholder == 0) {
					players.at(i)->setStrategy(new Benevolent(players.at(i)));
					NbBenevolentPlayersholder--;
					players.at(i)->setName("Benevolent");
					cout << "Benevolent" << endl;
				}
				else {
					cout << "" << endl;
					players.at(i)->setStrategy(new Cheater(players.at(i)));
					NbCheaterPlayersholder--;
					players.at(i)->setName("Cheater");
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
			
				maps.at(mapNumber).setNbArmies((**i), 1);
				
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

			maps.at(mapNumber).printMap();
			
			for (vector<Country*>::iterator i = allC.begin(); i != allC.end(); ++i) {
				(*i)->owner->addCountry(*i);
			}



			/***********************************************   MAIN GAME LOOP **********************************************/
			int numberOfTurnsDuplicate = numberOfTurns; //Holds the amount of turns per game chosen by user
			bool gameOver = false;
			while (!gameOver && numberOfTurnsDuplicate != 0) { //loop terminates if a player wins or number of turns is reached

				// Each player has a turn
				for (int j = 0; j < players.size(); j++) {
					cout << "---------------------------------------------------------------------- \n"
						"/////////////////////////// PLAYER " << j + 1 << " TURN ///////////////////////////  \n"
						"----------------------------------------------------------------------" << endl;

					checkPlayersEliminatedTournament(&players);
					if(players.size() == 1){
						gameOver = true;
					}else{
						players.at(j)->play();
						cout << endl;
						maps.at(mapNumber).update(allC);
					}
				}
				//loop to check whether the a player has lost all territories
				checkPlayersEliminatedTournament(&players);
			    if(players.size() == 1)
					gameOver = true;
				numberOfTurnsDuplicate--; 
			}
			maps.at(mapNumber).printMap();
			//Sets winners strategy type in proper cell of 2d vector.
			if (players.size() == 1) {
				winners.at(mapNumber).at(gameNumber) = players.at(0)->getName();
				gameOver = true;
			}
			else
				winners.at(mapNumber).at(gameNumber) = "Draw";
			
			// Destory objects to prevent memory leaks
			for (int i = 0; i < players.size(); i++) {
				delete players.at(i);
			}
		}
	}
	
	cout << endl << endl<< "FINAL RESULT OF THE TOURNAMENT:" << endl;
	//loop that will create table of maps and games
	cout <<"\n"<< "          ";
	for (size_t x = 0; x < numberOfGames; x++)
		cout << "Game " << +x + 1 <<"     ";

	cout << "" << endl;
	for (size_t x = 0; x < NbMaps; x++) {
		cout << "Map " << +x + 1<<"     ";
		for (size_t y = 0; y < numberOfGames; y++)
			if(winners.at(x).at(y).compare("Draw") == 0)
			cout << winners.at(x).at(y)<<"        ";
			else if((winners.at(x).at(y).compare("Cheater") == 0))
				cout << winners.at(x).at(y) << "     ";
			else if ((winners.at(x).at(y).compare("Random") == 0))
				cout << winners.at(x).at(y) << "      ";
			else
				cout << winners.at(x).at(y) << "   ";
		cout << "" << endl;

	}
	cout << endl;
	system("PAUSE");
}


// Clears the user input from the console
void clearInputsTournament() {
	cout << "Not a valid answer." << endl;
	cin.clear();
	std::string ignoreLine; //read the invalid input into it
	std::getline(cin, ignoreLine); //read the line till next space
}


// If a player has no countries left, it is eliminated from the game
// Checked after each player's turn
void checkPlayersEliminatedTournament(vector<Player*> * players) {
	for (int i = 0; i < players->size(); i++) {
		if (players->at(i)->myTerritories.size() == 0) {
			cout << endl << "Player " << players->at(i)->name << " has been eliminated from the game. Better luck next time!" << endl;
			delete players->at(i); // deletes memory location of pointer (player object)
			players->erase(players->begin() + i); // removes it from the vector list of active players
		}
	}
}


