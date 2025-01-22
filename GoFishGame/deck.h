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
 * <deck structure and functions header file>
 *
 */

#ifndef DECK_H
#define DECK_H
#include <vector>
#include "card.h"

struct Deck {
	std::vector<Card> cards;
};

Deck createDeck();

void shuffleDeck(Deck &deck);

Card drawCard(Deck &deck);

void dealCards(Deck& deck, std::vector<Card>& playerHand, std::vector<Card>& computerHand);

bool areThereCardsLeft(const Deck& deck);

#endif
