#pragma once
#include "Dice.h"
#include "Deck.h"
#include "Hand.h"
#include <string>

class Player;

//Fake vertex of the graph (only for demo)
struct Country {
	string name; 
	Player* owner; 
	int nbArmies;
	vector<Country*> nbr;
};


class Player {
	// Attributes
	vector<Country*> myTerritories;
	Dice dice; // a dice rolling facility
	Hand hand;
	string name;

public: 
	// Constructors & destructors
	Player(); // default constructor
	Player(Deck *deck);
	~Player(); // destructor
	// Getters
	Dice* getDice(); // returns the dice facility the player owns
	void getCountries(); // prints the names of the countries owned 
	Hand* getHand();
	string getName();
	// Setters
	void setHand(Deck *deck); // method to add cards to the vector handOfCards
	void setName(string name);
	// Other methods
	void addCountry(Country* country); // add a country to the vector of owned countries
	void removeCountry(Country* country); // remove a country from the vector of owned countries

	// Game methods
	void reinforce();
	void attack();
	void fortify();

};




