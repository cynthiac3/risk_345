#include <iostream>
#include "Benevolent.h"
#include <windows.h.>
#include "Player.h"

using namespace std;

void clearInputB();
void moveArmiesB(Country* receiver, Country* giver);
bool checkValidNeighbors_AttackB(Country* attacking);
bool checkValidNeighbors_FortifyB(Country* attacking);

/*	BENEVOLENT COMPUTER PLAYER:
	a benevolent computer player that focuses on protecting its weak countries (reinforces
	its weakest countries, never attacks, then fortifies in order to move armies to weaker countries). 
*/


/***********************************************  REINFORCING PHASE **********************************************/
/*
	 Player gets a number of armies to place on its countries.
*/
void Benevolent::reinforce() {
	cout << "Benevolent computer player's reinforce method." << endl;

	cout << "---------------------------------------------------------------------- \n"
			"////////////////////// BEGIN REINFORCE PHASE ///////////////////////  \n"
			"----------------------------------------------------------------------" << endl;

	/* FIND WEAKEST COUNTRY */
	Country * weakest = p->myTerritories.at(0);
	for (int i = 1; i < p->myTerritories.size(); i++) {
		if (weakest->nbArmies > p->myTerritories.at(i)->nbArmies) {
			weakest = p->myTerritories.at(i);
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
		cout << "Benevolent computer doesn't own any continents." << endl << "They get 0 bonus armies." << endl;
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

	cout << "Benevolent computer has this many armies to place: " << nbArmiesToPlace << endl << endl;

	// STEP 4: Give armies to weakest country owned
	cout << "Benevolent computer's weakest country is " << weakest->name << " with " << weakest->nbArmies << " armies" << endl;
	weakest->nbArmies += nbArmiesToPlace;
	cout << "Benevolent computer places " << nbArmiesToPlace << " armies on " << weakest->name << "." << endl;

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
void Benevolent::attack() {
	cout << "Benevolent computer player's attack method." << endl;

	cout << "Benevolent computer decides not to attack." << endl;
}


/***********************************************   FORTIFICATION PHASE **********************************************/
/*	After Attack Phase is complete:
		Player may move as many armies as they want in to a NEIGHBOURING country that they own.
		Player may only do this ONE time (you can't fortify multiple countries).
*/
void Benevolent::fortify() {
	cout << "Benevolent computer player's fortify method." << endl;

	cout << "---------------------------------------------------------------------- \n"
		"///////////////////// BEGIN FORTIFICATION PHASE //////////////////////  \n"
		"----------------------------------------------------------------------" << endl;

	/* FIND WEAKEST COUNTRY */
	bool validCountry = false; 
	Country * weakest = p->myTerritories.at(0);

	for (int i = 1; i < p->myTerritories.size(); i++) {
		// Finds a country owned with less armies than current temp weakest country
		if (weakest->nbArmies > p->myTerritories.at(i)->nbArmies) {
			// Verifies if country has a neighbor that can fortify it
			if (checkValidNeighbors_FortifyB(weakest)) {
				weakest = p->myTerritories.at(i);
			}	
		}
	}
	// Double check if weakest found has valid neighbors (in case it is still country at index 0)
	if (checkValidNeighbors_FortifyB(weakest)) {
		validCountry = true;
	}
	else {
		cout << "Benevolent computer currently doesn't have any weak country that can be fortified by one of its neighbors." << endl;
	}

	/* FIND STRONGEST NEIGHBOR */
	if (validCountry) {
		cout << "Weakest country of Benevolent computer is: " << weakest->name << " with " << weakest->nbArmies << " armies." << endl;
		Country* strongestNbr = weakest->nbr.at(0);
		bool firstFound = false;
		// Find strongest neighbor of weakest country
		for (int j = 1; j < weakest->nbr.size(); j++) {
			if (!firstFound && weakest->nbr.at(j)->owner == p) {
				strongestNbr = weakest->nbr.at(j);
				firstFound = true;
			}
			else {
				if (strongestNbr->nbArmies < weakest->nbr.at(j)->nbArmies && weakest->nbr.at(j)->owner == p) {
					strongestNbr = weakest->nbr.at(j);
				}
			}
		}
		cout << "Strongest neighbor of " << weakest->name << " is " << strongestNbr->name << " with " << strongestNbr->nbArmies << " armies." << endl;
		// Transfer the armies from strongest neighbor to weakest country
		int value = floor(strongestNbr->nbArmies / 2);
		cout << "Number of armies transferred is " << strongestNbr->nbArmies << " / 2  = " << value << endl;
		strongestNbr->nbArmies -= value;
		weakest->nbArmies += value;

		//Display the new army totals for each country
		cout << endl << "This is the updated list of countries (and armies): " << endl;
		p->getCountries();
	}

	cout << endl << "---------------------------------------------------------------------- \n"
		"////////////////////// END FORTIFICATION PHASE ///////////////////////  \n"
		"----------------------------------------------------------------------" << endl;
}

void clearInputB() {
	cout << "Not a valid answer." << endl;
	cin.clear();
	std::string ignoreLine; //read the invalid input into it
	std::getline(cin, ignoreLine); //read the line till next space
}


void moveArmiesB(Country* receiver, Country* giver) {
	bool validMoveArmy = false;
	int movingArmies;

	while (!validMoveArmy) {
		cout << "Please enter the number of armies you want to move: " << endl;
		cin >> movingArmies;

		if (cin.fail()) {
			clearInputB();
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

bool checkValidNeighbors_AttackB(Country* attacking) {
	for (int i = 0; i < attacking->nbr.size(); i++) {
		if (attacking->nbr.at(i)->owner != attacking->owner)
			return true; // at least one neighbor is not owned by the same player 
	}
	return false;
}

bool checkValidNeighbors_FortifyB(Country* attacking) {
	for (int i = 0; i < attacking->nbr.size(); i++) {
		if (attacking->nbr.at(i)->owner == attacking->owner)
			return true; // at least one neighbor is owned by the same player 
	}
	return false;
}