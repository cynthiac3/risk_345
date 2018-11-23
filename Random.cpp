#include <iostream>
#include "Random.h"
#include <windows.h.>
#include "Player.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h> 

using namespace std;


/* RANDOM COMPUTER PLAYER:
	a random computer player that reinforces at random a random country, attacks a random number of times a random
	country, and fortifies a random countries. 
*/


/***********************************************  REINFORCING PHASE **********************************************/
/*
	 Player gets a number of armies to place on its countries.
*/
void Random::reinforce() {
	int countryNB;

	cout << "---------------------------------------------------------------------- \n"
			"////////////////////// BEGIN REINFORCE PHASE ///////////////////////  \n"
			"----------------------------------------------------------------------" << endl;

	// Choose one country to reinforce at random
	srand(time(NULL)); // Initialize random seed based on the time

	countryNB = rand() % (p->myTerritories.size());	// ... generate random number between 0 and nb of countries-1

	// STEP 1: Player receives armies equals to nb of countries owned divided by 3 rounded down
	int nbArmiesToPlace = floor(p->myTerritories.size() / 3);
	if (nbArmiesToPlace < 3) // min is 3
		nbArmiesToPlace = 3;

	cout << "Based on the number of countries they own, they get " << nbArmiesToPlace << " armies." << endl;

	// STEP 2: Player gets a certain bonus for each continent owned
	int bonusValue = 0;
	if (p->myContinents.size() == 0) {
		cout << "Random computer doesn't own any continents." << endl << "They get 0 bonus armies." << endl;
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

	cout << "Random computer has this many armies to place: " << nbArmiesToPlace << endl << endl;

	// STEP 4: Give armies to random country
	cout << "Random computer's random country is " << p->myTerritories.at(countryNB)->name << " with " << p->myTerritories.at(countryNB)->nbArmies << " armies" << endl;
	p->myTerritories.at(countryNB)->nbArmies += nbArmiesToPlace;
	cout << "Random computer places " << nbArmiesToPlace << " armies on " << p->myTerritories.at(countryNB)->name  << "." << endl << endl;

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
void Random::attack() {
	int dicesAttack, dicesDefend;
	bool validDice = false;

	cout << "---------------------------------------------------------------------- \n"
		"////////////////////// BEGIN ATTACK PHASE ///////////////////////  \n"
		"----------------------------------------------------------------------" << endl;
	
	// Random player attacks a random nb of times - at least 1
	srand(time(NULL)); // Initialize random seed based on the time
	int nbAttacks = (rand() % 4) + 1; // can go up to 5 turns
	int turn = 1;
	cout << endl << "Random player decides to attack " << nbAttacks << " times." << endl;

	do {
		cout << endl << "ATTACK TURN #" << turn << ":" << endl 
			<< "---------------" << endl;
		/* PICK RANDOM COUNTRY */
		srand(time(NULL)); // Initialize random seed based on the time
		bool validCountry = false;
		Country * random = p->myTerritories.at(rand() % (p->myTerritories.size()));

		
		// Check if random found has valid neighbors and has at least 2 armies
		if (checkValidNeighbors_Attack(random) && random->nbArmies >= 2) {
			validCountry = true;
		}
		else {
			cout << endl << "Random computer randomly picked " << random->name << " with " << random->nbArmies << " armies. " << endl
				<<  "but it is not a valid country to attack from." << endl 
				<< "Attack phase is aborted." << endl;
		}

		/* PICK RANDOM NEIGHBOR */
		if (validCountry) {
			cout << endl << "Random country picked by Random computer is: " << random->name << " with " << random->nbArmies << " armies." << endl;

			// Pick random neighbor
			Country* randomNbr = random->nbr.at(rand() % (random->nbr.size()));

			if (randomNbr->owner == p) { // if random neighbor is owned by player, cannot attack
				cout << "Random neighbor picked by computer is " << randomNbr->name << " but it also belongs to " << p->getName() << endl
					<< "Attack is not valid so attack phase is aborted." << endl;
				turn++;
				Sleep(2000);// wait between each turn (for random variables)
				continue;

			}
			else {
				cout << "Random neighbor of " << random->name << " is " << randomNbr->name << " with " << randomNbr->nbArmies << " armies." << endl;
			}

			// Roll dices
			// Find nb of dices to roll for player
			if ((random->nbArmies - 1) >= 3) {
				dicesAttack = (rand() % 3) + 1; // random between 1-3
			}
			else if ((random->nbArmies - 1) >= 2) {
				dicesAttack = (rand() % 2) + 1; // random between 1-2
			}
			else
				dicesAttack = 1; 
			p->getDice()->rollDice(dicesAttack);
			Sleep(2000);

			// Owner of defendent country is a HUMAN
			if (randomNbr->owner->strategy->isHuman()) {
				while (!validDice) {

					cout << endl << "NOTE: the defender's number of dice can only be smaller or equal \n to the number of armies on the defender's country." << endl
						<< "Defender chooses number of dices to roll (1 or 2): " << endl;
					cin >> dicesDefend;

					if (cin.fail()) {
						clearInput();
					}
					else if (dicesDefend > randomNbr->nbArmies) {
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
				if (randomNbr->nbArmies >= 2)
					dicesDefend = 2;
				else
					dicesDefend = 1;
				randomNbr->owner->getDice()->rollDice(dicesDefend);
			}


			// HIGHEST ROLL - Attacker wins
			if (p->dice.containerOfDiceRolls[2] > randomNbr->owner->getDice()->containerOfDiceRolls[2]) {
				randomNbr->nbArmies--;
				cout << "Defender loses 1 army" << endl;
			}
			else { // Attacker loses
				random->nbArmies--;
				cout << "Attacker loses 1 army" << endl;
			}
			// MID ROLL - Only if both players rolled at least 2 dices
			if (dicesAttack > 1 && dicesDefend > 1) {
				if (p->dice.containerOfDiceRolls[1] > randomNbr->owner->getDice()->containerOfDiceRolls[1]) {
					randomNbr->nbArmies--;
					cout << "Defender loses 1 army" << endl;
				}
				else { // Attacker loses
					random->nbArmies--;
					cout << "Attacker loses 1 army" << endl;
				}
			}

			cout << endl << "Result: " << endl << random->name << ": " << random->nbArmies << " armies." << endl
				<< randomNbr->name << ": " << randomNbr->nbArmies << " armies" << endl << endl;

			// Check if defender has 0 armies 
			if (randomNbr->nbArmies <= 0) { // Defender country loses
				randomNbr->owner->removeCountry(randomNbr); // remove country from other player's list

				// Check if defending player is defeated
				Player* p2;
				if (randomNbr->owner->myTerritories.size() == 0) {
					p2 = randomNbr->owner;
				}
				else {
					p2 = NULL;
				}

				randomNbr->owner = p; // player now owns the defender country
				p->myTerritories.push_back(randomNbr); // add it to owned territories

				cout << "-------------------------------------------------------------------------------------" << endl;
				cout << "Defending country has been defeated. This country now belong to the attacking player." << endl;

				// Random number of armies moved (1 to nb armies on attacking country -1) so that there is at least 1 country left
				int value = (rand() % (random->nbArmies - 1)) +1;
				cout << "Random number of armies transferred is " << value << "." << endl
					<< "NOTE: minimum value of armies moved is 1." << endl;

				// Move a number of armies from one country to another
				random->nbArmies -= value;
				p->myTerritories.at(p->myTerritories.size() - 1)->nbArmies += value;

				// Pick up a new cards because country is conquered
				p->getHand()->pickUpCard();
				cout << endl << "Because you conquered one new country, you pick up one new risk card." << endl;
				p->getHand()->printHand();

				// Check if a card exchange has to be made
				defenderEliminated(p, p2);
				cout << "-------------------------------------------------------------------------------------" << endl << endl;
			}

			//Display the new army totals for each country
			p->getCountries();
		}
		turn++;
		Sleep(2000);// wait between each turn (for random variables)

	} while (nbAttacks >= turn);

	cout << endl << "---------------------------------------------------------------------- \n"
					"////////////////////// END ATTACKING PHASE ///////////////////////  \n"
					"----------------------------------------------------------------------" << endl;
}

/***********************************************   FORTIFICATION PHASE **********************************************/
/*	After Attack Phase is complete:
		Player may move as many armies as they want in to a NEIGHBOURING country that they own.
		Player may only do this ONE time (you can't fortify multiple countries).
*/
void Random::fortify() {
	int countryNB, neighborNB;
	bool validCountry = false, validNeighbor = false;
	cout << "---------------------------------------------------------------------- \n"
			"///////////////////// BEGIN FORTIFICATION PHASE //////////////////////  \n"
			"----------------------------------------------------------------------" << endl;

	// Choose one country to fortify at random
	srand(time(NULL)); // Initialize random seed based on the time

	countryNB = rand() % (p->myTerritories.size());	// ... generate random number between 0 and nb of countries-1

	// Double check if weakest found has valid neighbors (in case it is still country at index 0)
	if (checkValidNeighbors_Fortify(p->myTerritories.at(countryNB))) {
		validCountry = true;
	}
	else {
		cout << "Random computer selected " << p->myTerritories.at(countryNB)->name << " but this country doesn't have a neighbor that can fortify it." << endl;
	}

	// Choose random neighbor
	if (validCountry) {
		cout << "Random country selected is: " << p->myTerritories.at(countryNB)->name << " with " << p->myTerritories.at(countryNB)->nbArmies << " armies." << endl;
		
		neighborNB = rand() % (p->myTerritories.at(countryNB)->nbr.size());
		
		// Check if random neighbor is valid or not (belong to same player)
		if (p->myTerritories.at(countryNB)->nbr.at(neighborNB)->owner == p) {
			cout << "Random neighbor selected is: " << p->myTerritories.at(countryNB)->nbr.at(neighborNB)->name << " with "
				<< p->myTerritories.at(countryNB)->nbr.at(neighborNB)->nbArmies << " armies." << endl;
			validNeighbor = true;
		}
		else {
			cout << "Random neighbor selected is " << p->myTerritories.at(countryNB)->nbr.at(neighborNB)->name << " but it doesn't belong to " << p->getName()
				<< ".\nFortification cannot proceed. " << endl;
		}
		
		if (validNeighbor) {
			// Transfer the armies from random neighbor to random country
			int value = floor(p->myTerritories.at(countryNB)->nbr.at(neighborNB)->nbArmies / 2);
			cout << "Number of armies transferred is " << p->myTerritories.at(countryNB)->nbr.at(neighborNB)->nbArmies << " / 2  = " << value << endl << endl;
			p->myTerritories.at(countryNB)->nbr.at(neighborNB)->nbArmies -= value;
			p->myTerritories.at(countryNB)->nbArmies += value;

			//Display the new army totals for each country
			p->getCountries();
		}
	}

	cout << endl << "---------------------------------------------------------------------- \n"
					"////////////////////// END FORTIFICATION PHASE ///////////////////////  \n"
					"----------------------------------------------------------------------" << endl;
}