#include "Hand.h"
#include <iostream>
#include <stdlib.h>
#include <string>




Deck *playingDeck;
vector<Deck::Cards> handOfCards(0);


//to show number of armies users has that are untraded as well as how many army units they have traded for
int armies = 0;
int infantry = 0;
int cavalry = 0;
int artillery = 0;
int numberOfExchanges = 1;

Hand::Hand()
{
	handOfCards.resize(5);
}

void Hand::setDeck(Deck deck) 
{
	this->deck = deck;
}

#include "Hand.h"
#include <iostream>
#include <stdlib.h>
#include <String>

//Constructor that takes Deck object that will be used by all players playing the same game and sets handOfCards to size 5
Hand::Hand(Deck *deck) 
{
	playingDeck = deck;
	handOfCards.resize(5);
}



//Takes address of deck object, finds empty spot in hand and fills with card.  If no empty spots no card is accepted
void Hand::fillHand(Deck &playingDeck)
{
	for (size_t x = 0; x < handOfCards.size(); x++)
	{
	
		if (handOfCards[x]== Deck::Cards::Null)
		{
			handOfCards.at(x) = playingDeck.draw(playingDeck.deck);
			break;
		}
	}
}



void  Hand::exchange(int cardOne, int cardTwo, int cardThree, vector<Deck::Cards> &playersHand)
{ 
	Deck::Cards first = playersHand[cardOne-1];    //Used only to make conditional statement shorter
	Deck::Cards second = playersHand[cardTwo-1];
	Deck::Cards third = playersHand[cardThree-1];
	int armies = 0;      //Amount of units of either infantry, cavalry or artillery user wishes to exchange for.
	int availableArmyUnits = 0;  //tracks number of armies exchanged for that user has remaining
	int goOn = 1; //Sets to zero and exits while loop if user has made all desired trades.



	if (((first == second)&&(second == third))||((first != second) && (second != third) &&  (third != first))) //Checks if cards selected are 3 of a kind or 3 all of different suits
	{ 
		playersHand[cardOne-1] = Deck::Cards::Null; //Sets cards exchanged to null
		playersHand[cardTwo-1] = Deck::Cards::Null;
		playersHand[cardThree-1] = Deck::Cards::Null;

		if (numberOfExchanges < 6 ||numberOfExchanges > 0) //Depending on number of exchanges selects different equation for armies offered
			availableArmyUnits = ((numberOfExchanges)-1)*2+4; 
		else 
			availableArmyUnits = (numberOfExchanges - 1) * 2 + 5;


		//Loop to make selection of army units for armies
		while (goOn!=0)
		{
			cout <<"You have " << availableArmyUnits << " army units"<< endl;
			cout <<"1 infantry = 1 army unit \n1 cavalry = 5 army units\n1 artillery = 10 army units" << endl;
			while (0==0)
			{	
				cout << "How many units of infantry units would you like?  You have "<< availableArmyUnits<<" units left"<<endl;
				cin >> armies;
				if (armies > availableArmyUnits)
					cout << "Invalid amount.  Try again or type 0 to move to cavalry " << endl;
				else
				{
					infantry += armies;  //incremenst how many infantry units players has total
					availableArmyUnits -= armies;
					break;
				}
			}

			while (0==0)
			{
				cout << "How many units of cavalry units would you like?  You have " << availableArmyUnits << " units left" << endl;
			   cin >> armies;
			   if (armies * 5 > availableArmyUnits)
				    cout << "Invalid amount.  Try again or type 0 to move to artillery " << endl;
			   
			   else
			   {
				   cavalry += armies;//incremenst how many cavalry units players has total
				   availableArmyUnits -= armies*5;
				   break;
			    }
		    } 

			while (0==0)
			{
				cout << "How many units of artillery units would you like?  You have " << availableArmyUnits << " units left" << endl;
				cin >> armies;
				if (armies * 10 > availableArmyUnits)
					cout << "Invalid amount.  Try again or type 0 to move on " << endl;
				else
				{
					cavalry += armies;
					availableArmyUnits -= armies * 10;//incremenst how many artillery units players has total
					break;
				}
			}

			numberOfExchanges += 1; //tracks number of exchanges player has had 
			cout << "Go on? Type 0 to quit ";
			cin >> goOn;

		}
	}
}

//Function to convert Deck::Cards enum to string for print
string convertCardsToString(Deck::Cards card)
{
	switch (card)
	{
	case Deck::Cards::Infantry : return "Infantry";

	case Deck::Cards::Cavalry: return "Cavalary";

	case Deck::Cards::Artillery: return "Artillery";

	case Deck::Cards::Null: return "Empty";
	}
}





int main() {

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

	//holds number of card users wants to trade
	int first = 0;
	int second = 0;
	int third = 0;
	cout << "Which cards would you like to exchange: (select 3 from 1 to 5 hitting enter after each selection)" << endl;
	cin >> first;
	cin >> second;
	cin >> third;

	hand.exchange(first, second, third, hand.handOfCards);  //exchanges cards selected by user







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


	cout << "Which cards would you like to exchange: (select 3 from 1 to 5 hitting enter after each selection)" << endl;
	cin >> first;
	cin >> second;
	cin >> third;


	hand.exchange(first, second, third, hand.handOfCards);//exchange cards selected by user

	cout << "You have " << infantry << " infantry units" << endl;
	cout << "You have " << cavalry << " cavalary units" << endl;
	cout << "You have " << artillery << " artillery units" << endl;






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



	cout << "Which cards would you like to exchange: (select 3 from 1 to 5 hitting enter after each selection)" << endl;
	cin >> first;
	cin >> second;
	cin >> third;


	hand.exchange(first, second, third, hand.handOfCards); //exchanges cards selected by user

	cout << "You have " << infantry << " infantry units" << endl;
	cout << "You have " << cavalry << " cavalary units" << endl;
	cout << "You have " << artillery << " artillery units" << endl;

	return 0;

}
