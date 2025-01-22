/**
 *
 * Solution to course project # 8
 * Introduction to programming course
 * Faculty of Mathematics and Informatics of Sofia University
 * Winter semester 2023/2024
 *
 * @author Polina Staneva
 * @idnumber 4MI0600481
 * @compiler VC
 *
 * <main game file>
 *
 */

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
        handleSecondPhase(player, computer); // Main game loop for the second phase
    }

    
    determineWinner(player, computer); // Determine the winner of the game

    // End the game with a thank-you message
    std::cout << "Game over! Thank you for playing!" << std::endl;

    return 0;
}
