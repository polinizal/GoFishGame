// GoFishGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "deck.h"
#include <iostream>

int main()
{
    std::vector<Card> deck = createDeck();
    shuffleDeck(deck);

    // Draw 5 random cards
    std::cout << "Drawing 6 random cards:\n";
    for (int i = 0; i < 6; ++i) {
        Card card = dealCard(deck);
        std::cout << card.rank << " of " << card.suit << std::endl;
    }

    std::cout << "Remaining cards in deck: " << deck.size() << "\n";
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
