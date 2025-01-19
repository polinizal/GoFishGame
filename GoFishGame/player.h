#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "card.h"
#include "string"

struct Player {
	std::vector<Card> hand;
	std::vector<std::string> claimedSets;
};

void addCardToHand(Player& player, const Card& card);

void removeCardsByRank(Player& player, const std::string& rank);

bool hasFullSet(const Player& player, const std::string& rank);

void claimSet(Player& player, const std::string& rank);

void displayHand(const Player& player);

void handEmpty(Player& player);

#endif