#include "deck.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "card.h"

Deck createDeck() {
    Deck deck;

    for (const std::string& suit : SUITS) {
        for (const std::string& rank : RANKS) {
            deck.cards.push_back({ suit, rank });
        }
    }

    return deck;
}

void swapCards(Deck& deck, size_t i, size_t j) {
    Card temp = deck.cards[i];
    deck.cards[i] = deck.cards[j];
    deck.cards[j] = temp;
}

void shuffleDeck(Deck& deck) {
    std::srand(std::time(0));
    int n = deck.cards.size();
    for (size_t i = 0; i < n; i++) {
        int randomIndex = i + std::rand() % (n - i);
        swapCards(deck, i, randomIndex);
    }
}

Card drawCard(Deck& deck) {
    size_t randomIndex = std::rand() % deck.cards.size();
    Card drawnCard = deck.cards[randomIndex];
    swapCards(deck, randomIndex, deck.cards.size() - 1);
    deck.cards.pop_back();
    return drawnCard;
}

void dealCards(Deck& deck, std::vector<Card>& playerHand, std::vector<Card>& computerHand) {
    for (int i = 0; i < 6; i++) {
        playerHand.push_back(drawCard(deck));
        computerHand.push_back(drawCard(deck));
    }
}

bool areThereCardsLeft(const Deck& deck) {
    return !deck.cards.empty();
}
