#pragma once
#include "Map_CPNT.h"
#include "Dice.h"
#include "Deck.h"
#include "Hand.h"


class Player {
	// Attributes
	vector<Territory*> myTerritories; // a collection of countries the player owns
	Dice dice; // a dice rolling facility
	Hand hand; // hand that holds the cards

public: 
	Player(); // default constructor
	Player(Deck *deck);
	Dice getDice(); // returns the dice facility the player owns
	void getCountries(); // prints the names of the countries owned 
	Hand* getHand(); // return hand of cards the player owns
	void setHand(Deck *deck); // method to add cards to the vector handOfCards

	// Methods to implement in later assignments:
	void reinforce();
	void attack();
	void fortify();

};
