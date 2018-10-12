#include <iostream>
#include "player.h"


using namespace std;
	

Player::Player() {
	// Initialize a collection of countries that the player owns
	int coord[] = { 10, 20};
	int coord2[] = { 20, 30 };
	Territorie* t1 = new Territorie("Canada", coord, 3, "North America");
	Territorie* t2 = new Territorie("France", coord2, 5, "Europe");
	myTerritories.push_back(t1);
	myTerritories.push_back(t2);

	delete t1, t2;
	t1 = NULL;
	t2 = NULL;

	// Initialize a deck and a hand of cards
	Deck playerDeck;
	hand = Hand(playerDeck);

	cout << "A player was created." << endl;
} 

void Player::reinforce() {
	cout << "The player is reinforcing itself." << endl;
}

void Player::attack() {
	cout << "The player is attacking." << endl;
}

void Player::fortify() {
	cout << "The player is fortifying itself." << endl;
}

Dice Player::getDice(){
	return dice;
}

void Player::getCountries() {
	if (myTerritories.size() == 0) {
		cout << "Player doesn't own any countries.";
	}
	else {
		/*
		for (int i =0; i < myTerritories.size(); i++)
				cout << myTerritories.at(i)->getName();
				*/
		cout << "List of countries...";
	}
}

/*** Driver ***/
int main() {
	int ans; // option number the player chooses from the menu

	Player player;
	while (true) {
		cout << "------------------------------------" << endl
			<< "Select an action to perform: " << endl << "1. Reinforce" << endl << "2. Attack" << endl << "3. Fortify" << endl
			<< "----------------" << endl << "4. Roll one Dice" << endl << "5. Draw a card" << endl << "6. See list of countries owned" << endl
			<< "------------------------------------" << endl;
		// Player enters a choice from the menu
		cin >> ans;

		// Type checking the input
		if (cin.fail())
		{
			cout << "You did not input a number." << endl;
			cin.clear();
			std::string ignoreLine; //read the invalid input into it
			std::getline(cin, ignoreLine); //read the line till next space
		}
		else {
			switch (ans) {
				case 1: player.reinforce(); break;
				case 2: player.attack(); break;
				case 3: player.fortify(); break;
				case 4: player.getDice().rollDice(1); break;
				case 5: player.getCountries(); break;
				default: cout << "Invalid answer." << endl;
			}
		}

	}
	return 0;
}
