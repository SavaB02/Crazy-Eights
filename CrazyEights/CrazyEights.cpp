#include <iostream>
#include <string>
#include <vector>
#include "template/Card.h"
#include "template/Deck.h"
#include "template/Player.h"

using namespace std;

int main()
{
    bool playAgain = true;

    while (playAgain)                   //while loop to ask if the players want to play again at the end of the game
    {
        Deck gameDeck = Deck();
        Deck discardDeck = Deck();      //creating two decks, one is the game deck, the other is used to store all the discarded cards

        int numPlayers = 0;             //used to store the current amount of players in the game
        int userInputInt;
        bool isGameActive = true;       //a boolean variable to track if the game is being played or not
        int currentPlayer = 1;          //used to track the current player


        gameDeck.shuffle();             //shuffles the deck at the beginning of the game

        
        cout << "How many players (2-4)? ";
        cin >> numPlayers;
        if (numPlayers < 2 or numPlayers > 4)           //asking for the number of players (up to four)
        {         
            cout << "Invalid number of players. The number of players needs to be between two and four." << endl;
            continue;                                   //if the input is wrong, it resets the playAgain while loop
        }

        
        Player players[4];                              //creating an array of players based on the number of players
        for (int i = 0; i < numPlayers; i++) 
        {
            players[i] = Player();                      //adding the amount of players that the user chose
        }

        if (gameDeck.isEmpty())                         //if there's no cards in the game deck, refills it from the discard deck and shuffles again
        {       
            gameDeck = discardDeck;
            gameDeck.shuffle();
            discardDeck.clear();
        }

        discardDeck.clear();                            //clearing all cards from the discard deck

        
        for (int i = 0; i < 5; i++) 
        {
            for (int o = 0; o < numPlayers; o++) 
            {
                players[o].addCard(gameDeck.getTopCard());  //going through all the players in the game and adding 5 cards to each of them
            }
        }

        Card discardCard = gameDeck.getTopCard();           //setting up the initial discard card
        discardDeck.addCard(discardCard);                   //adding this discard card to the discard pile

        while (isGameActive)
        {
            Player* currentPlayerPointer = &players[currentPlayer - 1];     //creating a pointer to the current player

            cout << "Player " << currentPlayer << "'s turn" << endl;        //showing who is the current player

            vector<Card> currentHand = currentPlayerPointer->getHand();     //creating a vector of current player's hand
            bool isPlayable = false;

            for (Card card : currentHand)                                   //checking if the current player has a playable card
            {                                 

                if (card.getRank() == 8)                                    //if the player has a Wild card (eights)
                {                                  
                    isPlayable = true;
                    break;                                                  //exiting the loop if the player has a wild card
                }

                if (card.getSuit() == discardDeck.peekTopCard().getSuit() or card.getRank() == discardDeck.peekTopCard().getRank()) //if the player has any card to play
                {
                    isPlayable = true;
                    break;                                                  //exiting the if statement if the playable card is found
                }
            }

            if (isPlayable)
            {
                system("cls");                                                      //clearing the console

                cout << "|------------------------------------------|" << endl;
                cout << "| Player " << currentPlayer << "'s Turn |" << endl;        //showing which player's turn it is
                cout << "|------------------------------------------|" << endl;

                system("pause");                                                    //pausing to give other players time to look away

                system("cls");                                                      //clearing the console
                cout << "|------------------------------------------|" << endl;
                cout << "| Player " << currentPlayer << "'s Turn |" << endl;        //showing which player's turn it is
                cout << "|------------------------------------------|" << endl;

                cout << "|The current card is | " << discardDeck.peekTopCard().toString() << " | play your cards!|" << endl;    //showing the current discard card
                cout << "|----------------------------------------------------|" << endl;
                cout << "|Your cards are:" << endl;

                for (int i = 0; i < currentPlayerPointer->getHandSize(); i++)       //for loop to rotate through the player's hand and attach a number to each of them
                {  
                    cout << "|" << i + 1 << " - " << currentPlayerPointer->peekCard(i).toString() << endl;
                }

                cout << "|----------------------------------------------------|" << endl;

                bool validInput = false;                                            //creating a "flag" varaible to check if the user's input is valid

                while (validInput == false) 
                {
                    cout << "|Type a number of the card you wish to play: ";
                    cin >> userInputInt;

                    if (userInputInt > 0 and userInputInt <= currentPlayerPointer->getHandSize()) 
                    {
                        Card chosenCard = currentPlayerPointer->peekCard(userInputInt - 1);         //creating a separate variable to copy the player's card choice

                        if (chosenCard.getRank() == 8 or chosenCard.getRank() == discardDeck.peekTopCard().getRank() or chosenCard.getSuit() == discardDeck.peekTopCard().getSuit()) 
                        {
                            cout << "You picked " << chosenCard.toString() << endl;
                            discardDeck.addCard(currentPlayerPointer->getCard(userInputInt - 1));   //placing card that the player picked into a discard deck
                            system("cls");                                                          //clearing the console

                            if (currentPlayerPointer->getHandSize() == 0)                           //checking if the current player has zero cards in their hand i.e. they won
                            {                         
                                cout << "Player " << currentPlayer << " wins! Congratulations!" << endl;
                                isGameActive = false;
                                break;                                                              //breaking the loop
                            }

                            validInput = true;                                                      //setting the valid input to true to break the loop
                        }
                        else 
                        {
                            cout << "Invalid card. Try again." << endl;
                        }
                    }
                    else 
                    {
                        cout << "Invalid input. Try again." << endl;
                    }
                }
            }
            else                                                                                    //if there's no matching card in player's hand, ask to draw a card from the deck pile
            {  
                system("cls");                                                                      //clear the console before displaying the turn message

                cout << "|------------------------------------------|" << endl;
                cout << "| Player " << currentPlayer << "'s Turn |" << endl;                        //showing which player's turn it is
                cout << "|------------------------------------------|" << endl;
                cout << "|No matching card, you must draw a card." << endl;

                system("pause");                                                                    //pausing to wait for user's input
                system("cls");                                                                      //clearing the console before displaying the turn message


                Card drawnCard = gameDeck.getTopCard();                                             //variable to take a card from the game deck
                currentPlayerPointer->addCard(drawnCard);                                           //adding that card to the current player's hand

                cout << "|------------------------------------------|" << endl;
                cout << "| Player " << currentPlayer << "'s Turn |" << endl;                        //showing which player's turn it is
                cout << "|------------------------------------------|" << endl;
                cout << "|You drew: " << drawnCard.toString() << endl;

                if (drawnCard.getRank() == discardDeck.peekTopCard().getRank() or drawnCard.getSuit() == discardDeck.peekTopCard().getSuit())   //if it matches the current discard card then go into if statement
                {  
                    cout << "|The drawn card matches the top card of the discard pile." << endl;
                    cout << "|Type 1 to play it, type 2 to not play the card." << endl;
                    cin >> userInputInt;

                    if (userInputInt == 1) 
                    {
                        discardDeck.addCard(currentPlayerPointer->getCard(currentPlayerPointer->getHandSize() - 1));    //removing the card that player just picked up 

                        cout << "|You played: " << drawnCard.toString() << endl;
                        system("cls");                                                                                  //clearing the console

                        if (currentPlayerPointer->getHandSize() == 0)                                                   //checking if the current player has won
                        {  
                            cout << "Player " << currentPlayer << " wins! Congratulations!" << endl;
                            isGameActive = false;                                                                       //ending the game loop
                            break;                                                                                      //breaking the loop
                        }
                    }
                    else 
                    {
                        cout << "|You chose not to play the card. Turn skipped." << endl;
                        
                        
                        system("pause");                                                                                //pausing to wait for user's input
                        
                        
                        system("cls");                                                                                  //clearing the console
                    }
                }
                else 
                {
                    cout << "|The drawn card does not match. Turn skipped." << endl;
                    system("pause");                                                                                    //pausing to wait for user's input
                    system("cls");                                                                                      //clearing the console
                }
            }

            if (currentPlayer == numPlayers)                                                                            //if the current player is equal to the max amount of players then
            {  
                currentPlayer = 1;                                                                                      //reset to the first player
            }
            else 
            {
                currentPlayer++;                                                                                        //else, switch a turn to the next player
            }

        }

        cout << "Do you want to play again? (1 for Yes, 0 for No): ";                                                   //after the game loop ask if the user want to play again
        cin >> userInputInt;
        if (userInputInt != 1) 
        {
            playAgain = false;
            cout << "Thanks for playing! Goodbye!" << endl;
        }
    }

    return 0;           //making sure that the applicaion exits correctly
}