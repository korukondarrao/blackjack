#include "blackjack.h"
#include <ctime>
#include <iomanip>

const string suits[4] = { "Hearts", "Diamonds", "Clubs", "Spades" }; 
const string faceCards[3] = { "Jack", "Queen", "King" };

// Description: Generate a random card within a specified range.
// Pre: Min and max must be valid card values within the game rules. 
// Post: Returns a Card struct with a random value and suit assigned.
Card generateRandomCard(const int min, const int max) 
{
    Card card;
    int value = rand() % (max - min + 1) + min;
    if (value == 1) 
    {
        card.value = 1;
        card.name = "Ace";
    } 
    else if (value >= 2 && value <= 10) 
    {
        card.value = value;
        card.name = to_string(value);
    } 
    else 
    {
        card.value = 10;
        card.name = faceCards[value - 11];
    }
    card.suit = suits[rand() % 4];
    return card;
}

// Description: Generate a random card with a specified probability of drawing a 10-valued card.
// Pre: Probability must be between 0 and 100. 
// Post: Returns a Card struct where a 10-value card is drawn based on probability.
Card generateRandomCard(const int min, const int max, const int probability) 
{
    Card card;
    int randomValue = rand() % 100;
    if (randomValue < probability) 
    {
        card.value = 10;
        card.name = faceCards[rand() % 3];
    } 
    else 
    {
        card = generateRandomCard(min, max);
    }
    return card;
}

// Description: Generate a wildcard.
// Pre: None. 
// Post: Returns a wildcard Card struct with a random value and suit.
Card generateWildCard() 
{
    Card wildcard;
    wildcard.value = rand() % 11 + 1;
    wildcard.suit = suits[rand() % 4];
    wildcard.name = "Wildcard";
    return wildcard;
}

// Description: Checks if a hand is a Blackjack.
// Pre: The hand must contain exactly two cards. 
// Post: Returns true if the hand is a Blackjack, false otherwise.
bool isBlackjack(const vector<Card>& hand) 
{
    if (hand.size() == 2) 
    {
        int value1 = hand[0].value;
        int value2 = hand[1].value;
        if ((value1 == 1 && value2 == 10) || (value1 == 10 && value2 == 1)) 
        {
            return true;
        }
    }
    return false;
}

// Description: Calculates the total value of a hand, adjusting for Aces.
// Pre: The hand must contain at least one card.
// Post: Returns the total hand value considering Ace flexibility.
int calculateHandTotal(const vector<Card>& hand) 
{
    int total = 0;
    int aceCount = 0;
    for (const auto& card : hand) 
    {
        if (card.value == 1) 
        {
            aceCount++;
            total += 11; // Initially count Ace as 11
        } 
        else 
        {
            total += card.value;
        }
    }
    // Adjust for Aces if total exceeds 21
    while (total > 21 && aceCount > 0) 
    {
        total -= 10;
        aceCount--;
    }
    return total;
}

// Description: Applies the effect of a wildcard based on its suit.
// Pre: A wildcard must be drawn and assigned to a suit.
// Post: Modifies the wildcard’s value and potentially the player's hand.
void applyWildCardEffect(Player& player, Card& wildcard) 
{
    if (wildcard.suit == "Hearts") 
    {
        wildcard.value *= 2;
    } 
    else if (wildcard.suit == "Diamonds") 
    {
        wildcard.value = 21 - calculateHandTotal(player.hand);
    } 
    else if (wildcard.suit == "Clubs") 
    {
        if (calculateHandTotal(player.hand) <= 21) 
        {
            player.hand.push_back(generateRandomCard(1, 10));
        }
    } 
    else if (wildcard.suit == "Spades") 
    {
        wildcard.value = (wildcard.value + 1) / 2;
    }
}

// Description: Updates the player's balance based on game outcome.
// Pre: The player must have a valid wager.
// Post: Adjusts the balance depending on win, loss, blackjack, or double down.
void updatePlayerBalance(Player& player, double wager, bool win, bool blackjack, bool doubleDown) 
{
    if (win) 
    {
        if (blackjack) 
        {
            player.balance += 1.5 * wager;  // 1.5:1 payout for Blackjack win
        } 
        else if (doubleDown) 
        {
            player.balance += 2 * wager;  // 2:1 payout for double down win
        } 
        else 
        {
            player.balance += wager;  // 1:1 payout for regular win
        }
    } 
    else 
    {
        player.balance -= wager;  // Deduct wager for loss
    }
}

// Description: Displays the outcome of the game round.
// Pre: The player must have finished the round.
// Post: Outputs the game outcome and updates the balance display.
void displayOutcome(const Player& player, const string& outcome, double wager, bool win) 
{
    cout << outcome << endl;
    cout << "Balance Update: " 
         << (win ? "+" : "-") << "$" << fixed << setprecision(2) << wager << endl;
    cout << "Your new balance is $" << fixed << setprecision(2) << player.balance << endl;
}

// Description: Displays a summary of the player's game session.
// Pre: The game must have ended or the player must have chosen to exit.
// Post: Outputs the game summary with win/loss statistics and final balance.
void displayGameSummary(const Player& player, double initialBalance, int totalRounds, int totalWins, int totalBlackjackWins, int totalLosses, int totalBlackjackLosses, int totalTies) 
{
    double netGainLoss = player.balance - initialBalance;
    cout << "\n=== Game Summary ===" << endl;
    cout << "Total Rounds Played: " << totalRounds << endl;
    cout << "Total Wins (Regular): " << totalWins << endl;
    cout << "Total Wins (Blackjack): " << totalBlackjackWins << endl;
    cout << "Total Losses (Regular): " << totalLosses << endl;
    cout << "Total Losses (Blackjack): " << totalBlackjackLosses << endl;
    cout << "Total Ties (Regular): " << totalTies << endl;
    cout << "Total Ties (Blackjack): " << 0 << endl;
    cout << "Final Balance: $" << fixed << setprecision(2) << player.balance << endl;
    cout << "Net Gain/Loss: " << (netGainLoss >= 0 ? "+" : "-") << "$" << fixed << setprecision(2) << abs(netGainLoss) << endl;
    cout << endl;
    cout << "\nThank you for playing CodeJack: The Blackjack Simulator!" << endl;
    cout << "We hope to see you again soon." << endl;
}


