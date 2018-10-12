#pragma once
#include "Map_CPNT.h"
#include "dice.h"

class Player {

	/* Attributes */
	// collection of countries that the player owns
	vector<Territorie> myTerritories;
	// A dice rolling facility
	Dice dice;
	// Hand of risk card
	//... 	

public: 
	Player();
	Dice getDice(); // returns the dice facility the player owns
	// Methods to implement in later assignments:
	void reinforce();
	void attack();
	void fortify();

};