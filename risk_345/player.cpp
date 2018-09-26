#include <iostream>
//#include ".\Map_loader.h"

using namespace std;


class Player {

public:
	/* ATTRIBUTES:
		-hand of risk cards
		-dice rolling facility
	 */

	// collection of countries that the player owns
	//vector<Territory> myTerritories;

	Player() {
		cout << "A player was created." << endl;
	} 

	void reinforce() {
		cout << "The player is reinforcing itself." << endl;
	}

	void attack() {
		cout << "The player is attacking." << endl;
	}

	void fortify() {
		cout << "The player is fortifying itself." << endl;
	}
};

// Driver
int main() {
	int ans;

	Player player;
	while (true) {
		cout << "Select an action to perform: " << endl << "1. Reinforce" << endl << "2. Attack" << endl << "3. Fortify" << endl; \
			cin >> ans;

		switch (ans) {
		case 1: player.reinforce(); break;
		case 2: player.attack(); break;
		case 3: player.fortify(); break;
		default: cout << "Invalid answer." << endl;
		}
	}
	return 0;
}