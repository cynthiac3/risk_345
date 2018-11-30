#pragma once
#include "Dice.h"
#include "Deck.h"
#include "Hand.h"
#include <string>
#include "Strategy.h"

class Player;

//Free functions
void setUpGameDemo(Player* mark, Player* bob);
void clearInput();
void chooseStrategy(Player* p); // This method only used in the Player Driver, not main game
void checkPlayerEliminated(vector<Player*> * players);


//Fake vertex of the graph (only for demo)
struct Country {
	std::string name;
	Player* owner;
	int nbArmies;
	vector<Country*> nbr;
	std::string continent;
};

//Fake subgraph of the graph (only for demo)
struct Continent {
	std::string name;
	int bonus;
};


class Player {
public:
	// Attributes
	vector<Country*> myTerritories;
	vector<Continent*> myContinents;
	Dice dice;
	Hand hand;
	string name;
	Strategy* strategy;

	// Constructors & destructors
	Player(); // default constructor
	~Player(); // destructor
	// Getters
	Dice* getDice(); // returns the dice facility the player owns
	void getCountries(); // prints the names of the countries owned 
	Hand* getHand();
	string getName();
	// Setters
	void setHand(Deck *deck); // method to add cards to the vector handOfCards
	void setName(string name);
	void setStrategy(Strategy* s);
	// Other methods
	void addCountry(Country* country); // add a country to the vector of owned countries
	void removeCountry(Country* country); // remove a country from the vector of owned countries
	void addContinent(Continent* continent); // add a country to the vector of owned countries
	void removeContinent(Continent* continent); // add a country to the vector of owned countries

	// Game methods
	void play();
	void reinforce();
	void attack();
	void fortify();

};




