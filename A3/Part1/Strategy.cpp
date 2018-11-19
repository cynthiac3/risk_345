#include "Strategy.h"
#include <iostream>
#include <string>
#include "Player.h"

using namespace std;

// Clears the user input from the console
void Strategy::clearInput() {
	cout << "Not a valid answer." << endl;
	cin.clear();
	std::string ignoreLine; //read the invalid input into it
	std::getline(cin, ignoreLine); //read the line till next space
}

// Transfer a certain number of armies from one country to another by user input
void Strategy::moveArmies(Country* receiver, Country* giver) {
	bool validMoveArmy = false;
	int movingArmies;

	while (!validMoveArmy) {
		cout << "Please enter the number of armies you want to move: " << endl;
		cin >> movingArmies;

		if (cin.fail()) {
			clearInput();
		}
		else if (movingArmies < 1) {
			cout << "Number must be at least 1." << endl;
		}
		else if (movingArmies > giver->nbArmies - 1) {
			cout << "Number bigger than armies on the country - 1." << endl;
		}

		else {
			cout << movingArmies << " armies are moved from " << giver->name << " to "
				<< receiver->name << endl;
			giver->nbArmies -= movingArmies;
			receiver->nbArmies += movingArmies;
			validMoveArmy = true;
		}
	}
	validMoveArmy = false;

}

// Verifies if a certain country has any neighbor that doesn't belong to their owner 
// (in other words, a neighbor they can attack)
bool Strategy::checkValidNeighbors_Attack(Country* attacking) {
	for (int i = 0; i < attacking->nbr.size(); i++) {
		if (attacking->nbr.at(i)->owner != attacking->owner)
			return true; // at least one neighbor is not owned by the same player 
	}
	return false;
}

// Verifies if a certain country has any neighbor that also belongs to their owner 
// (in other words, a neighbor they can fortify)
bool Strategy::checkValidNeighbors_Fortify(Country* attacking) {
	for (int i = 0; i < attacking->nbr.size(); i++) {
		if (attacking->nbr.at(i)->owner == attacking->owner)
			return true; // at least one neighbor is owned by the same player 
	}
	return false;
}

// Verifies if the defending country which was defeated was the last country of their owner
// if it was, the player is eliminated from the game
void Strategy::defenderEliminated(Player* p1, Player* p2) {
	if (p2 != NULL) {
		cout << endl << "Defending player " << p2->name << " has no country left. This player is eliminated from the game and "
			<< p1->name << " receives their cards. " << endl;

		// transfer cards from loser(p2) to winner(p1)
		for (int j = 0; j < p2->getHand()->handOfCards.size(); j++) {
			p1->getHand()->handOfCards.push_back(p2->getHand()->handOfCards.at(j));
		}
		p2->getHand()->handOfCards.clear();

	}
	else {
		cout << endl << "Defending player has some countries left. Player is NOT eliminated from the game" << endl;
	}
}

