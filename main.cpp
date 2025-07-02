#include "blackjack.h"
#include <ctime>
#include <iomanip>

int main() 
{
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator

    Player player;
    Dealer dealer;

    // Get player's name and initialize balance
    cout << "Welcome to CodeJack: The Blackjack Simulator!\n";
    cout << "Player, please enter your name: ";
    cin >> player.name;

    player.balance = (rand() % 9900 + 1010) / 100.0;
    double initialBalance = player.balance;
    cout << "\nHello, " << player.name << "! Your starting balance is $" << fixed << setprecision(2) << player.balance << endl;

    // Initialize game statistics
    int totalRounds = 0;
    int totalWins = 0;
    int totalBlackjackWins = 0;
    int totalLosses = 0;
    int totalBlackjackLosses = 0;
    int totalTies = 0;

    char playAgain = 'y';
    while (player.balance > 0.00 && playAgain == 'y') 
    {
        totalRounds++;
        double wager;
        cout << "\nEnter your wager: $";
        cin >> wager;
        while (wager > player.balance || wager <= 0) 
        {
            cout << "Invalid wager. Enter an amount between $0.00 and $" << player.balance << ": $";
            cin >> wager;
        }

        // Deal initial cards
        player.hand.clear();
        dealer.hand.clear();

        bool playerLucky = (rand() % 100) < 30;
        int probability = playerLucky ? (rand() % 100 + 1) : 0;

        // Generate initial cards for player with or without luck factor
        if (playerLucky) 
        {
            player.hand.push_back(generateRandomCard(1, 10, probability));
            player.hand.push_back(generateRandomCard(1, 10, rand() % 100 + 1));
        } 
        else
        {
            player.hand.push_back(generateRandomCard(1, 10));
            player.hand.push_back(generateRandomCard(1, 10));
        }

        // Generate initial cards for dealer
        dealer.hand.push_back(generateRandomCard(1, 10));
        dealer.hand.push_back(generateRandomCard(1, 10));

        // Display initial hands
        cout << "Player's Hand: " << player.hand[0].name << " of " << player.hand[0].suit << ", " << player.hand[1].name << " of " << player.hand[1].suit 
             << " (Total: " << calculateHandTotal(player.hand) << ")" << endl;
        cout << "Dealer's Hand: " << dealer.hand[0].name << " of " << dealer.hand[0].suit << ", [Hidden Card]" << endl;

        // Check for initial blackjack
        bool playerBlackjack = isBlackjack(player.hand);
        bool dealerBlackjack = isBlackjack(dealer.hand);

        if (playerBlackjack || dealerBlackjack) 
        {
            if (playerBlackjack && dealerBlackjack) 
            {
                cout << "Both player and dealer have Blackjack! It's a tie." << endl;
                totalTies++;
            } 
            else if (playerBlackjack) {
                updatePlayerBalance(player, wager, true, true, false);
                totalBlackjackWins++;
                displayOutcome(player, "Congratulations! You hit Blackjack!", wager, true);
            } 
            else 
            {
                updatePlayerBalance(player, wager, false, false, false);
                totalBlackjackLosses++;
                displayOutcome(player, "Dealer has Blackjack. You lose.", wager, false);
            }
        } 
        else 
        {
            // Player's turn
            char action;
            bool doubleDown = false;
            bool initialAction = true;
            do 
            {
                if (initialAction) 
                {
                    cout << "Choose an action: (h)it, (s)tand, (d)ouble down: ";
                } 
                else 
                {
                    cout << "Choose an action: (h)it, (s)tand: ";
                }
                cin >> action;
                if (action == 'h') 
                {
                    Card newCard = generateRandomCard(1, 10);
                    // Check if the card drawn is a wildcard
                    if (rand() % 100 < 18) 
                    {
                        newCard = generateWildCard();
                        cout << "You drew a Wildcard! Choose a value (1-11): ";
                        cin >> newCard.value;
                        applyWildCardEffect(player, newCard);
                    }
                    player.hand.push_back(newCard);
                    cout << "Player's Hand: ";
                    for (const auto& card : player.hand) 
                    {
                        cout << card.name << " of " << card.suit << ", ";
                    }
                    cout << " (Total: " << calculateHandTotal(player.hand) << ")" << endl;
                    if (calculateHandTotal(player.hand) > 21) 
                    {
                        updatePlayerBalance(player, wager, false, false, false);
                        totalLosses++;
                        displayOutcome(player, "You bust!", wager, false);
                        break;
                    }
                    initialAction = false;
                } 
                else if (action == 'd' && initialAction) 
                {
                    if (player.balance < wager) 
                    {
                        cout << "You do not have enough balance to double down." << endl;
                        continue;
                    }
                    doubleDown = true;
                    wager *= 2;
                    Card newCard = generateRandomCard(1, 10);
                    // Check if the card drawn is a wildcard
                    if (rand() % 100 < 18) 
                    {
                        newCard = generateWildCard();
                        cout << "You drew a Wildcard! Choose a value (1-11): ";
                        cin >> newCard.value;
                        applyWildCardEffect(player, newCard);
                    }
                    player.hand.push_back(newCard);
                    cout << "Player's Hand: ";
                    for (const auto& card : player.hand) 
                    {
                        cout << card.name << " of " << card.suit << ", ";
                    }
                    cout << " (Total: " << calculateHandTotal(player.hand) << ")" << endl;
                    if (calculateHandTotal(player.hand) > 21) 
                    {
                        updatePlayerBalance(player, wager, false, false, false);
                        totalLosses++;
                        displayOutcome(player, "You bust!", wager, false);
                    }
                    break;
                } 
                else if (action == 's') 
                {
                    break;
                } 
                else 
                {
                    cout << "Invalid action. Please choose again." << endl;
                }
            } 
            while (true);

            if (calculateHandTotal(player.hand) <= 21) 
            {
                // Dealer's turn
                cout << "Dealer's Hand: " << dealer.hand[0].name << " of " << dealer.hand[0].suit << ", " << dealer.hand[1].name << " of " << dealer.hand[1].suit 
                     << " (Total: " << calculateHandTotal(dealer.hand) << ")" << endl;

                while (calculateHandTotal(dealer.hand) < 17) 
                {
                    Card newCard = generateRandomCard(1, 10);
                    // Check if the card drawn is a wildcard
                    if (rand() % 100 < 18) 
                    {
                        newCard = generateWildCard();
                        cout << "Dealer drew a Wildcard! Value: " << newCard.value << endl;
                    }
                    dealer.hand.push_back(newCard);
                    cout << "Dealer's Hand: ";
                    for (const auto& card : dealer.hand) 
                    {
                        cout << card.name << " of " << card.suit << ", ";
                    }
                    cout << " (Total: " << calculateHandTotal(dealer.hand) << ")" << endl;
                }

                // Determine the outcome
                if (calculateHandTotal(dealer.hand) > 21) 
                {
                    updatePlayerBalance(player, wager, true, false, doubleDown);
                    totalWins++;
                    displayOutcome(player, "Dealer busts. You win!", wager, true);
                } 
                else if (calculateHandTotal(dealer.hand) > calculateHandTotal(player.hand)) 
                {
                    updatePlayerBalance(player, wager, false, false, false);
                    totalLosses++;
                    displayOutcome(player, "Dealer wins.", wager, false);
                } 
                else if (calculateHandTotal(dealer.hand) == calculateHandTotal(player.hand)) 
                {
                    totalTies++;
                    displayOutcome(player, "It's a tie.", wager, false);
                } 
                else 
                {
                    updatePlayerBalance(player, wager, true, false, doubleDown);
                    totalWins++;
                    displayOutcome(player, "You win!", wager, true);
                }
            }
        }

        // Prompt the player to play another round
        do 
        {
            cout << "\nDo you want to play another round? (y/n): ";
            cin >> playAgain;
            if (playAgain != 'y' && playAgain != 'n') 
            {
                cout << "Invalid input. Please enter 'y' or 'n'." << endl;
            }
        } 
        while (playAgain != 'y' && playAgain != 'n');
    }

    // Specify to player about insufficient balance
    if (player.balance <= 0.00 && playAgain == 'y')
    {
	cout << "\nSorry! You don't have enough money for another round.\n";
    }

    // Display the game summary
    displayGameSummary(player, initialBalance, totalRounds, totalWins, totalBlackjackWins, totalLosses, totalBlackjackLosses, totalTies);

    return 0;
}
