#include <iostream>
#include "Aggressive.h"
#include <windows.h.>
#include "Player.h"

using namespace std;

void clearInputA();
void moveArmiesB(Country* receiver, Country* giver);
bool checkValidNeighbors_AttackA(Country* attacking);
bool checkValidNeighbors_FortifyA(Country* attacking);

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
	cout << "Aggressive computer player's reinforce method." << endl;

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
	cout << "Aggressive computer player's attack method." << endl;

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
				if (checkValidNeighbors_AttackA(p->myTerritories.at(i)) && (p->myTerritories.at(i)->nbArmies > 2)) {
					strongest = p->myTerritories.at(i);
				}
			}
		}
		// Double check if weakest found has valid neighbors (in case it is still country at index 0)
		if (checkValidNeighbors_AttackA(strongest) && strongest->nbArmies > 2) {
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

			// TODO: Roll dices
			// Find nb of dices to roll for player
			if (strongest->nbArmies - 1 >= 3)
				dicesAttack = 3;
			else
				dicesAttack = 2;
			p->getDice()->rollDice(dicesAttack);
			Sleep(2000);
			// Assume owner of defendent country is a computer 
			if (weakestNbr->nbArmies >= 2)
				dicesDefend = 2;
			else
				dicesDefend = 1;
			weakestNbr->owner->getDice()->rollDice(dicesDefend);

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
				weakestNbr->owner = p; // player now owns the defender country
				p->myTerritories.push_back(weakestNbr); // add it to owned territories

				cout << "Defending country has been defeated. This country now belong to the attacking player." << endl;
				int value = floor(strongest->nbArmies / 3);
				if (value < 1)
					value = 1;
				cout << "Number of armies transferred is " << strongest->nbArmies << " / 3  = " << value << "." << endl
					<< "NOTE: minimum value of armies moved is 1." << endl;
				strongest->nbArmies -= value;
				p->myTerritories.at(p->myTerritories.size() - 1)->nbArmies += value;
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
	cout << "Aggressive computer player's fortify method." << endl;

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
			if (checkValidNeighbors_FortifyA(p->myTerritories.at(i))) {
				strongest = p->myTerritories.at(i);
			}
		}
	}
	// Double check if weakest found has valid neighbors (in case it is still country at index 0)
	if (checkValidNeighbors_FortifyA(strongest)) {
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

void clearInputA() {
	cout << "Not a valid answer." << endl;
	cin.clear();
	std::string ignoreLine; //read the invalid input into it
	std::getline(cin, ignoreLine); //read the line till next space
}


void moveArmiesA(Country* receiver, Country* giver) {
	bool validMoveArmy = false;
	int movingArmies;

	while (!validMoveArmy) {
		cout << "Please enter the number of armies you want to move: " << endl;
		cin >> movingArmies;

		if (cin.fail()) {
			clearInputA();
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

bool checkValidNeighbors_AttackA(Country* attacking) {
	for (int i = 0; i < attacking->nbr.size(); i++) {
		if (attacking->nbr.at(i)->owner != attacking->owner)
			return true; // at least one neighbor is not owned by the same player 
	}
	return false;
}

bool checkValidNeighbors_FortifyA(Country* attacking) {
	for (int i = 0; i < attacking->nbr.size(); i++) {
		if (attacking->nbr.at(i)->owner == attacking->owner)
			return true; // at least one neighbor is owned by the same player 
	}
	return false;
}