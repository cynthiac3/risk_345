#include <iostream>
#include <cmath>
#include "Player.h"


using namespace std;


// Declare method to use it in main()
void setUpGameDemo(Player* mark, Player* bob);

vector<Country*> Player::Europe;
vector<Country*> Player::Arctic;
vector <vector<Country*>> Player::continents;
void Player::addCountryToContinentArctic(Country * country) {

	if (Arctic.at(0)==0)
		Arctic.at(0) = country;
	else
	Arctic.push_back(country);
}

void Player::addCountryToContinentEurope(Country * country) {

	if (Europe.at(0)==0)
		Europe.at(0) = country;
	else
		Europe.push_back(country);
}
 void Player::addContinentToVector()
{
	 continents.at(0) = Arctic;
	continents.push_back(Europe);
}









Player::Player() {
	cout << "A player was created." << endl;
}











void Player::reinforce() {
	cout << "The player is reinforcing itself." << endl;

	// Player received nb of countries owned divided by 3 rounded down
	int nbArmiesToPlace = floor(myTerritories.size() / 3);
	if (nbArmiesToPlace < 3) // min is 3
		nbArmiesToPlace = 3;

	cout << "Based on the number of countries you own, you get " << nbArmiesToPlace << " armies." << endl;

	bool hasContinent = true;
	for (size_t x = 0; x < continents.size(); x++)
	{

		for (size_t y = 0; y < continents[x].size(); y++)
		{

			for (size_t xyz = 0; xyz < myTerritories.size(); xyz++)
			{
				if (myTerritories[xyz]->name != continents[x][y]->name)
				{
					hasContinent = false;
					break;
				}
				else 
				{
					 hasContinent = true;
				}

			}	
		}
		
	}

	if (hasContinent == false)
		cout << "You don't own any continents, no bonus armies for you!.\n" << endl;
	else
		cout <<"You are awarded 2 bonus armies.\n" << endl;


	//If handOfCards is greater than 5 it forces player to exchange cards for army units
	if (hand.howManyCardsInHand() > 5) 
	{
		bool check = true;
		do
		{
			cout << "You have more than 5 cards.  You must make and exchange" << endl;
			nbArmiesToPlace += hand.exchange();
			if (hand.howManyCardsInHand() < 6)
				check = false;
		} while (check);
	}

	cout << "You have this many armies to place " << nbArmiesToPlace << endl;

	while (nbArmiesToPlace > 0) {

		
		int nbOfUnits = 0;
		cout << "Please select which of your countries you would like to place your armies on" << endl;
		for (size_t x = 0; x < myTerritories.size(); x++) 
		{
			cout << "How many units would you like to place on   ";
			cout << myTerritories[x]->name<< endl;
			cin >> nbOfUnits;
			if (nbOfUnits > nbArmiesToPlace)
				cout << "Sorry you selected too many.  Try again" << endl;
			else {
				myTerritories.at(x)->nbArmies = nbOfUnits;
				nbArmiesToPlace -= nbOfUnits;
			}
			if (nbArmiesToPlace == 0)
				break;
			
		}
		
		cout << "You have " << nbArmiesToPlace << " left" << endl;
	}


}


void Player::fortify(){
	cout << "The player is fortifying itself." << endl;
}


// Returns the Hand object holding the player's cards
Hand* Player::getHand(){
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
	hand.handOfCards.resize(6);
}

void Player::addCountry(Country* country) {
	myTerritories.push_back(country);
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
	player1->setName("Mark");
	player1->hand.fillHand(gameDeck);
	player1->hand.fillHand(gameDeck);
	player1->hand.fillHand(gameDeck);
	player1->hand.fillHand(gameDeck);
	player1->hand.fillHand(gameDeck);
	player1->hand.fillHand(gameDeck);

	/*
		CREATING PLAYER 2
	*/
	Player* player2 = new Player();
	player2->setHand(&gameDeck);
	player2->getHand()->fillHand(gameDeck);
	player2->setName("Bob");
	player2->hand.fillHand(gameDeck);
	player2->hand.fillHand(gameDeck);
	player2->hand.fillHand(gameDeck);
	player2->hand.fillHand(gameDeck);
	player2->hand.fillHand(gameDeck);
	player2->hand.fillHand(gameDeck);

	

	// Create vector of players
	vector<Player*> players;
	players.push_back(player1);
	players.push_back(player2);

	// Set up the game map (for demo only)
	setUpGameDemo(player1, player2);


	while (true) {

		// Each player has a turn
		for (int j = 0; j < players.size(); j++) 
		{

			// MENU
			cout << endl << "---------------------------------------------------------------------- \n"
				"/////////////////////////// PLAYER " << j + 1 << " TURN ///////////////////////////  \n"
				"----------------------------------------------------------------------" << endl
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
				switch (ans)
				{
				case 1: players.at(j)->reinforce();
				}
			}
		}break;
		
	}
	return 0;
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
	Player::continents.resize(1);
	Player::Arctic.resize(1);
	Player::Europe.resize(1);
	Player::addCountryToContinentArctic(Iceland);
	Player::addCountryToContinentEurope(Germany);
	Player::addCountryToContinentEurope(Spain);
	Player::addCountryToContinentEurope(Italy);
	Player::addCountryToContinentEurope(France);
	Player::addContinentToVector();

	cout << Player::Arctic.size() << endl;
	cout << Player::Europe.size() << endl;
	cout << Player::continents.size() << endl;
}