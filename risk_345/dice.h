#pragma once


class Dice {

private:
	int howManyDice=0;
	int howManyTimesEachValueHasOccurred [6] = { 0,0,0,0,0,0 };
	int containerOfDiceRolls [3] = { 0, 0, 0 };
	int totalTimesPlayerHasRolledDice = 0;

public:
	int decideHowManyDiceToRoll();
	void rollDice(int howManyDice);
	void calculatePercentageDiceRolls(int player);

};