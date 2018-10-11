//#include "stdafx.h"		/* included automatically by Visual Studio*/
#include <iostream>		/* cout */
#include <stdio.h>    
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "dice.h"
using namespace std;



////////////////////////////////////////////////////////////////////
/////////////////////////// VARIABLES ///////////////////////////
////////////////////////////////////////////////////////////////////
int howManyDice; // Number of dice player will roll on their turn
int howManyTimesEachValueHasOccurred [6] ; // Array stores how many times each dice value has appeared (each player has their own copy of this array to store their own values)
int containerOfDiceRolls [3]; // User can roll 1-3 dice per turn. These 1-3 rolls must be kept in a "container" so we will keep them in an array.
int totalTimesPlayerHasRolledDice;



////////////////////////////////////////////////////////////////////
/////////////////////////// METHOD 1 ///////////////////////////
////////////////////////////////////////////////////////////////////
// DECIDE HOW MANY DICE TO ROLL
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



////////////////////////////////////////////////////////////////////
/////////////////////////// METHOD 2 ///////////////////////////
////////////////////////////////////////////////////////////////////
// GENERATE & DISPLAY RANDOM DICE ROLL VALUES
// Also keeps track of how many times each value (1-6) has occurred, and stores this count in an array[6].
void Dice::rollDice(int howManyDiceP)  // Use "howManyDiceP" to distinguish it as a parameter (P) and not the variable "howManyDice"
{ 
	cout << "Rolling dice now..." << endl;	
	for (int d = 0; d < 3; d++) {
			containerOfDiceRolls[d] = 0; // Initialize all 3 Dice to "0"
	}
	srand(time(NULL)); // Initialize random seed based on the time
		
	for (int i = 0; i < howManyDiceP; i++) {				// For each die:
			containerOfDiceRolls[i] = rand() % 6 + 1;	// ... generate random number between 1 and 6
			cout << containerOfDiceRolls[i] << endl;	// ... print result on screen
			totalTimesPlayerHasRolledDice++;			// ... update total count of dice rolls

			// Keep track of how many times each value (1-6) appears
			for (int k = 0; k < 6; k++) {
				if (containerOfDiceRolls[i] == (k+1))					
					howManyTimesEachValueHasOccurred[k]++;	
			}
	}
	//Display Roll Results
	if(howManyDiceP == 1)
		cout << "You rolled a "<< containerOfDiceRolls[0] << endl;
	if (howManyDiceP == 2)
		cout << "You rolled a " << containerOfDiceRolls[0] << ", " << containerOfDiceRolls[1] << endl;
	if (howManyDiceP == 3)
		cout << "You rolled a " << containerOfDiceRolls[0] << ", " << containerOfDiceRolls[1] << ", " << containerOfDiceRolls[2] << endl;
}



////////////////////////////////////////////////////////////////////
/////////////////////////// METHOD 3 ///////////////////////////
////////////////////////////////////////////////////////////////////
// CALCULATE PERCENTAGE OF HOW MANY TIMES EACH VALUE (1-6) HAS OCCURRED
void Dice::calculatePercentageDiceRolls(int player) {
	cout << "So far, Player " << player << " has rolled " << totalTimesPlayerHasRolledDice << " total dice." << endl;
	//Calculate the percentage of how many times each dice value has appeared
	for (int i = 0; i < 6; i++) {
		cout << i+1 << ": " << howManyTimesEachValueHasOccurred[i] << " times ("
		<< (((float)howManyTimesEachValueHasOccurred[i]) / ((float)totalTimesPlayerHasRolledDice) * 100) << "%)"<< endl;
	}
}