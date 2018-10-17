/*
	file: Map_loader.h
*/
	
#include ".\Map_loader.h"
#include "Player.h"

int main() {
	//make a new map loader
	Map_loader Ml;

	//load the map
	Ml.parser(Ml.choose_file());
	//print map infor
	Ml.myInfo.printInfo();
	//print map graph	
	Ml.map_loaded.printGraph();

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
	// Create a deck for the game
	Deck gameDeck;
	gameDeck.fillDeck(42);

	// Create new players in a vector
	for (int i = 0; i < NbPlayers; i++) {
		players.push_back(new Player()); // create player object
		players.at(i)->setHand(gameDeck); // assign a hand of cards
	}

	// MAIN GAME LOOP
	bool gameOver = false;
	while (!gameOver){
	
		// Each player has a turn
		for (int j = 0; j < players.size(); j++) {
			cout << "---------------------------------------------------------------------- \n"
				"/////////////////////////// PLAYER " << j + 1 << " TURN ///////////////////////////  \n"
				"----------------------------------------------------------------------" << endl;
			// PHASE 1: REINFORCE
			players.at(j)->reinforce();
			// PHASE 2: ATTACK
			players.at(j)->attack();
			// PHASE 3: FORTIFY
			players.at(j)->fortify();
		}

		// TODO: if all the countries belong to one player, the game is over
	}

	system("PAUSE");

	return 0;

}

