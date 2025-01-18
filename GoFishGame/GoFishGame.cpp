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
    while ((!IsReadyForSecondPhase(deck,player,computer))&&(!isGameOver(player,computer))) {
        
        handlePlayerTurn(player, computer, deck);
        
        handleComputerTurn(player, computer, deck);
    }

    
    if (!isGameOver(player, computer)) {
        handleSecondPhase(player, computer);
    }

    
    determineWinner(player, computer);

    // End the game with a thank-you message
    std::cout << "Game over! Thank you for playing!" << std::endl;

    return 0;
}
