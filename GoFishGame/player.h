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
 * <player structure and functions header file>
 *
 */

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

bool isHandEmpty(const Player& player);

void claimSet(Player& player, const std::string& rank);

void displayHand(const Player& player);

void handEmpty(Player& player);

bool isPlayerClaimedSetEmpty(const Player& player);

#endif