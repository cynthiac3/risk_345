#include <iostream>
#include "player.h"
#include <cmath>
#include <windows.h.>


using namespace std;

// Declare methods to use it in main()
void setUpGameDemo(Player* mark, Player* bob);
void clearInput();
void moveArmies(Country* receiver, Country* giver);


Player::Player() {
	cout << "A player was created." << endl;
} 

Player::~Player() {
	// Delete vector of pointers to countries
	for (int i = 0; i < myTerritories.size(); i++){		
		delete myTerritories.at(i);
	}
	cout << "Player was deleted." << endl;
}

// To be implemented in later assignments
void Player::reinforce() {
	cout << "The player is reinforcing itself." << endl;

}

// Player is allowed to declare a series of attacks to try to gain control of additional countries, and eventually control the entire map.
void Player::attack() {
	char ans;
	int countryNB, nbrNB, dicesAttack, dicesDefend;
	bool validCountry = false, validDice = false, attackOver = false, validMoveArmy = false, validNbr = false;

	// Player chooses if they want to attack or not
	while (!attackOver) {
		cout << "Do you want to attack a country? (y/n)" << endl;
		cin >> ans;
		cout << endl;

		if (ans == 'y') {
			getCountries();
			cin.clear();

			// Enter a valid country to attack from
			while (!validCountry) {
				cout << endl << "Select a country to attack from: ";
				cin >> countryNB;

				if (cin.fail()) {
					clearInput();
				}
				else if (countryNB >= myTerritories.size() || countryNB < 0) {
					cout << "Invalid number." << endl;
				}
				else if (myTerritories.at(countryNB)->nbArmies < 2) {
					cout << "The country must have at least 2 armies on it." << endl;
				}
				else if (myTerritories.at(countryNB)->nbr.size() == 0) {
					cout << "This country has no neighbors." << endl;
				}
				else {
					validCountry = true;
				}
			}
			validCountry = false;

			// Player chooses on of the country's neighbor to attack
			for (int i = 0; i < myTerritories.at(countryNB)->nbr.size(); i++) {
				if (myTerritories.at(countryNB)->nbr.at(i)->owner != this) {
					cout << endl << "Neighbor #" << i << " : " << myTerritories.at(countryNB)->nbr.at(i)->name
						<< ". Armies: " << myTerritories.at(countryNB)->nbr.at(i)->nbArmies;
				}
			}
			cout << endl << "Note: neighbor countries of " << myTerritories.at(countryNB)->name << " that belong to you were omitted." << endl;
			while (!validNbr) {
				cout << "Select the neighbor of this country to attack: ";
				cin >> nbrNB;

				if (cin.fail()) {
					clearInput();
				}
				else if (nbrNB >= myTerritories.at(countryNB)->nbr.size()
					|| nbrNB < 0 || myTerritories.at(countryNB)->nbr.at(nbrNB)->owner == this) {
					cout << "Not a valid number." << endl;
				}
				else {
					validNbr = true;
				}
			}
			validNbr = false;

			// Store neighbor country in a new variable to access to owner easily
			Country* defenderCountry = myTerritories.at(countryNB)->nbr.at(nbrNB);
			cout << "This country belongs to: " << defenderCountry->owner->name << endl;


			/*The attacker and defender players choose the number of dice to roll for their attack/defense. The attacker
			is allowed 1 to 3 dice, with the maximum number of dice being the number of armies on the attacking
			country, minus one. The defender is allowed 1 to 2 dice, with the maximum number of dice being the
			number of armies on the defending country.
			*/
			while (!validDice) {
				cout << endl << "Attacker must choose number of dices to roll (1, 2 or 3): ";
				cin >> dicesAttack;

				if (cin.fail()) {
					clearInput();
				}
				else if (dicesAttack > myTerritories.at(countryNB)->nbArmies - 1) {
					cout << "Number of dices must be smaller or equal to number of armies - 1 on the attacking country." << endl;

				}
				else if (dicesAttack > 3 || dicesAttack < 1) {
					cout << "Not a valid number.";
				}
				else {
					validDice = true;
				}
			}
			validDice = false;


			while (!validDice) {
				cout << endl << "Defender chooses number of dices to roll (1 or 2): ";
				cin >> dicesDefend;

				if (cin.fail()) {
					clearInput();
				}
				else if (dicesDefend > defenderCountry->nbArmies) {
					cout << "Number of dices must be smaller or equal to the number of armies on the defending country." << endl;

				}
				else if (dicesDefend > 2 || dicesDefend < 1) {
					cout << "Not a valid number.";
				}
				else {
					validDice = true;
				}
			}
			validDice = false;


			/*The dice are rolled for each player and sorted, then compared pair-wise. For each pair starting with the
			highest, the player with the lowest roll loses one army. If the pair is equal, the attacker loses an army. */
			this->dice.rollDice(dicesAttack);
			Sleep(2000);
			defenderCountry->owner->getDice()->rollDice(dicesDefend);

			// HIGHEST ROLL - Attacker wins
			if (dice.containerOfDiceRolls[2] > defenderCountry->owner->getDice()->containerOfDiceRolls[2]) {
				defenderCountry->nbArmies--;
				cout << "Defender loses 1 army" << endl;
			}
			else { // Attacker loses
				myTerritories.at(countryNB)->nbArmies--;
				cout << "Attacker loses 1 army" << endl;
			}
			// MID ROLL - Attacker wins
			if (dice.containerOfDiceRolls[1] > defenderCountry->owner->getDice()->containerOfDiceRolls[1]) {
				defenderCountry->nbArmies--;
				cout << "Defender loses 1 army" << endl;
			}
			else { // Attacker looes
				myTerritories.at(countryNB)->nbArmies--;
				cout << "Attacker loses 1 army" << endl;
			}
			// LOWEST ROLL - Attacker wins
			if (dice.containerOfDiceRolls[0] > defenderCountry->owner->getDice()->containerOfDiceRolls[0]) {
				defenderCountry->nbArmies--;
				cout << "Defender loses 1 army" << endl;
			}
			else { // Attacker loses
				myTerritories.at(countryNB)->nbArmies--;
				cout << "Attacker loses 1 army" << endl;
			}

			// If number of armies gets lower than 0, set it to 0
			if (defenderCountry->nbArmies < 0)
				defenderCountry->nbArmies = 0;
			if (myTerritories.at(countryNB)->nbArmies < 0)
				myTerritories.at(countryNB)->nbArmies = 0;

			cout << endl << "Result: " << endl << myTerritories.at(countryNB)->name << ": " << myTerritories.at(countryNB)->nbArmies << " armies." << endl
				<< defenderCountry->name << ": " << defenderCountry->nbArmies << " armies" << endl;


			/* If the attacked country runs out of armies, it has been defeated. The defending country now belongs to
			the attacking player. The attacker is allowed to move a number of armies from the attacking country to the
			attacked country, in the range [1 to (number of armies on attacking country -1)] */
			if (defenderCountry->nbArmies <= 0) {
				defenderCountry->owner->removeCountry(defenderCountry); // remove country from other player's list
				defenderCountry->owner = this; // player now owns the defender country
				myTerritories.push_back(defenderCountry); // add it to owned territories

				cout << "Defending country has been defeated. This country now belong to the attacking player."
					<< endl << "Attacking player now needs to move at least 1 army from the attacking country to their new country." << endl;

				// Move a number of armies from one country to another
				moveArmies(myTerritories.at(myTerritories.size() - 1), myTerritories.at(countryNB)); 	// receiver, giver
			}
			else if (myTerritories.at(countryNB)->nbArmies == 0) {
				cout << "Attacking country has been defeated. This country now belong to the defending player."
					<< endl << "Defending player now needs to move at least 1 army from the defending country to their new country." << endl;

				// Move a number of armies from one country to another
				moveArmies(myTerritories.at(countryNB), defenderCountry); 	// receiver, giver

				myTerritories.at(countryNB)->owner = defenderCountry->owner; // player now owns the defender country
				defenderCountry->owner->addCountry(myTerritories.at(countryNB));// add it to other player's territories
				removeCountry(myTerritories.at(countryNB)); // remove country from player's list

			}
		}
		else if (ans == 'n') { // Player doesn't want to attack
			attackOver = true;
		}
		else {
			clearInput();
		}
	}
}

// To be implemented in later assignments
void Player::fortify() {
	cout << "The player is fortifying itself." << endl;
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

void Player::addCountry(Country* country) {
	myTerritories.push_back(country);
}

// remove a country from the vector of owned countries
void Player::removeCountry(Country* country) {
	for (int i = 0; i < myTerritories.size(); i++) {
		if (myTerritories.at(i) == country) {
			myTerritories.erase(myTerritories.begin() + i);
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

	/*
		CREATING PLAYER 2
	*/
	Player* player2 = new Player();
	player2->setHand(&gameDeck);
	player2->getHand()->fillHand(gameDeck);
	player2->setName("Player2");

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
				<< "----------------" << endl << "4. Roll one Dice" << endl << "5. Show hand of cards" << endl << "6. See list of countries owned" << endl
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
				case 1: players.at(j)->reinforce(); break;
				case 2: players.at(j)->attack(); break;
				case 3: players.at(j)->fortify(); break;
				case 4: players.at(j)->getDice()->rollDice(1); break;
				case 5: printPlayersCards(players.at(j)); break;
				case 6: players.at(j)->getCountries(); break;
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

	// Deal with dangling pointers
	Iceland = NULL;
	France = NULL;
	Germany = NULL;
	Spain = NULL;
	Italy = NULL;

}

void clearInput() {
	cout << "Not a valid answer." << endl;
	cin.clear();
	std::string ignoreLine; //read the invalid input into it
	std::getline(cin, ignoreLine); //read the line till next space
}

void moveArmies(Country* receiver, Country* giver) {
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
