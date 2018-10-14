#include <iostream>		/* cout */
#include <stdio.h>    
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "Dice.h"
#include <algorithm>  /* sort */

using namespace std;

/*** Method 1 ***/
// Player can choose how many dice (1, 2, or 3) to roll
int Dice::decideHowManyDiceToRoll()
{
	bool numberOfDiceValid = false;	
	howManyDice = 0;  // Initialize number of dice to 0 for this turn

	while (numberOfDiceValid == false) {
		cout << "Enter number of dice to roll (1, 2, or 3 dice):" << endl;
		cin >> howManyDice;
		if ((howManyDice > 3) || (howManyDice < 1)) {
			cout << "Number of dice must be 1, 2, or 3. Try again." << endl;
			numberOfDiceValid = false;
		}
		else {
			cout << "Excellent. You will roll " << howManyDice << " dice." << endl;
			numberOfDiceValid = true;
		}
	}
	return howManyDice;
}


/*** Method 2 ***/
// Generate & display random dice roll values
// Also keeps track of how many times each value (1-6) has occurred, and stores this count in an array[6].
void Dice::rollDice(int howManyDiceP)  // Use "howManyDiceP" to distinguish it as a parameter (P) and not the variable "howManyDice"
{ 
	cout << "Rolling dice now..." << endl;	
	for (int d = 0; d < 3; d++) {
			containerOfDiceRolls[d] = 0; // Initialize all 3 Dice to "0"
	}
	srand(time(NULL)); // Initialize random seed based on the time
		
	for (int i = 0; i < howManyDiceP; i++) {			// For each die:
			containerOfDiceRolls[i] = rand() % 6 + 1;	// ... generate random number between 1 and 6
			cout << containerOfDiceRolls[i] << endl;	// ... print result on screen
			totalTimesPlayerHasRolledDice++;			// ... update total count of dice rolls

			// Keep track of how many times each value (1-6) appears
			for (int k = 0; k < 6; k++) {
				if (containerOfDiceRolls[i] == (k+1))					
					howManyTimesEachValueHasOccurred[k]++;	
			}
	}
	// Sort the array
	sort(begin(containerOfDiceRolls), end(containerOfDiceRolls));
	//Display Roll Results
	if(howManyDiceP == 1)
		cout << "You rolled "<< containerOfDiceRolls[2] << endl;
	if (howManyDiceP == 2)
		cout << "You rolled " << containerOfDiceRolls[1] << ", " << containerOfDiceRolls[2] << endl;
	if (howManyDiceP == 3)
		cout << "You rolled " << containerOfDiceRolls[0] << ", " << containerOfDiceRolls[1] << ", " << containerOfDiceRolls[2] << endl;
}


/*** Method 3***/
// Calculate percentage of how many times each value (1-6) has occurred
void Dice::calculatePercentageDiceRolls(int player) {
	cout << "So far, Player " << player << " has rolled " << totalTimesPlayerHasRolledDice << " total dice." << endl;
	//Calculate the percentage of how many times each dice value has appeared
	for (int i = 0; i < 6; i++) {
		cout << i+1 << ": " << howManyTimesEachValueHasOccurred[i] << " times ("
		<< (((float)howManyTimesEachValueHasOccurred[i]) / ((float)totalTimesPlayerHasRolledDice) * 100) << "%)"<< endl;
	}
}


/*** Driver ***/
int main() {

	Dice Player1Dice, Player2Dice;

	while (true) {

		cout << "---------------------------------------------------------------------- \n"
			"/////////////////////////// PLAYER 1 TURN ///////////////////////////  \n"
			"----------------------------------------------------------------------" << endl;
		Player1Dice.rollDice(Player1Dice.decideHowManyDiceToRoll());
		cout << "---------------------------------------------------------------------- \n"
			"/////////////////////////// PLAYER 2 TURN ///////////////////////////  \n"
			"----------------------------------------------------------------------" << endl;
		Player2Dice.rollDice(Player2Dice.decideHowManyDiceToRoll());
		cout << "---------------------------------------------------------------------- \n"
			"/////////////////////////// ROUND RESULTS ///////////////////////////  \n"
			"----------------------------------------------------------------------" << endl;
		Player1Dice.calculatePercentageDiceRolls(1);
		Player2Dice.calculatePercentageDiceRolls(2);

	}
	system("PAUSE");

	return 0;
}
