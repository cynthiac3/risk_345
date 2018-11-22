#pragma once


class Dice {

private:
	int howManyDice=0; // Number of dice player will roll on their turn
	// Array stores how many times each dice value has appeared (each player has their own copy of this array to store their own values)
	int howManyTimesEachValueHasOccurred [6] = { 0,0,0,0,0,0 }; 	
	int totalTimesPlayerHasRolledDice = 0;

public:
	// User can roll 1-3 dice per turn. These 1-3 rolls must be kept in a "container" so we will keep them in an array.
	int containerOfDiceRolls[3] = { 0, 0, 0 };
	int decideHowManyDiceToRoll();
	void rollDice(int howManyDiceP); // parameter is "howManyDiceP" to distinguish it from the "howManyDice" variable 
	void calculatePercentageDiceRolls(int player);

};
