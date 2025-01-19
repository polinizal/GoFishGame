#ifndef CARD_H
#define CARD_H

#include <string>
#include <vector>

const std::vector<std::string> SUITS = { "Hearts", "Diamonds", "Clubs", "Spades" };
const std::vector<std::string> RANKS = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace" };

struct Card
{
    std::string suit;
    std::string rank;
};

std::string cardToString(const Card& card);
bool areCardsEqualRank(const Card& card1, const Card& card2);
bool isValidRank(const std::string& rank);

#endif