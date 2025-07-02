#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Struct to represent a playing card
struct Card 
{
    int value;         // Numeric value of the card
    string name;       // Name of the card (e.g., "Ace", "2", "King")
    string suit;       // Suit of the card (e.g., "Hearts", "Spades")
};

// Struct to represent a player
struct Player 
{
    string name;               // Name of the player
    double balance;            // Balance of the player
    vector<Card> hand;         // Cards in the player's hand
};

// Struct to represent a dealer
struct Dealer 
{
    vector<Card> hand;         // Cards in the dealer's hand
};

#endif
