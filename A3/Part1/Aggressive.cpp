#include <iostream>
#include "Aggressive.h"
#include <windows.h.>
#include "Player.h"

using namespace std;


/* AGGRESSIVE COMPUTER PLAYER:
	an aggressive computer player that focuses on attack (reinforces its strongest
	country, then always attack with it until it cannot attack anymore, then fortifies in order to maximize aggregation of
	forces in one country),
*/


/***********************************************  REINFORCING PHASE **********************************************/
/*
	 Player gets a number of armies to place on its countries.
*/
void Aggressive::reinforce() {

	cout << "---------------------------------------------------------------------- \n"
			"////////////////////// BEGIN REINFORCE PHASE ///////////////////////  \n"
			"----------------------------------------------------------------------" << endl;

	/* FIND STRONGEST COUNTRY */
	Country * strongest = p->myTerritories.at(0);
	for (int i = 1; i < p->myTerritories.size(); i++) {
		if (strongest->nbArmies < p->myTerritories.at(i)->nbArmies) {
			strongest = p->myTerritories.at(i);
		}
	}

	// STEP 1: Player receives armies equals to nb of countries owned divided by 3 rounded down
	int nbArmiesToPlace = floor(p->myTerritories.size() / 3);
	if (nbArmiesToPlace < 3) // min is 3
		nbArmiesToPlace = 3;

	cout << "Based on the number of countries they own, they get " << nbArmiesToPlace << " armies." << endl;

	// STEP 2: Player gets a certain bonus for each continent owned
	int bonusValue = 0;
	if (p->myContinents.size() == 0) {
		cout << "Aggressive computer doesn't own any continents." << endl << "They get 0 bonus armies." << endl;
	}
	else {
		for (int x = 0; x < p->myContinents.size(); x++) {
			cout << "They own " << p->myContinents.at(x)->name << " so they get " << p->myContinents.at(x)->bonus << " bonus armies." << endl;
			bonusValue += p->myContinents.at(x)->bonus;
		}
		nbArmiesToPlace += bonusValue;
		cout << "Computer gets a total of " << bonusValue << " bonus armies for a new total of " << nbArmiesToPlace << " armies." << endl;
	}

	// STEP 3: Player can exchange cards for armies
	int resultingArmies = p->hand.exchangeComputer();
	if (resultingArmies == 0)
		cout << "Computer can't make an exchange. They do not get any armies." << endl;
	else
		cout << "This is the computer's exchange #" << p->hand.numberOfExchanges << ", they get " << resultingArmies << " armies." << endl;
	nbArmiesToPlace += resultingArmies;

	cout << "Aggressive computer has this many armies to place: " << nbArmiesToPlace << endl << endl;

	// STEP 4: Give armies to weakest country owned
	cout << "Aggressive computer's strongest country is " << strongest->name << " with " << strongest->nbArmies << " armies" << endl;
	strongest->nbArmies += nbArmiesToPlace;
	cout << "Aggressive computer places " << nbArmiesToPlace << " armies on " << strongest->name << "." << endl;

	// Results
	cout << endl << "This is the updated list of countries (and armies): " << endl;
	p->getCountries();

	cout << endl << "---------------------------------------------------------------------- \n"
					"////////////////////// END REINFORCE PHASE ///////////////////////  \n"
					"----------------------------------------------------------------------" << endl;
}


/*********************************************** ATTACKING PHASE **********************************************/
/*
	Player is allowed to declare a series of attacks to try to gain control of additional countries,
	and eventually control the entire map.
*/
void Aggressive::attack() {
	int dicesAttack, dicesDefend;
	bool validDice = false;

	cout << "---------------------------------------------------------------------- \n"
		"////////////////////// BEGIN ATTACK PHASE ///////////////////////  \n"
		"----------------------------------------------------------------------" << endl;
	bool canAttack = true;
	do {
		/* FIND STRONGEST COUNTRY */
		bool validCountry = false;
		Country * strongest = p->myTerritories.at(0);

		for (int i = 1; i < p->myTerritories.size(); i++) {
			// Finds a country owned with more armies than current temp strongest country
			if (strongest->nbArmies < p->myTerritories.at(i)->nbArmies) {
				// Verifies if country has a neighbor that they can attack & country has more than 2 armies
				if (checkValidNeighbors_Attack(p->myTerritories.at(i)) && (p->myTerritories.at(i)->nbArmies >= 2)) {
					strongest = p->myTerritories.at(i);
				}
			}
		}
		// Double check if weakest found has valid neighbors (in case it is still country at index 0)
		if (checkValidNeighbors_Attack(strongest) && strongest->nbArmies >= 2) {
			validCountry = true;
		}
		else {
			cout << endl << "Aggressive computer currently doesn't have any strong country that can attack one of its neighbors." << endl;
			canAttack = false;
		}

		/* FIND WEAKEST NEIGHBOR */
		if (validCountry) {
			cout <<  endl << "Strongest country of Aggressive computer is: " << strongest->name << " with " << strongest->nbArmies << " armies." << endl;
			Country* weakestNbr = strongest->nbr.at(0);
			bool firstFound = false;

			// Find weakest neighbor of strongest country & not owned by aggressive player
			for (int j = 0; j < strongest->nbr.size(); j++) {
				if (!firstFound && strongest->nbr.at(j)->owner != p) {
					weakestNbr = strongest->nbr.at(j);
					firstFound = true;
				}
				else {
					if (weakestNbr->nbArmies > strongest->nbr.at(j)->nbArmies && strongest->nbr.at(j)->owner != p) {
						weakestNbr = strongest->nbr.at(j);
					}
				}
			}
			cout << "Weakest neighbor of " << strongest->name << " is " << weakestNbr->name << " with " << weakestNbr->nbArmies << " armies." << endl;

			// Roll dices
			// Find nb of dices to roll for player
			if ((strongest->nbArmies - 1) >= 3)
				dicesAttack = 3;
			else if ((strongest->nbArmies - 1) >= 2)
				dicesAttack = 2;
			else
				dicesAttack = 1;
			p->getDice()->rollDice(dicesAttack);
			Sleep(2000);
			
			// Owner of defendent country is a HUMAN
			if (weakestNbr->owner->strategy->isHuman()) {
				while (!validDice) {

					cout << endl << "NOTE: the defender's number of dice can only be smaller or equal \n to the number of armies on the defender's country." << endl
						<< "Defender chooses number of dices to roll (1 or 2): " << endl;
					cin >> dicesDefend;

					if (cin.fail()) {
						clearInput();
					}
					else if (dicesDefend > weakestNbr->nbArmies) {
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
			}
			else { // Owner of defendent country is a COMPUTER
				if (weakestNbr->nbArmies >= 2)
					dicesDefend = 2;
				else
					dicesDefend = 1;
				weakestNbr->owner->getDice()->rollDice(dicesDefend);		
			}


			// HIGHEST ROLL - Attacker wins
			if (p->dice.containerOfDiceRolls[2] > weakestNbr->owner->getDice()->containerOfDiceRolls[2]) {
				weakestNbr->nbArmies--;
				cout << "Defender loses 1 army" << endl;
			}
			else { // Attacker loses
				strongest->nbArmies--;
				cout << "Attacker loses 1 army" << endl;
			}
			// MID ROLL - Only if both players rolled at least 2 dices
			if (dicesAttack > 1 && dicesDefend > 1) {
				if (p->dice.containerOfDiceRolls[1] > weakestNbr->owner->getDice()->containerOfDiceRolls[1]) {
					weakestNbr->nbArmies--;
					cout << "Defender loses 1 army" << endl;
				}
				else { // Attacker loses
					strongest->nbArmies--;
					cout << "Attacker loses 1 army" << endl;
				}
			}

			cout << endl << "Result: " << endl << strongest->name << ": " << strongest->nbArmies << " armies." << endl
				<< weakestNbr->name << ": " << weakestNbr->nbArmies << " armies" << endl << endl;

			// Check if defender has 0 armies 
			if (weakestNbr->nbArmies <= 0) { // Defender country loses
				weakestNbr->owner->removeCountry(weakestNbr); // remove country from other player's list

				// Check if defending player is defeated
				Player* p2;
				if (weakestNbr->owner->myTerritories.size() == 0) {
					p2 = weakestNbr->owner;
				}
				else {
					p2 = NULL;
				}

				weakestNbr->owner = p; // player now owns the defender country
				p->myTerritories.push_back(weakestNbr); // add it to owned territories

				cout << "-------------------------------------------------------------------------------------" << endl;
				cout << "Defending country has been defeated. This country now belong to the attacking player." << endl;
				int value = floor(strongest->nbArmies / 3);
				if (value < 1)
					value = 1;
				cout << "Number of armies transferred is " << strongest->nbArmies << " / 3  = " << value << "." << endl
					<< "NOTE: minimum value of armies moved is 1." << endl;

				// Move a number of armies from one country to another
				strongest->nbArmies -= value;
				p->myTerritories.at(p->myTerritories.size() - 1)->nbArmies += value;

				// Pick up a new cards because country is conquered
				p->getHand()->pickUpCard();
				cout << "Because you conquered one new country, you pick up one new risk card. Here is your new hand:" << endl;
				p->getHand()->printHand();			

				// Check if a card exchange has to be made
				defenderEliminated(p,p2);
				cout << "-------------------------------------------------------------------------------------" << endl;
			}

			//Display the new army totals for each country
			cout << endl << "This is the updated list of countries (and armies): " << endl;
			p->getCountries();
		}

	}while (canAttack);

	cout << endl << "---------------------------------------------------------------------- \n"
					"////////////////////// END ATTACKING PHASE ///////////////////////  \n"
					"----------------------------------------------------------------------" << endl;
}

/***********************************************   FORTIFICATION PHASE **********************************************/
/*	After Attack Phase is complete:
		Player may move as many armies as they want in to a NEIGHBOURING country that they own.
		Player may only do this ONE time (you can't fortify multiple countries).
*/
void Aggressive::fortify() {

	cout << "---------------------------------------------------------------------- \n"
			"///////////////////// BEGIN FORTIFICATION PHASE //////////////////////  \n"
			"----------------------------------------------------------------------" << endl;

	/* FIND STRONGEST COUNTRY */
	bool validCountry = false;
	Country * strongest = p->myTerritories.at(0);

	for (int i = 1; i < p->myTerritories.size(); i++) {
		// Finds a country owned with less armies than current temp weakest country
		if (strongest->nbArmies < p->myTerritories.at(i)->nbArmies) {
			// Verifies if country has a neighbor that can fortify it
			if (checkValidNeighbors_Fortify(p->myTerritories.at(i))) {
				strongest = p->myTerritories.at(i);
			}
		}
	}
	// Double check if weakest found has valid neighbors (in case it is still country at index 0)
	if (checkValidNeighbors_Fortify(strongest)) {
		validCountry = true;
	}
	else {
		cout << "Aggressive computer currently doesn't have any strong country that can be fortified by one of its neighbors." << endl;
	}

	/* FIND STRONGEST NEIGHBOR */
	if (validCountry) {
		cout << "Strongest country of Aggressive computer is: " << strongest->name << " with " << strongest->nbArmies << " armies." << endl;
		Country* strongestNbr = strongest->nbr.at(0);
		bool firstFound = false;

		// Find strongest neighbor of weakest country & also owned by aggressive player
		for (int j = 0; j < strongest->nbr.size(); j++) {
			if (!firstFound && strongest->nbr.at(j)->owner == p) {
				strongestNbr = strongest->nbr.at(j);
				firstFound = true;
			}
			else {
				if (strongestNbr->nbArmies < strongest->nbr.at(j)->nbArmies && strongest->nbr.at(j)->owner == p) {
					strongestNbr = strongest->nbr.at(j);
				}
			}
		}

		cout << "Strongest neighbor of " << strongest->name << " is " << strongestNbr->name << " with " << strongestNbr->nbArmies << " armies." << endl;

		// Transfer the armies from strongest neighbor to weakest country
		int value = floor(strongestNbr->nbArmies / 2);
		cout << "Number of armies transferred is " << strongestNbr->nbArmies << " / 2  = " << value << endl;
		strongestNbr->nbArmies -= value;
		strongest->nbArmies += value;

		//Display the new army totals for each country
		cout << endl << "This is the updated list of countries (and armies): " << endl;
		p->getCountries();
	}

	cout << endl << "---------------------------------------------------------------------- \n"
		"////////////////////// END FORTIFICATION PHASE ///////////////////////  \n"
		"----------------------------------------------------------------------" << endl;
}

