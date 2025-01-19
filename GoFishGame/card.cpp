#include "card.h"

std::string cardToString(const Card& card)
{
    return card.rank + " of " + card.suit;
}

bool areCardsEqualRank(const Card& card1, const Card& card2)
{
    return card1.rank == card2.rank;
}

bool isValidRank(const std::string& rank)
{
    for (const std::string& validRank : RANKS)
    {
        if (validRank == rank)
        {
            return true;
        }
    }
    return false;
}
