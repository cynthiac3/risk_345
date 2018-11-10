#include <iostream>
#include <cmath>
#include <windows.h.>
#include "player.h"
#include "Human.h"
#include "Strategy.h"
#include "Aggressive.h"
#include "Benevolent.h"


using namespace std;

// Declare free functions
void setUpGameDemo(Player* mark, Player* bob);
void clearInput();
void chooseStrategy(Player* p);

// Default constructor
Player::Player() {
	cout << "A player was created." << endl;
} 

// Default destructor
Player::~Player() {
	// Delete vector of pointers to countries
	for (int i = 0; i < myTerritories.size(); i++){		
		delete myTerritories.at(i);
	}
	cout << "Player was deleted." << endl;
}


/***********************************************   ASSIGNMENT #2 - PART 4 **********************************************/
// REINFORCING PHASE
/*
	 Player gets a number of armies to place on its countries.
*/
void Player::reinforce() {
	strategy->reinforce();
}

/***********************************************   ASSIGNMENT #2 - PART 5 **********************************************/
// ATTACKING PHASE
/*	
	Player is allowed to declare a series of attacks to try to gain control of additional countries, 
	and eventually control the entire map.
*/
void Player::attack() {
	strategy->attack();
}

/***********************************************   ASSIGNMENT #2 - PART 6 **********************************************/
// FORTIFICATION PHASE
/*	After Attack Phase is complete:
		Player may move as many armies as they want in to a NEIGHBOURING country that they own.
		Player may only do this ONE time (you can't fortify multiple countries).
*/
void Player::fortify() {
	strategy->fortify();
}

// Returns the dice facility of the player
Dice* Player::getDice(){
	return &dice;
}

// Returns the Hand object holding the player's cards
Hand* Player::getHand() {
	return &hand;
}

// Returns the Hand object holding the player's cards
string Player::getName() {
	return name;
}

// Set 5 cards in the hand of the player, picked from the deck passed as a parameter
void Player::setName(string theName) {
	name = theName;
}

// Set 5 cards in the hand of the player, picked from the deck passed as a parameter
void Player::setHand(Deck *theDeck) {
	hand.playingDeck = theDeck;
	hand.handOfCards.resize(5);
}

// Set a strategy for the player
void Player::setStrategy(Strategy* s) {
	strategy = s;
}

// Add a country to the vector of countries owned
void Player::addCountry(Country* country) {
	myTerritories.push_back(country);
}

// Remove a country from the vector of owned countries
void Player::removeCountry(Country* country) {
	for (int i = 0; i < myTerritories.size(); i++) {
		if (myTerritories.at(i) == country) {
			myTerritories.erase(myTerritories.begin() + i);
		}
	}
}

// Add a continent to the vector of continents owned
void Player::addContinent(Continent* continent) {
	myContinents.push_back(continent);
}

// Remove a continent from the vector of owned countries
void Player::removeContinent(Continent* continent) {
	for (int i = 0; i < myContinents.size(); i++) {
		if (myContinents.at(i) == continent) {
			myContinents.erase(myContinents.begin() + i);
		}
	}
}

// Prints the names of the country that the player owns
void Player::getCountries() {
	if (myTerritories.size() == 0) {
		cout << "Player doesn't own any countries.";
	}
	else {
		for (int i = 0; i < myTerritories.size(); i++)
			cout << "Territory #" << i << ": " << myTerritories.at(i)->name
			<< ". Armies: " << myTerritories.at(i)->nbArmies << endl;
	}
}

// Print the cards that the player owns 
void printPlayersCards(Player* p) {

	for (int i = 0; i < p->getHand()->handOfCards.size(); i++)
	{
			switch (p->getHand()->handOfCards.at(i))
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

	// Create a deck for the game (same for all players) 
	Deck gameDeck;
	gameDeck.fillDeck(42);
	
	// Create players and set the players' hand of cards with 5 cards from the deck created
	/*	
		CREATING PLAYER 1
	*/
	Player* player1 = new Player();
	player1->setHand(&gameDeck);
	player1->getHand()->fillHand(gameDeck);
	player1->setName("Player1");
	player1->setStrategy(new Human(player1));

	/*
		CREATING PLAYER 2
	*/
	Player* player2 = new Player();
	player2->setHand(&gameDeck);
	player2->getHand()->fillHand(gameDeck);
	player2->setName("Player2");
	player2->setStrategy(new Human(player2));

	// Create vector of players
	vector<Player*> players;
	players.push_back(player1);
	players.push_back(player2);

	// Set up the game map (for demo only)
	setUpGameDemo(player1, player2);


	while (true) {

		// Each player has a turn
		for (int j = 0; j < players.size(); j++) {

			// MENU
			cout << endl << "---------------------------------------------------------------------- \n"
				"/////////////////////////// PLAYER " << j + 1 << " TURN ///////////////////////////  \n"
				"----------------------------------------------------------------------" << endl
				<< "Select an action to perform: " << endl << "1. Reinforce" << endl << "2. Attack" << endl << "3. Fortify" << endl
				<< "----------------" << endl << "4. Roll one Dice" << endl << "5. Show hand of cards" << endl << "6. See list of countries owned" << endl << "7. Change strategy" << endl
				<< "------------------------------------" << endl;
			// Player enters a choice from the menu
			cin >> ans;
			cout << endl;

			// Type checking the input
			if (cin.fail()){
				clearInput();
			}
			else {
				// Perform the action the player chose 
				switch (ans) {
				case 1: players.at(j)->strategy->reinforce(); break;
				case 2: players.at(j)->strategy->attack(); break;
				case 3: players.at(j)->strategy->fortify(); break;
				case 4: players.at(j)->getDice()->rollDice(1); break;
				case 5: printPlayersCards(players.at(j)); break;
				case 6: players.at(j)->getCountries(); break;
				case 7: chooseStrategy(players.at(j)); break;
				default: cout << "Invalid answer." << endl;
				}
			}
		} // Player turn ends

	} // Game ends

	// Destory objects to prevent memory leaks
	delete player1;
	delete player2;

	return 0;
}

// Display menu that allows to change its current strategy
void chooseStrategy(Player* p) {
	int answ;
	bool valid;
	cout << "Which strategy do you want to use?" << endl << "1. Human interactive strategy"
		<< endl << "2. Aggressive computer strategy" << endl << "3. Benevolent computer strategy" << endl << "--------------------------------" << endl;
	cin >> answ;
	// Type checking the input
	if (cin.fail()) {
		clearInput();
	}
	else {
		// Perform the action the player chose 
		switch (answ) {
		case 1: p->setStrategy(new Human(p)); 
				cout << "Strategy set to Human." << endl;
				break;
		case 2: p->setStrategy(new Aggressive(p)); 
				cout << "Strategy set to Aggressive." << endl;
				break;
		case 3: p->setStrategy(new Benevolent(p)); 
				cout << "Strategy set to Benevolent." << endl;
				break;
		default: cout << "Invalid answer." << endl;
		}
	}
}


void setUpGameDemo(Player* mark, Player* bob) {
	// Create countries
	Country* Iceland = new Country();
	Iceland->name = "Iceland";
	Iceland->nbArmies = 2;
	Iceland->owner = bob;

	Country* France = new Country();
	France->name = "France";
	France->nbArmies = 6;
	France->owner = mark;

	Country* Germany = new Country();
	Germany->name = "Germany";
	Germany->nbArmies = 1;
	Germany->owner = mark;

	Country* Spain = new Country();
	Spain->name = "Spain";
	Spain->nbArmies = 2;
	Spain->owner = bob;

	Country* Italy = new Country();
	Italy->name = "Italy";
	Italy->nbArmies = 5;
	Italy->owner = bob;

	// Set up neighbors
	Iceland->nbr = {};
	France->nbr = { Germany, Spain, Italy };
	Germany->nbr = { France };
	Spain->nbr = { France };
	Italy->nbr = { France };

	// Put countries inside player's vector
	mark->addCountry(France);
	mark->addCountry(Germany);
	bob->addCountry(Spain);
	bob->addCountry(Italy);
	bob->addCountry(Iceland);

	// Add one continent for bob
	Continent* Antartica = new Continent();
	Antartica->name = "Antartica";
	Antartica->bonus = 2;
	bob->addContinent(Antartica);

	// Deal with dangling pointers
	Iceland = NULL;
	France = NULL;
	Germany = NULL;
	Spain = NULL;
	Italy = NULL;
	Antartica = NULL;

}

void clearInput() {
	cout << "Not a valid answer." << endl;
	cin.clear();
	std::string ignoreLine; //read the invalid input into it
	std::getline(cin, ignoreLine); //read the line till next space
}