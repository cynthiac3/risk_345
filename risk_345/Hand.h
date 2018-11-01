#pragma once
#include "Deck.h"


class Hand 
{

public:

	Deck *playingDeck; //deck object for all players to play from
	vector <Deck::Cards> handOfCards; //Cards in Players possesion
	enum Army { Infantry, Cavalry, Artillery };  //Possible types of Army

	Hand(Deck *deck); //Constructor that passes reference of Deck so all players share same deck
	Hand (); //Default constructor
	void fillHand(Deck &playingDeck);
	void exchange(int cardOne, int cardTwo, int cardThree, vector<Deck::Cards> &playingDeck);
	string convertCardsToString(Deck::Cards card);
};
