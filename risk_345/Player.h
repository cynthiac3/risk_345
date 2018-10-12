#pragma once
#include "Map_CPNT.h"
#include "Dice.h"
#include "Hand.h"



class Player {
	// Attributes
	vector<Territorie*> myTerritories;
	Dice dice;
	Hand hand;

public: 
	Player();
	Dice getDice(); // returns the dice facility the player owns
	void getCountries(); // returns a string that list the countries info 
	void getHand(); // returns the hand of cards of the player
	// Methods to implement in later assignments:
	void reinforce();
	void attack();
	void fortify();

};
