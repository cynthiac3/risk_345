#pragma once
#include "Deck.h"


class Hand {

public:
	Deck deck; //deck object for all players to play from
	enum Army { Infantry, Cavalry, Artillery };  //Possible type of Army
	vector <Deck::Cards> handOfCards;

	Hand(Deck deck); //Constructor that passes reference of Deck so all players share same deck

	void fillHand(Deck &playingDeck);

	void exchange(Deck::Cards first, Deck::Cards second, Deck::Cards third);

	string convertCardsToString(Deck::Cards card);

};