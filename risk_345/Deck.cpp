

#include "Deck.h"
#include <iostream>
//random number generator
#include <algorithm>
#include <ctime> 

using namespace std;

enum Cards { Infantry, Cavalry, Artillery };

vector<Cards>deck;



void Deck::fillDeck(int numberOfCountries)
{
	int xx = numberOfCountries;

	for (int x = xx/3; x >0; x--)
	{
		deck.insert(deck.begin(), Cards::Infantry);
		
	}

	for (int x = xx / 3; x > 0; x--)
	{
		deck.insert(deck.begin(), Cards::Artillery);

	}

	for (int x = xx / 3; x > 0; x--)
	{

		deck.insert(deck.begin(), Cards::Cavalry);
	}

	if (numberOfCountries % 3 != 0)
	{ 
		std::srand(unsigned(std::time(0)));
		int random[3]= { 0,1,2 };
		random_shuffle(std::begin(random), std::end(random));

		if (numberOfCountries % 3 == 2) 
		{
			deck.insert(deck.begin(), (Cards)random[0]);
			deck.insert(deck.begin(), (Cards)random[1]);
		}
	
		else
			deck.insert(deck.begin(), (Cards)random[0]);
	}

	    std::srand(unsigned(std::time(0)));
	    random_shuffle(begin(deck), end(deck));
}

Deck::Cards Deck::draw(vector<Deck::Cards> &gameDeck)
{
	Cards x = gameDeck[gameDeck.size()-1];
	gameDeck.erase(gameDeck.end()-1);
	 
	if (x == Cards::Infantry)
		return Cards::Infantry;
	else if (x == Cards::Cavalry)
		return Cards::Cavalry;
	else
		return  Cards::Artillery;
}



 