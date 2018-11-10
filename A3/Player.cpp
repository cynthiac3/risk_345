#include <iostream>
#include "player.h"
#include <cmath>
#include <windows.h.>


using namespace std;

// Declare free functions
void setUpGameDemo(Player* mark, Player* bob);
void clearInput();
void moveArmies(Country* receiver, Country* giver);
bool checkValidNeighbors_Attack(Country* attacking);
bool checkValidNeighbors_Fortify(Country* attacking);

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
	bool validCountry = false, validNB = false, exchangeCards = false, validAns = false;
	int countryNB, nbOfUnits = 0;
	char ans;
	cout << "---------------------------------------------------------------------- \n"
			"////////////////////// BEGIN REINFORCE PHASE ///////////////////////  \n"
			"----------------------------------------------------------------------" << endl;

	// STEP 1: Player receives armies equals to nb of countries owned divided by 3 rounded down
	int nbArmiesToPlace = floor(myTerritories.size() / 3);
	if (nbArmiesToPlace < 3) // min is 3
		nbArmiesToPlace = 3;

	cout << "Based on the number of countries you own, you get " << nbArmiesToPlace << " armies." << endl;

	// STEP 2: Player gets a certain bonus for each continent owned
	// bonusValue = int bonusContinents(Player* p);
	int bonusValue = 0;
	if (myContinents.size() == 0) {
		cout << "You don't own any continents." << endl << "You get 0 bonus armies." << endl;
	}
	else {
		for (int x = 0; x < myContinents.size(); x++) {
			cout << "You own " << myContinents.at(x)->name << " so you get " << myContinents.at(x)->bonus << " bonus armies." << endl;
			bonusValue += myContinents.at(x)->bonus;
		}
		nbArmiesToPlace += bonusValue;
		cout << "You get a total of " << bonusValue << " bonus armies for a new total of " << nbArmiesToPlace << " armies." << endl;
	}

	// STEP 3: Player can exchange cards for armies
	if (hand.howManyCardsInHand() > 5) {//If handOfCards is greater than 5 it forces player to exchange cards for army units
		cout << "You have more than 5 cards in hand. You must make an exchange." << endl;
		exchangeCards = true;
	}
	else {
		while (!validAns) {
			cout << endl << "Would you like to trade cards for armies? ";
			cin >> ans;
			if (cin.fail()) {
				clearInput();
			}
			if (ans == 'y' || ans == 'Y') { // Player wants to draw cards
				exchangeCards = true;
				validAns = true;
			}
			else if (ans == 'n' || ans == 'N') { // Player doesn't want to draw cards
				validAns = true;
			}
			else {
				cout << "Not a valid answer." << endl;
			}
		}
	}
	if (exchangeCards) { // If player want to exchange cards
		bool check = true;
		int resultingArmies;
		do
		{
			//cout << "You have more than 2 cards. You can make and exchange" << endl;
			resultingArmies = hand.exchange();
			if (resultingArmies == 0)
				cout << "Not a valid exchange. You don't get any armies." << endl;
			else
				cout << "This is your exchange #" << hand.numberOfExchanges << ", you get " << resultingArmies << " armies." << endl;
			nbArmiesToPlace += resultingArmies;
			
			if (hand.howManyCardsInHand() < 6)
				check = false;
		} while (check);
	}

	// STEP 4: Give armies to any countries owned
	cout << "You have this many armies to place: " << nbArmiesToPlace << endl << endl;

	while (nbArmiesToPlace > 0) {
		// Print countries owned
		getCountries();
		// Enter a valid country
		while (!validCountry) {
			cout << "Please select which of your countries you would like to place your armies on: " << endl;
			cin >> countryNB;

			if (cin.fail()) {
				clearInput();
			}
			else if (countryNB >= myTerritories.size() || countryNB < 0) {
				cout << "Invalid number." << endl;
			}
			else {
				validCountry = true;
			}
		}
		validCountry = false;
		// Enter a valid number to armies to place
		while (!validNB) {
			cout << "How many units would you like to place on " << myTerritories.at(countryNB)->name << " ? ";
			cin >> nbOfUnits;

			if (cin.fail()) {
				clearInput();
			}
			else if (nbOfUnits < 0 || nbOfUnits > nbArmiesToPlace) {
				cout << "Invalid number. Please enter a number from 0 to " << nbArmiesToPlace << "." << endl;
			
			}
			else {
				validNB = true;
			}
		}
		validNB = false;
		
		// Results
		myTerritories.at(countryNB)->nbArmies += nbOfUnits;
		nbArmiesToPlace -= nbOfUnits;

		cout << "You placed " << nbOfUnits << " armies on " << myTerritories.at(countryNB)->name << "." << endl;
		cout << "You have " << nbArmiesToPlace << " left." << endl << endl;
	}
	
	cout << "This is the updated list of countries (and armies): " << endl;
	getCountries();

	cout << endl << "---------------------------------------------------------------------- \n"
					"////////////////////// END REINFORCE PHASE ///////////////////////  \n"
					"----------------------------------------------------------------------" << endl;

}

/***********************************************   ASSIGNMENT #2 - PART 5 **********************************************/
// ATTACKING PHASE
/*	
	Player is allowed to declare a series of attacks to try to gain control of additional countries, 
	and eventually control the entire map.
*/
void Player::attack() {
	char ans;
	int countryNB, nbrNB, dicesAttack, dicesDefend;
	bool validCountry = false, validDice = false, attackOver = false, validMoveArmy = false, validNbr = false;

	cout << "---------------------------------------------------------------------- \n"
		"////////////////////// BEGIN ATTACK PHASE ///////////////////////  \n"
		"----------------------------------------------------------------------" << endl;

	// Player chooses if they want to attack or not
	while (!attackOver) {
		cout << "Do you want to attack a country? ([Y] = Yes, [N] = No.)" << endl;
		cin >> ans;
		cout << endl;

		if (ans == 'y' || ans == 'Y') {
			cout << "Here is a list of all your countries :" << endl;
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
				else if (!checkValidNeighbors_Attack(myTerritories.at(countryNB))) {
					cout << "This country doesn't have any neighbors owned by other players." << endl;
				}
				else {
					validCountry = true;
				}
			}
			validCountry = false;

			// Player chooses on of the country's neighbor to attack
			cout << endl << "Here are the neighbors of " << myTerritories.at(countryNB)->name << ": ";
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
			
			if (defenderCountry->nbArmies <= 0) { // Defender country loses
				defenderCountry->owner->removeCountry(defenderCountry); // remove country from other player's list
				defenderCountry->owner = this; // player now owns the defender country
				myTerritories.push_back(defenderCountry); // add it to owned territories

				cout << "Defending country has been defeated. This country now belong to the attacking player."
					<< endl << "Attacking player now needs to move at least 1 army from the attacking country to their new country." << endl;

				// Move a number of armies from one country to another
				moveArmies(myTerritories.at(myTerritories.size() - 1), myTerritories.at(countryNB)); 	// receiver, giver
			} 
			else if (myTerritories.at(countryNB)->nbArmies == 0) { // Attacking country loses
				cout << "Attacking country has been defeated. This country now belong to the defending player."
					<< endl << "Defending player now needs to move at least 1 army from the defending country to their new country." << endl;

				// Move a number of armies from one country to another
				moveArmies(myTerritories.at(countryNB), defenderCountry); 	// receiver, giver

				myTerritories.at(countryNB)->owner = defenderCountry->owner; // player now owns the defender country
				defenderCountry->owner->addCountry(myTerritories.at(countryNB));// add it to other player's territories
				removeCountry(myTerritories.at(countryNB)); // remove country from player's list

			}
		}
		else if (ans == 'n' || ans == 'N') { // Player doesn't want to attack
			attackOver = true;
		}
		else {
			clearInput();
		}
	}
	cout << endl << "---------------------------------------------------------------------- \n"
					"////////////////////// END ATTACKING PHASE ///////////////////////  \n"
					"----------------------------------------------------------------------" << endl;
}


/***********************************************   ASSIGNMENT #2 - PART 6 **********************************************/
// FORTIFICATION PHASE
/*	After Attack Phase is complete:
		Player may move as many armies as they want in to a NEIGHBOURING country that they own.
		Player may only do this ONE time (you can't fortify multiple countries).
*/
void Player::fortify() {
	// Variables borrowed from Attack()
	int countryNB, nbrNB;
	bool validCountry = false, validNbr = false;

	// Variables used in Fortify method:
	bool fortificationPhaseIsHappening = true; // Needed to end fortification phase if player does not want to fortify
	bool playerWantsToFortifyAnswerIsValid = false;
	bool validNumberOfArmies = false;
	char playerWantsToFortifyAnswer;
	int numberOfFortifyingArmies;

	cout << "---------------------------------------------------------------------- \n"
		"///////////////////// BEGIN FORTIFICATION PHASE //////////////////////  \n"
		"----------------------------------------------------------------------" << endl;
	while (fortificationPhaseIsHappening == true) {

		/* PART 1) Ask if Player wants to fortify a country (if "NO", Player's turn is finished.)
		*/
		while (playerWantsToFortifyAnswerIsValid == false) {
			cout << "Do you wish to fortify one of your countries? ([Y] = Yes, [N] = No.)" << endl;
			cin >> playerWantsToFortifyAnswer;

			if (cin.fail()) {
				clearInput();
			}
			if ((playerWantsToFortifyAnswer == 'Y') || (playerWantsToFortifyAnswer == 'y') || (playerWantsToFortifyAnswer == 'N') || (playerWantsToFortifyAnswer == 'n')) {
				playerWantsToFortifyAnswerIsValid = true; // Answer is valid "Yes" or "No" 
			}
			else {
				std::cout << "Invalid selection. Answer must be [Y] for Yes, or [N] for No." << endl;
				playerWantsToFortifyAnswerIsValid = false; // Answer not valid, keep looping
			}
		}
		// If player does not want to fortify, exit fortify method
		if ((playerWantsToFortifyAnswer == 'N') || (playerWantsToFortifyAnswer == 'n')) {
			std::cout << "Ok. This ends the fortification phase for this turn." << endl;
			fortificationPhaseIsHappening = false;
			break;
		}

		// METHOD 2) Ask which country will be the "SOURCE" country
		// NEEDED FOR DEMO: Display list of invalid countries that can't be selected. 
		//			Invalid countries are: 1) Countries with no neighbours
		//								   2) Countries where all the neighbours only have 1 army each
		cout << endl <<  "Ok. Here is a list of all your countries :" << endl;
		getCountries();
		cin.clear();
		cout << endl << "    NOTE: A SOURCE country can only fortify a TARGET country if: " << endl
					 << "    1) SOURCE and TARGET are neighbours" << endl
					 << "    1) SOURCE and TARGET are owned by same player" << endl
					 << "    2) SOURCE has more than 1 army" << endl << endl;

		// Note: Was going to add a method here to DISPLAY a list of countries that player is not allowed to fortify. Will implement it later.

		// Enter a valid SOURCE country
		while (!validCountry) {
			cout << endl << "Select the country that will be supplying the armies (the SOURCE country): ";
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
			else if(!checkValidNeighbors_Fortify(myTerritories.at(countryNB))){
				cout << "This country has no neighbors that are also owned by you." << endl;
			}
			else {
				validCountry = true;
			}
		}
		validCountry = false;
		// Display player's choice of SOURCE country
		cout << endl << "You selected " << myTerritories.at(countryNB)->name << "." << endl;
		cout << myTerritories.at(countryNB)->name << "'s neighbours are: " << endl << endl;

		// PART 3) After player has selected SOURCE country, ask which neighbour ("TARGET" country) you want to fortify
		// Enter valid TARGET country to fortify
		for (int i = 0; i < myTerritories.at(countryNB)->nbr.size(); i++) {
			if (myTerritories.at(countryNB)->nbr.at(i)->owner == this) {
				cout << "Neighbor #" << i << ": " << myTerritories.at(countryNB)->nbr.at(i)->name
					<< ". Armies: " << myTerritories.at(countryNB)->nbr.at(i)->nbArmies << endl;
			}
		}
		cout << endl << "Note: neighbor countries of " << myTerritories.at(countryNB)->name << " that belong to other players were omitted." << endl;
		while (!validNbr) {
			cout << "Select the neighbor of this country to fortify: ";
			cin >> nbrNB;

			if (cin.fail()) {
				clearInput();
			}
			else if (nbrNB >= myTerritories.at(countryNB)->nbr.size()
				|| nbrNB < 0 || myTerritories.at(countryNB)->nbr.at(nbrNB)->owner != this) {
				cout << "Not a valid number." << endl;
			}
			else {
				validNbr = true;
			}
		}
		validNbr = false;

		// Store neighbor country in a new variable to access to owner easily (changed "defenderCountry" to "targetCountry")
		Country* targetCountry = myTerritories.at(countryNB)->nbr.at(nbrNB);
		cout << "This country belongs to: " << targetCountry->owner->name << endl << endl;

		// PART 4) Move armies to country
		// NEEDED FOR DEMO: Show that player can't take so many armies that would leave less than 1 army in Source country
		// Display the updated number of armies in each country.
		moveArmies(targetCountry, myTerritories.at(countryNB));

		//Display the new army totals for each country
		cout << endl << "This is the updated list of countries (and armies): " << endl;
		getCountries();
		break; // needed to exit Loop

	}//End While Loop: fortificationPhaseIsHappening
	
	cout << endl << "---------------------------------------------------------------------- \n"
					"////////////////////// END FORTIFICATION PHASE ///////////////////////  \n"
					"----------------------------------------------------------------------" << endl;
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

bool checkValidNeighbors_Attack(Country* attacking) {
	for (int i = 0; i < attacking->nbr.size(); i++) {
		if (attacking->nbr.at(i)->owner != attacking->owner)
			return true; // at least one neighbor is not owned by the same player 
	}
	return false;
}

bool checkValidNeighbors_Fortify(Country* attacking) {
	for (int i = 0; i < attacking->nbr.size(); i++) {
		if (attacking->nbr.at(i)->owner == attacking->owner)
			return true; // at least one neighbor is owned by the same player 
	}
	return false;
}
