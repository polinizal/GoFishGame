#include "game.h"
#include <iostream>

int main() {
    // Create player and computer structures
    Player player;
    Player computer;

    // Create and initialize the deck
    Deck deck;
    initializeGame(player, computer, deck);

    // Main game loop for the first phase
    while (areCardsEqualRank && !isGameOver(player, computer, deck)) {
        // Player's turn
        handlePlayerTurn(player, computer, deck);

        // Check if the deck is empty
        if (!areThereCardsLeft) {
            std::cout << "\nThe deck is now empty. Transitioning to the second phase of the game!" << std::endl;
            break;
        }

        // Check if the game is over after the player's turn
        if (isGameOver(player, computer, deck)) {
            break;
        }

        // Computer's turn
        handleComputerTurn(player, computer, deck);
    }

    // Transition to the second phase if the game is not over
    if (!isGameOver(player, computer, deck)) {
        handleSecondPhase(player, computer);
    }

    // Determine and display the winner
    determineWinner(player, computer);

    // End the game with a thank-you message
    std::cout << "Game over! Thank you for playing!" << std::endl;

    return 0;
}
