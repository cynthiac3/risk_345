#include "Hand.h"
#include <iostream>
#include <stdlib.h>
#include <string>

Deck playingDeck;
vector<Deck::Cards> handOfCards(0);
int armies = 0;
int infantry = 0;
int cavalary = 0;
int artillery = 0;
int numberOfExchanges = 1;

Hand::Hand()
{
	handOfCards.resize(5);
}

Hand::Hand(Deck deck)
{
	playingDeck = deck;
	handOfCards.resize(5);
}

void Hand::setDeck(Deck deck) 
{
	this->deck = deck;
}

void Hand::fillHand(Deck &playingDeck)
{	
	handOfCards.insert(handOfCards.begin(), playingDeck.draw(playingDeck.deck));
}


void  Hand::exchange(Deck::Cards first, Deck::Cards second, Deck::Cards third)
{
	int armies = 0;
	int availableArmyUnits = 0;
	int goOn = 1;
	if (((first == second)&&(second == third))||((first != second) && (second != third) &&  (third != first)))
	{
		if (numberOfExchanges < 6 ||numberOfExchanges > 0)
			availableArmyUnits = ((numberOfExchanges)-1)*2+4;
		else 
			availableArmyUnits = (numberOfExchanges - 1) * 2 + 5;

		while (goOn!=0)
		{
			cout << "You can select up to " << availableArmyUnits << endl;
			while (0==0)
			{	
				cout << "How many units of infantry would you like? ";
		        cin>> armies;
				if (armies > availableArmyUnits)
					cout << "Invalid amount.  Try again or type 0 to move to cavalry " << endl;
				else
				{
					infantry += armies;
					availableArmyUnits -= armies;
					break;
				}
			}

			while (0==0)
			{
			   cout << "How many units of cavalry would you like? ";
			   cin >> armies;
			   if (armies * 5 > availableArmyUnits)
				    cout << "Invalid amount.  Try again or type 0 to move to artillery " << endl;
			   
			   else
			   {
				   cavalary += armies;
				   availableArmyUnits -= armies*5;
				   break;
			    }
		    } 

			while (0==0)
			{
				cout << "How many units of artillery would you like? ";
				cin >> armies;
				if (armies * 10 > availableArmyUnits)
					cout << "Invalid amount.  Try again or type 0 to move on " << endl;
				else
				{
					cavalary += armies;
					availableArmyUnits -= armies * 10;
					break;
				}
			}

			numberOfExchanges += 1;
			cout << "Go on? Type 0 to quit ";
			cin >> goOn;

		}
	}
}


string convertCardsToString(Deck::Cards card)
{
	switch (card)
	{
	case Deck::Cards::Infantry : return "Infantry";

	case Deck::Cards::Cavalry: return "Cavalry";

	case Deck::Cards::Artillery: return "Artillery";
	}
}


int main() {

	Deck playerDeck;
	Hand hand = Hand(playerDeck);
	int deckSize = 0;
	int numberOfInfantryCards = 0;
	int numberOfCavalaryCards = 0;
	int numberOfArtilleryCards = 0;

	cout << "How many cards in the deck would you like?:   " << endl;
	cin >> deckSize;
	playerDeck.fillDeck(deckSize);
	for (int i = 0; i < deckSize; i++)
	{
		if (playerDeck.deck[i] == Deck::Cards::Infantry)
			numberOfInfantryCards += 1;
		else if (playerDeck.deck[i] == Deck::Cards::Cavalry)
			numberOfCavalryCards += 1;
		else
			numberOfArtilleryCards += 1;
	}

	cout << "There is " << numberOfInfantryCards << " infantry cards" << endl;
	cout << "There is " << numberOfCavalaryCards << " cavalary cards" << endl;
	cout << "There is " << numberOfArtilleryCards << " artillery cards" << endl;

	// FILL HAND FIRST TIME
	hand.fillHand(playerDeck);
	hand.fillHand(playerDeck);
	hand.fillHand(playerDeck);
	hand.fillHand(playerDeck);
	hand.fillHand(playerDeck);

	string one   = convertCardsToString(hand.handOfCards[0]);
	string two   = convertCardsToString(hand.handOfCards[1]);
	string three = convertCardsToString(hand.handOfCards[2]);
	string four  = convertCardsToString(hand.handOfCards[3]);
	string five  = convertCardsToString(hand.handOfCards[4]);

	cout << "You now have a hand of 5 cards.  They are as follows: " << one << ", " << two << ", " << three << ", " << four << ", " << five << endl;

	int first = 0;
	int second = 0;
	int third = 0;
	cout << "Which cards would you like to exchange: (select 3 from 1 to 5 hitting enter after each selection)" << endl;
	cin >> first;
	cin >> second;
	cin >> third;

	cout << hand.handOfCards.size() << endl;
	hand.exchange(hand.handOfCards[first-1], hand.handOfCards[second-1], hand.handOfCards[third-1]);


	// FILLING HAND SECOND TIME
	hand.fillHand(playerDeck);
	hand.fillHand(playerDeck);
	hand.fillHand(playerDeck);

	one = convertCardsToString(hand.handOfCards[0]);
        two = convertCardsToString(hand.handOfCards[1]);
        three = convertCardsToString(hand.handOfCards[2]);
        four = convertCardsToString(hand.handOfCards[3]);
	five = convertCardsToString(hand.handOfCards[4]);

	cout << "You now have a hand of 5 cards.  They are as follows: " << one << ", " << two << ", " << three << ", " << four << ", " << five << endl;

	cout << "Which cards would you like to exchange: (select 3 from 1 to 5 hitting enter after each selection)" << endl;
	cin >> first;
	cin >> second;
	cin >> third;

	hand.exchange(hand.handOfCards[first - 1], hand.handOfCards[second - 1], hand.handOfCards[third - 1]);

	cout << "You have " << infantry << " infantry units" << endl;
	cout << "You have " << cavalary << " cavalary units" << endl;
	cout << "You have " << artillery << " artillery units" << endl;
	
 	return 0;
}
