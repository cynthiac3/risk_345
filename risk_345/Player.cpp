#include <iostream>
#include "player.h"
#include <cmath>


using namespace std;
	

Player::Player() {
	// Initialize a collection of countries that the player owns (HARDCODED FOR ASSIGNMENT#1 ONLY)
	// The coordinates of each country
	string coord1[] = { "10", "20" };
	string coord2[] = { "20", "30" };
	// The list of neighbors of each country
	vector<string> nbr1{ "USA" };
	vector<string> nbr2{ "Sweden", "Finland" };
	// Initializing the pointers to new territories objects
	Territory* t1 = new Territory("Canada", coord1, "North America", nbr1);
	Territory* t2 = new Territory("Norway", coord2, "Europe", nbr2);
	// Adding the territories to the list
	myTerritories.push_back(t1);
	myTerritories.push_back(t2);

	t1 = NULL;
	t2 = NULL;

	cout << "A player was created." << endl;
} 

// To be implemented in later assignments
void Player::reinforce() {
	cout << "The player is reinforcing itself." << endl;

	// Player received nb of countries owned divided by 3 rounded down
	int nbArmiesToPlace = floor(myTerritories.size() / 3);
	if (nbArmiesToPlace < 3) // min is 3
		nbArmiesToPlace = 3;

	cout << "Based on the number of countries you own, you get " << nbArmiesToPlace << " armies." << endl;

	// TODO: If the player owns an entire continent, add the bonus armies
	cout << "You don't own any continent, no bonus armies." << endl;

	// TODO: Exchange cards 
	//etc.

}

// To be implemented in later assignments
void Player::attack() {
	char ans;
	int countryNB;
	int nbrNB;
	bool validCountry = false;

	// Player chooses if they want to attack or not
	cout << "The player is attacking." << endl;
	cout << "Do you want to attack? (y/n)" << endl;
	cin >> ans;
	cout << endl;

	if (ans == 'y') {
		getCountries();

		// Enter a valid country to attack from
		while (!validCountry) {
			cout << endl << "Select a country to attack from: ";
			cin >> countryNB;
			countryNB--; // bc indexes in vector starts at 0
			if (myTerritories.at(countryNB)->getArmies() >= 2) {
				validCountry = true;
			}
			else {
				cout << "The country must have at least 2 armies on it." << endl;
			}
		}

		// Player chooses on of the country's neighbor to attack
		for (int i = 0; i < myTerritories.at(countryNB)->getNbr().size(); i++) {
			cout << "Neighbor #" << i+1 << " : " << myTerritories.at(countryNB)->getNbr().at(i) << endl;
		}
		cout << "Select the neighbor of this country to attack: ";
		cin >> nbrNB;

	}
}

// To be implemented in later assignments
void Player::fortify() {
	cout << "The player is fortifying itself." << endl;
}

// Returns the dice facility of the player
Dice Player::getDice(){
	return dice;
}


// Returns the Hand object holding the player's cards
Hand* Player::getHand() {
	return &hand;
}


// Set 5 cards in the hand of the player, picked from the deck passed as a parameter
void Player::setHand(Deck *theDeck) {
	hand.playingDeck = theDeck;
	hand.handOfCards.resize(5);
}

// Prints the names of the country that the player owns
void Player::getCountries() {
	if (myTerritories.size() == 0) {
		cout << "Player doesn't own any countries.";
	}
	else {
		for (int i = 0; i < myTerritories.size(); i++)
			cout << "Territory #" << i + 1 << ": " << myTerritories.at(i)->getName()
			<< ". Armies: " << myTerritories.at(i)->getArmies() << endl;
	}
}

// Print the cards that the player owns 
void printPlayersCards(Player p) {

	
	for (int i = 0; i < p.getHand()->handOfCards.size(); i++)
	{
			switch (p.getHand()->handOfCards.at(i))
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

	// Create a deck for the game (would be the same for all players) 
	Deck gameDeck;
	gameDeck.fillDeck(42);
	
	// Create one player and set the player's hand of cards with 5 cards from the deck created
	Player player;
	player.setHand(&gameDeck);
	player.getHand()->fillHand(gameDeck);

	while (true) {
		// MENU
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
