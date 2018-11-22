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

using namespace std;

// free functions declaration
void clearInputs();
void checkPlayersEliminated(vector<Player*> * players);

int main() {

	/***********************************************  LOAD MAP **********************************************/
	
	
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
			if (NbPlayers > 1 && NbPlayers <= 6) {
				validNB = true;
			}
			else {
				validNB = false;
				cout << "Number of player must be 2,3,4,5 or 6." << endl;
			}
		}
	}
	cin.clear();

	// Create a deck for the game
	Deck gameDeck;
	gameDeck.fillDeck(42);

	// Create new players in a vector
	for (int i = 0; i < NbPlayers; i++) {
		players.push_back(new Player()); // create player object
		players.at(i)->setHand(&gameDeck); // assign a hand of cards
		players.at(i)->getHand()->fillHand(gameDeck);
		players.at(i)->setStrategy(new Human(players.at(i)));
		players.at(i)->getHand()->setDeck(gameDeck);

		// TODO: add option to set name (user input)
	}

	/***********************************************  ASSIGN COUNTRIES & ARMIES TO PLAYERS **********************************************/
	// Calculate the number of armies for each players (depends on nb of players)
	// Assign their armies to countries so that the player own these countries
	// etc.

	// TODO: add a menu to select game mode

	/***********************************************   MAIN GAME LOOP **********************************************/
	bool gameOver = false;
	while (!gameOver){
	
		// Each player has a turn
		for (int j = 0; j < players.size(); j++) {
			cout << "---------------------------------------------------------------------- \n"
				"/////////////////////////// PLAYER " << j + 1 << " TURN ///////////////////////////  \n"
				"----------------------------------------------------------------------" << endl;
			
			// add menu? so that player may change strategies at runtime -> see Player.cpp
			
			players.at(j)->play();

			cout << endl;
			system("PAUSE");
		}
	
		// pass vector of player to check if one is eliminated from the game
		checkPlayersEliminated(&players);
		// TODO: if all the countries belong to one player, the game is over (Part 3 of assignment)
	}

	// Destory objects to prevent memory leaks
	for (int i = 0; i < players.size(); i++) {
		delete players.at(i);
	}

	
	return 0;

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


