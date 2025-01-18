#pragma once
#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "deck.h"

// Function declarations
void initializeGame(Player& player, Player& computer, Deck& deck);
void handlePlayerTurn(Player& player, Player& computer, Deck& deck);
void handleComputerTurn(Player& player, Player& computer, Deck& deck);
bool isGameOver(const Player& player, const Player& computer, const Deck& deck);
Player determineWinner(const Player& player, const Player& computer);
void handleSecondPhase(Player& player, Player& computer);	


#endif
