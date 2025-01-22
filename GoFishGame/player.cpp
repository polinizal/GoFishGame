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
 * <player functions source file>
 *
 */

#include "player.h"
#include <iostream>

void addCardToHand(Player& player, const Card& card)
{
	player.hand.push_back(card);
}
void handEmpty(Player& player)
{
	player.hand.clear();
}

bool isPlayerClaimedSetEmpty(const Player& player)
{
	return player.claimedSets.empty();
}

void removeCardsByRank(Player& player, const std::string& rank)
{
	std::vector<Card> newHand;
	for (size_t i = 0; i < player.hand.size(); i++) {
		if (player.hand[i].rank != rank) {
			newHand.push_back(player.hand[i]);
		}
	}
	player.hand = newHand;
}

bool hasFullSet(const Player& player, const std::string& rank)
{
	int count = 0;
	for (size_t i = 0; i < player.hand.size(); i++) {
		if (player.hand[i].rank == rank) {
			count++;
		}
	}
	return count == 4;
}

bool isHandEmpty(const Player& player)
{
	return player.hand.empty();
}

void claimSet(Player& player, const std::string& rank)
{
	if (hasFullSet(player, rank)) {
		removeCardsByRank(player, rank);
		player.claimedSets.push_back(rank);
	}
}

void displayHand(const Player& player)
{
	std::cout << "--------------------------------------" << std::endl;
	std::cout << "Your current hand:" << std::endl;
	for (size_t i = 0; i < player.hand.size(); i++) {
		std::cout << "- " << player.hand[i].rank << " of " << player.hand[i].suit << std::endl;
	}
	std::cout << "--------------------------------------" << std::endl;
}