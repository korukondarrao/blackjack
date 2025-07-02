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

// Generate a random card within a specified range
Card generateRandomCard(const int min, const int max);

// Generate a random card with a specified probability of drawing a 10-valued card
Card generateRandomCard(const int min, const int max, const int probability);

// Generate a wildcard
Card generateWildCard();

// Check if a hand is a Blackjack
bool isBlackjack(const vector<Card>& hand);

// Calculate the total value of a hand, adjusting for Aces
int calculateHandTotal(const vector<Card>& hand);

// Apply the effect of a wildcard based on its suit
void applyWildCardEffect(Player& player, Card& wildcard);

// Update the player's balance based on game outcome
void updatePlayerBalance(Player& player, double wager, bool win, bool blackjack, bool doubleDown);

// Display the outcome of the game round
void displayOutcome(const Player& player, const string& outcome, double wager, bool win);

// Display a summary of the player's game session
void displayGameSummary(const Player& player, double initialBalance, int totalRounds, int totalWins, int totalBlackjackWins, int totalLosses, int totalBlackjackLosses, int totalTies);

#endif
