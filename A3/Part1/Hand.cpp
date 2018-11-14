#include <iostream>
#include "Hand.h"


using namespace std;


// Default constructor
Hand::Hand()
{
}

//Constructor that takes Deck object that will be used by all players playing the same game and sets handOfCards to size 5
Hand::Hand(Deck *deck)
{
	playingDeck = deck;
	handOfCards.resize(6);
	numberOfExchanges = 1;
	armies = 0;
}

//Takes address of deck object, finds empty spot in hand and fills with card.  If no empty spots no card is accepted
void Hand::fillHand(Deck &playingDeck)
{
	for (size_t x = 0; x < handOfCards.size(); x++)
	{

		if (handOfCards[x] == Deck::Cards::Null)
		{
			handOfCards.at(x) = playingDeck.draw(playingDeck.deck);
		}

	}

}
//Method to calculate how many actual cards in vector not counting null
int Hand::howManyCardsInHand()
{
	int actualNumberOfCards = 0;
	for (size_t x = 0; x < handOfCards.size(); x++)
	{
		if (handOfCards[x] == 0) {}

		else
			actualNumberOfCards += 1;

	}
	return actualNumberOfCards;
}

int  Hand::exchange()
{
	armies = 0;
	cout << endl << "Your hand of cards is" << endl;
	for (size_t x = 0; x < handOfCards.size(); x++)
	{
		cout << x + 1 << ". " << convertCardsToString(handOfCards[x]) << endl;
	}
	int firstCardSelected = 0;
	int secondCardSelected = 0;
	int thirdCardSelected = 0;
	while (true) {
		cout << "Which cards would you like to exchange: (select 3 from 1 to 5 hitting enter after each selection)" << endl;
		cin >> firstCardSelected;
		cin >> secondCardSelected;
		cin >> thirdCardSelected;
		if (firstCardSelected > handOfCards.size() || secondCardSelected > handOfCards.size() || thirdCardSelected > handOfCards.size())
			cout << "Improper card selected.  Try again" << endl;
		else
			break;
	}

	Deck::Cards first = handOfCards[firstCardSelected - 1];    //Used only to make conditional statement shorter
	Deck::Cards second = handOfCards[secondCardSelected - 1];
	Deck::Cards third = handOfCards[thirdCardSelected - 1];


	if ( (((first == second) && (second == third)) || ((first != second) && (second != third) && (third != first)))
		&& (first != Deck::Cards::Null) && (second != Deck::Cards::Null) && (third != Deck::Cards::Null)) //Checks if cards selected are 3 of a kind or 3 all of different suits
	{

		handOfCards[firstCardSelected - 1] = Deck::Cards::Null; //Sets cards exchanged to null
		handOfCards[secondCardSelected - 1] = Deck::Cards::Null;
		handOfCards[thirdCardSelected - 1] = Deck::Cards::Null;

		if (numberOfExchanges < 6 || numberOfExchanges > 0) //Depending on number of exchanges selects different equation for armies offered
			armies = (((numberOfExchanges)-1) * 2) + 6;
		else if (numberOfExchanges > 5)
			armies = (numberOfExchanges - 5) * 5 + 10;

		numberOfExchanges++; //tracks number of exchanges player has had
	}
	return armies;
}

int  Hand::exchangeComputer()
{
	bool exchangeDif = false, exchangeSame = false;
	vector<int> cardsToExchange;
	int artillery = -1, infantry = -1, cavalry = -1, aNb = 0, iNb = 0, cNb = 0;
	armies = 0; // number to return 

	/* OPTION 1 */
	// Check if player owns 3 different card
	for (int x = 0; x < handOfCards.size(); x++)
	{
		if (handOfCards[x] == Deck::Cards::Artillery) {
			artillery = x;
			aNb++;
		}
		else if (handOfCards[x] == Deck::Cards::Infantry) {
			infantry = x;
			iNb++;
		}
		else if (handOfCards[x] == Deck::Cards::Cavalry) {
			cavalry = x;
			cNb++;
		}
	}
	if (artillery != -1 && infantry != -1 && cavalry != -1) { // exchange is valid
		exchangeDif = true;
		// Set the index of the cards to exchange
		cardsToExchange.push_back(artillery);
		cardsToExchange.push_back(infantry);
		cardsToExchange.push_back(cavalry);
	}

	/* OPTION 2 */
	// If not, check if player owns 3 cards of the same type
	if (!exchangeDif) {
		Deck::Cards typeToExchange;
		if (aNb >= 3) {
			typeToExchange = Deck::Cards::Artillery;
			exchangeSame = true;
		}
		else if (iNb >= 3) {
			typeToExchange = Deck::Cards::Infantry;
			exchangeSame = true;
		}
		else if (cNb >= 3) {
			typeToExchange = Deck::Cards::Cavalry;
			exchangeSame = true;
		}

		// Player can exchange 3 same cards, find them and add to vector
		if (exchangeSame) {
			for (int x = 0; x < handOfCards.size(); x++) {
				if (handOfCards[x] == typeToExchange) {
					cardsToExchange.push_back(x);
				}
			}
		}
	}

	cout << endl << "Player computer's hand of cards is:" << endl;
	for (size_t x = 0; x < handOfCards.size(); x++)
	{
		cout << x + 1 << ". " << convertCardsToString(handOfCards[x]) << endl;
	}
	// MAKE EXCHANGE
	if (exchangeDif || exchangeSame) {		
		cout << "Player can exchange cards " << cardsToExchange.at(0) + 1 << ", " << cardsToExchange.at(1) + 1 << ", " << cardsToExchange.at(2) + 1 << "." << endl;

		handOfCards[cardsToExchange.at(0)] = Deck::Cards::Null; //Sets cards exchanged to null
		handOfCards[cardsToExchange.at(1)] = Deck::Cards::Null; //Sets cards exchanged to null
		handOfCards[cardsToExchange.at(2)] = Deck::Cards::Null; //Sets cards exchanged to null
		
		if (numberOfExchanges < 6 || numberOfExchanges > 0) //Depending on number of exchanges selects different equation for armies offered
			armies = (((numberOfExchanges)-1) * 2) + 6;
		else if (numberOfExchanges > 5)
			armies = (numberOfExchanges - 5) * 5 + 10;

		numberOfExchanges++; //tracks number of exchanges player has had
	}

	return armies;
}


//Function to convert Deck::Cards enum to string for print
string convertCardsToString(Deck::Cards card)
{
	switch (card)
	{
	case Deck::Cards::Infantry: return "Infantry";

	case Deck::Cards::Cavalry: return "Cavalary";

	case Deck::Cards::Artillery: return "Artillery";

	case Deck::Cards::Null: return "Empty";
	}
}
