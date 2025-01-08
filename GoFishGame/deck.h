#pragma once
#ifndef DECK_H
#define DECK_H

#include <vector>
#include "card.h"

std::vector<Card> createDeck();
void shuffleDeck(std::vector<Card>& deck);
Card dealCard(std::vector<Card>& deck);

#endif