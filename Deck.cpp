#include "Deck.h"
#include <algorithm>
#include <ctime> 

using namespace std;

enum Cards { Null, Infantry, Cavalry, Artillery };


void Deck::fillDeck(int numberOfCountries)
{
	int xx = numberOfCountries;

	for (int x = xx / 3; x > 0; x--) //Divides number of countries by 3 and sets infantry units to first 1/3
	{
		deck.insert(deck.begin(), Cards::Infantry);

	}

	for (int x = xx / 3; x > 0; x--)
	{
		deck.insert(deck.begin(), Cards::Artillery); //Divides number of countries by 3 and sets cavalry units to second 1/3

	}

	for (int x = xx / 3; x > 0; x--)
	{

		deck.insert(deck.begin(), Cards::Cavalry); //Divides number of countries by 3 and sets artillery units to first 1/3
	}

	if (numberOfCountries % 3 != 0)  //if number of countries is not divisible by 3
	{
		std::srand(unsigned(std::time(0)));                               //shuffles an array of 3 numbers each number corresponding with infantry, cavalry or artillery
		int random[3] = { 0,1,2 };                                         //will only select each number once   
		random_shuffle(std::begin(random), std::end(random));

		if (numberOfCountries % 3 == 2)   //if 2 extra cards selects 2 numbers 
		{
			deck.insert(deck.begin(), (Cards)random[0]);
			deck.insert(deck.begin(), (Cards)random[1]);
		}

		else  //if one extra card selects only 1 number
			deck.insert(deck.begin(), (Cards)random[0]);
	}

	std::srand(unsigned(std::time(0)));  //shuffles deck
	random_shuffle(begin(deck), end(deck));
}



Deck::Cards Deck::draw(vector<Deck::Cards> &gameDeck) //takes address of deck of cards
{
	Cards x = gameDeck[gameDeck.size() - 1]; //draws last card in list
	gameDeck.erase(gameDeck.end() - 1);  //deletes card

	if (x == Cards::Infantry)  //returns the enum equivalent of card
		return Cards::Infantry;
	else if (x == Cards::Cavalry)
		return Cards::Cavalry;
	else
		return  Cards::Artillery;
}