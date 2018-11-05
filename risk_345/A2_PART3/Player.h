#pragma once
//#include "Dice.h"
#include "Hand.h"
#include <vector>;


class Player;
//Fake vertex of the graph (only for demo)
struct Country {
	string name;
	int nbArmies;
	vector<Country*> nbr;
	Player* owner;
};

class Player {
	// Attributes
	vector<Country*> myTerritories;
	//Dice dice; // a dice rolling facility
	string name;



public:
	Player(); // default constructor
	//Dice* getDice(); // returns the dice facility the player owns
	void getCountries(); // prints the names of the countries owned 
	Hand* getHand();
	void setHand(Deck *deck); // method to add cards to the vector handOfCards
	void setName(string name);
	string getName();
	Hand hand;
	
	
    void addCountry(Country* country); // add a country to the vector of owned countries
	
    static void addCountryToContinentArctic(Country * country);

	static void addCountryToContinentEurope(Country * country);

	static void addContinentToVector();

	static vector<Country*> Arctic;
	static vector<Country*> Europe;
	static vector <vector<Country*>> continents;


	// Game methods
	void reinforce();
	void attack();
	void fortify();

};


