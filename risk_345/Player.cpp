#include <iostream>
#include "player.h"

using namespace std;
	

Player::Player() {
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
				default: cout << "Invalid answer." << endl;
			}
		}

	}
	return 0;
}