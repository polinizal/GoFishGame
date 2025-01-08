#include "deck.h"
#include <cstdlib>
#include <ctime>
#include <iostream>


std::vector<Card> createDeck()
{
    std::vector<Card> deck;
    for (int i = 0; i < SUITS.size(); i++)
    {
        for (int j = 0; j < RANKS.size(); j++)
        {
			Card card;
			card.suit = SUITS[i];
			card.rank = RANKS[j];
			deck.push_back(card);
		}
	}

	return deck;

}

void swapCards(std::vector<Card>& deck, size_t i, size_t j) {

	Card temp = deck[i];
	deck[i] = deck[j];
	deck[j] = temp;
}

void shuffleDeck(std::vector<Card>& deck)
{
	std::srand(std::time(0));
	for (size_t i = 0; i < deck.size(); i++) {
		size_t j = std::rand() % deck.size();
		swapCards(deck, i, j);
	}
}



Card dealCard(std::vector<Card>& deck)
{
	if (deck.empty())
	{
		std::cout<<"Deck is empty! Cannot draw a card"<<std::endl; //research exceptions
	}

	size_t randomIndex = std::rand() % deck.size();

	Card drawnCard = deck[randomIndex];

	swapCards(deck, randomIndex, deck.size() - 1);

	deck.pop_back();

	return drawnCard;
	
}

