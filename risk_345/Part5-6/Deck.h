#pragma once
#include <vector>

using namespace std;

class Deck {

public:
	enum Cards {Null ,Infantry, Cavalry, Artillery};  //Possible type of cards
	vector <Cards> deck;

	void fillDeck(int NumberOfCountries);//Cards draw(); 
	Cards draw(vector<Deck::Cards> &deck);  //Draw function that allows you to draw a card
};




