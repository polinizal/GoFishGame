#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "deck.h"

// Function declarations
void initializeGame(Player& player, Player& computer, Deck& deck);

void handlePlayerTurn(Player& player, Player& computer, Deck& deck);

void handleComputerTurn(Player& player, Player& computer, Deck& deck);

void handleSecondPhase(Player& player, Player& computer);

bool isGameOver(const Player& player, const Player& computer);

bool IsReadyForSecondPhase(const Deck& deck, const Player& player, const Player& computer);

Player determineWinner(const Player& player, const Player& computer);

#endif
