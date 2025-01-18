#include "game.h"
#include <iostream>
#include <cstdlib> // For std::rand and std::srand
#include <ctime>   // For std::time

// Initializes the game: creates a deck, shuffles it, and deals cards
void initializeGame(Player& player, Player& computer, Deck& deck) {
    deck = createDeck();     // Create a standard deck
    shuffleDeck(deck);       // Shuffle the deck
    dealCards(deck, player.hand, computer.hand); // Deal 6 cards to each player

    std::cout << "Game initialized. Cards have been dealt." << std::endl;
    displayHand(player); // Show the player's initial hand
}

// Handles the player's turn
void handlePlayerTurn(Player& player, Player& computer, Deck& deck) {
    std::cout << "\nYour turn!" << std::endl;

    // Check if the player's hand is empty
    if (player.hand.empty()) {
        std::cout << "Your hand is empty. You must draw a card to continue." << std::endl;

        while (true) {
            std::string drawCommand;
            std::cout << "Type 'draw' to draw a card: ";
            std::cin >> drawCommand;
            if (drawCommand == "draw") {
                if (areThereCardsLeft(deck)) {
                    Card drawn = drawCard(deck);
                    if (!drawn.rank.empty()) { 
                        std::cout << "You drew: " << drawn.rank << " of " << drawn.suit << std::endl;
                        addCardToHand(player, drawn);
                        break; // End this forced draw action
                    }
                }
                else {
                    std::cout << "Oops, no cards left in the deck :( Your turn ends." << std::endl;
                    break; // End turn if no cards are in the deck
                }
            }
            else {
                std::cout << "Invalid command. Please type 'draw' to proceed." << std::endl;
            }
        }
    }

    while (true) {
        std::string command;
        std::cout << "Enter your command (ask <rank>, claim <rank>, show, check deck): ";
        std::cin >> command;

        if (command == "show") {
            displayHand(player);
        }
        else if (command == "ask") {
            std::string rank;
            std::cin >> rank;

            // Ensure the player has the rank they are asking for
            bool hasRank = false;
            for (const Card& card : player.hand) {
                if (card.rank == rank) {
                    hasRank = true;
                    break;
                }
            }

            if (!hasRank) {
                std::cout << "You can only ask for ranks you currently have in your hand!" << std::endl;
                continue; // Retry asking
            }

            // Check if the computer has the rank
            bool found = false;
            for (size_t i = 0; i < computer.hand.size(); i++) {
                if (computer.hand[i].rank == rank) {
                    found = true;
                    addCardToHand(player, computer.hand[i]);
                    computer.hand.erase(computer.hand.begin() + i);
                    std::cout << "You took: " << rank << " from the computer." << std::endl;
                    i--; // Adjust index after removing a card
                }
            }

            if (!found) {
                std::cout << "The computer doesn’t have any " << rank << "s. GoFish!" << std::endl;

                if (!areThereCardsLeft(deck)) {
                    std::cout << "Oops, you can't draw a card, there are no cards left in the deck :( Your turn ends." << std::endl;
                    break; // End the player's turn
                }

                std::string drawCommand;
                while (true) {
                    std::cout << "Type 'draw' to draw a card: ";
                    std::cin >> drawCommand;
                    if (drawCommand == "draw") {
                        break;
                    }
                    else {
                        std::cout << "Invalid command. Please type 'draw'." << std::endl;
                    }
                }

                Card drawn = drawCard(deck);
                if (!drawn.rank.empty()) {
                    std::cout << "You drew: " << drawn.rank << " of " << drawn.suit << std::endl;
                    addCardToHand(player, drawn);

                    if (drawn.rank == rank) {
                        std::cout << "You drew a " << rank << "! You can ask again." << std::endl;
                        continue;
                    }
                }

                break; // End the turn if no match
            }

            continue; // Allow player to ask again
        }
        else if (command == "claim") {
            std::string rank;
            std::cin >> rank;

            if (hasFullSet(player, rank)) {
                claimSet(player, rank);
                std::cout << "You claimed a full set of " << rank << "s!" << std::endl;
            }
            else {
                std::cout << "You do not have a full set of " << rank << "s to claim." << std::endl;
            }
        }
        else if (command == "check") { // Temporary debugging function
            std::cout << (areThereCardsLeft(deck) ? "The deck is not empty." : "The deck is empty.") << std::endl;
        }
        else {
            std::cout << "Invalid command. Please use 'ask <rank>', 'claim <rank>', or 'show'." << std::endl; 
        }
    }
}

// Handles the computer's turn
void handleComputerTurn(Player& player, Player& computer, Deck& deck) {
    std::cout << "\nComputer's turn!" << std::endl;

    // Check if the computer's hand is empty
    if (computer.hand.empty()) {
        std::cout << "The computer's hand is empty. It must draw a card to continue." << std::endl;

        if (areThereCardsLeft(deck)) {
            Card drawn = drawCard(deck);
            if (!drawn.rank.empty()) { 
                std::cout << "The computer drew a card from the deck" << std::endl;
                addCardToHand(computer, drawn);
                return; // End turn after forced draw
            }
        }
        else {
            std::cout << "The deck is empty. The computer cannot draw a card. Computer's turn ends." << std::endl;
            return; // End the computer's turn
        }
    }

    while (true) {
        // Randomly select a rank from the computer's hand to ask for
        size_t randomIndex = std::rand() % computer.hand.size();
        std::string rankToAsk = computer.hand[randomIndex].rank;
    
        std::cout << "The computer requests all cards of rank " << rankToAsk << ". Enter 'give <rank>' or 'GoFish!': ";
        std::string command, providedRank;
        std::cin >> command;
        if (command == "give") {
            std::cin >> providedRank;
            if (providedRank == rankToAsk) {
                bool hasGivenAny = false;
                for (auto it = player.hand.begin(); it != player.hand.end();) {
                    if (it->rank == rankToAsk) {
                        computer.hand.push_back(*it);
                        it = player.hand.erase(it);
                        hasGivenAny = true;
                    }
                    else {
                        ++it;
                    }
                }

                if (hasGivenAny) {
                    std::cout << "You gave all your " << rankToAsk << "s to the computer." << std::endl;
                    continue; // Computer can ask again
                }
                else {
					std::cout << "You do not have any " << rankToAsk << "s in your hand. Please check and try again: ";
                    
				}
            }
            else {
                std::cout << "Invalid card rank provided. Please check for "<<rankToAsk<<" and try again: ";
                
            }
            
        }
        else if (command == "GoFish!") {
            /*std::cout << "The computer draws a card from the deck." << std::endl;*/
            if (areThereCardsLeft(deck)) {
                Card drawn = drawCard(deck);
                if (!drawn.rank.empty()) { 
                    computer.hand.push_back(drawn);
                    std::cout << "The computer drew a card." << std::endl;

                    // If the drawn card matches the initial rank, ask again
                    if (drawn.rank == rankToAsk) {
                        std::cout << "But the card is a " << rankToAsk << " and can ask again!" << std::endl;
                        continue;
                    }
                }
            }
            else {
                std::cout << "The deck is empty. The computer cannot draw a card." << std::endl;
            }
            break; // End turn after drawing
        }
        else {
            std::cout << "Invalid command. Please type 'give <rank>' or 'GoFish!': ";
           
        }

        //break; End turn if no more actions
    }

    // Check for full sets
    for (const std::string& r : RANKS) {
        if (hasFullSet(computer, r)) {
            claimSet(computer, r);
            std::cout << "The computer claimed a full set of " << r << "s!" << std::endl;
        }
    }
}

bool isGameOver(const Player& player, const Player& computer) {
    // The game is over if one player owns all the sets
    return player.claimedSets.size() == RANKS.size() || computer.claimedSets.size() == RANKS.size();
}

void handleSecondPhase(Player& player, Player& computer) {
    std::cout << "\nThe deck is empty, and both players have no cards left in their hands. Starting the second phase of the game!" << std::endl;

    while (true) {
        // Player's turn
        while (true) {
            std::cout << "Your turn! Enter a command (ask set <rank>): ";
            std::string command, rank;
            std::cin >> command >> rank;

            if (command == "ask" && rank == "set") {
                auto it = std::find(computer.claimedSets.begin(), computer.claimedSets.end(), rank);
                if (it != computer.claimedSets.end()) {
                    std::cout << "You took the set of " << rank << "s from the computer!" << std::endl;
                    player.claimedSets.push_back(rank);
                    computer.claimedSets.erase(it);
                }
                else {
                    std::cout << "The computer doesn’t have the set of " << rank << "s. Your turn ends." << std::endl;
                    break; // End player's turn
                }

                // Check if the game is over
                if (isGameOver(player, computer)) {
                    determineWinner(player, computer);
                    return;
                }
            }
            else {
                std::cout << "Invalid command. Please use 'ask set <rank>'." << std::endl;
            }
        }

        // Computer's turn
        std::cout << "\nComputer's turn!" << std::endl;
        while (true) {
            if (!player.claimedSets.empty()) {
                size_t randomIndex = std::rand() % player.claimedSets.size();
                std::string rankToAsk = player.claimedSets[randomIndex];
                std::cout << "The computer asks for the set of " << rankToAsk << "s." << std::endl;

                auto it = std::find(player.claimedSets.begin(), player.claimedSets.end(), rankToAsk);
                if (it != player.claimedSets.end()) {
                    std::cout << "The computer took the set of " << rankToAsk << "s from you!" << std::endl;
                    computer.claimedSets.push_back(rankToAsk);
                    player.claimedSets.erase(it);
                }
                else {
                    std::cout << "You don’t have the set of " << rankToAsk << "s. The computer’s turn ends." << std::endl;
                    break; // End computer's turn
                }

                // Check if the game is over
                if (isGameOver(player, computer)) {
                    determineWinner(player, computer);
                    return;
                }
            }
            else {
                std::cout << "The computer has no sets to ask for. The turn ends." << std::endl;
                break; // End computer's turn
            }
        }
    }
}

bool IsReadyForSecondPhase(const Deck& deck, const Player& player, const Player& computer)
{
    return (!areThereCardsLeft(deck)) && (player.hand.empty()) && (computer.hand.empty());
}


Player determineWinner(const Player& player, const Player& computer) {
    if (player.claimedSets.size() == RANKS.size()) {
        std::cout << "You win by claiming all the sets!" << std::endl;
        return player;
    }
    else if (computer.claimedSets.size() == RANKS.size()) {
        std::cout << "The computer wins by claiming all the sets!" << std::endl;
        return computer;
    }
    else {
        std::cout << "Unexpected game state: no winner determined." << std::endl;
        return {}; // Empty Player to signify an unexpected state
    }
}
