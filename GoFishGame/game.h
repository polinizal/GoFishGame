#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "deck.h"

// Function declarations
void initializeGame(Player& player, Player& computer, Deck& deck);

void handlePlayerTurn(Player& player, Player& computer, Deck& deck);

void handlePlayerClaimCommand(Player& player, std::string& rank);

void handlePlayerDrawCommand(std::string& drawCommand, Deck& deck, Player& player, std::string& rank, int& retFlag);

void checkComputerForRank(Player& computer, std::string& rank, bool& found, Player& player);

void checkPlayerForRank(Player& player, std::string& rank, bool& hasRank);

void handlePlayerDrawWhenEmptyHand(Deck& deck, Player& player, bool& playerPlaying);

void handleComputerTurn(Player& player, Player& computer, Deck& deck);

void checkForComputerSets(Player& computer);

void handleComputerDrawWhenEmptyHand(Deck& deck, Player& computer, bool& retFlag);

void handleComputerGoFishCommand(Deck& deck, Player& computer, std::string& rankToAsk, bool& computerPlaying, int& retFlag);

void handlePlayerGiveCommand(std::string& providedRank, std::string& rankToAsk, Player& player, Player& computer, int& retFlag);

void checkComputerForFullSets(Player& computer);

void handleSecondPhase(Player& player, Player& computer);

void handleComputerAskSet(Player& player, std::string& rankToAsk, Player& computer, int& retFlag);

void handlePlayerAskSetCommand(Player& computer, std::string& rank, Player& player, int& retFlag);

bool isGameOver(const Player& player, const Player& computer);

bool IsReadyForSecondPhase(const Deck& deck, const Player& player, const Player& computer);

Player determineWinner(const Player& player, const Player& computer);

#endif
