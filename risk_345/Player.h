#pragma once
#include "Map_CPNT.h"
#include "Dice.h"
#include "Deck.h"


class Player {
	// Attributes
	vector<Territory*> myTerritories; // a collection of countries the player owns
	Dice dice; // a dice rolling facility
	vector<Deck::Cards> handOfCards; // a collection of cards that the player holds

public: 
	Player(); // default constructor
	Dice getDice(); // returns the dice facility the player owns
	void getCountries(); // prints the names of the countries owned 
	vector<Deck::Cards> getHand(); // returns the hand of cards of the player
	void setHand(Deck deck); // method to add cards to the vector handOfCards

	// Methods to implement in later assignments:
	void reinforce();
	void attack();
	void fortify();

};
