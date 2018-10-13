#include <iostream>
#include <string>
#include "player.h"
#include "Deck.h"


using namespace std;
	

Player::Player() {
	// Initialize a collection of countries that the player owns
	string coord1[] = { "10", "20" };
	string coord2[] = { "20", "30" };
	vector<string> nbr1{ "USA" };
	vector<string> nbr2{ "Sweden", "Finland" };
	Territory* t1 = new Territory("Canada", coord1, "North America", nbr1);
	Territory* t2 = new Territory("Norway", coord2, "Europe", nbr2);
	myTerritories.push_back(t1);
	myTerritories.push_back(t2);

	t1 = NULL;
	t2 = NULL;

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

Hand Player::getHand() {
	return hand;
}

void Player::getCountries() {
	if (myTerritories.size() == 0) {
		cout << "Player doesn't own any countries.";
	}
	else {
		for (int i =0; i < myTerritories.size(); i++)
			cout << "Territory #" << i+1 << ": " << myTerritories.at(i)->getName() << endl;
	}
}

void printPlayersCards(Player p) {
	for (int i = 0; i < p.getHand().handOfCards.size(); i++) 
	{
			switch (p.getHand().handOfCards[i])
			{
				case Deck::Cards::Infantry: cout << "Card #" << i + 1 << ": Infantry" << endl; break;
				case Deck::Cards::Cavalry: cout << "Card #" << i + 1 << ": Cavalry" << endl; break;
				case Deck::Cards::Artillery: cout << "Card #" << i + 1 << ": Artillery" << endl; break;
			}
	}
}

/*** Driver ***/
int main() {
	int ans; // option number the player chooses from the menu

	// Create a deck for the game and 1 player 
	Deck gameDeck;
	gameDeck.fillDeck(42);
	Player player;

	// Set the deck the player is gonna use
	player.getHand().setDeck(gameDeck);
	// Fill player hand with 5 cards (hardcoded only for this assignment)
	player.getHand().handOfCards[0] = Deck::Cards::Artillery;
	player.getHand().handOfCards[1] = Deck::Cards::Cavalry;
	player.getHand().handOfCards[2] = Deck::Cards::Cavalry;
	player.getHand().handOfCards[3] = Deck::Cards::Infantry;
	player.getHand().handOfCards[4] = Deck::Cards::Artillery;

	

	while (true) {
		cout << endl << "------------------------------------" << endl
			<< "Select an action to perform: " << endl << "1. Reinforce" << endl << "2. Attack" << endl << "3. Fortify" << endl
			<< "----------------" << endl << "4. Roll one Dice" << endl << "5. Show hand of cards" << endl << "6. See list of countries owned" << endl
			<< "------------------------------------" << endl;
		// Player enters a choice from the menu
		cin >> ans;
		cout << endl;

		// Type checking the input
		if (cin.fail())
		{
			cout << "You did not input a number." << endl;
			cin.clear();
			std::string ignoreLine; //read the invalid input into it
			std::getline(cin, ignoreLine); //read the line till next space
		}
		else {
			// Perform the action the player chose 
			switch (ans) {
				case 1: player.reinforce(); break;
				case 2: player.attack(); break;
				case 3: player.fortify(); break;
				case 4: player.getDice().rollDice(1); break;
				case 5: printPlayersCards(player); break;
				case 6: player.getCountries(); break;
				default: cout << "Invalid answer." << endl;
			}
		}

	}
	return 0;
}


