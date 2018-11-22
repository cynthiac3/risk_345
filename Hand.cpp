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

// Set the current deck for the game to the player's hand
void Hand::setDeck(Deck &deck) {
	playingDeck = &deck;

}

//Takes address of deck object, fills hand with cards from the deck
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

// Ask for user input to give 3 cards in exchange of some armies
// The 3 cards are either all different, or all the same
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
		cleanUpHand();

		if (numberOfExchanges < 6 || numberOfExchanges > 0) //Depending on number of exchanges selects different equation for armies offered
			armies = (((numberOfExchanges)-1) * 2) + 6;
		else if (numberOfExchanges > 5)
			armies = (numberOfExchanges - 5) * 5 + 10;

		numberOfExchanges++; //tracks number of exchanges player has had
	}
	return armies; // return armies to player (0 if no valid exchange)
}

// Automatically identifies if the player can make a valid card exchange
// used when a player is a computer and not a human
int  Hand::exchangeComputer()
{
	bool exchangeDif = false, exchangeSame = false; // check if a valid exchange can be made
	vector<int> cardsToExchange; // indexes of the cards to exchange
	int artillery = -1, infantry = -1, cavalry = -1, aNb = 0, iNb = 0, cNb = 0; // used to find the indexes
	armies = 0; // number of armies to return 

	/* OPTION 1 */
	// Check if player owns 3 different card
	for (int x = 0; x < handOfCards.size(); x++)
	{
		if (handOfCards[x] == Deck::Cards::Artillery) {
			artillery = x;
			aNb++; // stores nb of cards of type Artillery
		}
		else if (handOfCards[x] == Deck::Cards::Infantry) {
			infantry = x;
			iNb++; // stores nb of cards of type Infantry
		}
		else if (handOfCards[x] == Deck::Cards::Cavalry) {
			cavalry = x;
			cNb++; // stores nb of cards of type Cavalry
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

		// Player can exchange 3 same cards, find 3 of that type and add their indexes to vector
		if (exchangeSame) {
			for (int x = 0; x < handOfCards.size(); x++) {
				if (handOfCards[x] == typeToExchange) {
					cardsToExchange.push_back(x);
				}
			}
		}
	}

	// Display current hand of cards
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
		cleanUpHand();
		
		if (numberOfExchanges < 6 || numberOfExchanges > 0) //Depending on number of exchanges selects different equation for armies offered
			armies = (((numberOfExchanges)-1) * 2) + 6;
		else if (numberOfExchanges > 5)
			armies = (numberOfExchanges - 5) * 5 + 10;

		numberOfExchanges++; //tracks number of exchanges player has had
	}

	return armies; // return armies to player (0 if no valid exchange)
}

// Removes null/empty cards from the player's hand
void Hand::cleanUpHand() {
	vector<Deck::Cards>::iterator it = handOfCards.begin();
	while (it != handOfCards.end())
	{
		if (*it == Deck::Cards::Null)
		{
			it = handOfCards.erase(it);
		}
		else
			it++;
	}
}

// Player picks up one card from the game deck
void Hand::pickUpCard() {
	handOfCards.push_back(playingDeck->draw(playingDeck->deck));
}

// Print the cards that the player owns 
void Hand::printHand() {

	if (handOfCards.size() == 0) {
		cout << "Player currently doesn't have any cards." << endl;
	}
	else {
		cout << "This is the list of cards that the player currently owns: " << endl;
		for (int i = 0; i <handOfCards.size(); i++)
		{
			switch (handOfCards.at(i))
			{
			case Deck::Cards::Infantry: cout << "Card #" << i + 1 << ": Infantry" << endl; break;
			case Deck::Cards::Cavalry: cout << "Card #" << i + 1 << ": Cavalry" << endl; break;
			case Deck::Cards::Artillery: cout << "Card #" << i + 1 << ": Artillery" << endl; break;
			}
		}
	}
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
