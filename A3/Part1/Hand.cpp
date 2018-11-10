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
	cout << "Your hand of cards is" << endl;
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



/*int main() {

	Deck playerDeck; //Create Deck object
	Hand hand = Hand(&playerDeck); //Put in Hand Object
	int deckSize;

	//to show how many cards of each is created in deck
	int numberOfInfantryCards = 0;
	int numberOfCavalaryCards = 0;
	int numberOfArtilleryCards = 0;

	cout << "How many cards in the deck would you like?:   " << endl;
	cin >> deckSize;
	playerDeck.fillDeck(deckSize); //sets deck object in hand to player deck


	//counts number of infantry, cavlary and artillery units
	for (int i = 0; i < deckSize; i++)
	{
		if (playerDeck.deck[i] == Deck::Cards::Infantry)
			numberOfInfantryCards += 1;
		else if (playerDeck.deck[i] == Deck::Cards::Cavalry)
			numberOfCavalaryCards += 1;
		else
			numberOfArtilleryCards += 1;
	}

	cout << "There is " << numberOfInfantryCards << " infantry cards" << endl;
	cout << "There is " << numberOfCavalaryCards << " cavalary cards" << endl;
	cout << "There is " << numberOfArtilleryCards << " artillery cards" << endl;



	hand.fillHand(playerDeck);
	hand.fillHand(playerDeck);
	hand.fillHand(playerDeck);
	hand.fillHand(playerDeck);
	hand.fillHand(playerDeck);


	//Prints card values in hand
	cout << "You picked up 5 cards.  Your hand now is " << endl;
	for (int x = 0; x < hand.handOfCards.size(); x++)
	{
		cout << x + 1 << ". " << convertCardsToString(hand.handOfCards[x]) << endl;
	}


	hand.exchange();  //exchanges cards selected by user


	//FILLING HAND SECOND TIME
	hand.fillHand(playerDeck);
	hand.fillHand(playerDeck);
	hand.fillHand(playerDeck);

	//prints cards in hand
	cout << "\n\n\nYou picked up 3 more cards.  Your hand now is  " << endl;
	for (int x = 0; x < hand.handOfCards.size(); x++)
	{
		cout << x + 1 << ". " << convertCardsToString(hand.handOfCards[x]) << endl;
	}


	hand.exchange();//exchange cards selected by user


	//FILLING HAND THIRD TIME
	hand.fillHand(playerDeck);
	hand.fillHand(playerDeck);
	hand.fillHand(playerDeck);

	//prints cards in hand
	cout << "\n\n\nYou picked up 3 more cards.  Your hand now is  " << endl;
	for (int x = 0; x < hand.handOfCards.size(); x++)
	{
		cout << x + 1 << ". " << convertCardsToString(hand.handOfCards[x]) << endl;
	}

	hand.exchange(); //exchanges cards selected by user
	return 0;
}*/
