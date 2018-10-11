//#include "stdafx.h"
#include <iostream>
#include "dice.h"

using namespace std;



int main() {

	Dice Player1Dice, Player2Dice;

	bool gameBeingPlayed = true;

	while (gameBeingPlayed == true) {
		
		cout << "---------------------------------------------------------------------- \n" 
					"/////////////////////////// PLAYER 1 TURN ///////////////////////////  \n"
					"----------------------------------------------------------------------" << endl;
		Player1Dice.rollDice( Player1Dice.decideHowManyDiceToRoll() );
		cout << "---------------------------------------------------------------------- \n"
					"/////////////////////////// PLAYER 2 TURN ///////////////////////////  \n"
					"----------------------------------------------------------------------" << endl;
		Player2Dice.rollDice( Player2Dice.decideHowManyDiceToRoll() );
		cout << "---------------------------------------------------------------------- \n"
					"/////////////////////////// ROUND RESULTS ///////////////////////////  \n"
					"----------------------------------------------------------------------" << endl;
		Player1Dice.calculatePercentageDiceRolls(1);
		Player2Dice.calculatePercentageDiceRolls(2);

	}
	system("PAUSE");

	return 0;
}