#include <iostream>
#include <string>


#include "template/Card.h"
#include "template/Deck.h"
#include "template/Player.h"

using namespace std;

int main()
{
	Deck gameDeck = Deck();
	//Card discardDeck[52];
	Deck discardDeck = Deck();
	Player playerOne = Player();	//Declare variables
	Player playerTwo = Player();
	string userInput = "yes";



	gameDeck.shuffle();			//Create and shuffle a new deck
	if (gameDeck.isEmpty())		//If the deck is empty - fill it up and shuffle again
	{
		gameDeck.fillDeck();	//i'll put it in the loop later
		gameDeck.shuffle();
	}

	while (userInput == "yes" or userInput == "Yes") 		//creating a while loop for the main gameplay	
	{

		discardDeck.clear();								//removing all the cards from the discard deck

		for (int i = 0; i < 4; i++) {
			Card myCard = gameDeck.getTopCard();			//adding cards to players hands
			playerOne.addCard(myCard);
		}

		for (int i = 0; i < 4; i++) {
			Card myCard = gameDeck.getTopCard();			//adding cards to players hands
			playerTwo.addCard(myCard);
		}

		cout << "Player one = " << playerOne.getHand() << endl;
		cout << "Player two = " << playerTwo.getHand() << endl;

}