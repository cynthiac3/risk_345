#pragma once
#include "Deck.h"
#include <string>

class Hand
{

public:

	Deck *playingDeck; //deck object for all players to play from
	vector <Deck::Cards> handOfCards; //Cards in Players possesion
	enum Army { Infantry, Cavalry, Artillery };  //Possible types of Army

	int numberOfExchanges;
	int armies;

	Hand(Deck *deck); //Constructor that passes reference of Deck so all players share same deck
	Hand(); //Default constructor
	void fillHand(Deck &playingDeck);
	int exchange();
	int exchangeComputer();
	int howManyCardsInHand();
	void cleanUpHand();
	void pickUpCard();
	void setDeck(Deck &deck);
	void printHand(); // prints the cards in hand
};

string convertCardsToString(Deck::Cards card);