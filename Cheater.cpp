#include <iostream>
#include "Cheater.h"
#include <windows.h.>
#include "Player.h"

using namespace std;


/* CHEATER COMPUTER PLAYER:
	a cheater computer player whose reinforce method doubles the number of armies off all its countries, whose attack
	method automatically conquers all the neighbors of all its countries, and a fortify method that doubles the number
	of armies on countries that have neighbors that belong to other players
*/


/***********************************************  REINFORCING PHASE **********************************************/
/*
	 Player gets a number of armies to place on its countries.
*/
void Cheater::reinforce() {
	cout << "---------------------------------------------------------------------- \n"
			"////////////////////// BEGIN REINFORCE PHASE ///////////////////////  \n"
			"----------------------------------------------------------------------" << endl;
	// Display current list of countries and their armies
	p->getCountries();
	cout << endl << "Cheater player doubles the number of armies on all its countries." << endl << endl;

	// Double the nb of armies on each countries of the player
	for (int i = 0; i < p->myTerritories.size(); i++) {
		p->myTerritories.at(i)->nbArmies *= 2;
	}

	// Results
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
void Cheater::attack() {
	cout <<  "---------------------------------------------------------------------- \n"
			 "////////////////////// BEGIN ATTACK PHASE ///////////////////////  \n"
			 "----------------------------------------------------------------------" << endl;
	
	// Display current list of countries and their armies
	p->getCountries();
	cout << endl << "Cheater player conquers all the neighbors of the countries that they own." << endl << endl;
	
	// Create a new vector to save the countries conquered
	vector<Country*> conqueredCountries;

	for (int i = 0; i < p->myTerritories.size(); i++) { // for every  owned countries
		for (int j = 0; j < p->myTerritories.at(i)->nbr.size(); j++) {  // for every neighbor of one country
			if (p->myTerritories.at(i)->nbr.at(j)->owner != p) {
				// add neighbor to countries conquered
				conqueredCountries.push_back(p->myTerritories.at(i)->nbr.at(j));

				p->myTerritories.at(i)->nbr.at(j)->owner->removeCountry(p->myTerritories.at(i)->nbr.at(j)); // remove country from other player's list

				// Check if defending player is defeated
				Player* p2;
				if (p->myTerritories.at(i)->nbr.at(j)->owner->myTerritories.size() == 0) {
					p2 = p->myTerritories.at(i)->nbr.at(j)->owner;
				}
				else {
					p2 = NULL;
				}

				p->myTerritories.at(i)->nbr.at(j)->owner = p; // change owenership of the neighbor to current player	

				// Check if a card exchange has to be made
				defenderEliminated(p, p2); 
			}
		}
	}
	// Display countries conquered
	if (conqueredCountries.size() == 0) {
		cout << p->getName() << " cheater computer did not conquer any countries." << endl;
	}
	else {
		cout << p->getName() << " cheater computer conquered these countries: " << endl;
		for (int i = 0; i < conqueredCountries.size(); i++) {
			cout << "Territory #" << i << ": " << conqueredCountries.at(i)->name
				<< ". Armies: " << conqueredCountries.at(i)->nbArmies << endl;
		}
	}

	// Add all conquered countries to current player's list
	p->myTerritories.insert(p->myTerritories.end(), conqueredCountries.begin(), conqueredCountries.end());

	// Results
	cout << endl;
	p->getCountries();
	


	cout << endl << "---------------------------------------------------------------------- \n"
					"////////////////////// END ATTACK PHASE ///////////////////////  \n"
					"----------------------------------------------------------------------" << endl;

}

/***********************************************   FORTIFICATION PHASE **********************************************/
/*	After Attack Phase is complete:
		Player may move as many armies as they want in to a NEIGHBOURING country that they own.
		Player may only do this ONE time (you can't fortify multiple countries).
*/
void Cheater::fortify() {

	cout << "---------------------------------------------------------------------- \n"
			"////////////////////// BEGIN FORTIFICATION PHASE ///////////////////////  \n"
			"----------------------------------------------------------------------" << endl;

	// Display current list of countries and their armies
	p->getCountries();
	cout << endl << "Cheater player doubles the number of armies on its countries that have \nneighbors that belong to other players." << endl << endl;

	// Double the nb of armies on each countries of the player
	for (int i = 0; i < p->myTerritories.size(); i++) {
		if (checkValidNeighbors_Attack(p->myTerritories.at(i))) { // if they can attack one of their neighbor, then one belongs to another player
			p->myTerritories.at(i)->nbArmies *= 2;
		}	
	}

	// Results
	p->getCountries();

	cout << endl << "---------------------------------------------------------------------- \n"
					"////////////////////// END FORTIFICATION PHASE ///////////////////////  \n"
					"----------------------------------------------------------------------" << endl;

}