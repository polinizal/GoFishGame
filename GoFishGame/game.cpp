#include "game.h"
#include <iostream>
#include <cstdlib> 
#include <ctime>   

//Constants
const int ASKAGAIN = 3;
const int INVALID_COMMAND = 2;
const int END_TURN = 2;

// Initializes the game: creates a deck, shuffles it, and deals cards
void initializeGame(Player& player, Player& computer, Deck& deck) {
     deck = createDeck();     // Create the deck
     shuffleDeck(deck);       // Shuffle the deck
     dealCards(deck, player.hand, computer.hand); // Deal 6 cards to each player

     std::cout << "Game initialized. Cards have been dealt." << std::endl;
     displayHand(player); // Show the player's initial hand
}

// Handles the player's turn
void handlePlayerTurn(Player& player, Player& computer, Deck& deck) {
     std::cout << "\nYour turn!" << std::endl;
     bool playerPlaying = true;
     while (playerPlaying) {
            if (isHandEmpty(player)) {     // Check if the player's hand is empty
                std::cout << "Your hand is empty. You must draw a card to continue." << std::endl;
                handlePlayerDrawWhenEmptyHand(deck, player, playerPlaying);
            }
            else {
                std::string command;
                std::cout << "Enter your command (ask <rank>, claim <rank>, show, check deck): ";
                std::cin >> command;

                if (command == "show") {
                    displayHand(player);
                }
                else if (command == "ask") {
                        std::string rank;
                        std::cin >> rank;
                        bool hasRank = false;
                        checkPlayerForRank(player, rank, hasRank); // Check if the player has the rank

                        if (!hasRank) {
                            std::cout << "You can only ask for ranks you currently have in your hand!" << std::endl;
                            continue; // Retry asking
                        }

                        bool found = false;
                        checkComputerForRank(computer, rank, found, player); // Check if the computer has the rank

                        if (!found) {
                            std::cout << "The computer does not have any " << rank << "s. GoFish!" << std::endl;

                            if (!areThereCardsLeft(deck)) {
                                std::cout << "Oops, you can't draw a card, there are no cards left in the deck :( Your turn ends." << std::endl;
                                playerPlaying = false;
                                break; // End the player's turn
                            }

                            std::string drawCommand;
                            int retFlag; 
                            handlePlayerDrawCommand(drawCommand, deck, player, rank, retFlag);
                            if (retFlag == ASKAGAIN) continue; // Ask again if the drawn card matches the rank

                            break; // End the turn if no match
                        }
                        continue; // Allow player to ask again
                }
                else if (command == "claim") {
                    std::string rank;
                    std::cin >> rank;
                    handlePlayerClaimCommand(player, rank);
                }
                else {
                    std::cout << "Invalid command. Please use 'ask <rank>', 'claim <rank>', or 'show'." << std::endl;
                }
            }
     }
}

//Helper Commands for Player Turn
void handlePlayerClaimCommand(Player& player, std::string& rank)
{
    if (hasFullSet(player, rank)) {
        claimSet(player, rank);
        std::cout << "You claimed a full set of " << rank << "s!" << std::endl;
    }
    else {
        std::cout << "You do not have a full set of " << rank << "s to claim." << std::endl;
    }
}

void handlePlayerDrawCommand(std::string& drawCommand, Deck& deck, Player& player, std::string& rank, int& retFlag)
{
    retFlag = 1; // Default return flag
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
    if (!drawn.rank.empty()) { // Check if a card was drawn
        std::cout << "You drew: " << drawn.rank << " of " << drawn.suit << std::endl;
        addCardToHand(player, drawn);

        if (drawn.rank == rank) {
            std::cout << "You drew a " << rank << "! You can ask again." << std::endl;
            { retFlag = ASKAGAIN; return; }; // Ask again if the drawn card matches the rank
        }
    }
}

void checkComputerForRank(Player& computer, std::string& rank, bool& found, Player& player)
{
    for (size_t i = 0; i < computer.hand.size(); i++) { 
        if (computer.hand[i].rank == rank) {
            found = true;
            addCardToHand(player, computer.hand[i]);
            computer.hand.erase(computer.hand.begin() + i);
            std::cout << "You took: " << rank << " from the computer." << std::endl;
            i--; // Adjust index after removing a card
        }
    }
}

void checkPlayerForRank(Player& player, std::string& rank, bool& hasRank)
{
    for (size_t i = 0; i < player.hand.size(); ++i) {
        if (player.hand[i].rank == rank) {
            hasRank = true;
            break;
        }
    }
}

void handlePlayerDrawWhenEmptyHand(Deck& deck, Player& player, bool& playerPlaying)
{
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
                    break; // End draw action
                }
            }
            else {
                std::cout << "Oops, no cards left in the deck :( Your turn ends." << std::endl;
                playerPlaying = false;
                break; // End turn if no cards are in the deck
            }
        }
        else {
            std::cout << "Invalid command. Please type 'draw' to proceed." << std::endl;
        }
    }
} // new function 1

// Handles the computer's turn
void handleComputerTurn(Player& player, Player& computer, Deck& deck) {
     std::cout << "\nComputer's turn!" << std::endl;
     bool computerPlaying = true;
     while (computerPlaying) {
            checkComputerForFullSets(computer); // Check for full sets

            if (isHandEmpty(computer)) { // Check if the computer's hand is empty
                std::cout << "The computer's hand is empty. It must draw a card to continue." << std::endl;
                bool retFlag;
                handleComputerDrawWhenEmptyHand(deck, computer, retFlag);
                if (retFlag) return; // End the computer's turn
            }
            else {
                size_t randomIndex = std::rand() % computer.hand.size(); // Randomly select a rank from the computer's hand to ask for
                std::string rankToAsk = computer.hand[randomIndex].rank;

                while (true) {
                        std::cout << "The computer requests all cards of rank " << rankToAsk << ". Enter 'give <rank>', 'show' or 'GoFish!': ";
                        std::string command, providedRank;
                        std::cin >> command;
                        if (command == "give") {
                            std::cin >> providedRank;
                            int retFlag;
                            handlePlayerGiveCommand(providedRank, rankToAsk, player, computer, retFlag);
                            if (retFlag == ASKAGAIN) break;
                            if (retFlag == INVALID_COMMAND) continue; 

                        }
                        else if (command == "GoFish!") {
                            int retFlag;
                            handleComputerGoFishCommand(deck, computer, rankToAsk, computerPlaying, retFlag);
                            if (retFlag == END_TURN) break;
                        }
                        else if (command == "show") {
                            displayHand(player);
                            continue;
                        }
                        else {
                            std::cout << "Invalid command. Please type 'give <rank>' or 'GoFish!': \n";
                            continue;
                        }
                }
            }
            checkForComputerSets(computer); // Check for full sets
     }
}

// Helper Commands for Computer Turn
void checkForComputerSets(Player& computer)
{
    for (size_t i = 0; i < RANKS.size(); ++i) {
        const std::string& r = RANKS[i];
        if (hasFullSet(computer, r)) {
            claimSet(computer, r);
            std::cout << "The computer claimed a full set of " << r << "s!" << std::endl;
        }
    }
}

void handleComputerDrawWhenEmptyHand(Deck& deck, Player& computer, bool& retFlag)
{
    retFlag = true;
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
    retFlag = false;
}

void handleComputerGoFishCommand(Deck& deck, Player& computer, std::string& rankToAsk, bool& computerPlaying, int& retFlag)
{
    retFlag = 1;
    if (areThereCardsLeft(deck)) {
        Card drawn = drawCard(deck);
        if (!drawn.rank.empty()) {
            computer.hand.push_back(drawn);
            std::cout << "The computer drew a card." << std::endl;

            // If the drawn card matches the initial rank, ask again
            if (drawn.rank == rankToAsk) {
                std::cout << "But the card is a " << rankToAsk << " and can ask again!" << std::endl;
                { retFlag = END_TURN; return; }; 
            }
        }
    }
    else {
        std::cout << "The deck is empty. The computer cannot draw a card." << std::endl;
    }
    computerPlaying = false;
    { retFlag = END_TURN; return; }; // End turn after drawing
}

void handlePlayerGiveCommand(std::string& providedRank, std::string& rankToAsk, Player& player, Player& computer, int& retFlag)
{
    retFlag = 1;
    if (providedRank == rankToAsk) {
        bool hasGivenAny = false;
        for (size_t i = 0; i < player.hand.size(); /* no increment here */) {
            if (player.hand[i].rank == rankToAsk) {
                computer.hand.push_back(player.hand[i]);
                player.hand.erase(player.hand.begin() + i);
                hasGivenAny = true;
            }
            else {
                ++i; // Increment only if no element is erased
            }
        }

        if (hasGivenAny) {
            std::cout << "You gave all your " << rankToAsk << "s to the computer." << std::endl;
            { retFlag = ASKAGAIN; return; }; // Computer can ask again
        }
        else {
            std::cout << "You do not have any " << rankToAsk << "s in your hand. Please check and try again: \n";
            { retFlag = INVALID_COMMAND; return; };
        }
    }
    else {
        std::cout << "Invalid card rank provided. Please check for " << rankToAsk << " and try again: \n";
        { retFlag = INVALID_COMMAND; return; };

    }
}

void checkComputerForFullSets(Player& computer)
{
    for (size_t i = 0; i < RANKS.size(); ++i) {
        const std::string& r = RANKS[i];
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

// Handles the second phase of the game where players take turns asking for sets
void handleSecondPhase(Player& player, Player& computer) {
    std::cout << "\nThe deck is empty, and both players have no cards left in their hands. Starting the second phase of the game!" << std::endl;

    while (true) {
        // Player's turn
        while (true) {
            std::cout << "Your turn! Enter a command (askSet <rank>): ";
            std::string command;
            std::cin >> command;

            if (command == "askSet") {
                std::string rank;
                std::cin >> rank;
                int retFlag;
                handlePlayerAskSetCommand(computer, rank, player, retFlag); 
                if (retFlag == END_TURN) break; // End player's turn

                // Check if the game is over
                if (isGameOver(player, computer)) {
                    determineWinner(player, computer);
                    return;
                }
            }
            else {
                std::cout << "Invalid command. Please use 'askSet <rank>'." << std::endl;
                continue;
            }
        }
        // Computer's turn
        std::cout << "\nComputer's turn!" << std::endl;
        while (true) {
            if (!isPlayerClaimedSetEmpty(player)) {
                size_t randomIndex = std::rand() % RANKS.size(); // Randomly select a rank to ask for
                std::string rankToAsk = RANKS[randomIndex];
                std::cout << "The computer asks for the set of " << rankToAsk << "s." << std::endl;

                int retFlag;
                handleComputerAskSet(player, rankToAsk, computer, retFlag); // Ask the player for a set
                if (retFlag == END_TURN) break; 

                if (isGameOver(player, computer)) { // Check if the game is over
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

// Helper Commands for Second Phase
void handleComputerAskSet(Player& player, std::string& rankToAsk, Player& computer, int& retFlag)
{
    retFlag = 1;
    auto it = player.claimedSets.end();
    for (size_t i = 0; i < player.claimedSets.size(); ++i) {
        if (player.claimedSets[i] == rankToAsk) {
            it = player.claimedSets.begin() + i;
            break;
        }
    }
    if (it != player.claimedSets.end()) {
        std::cout << "The computer took the set of " << rankToAsk << "s from you!" << std::endl;
        computer.claimedSets.push_back(rankToAsk);
        player.claimedSets.erase(it);
    }
    else {
        std::cout << "You does not have the set of " << rankToAsk << "s. The computer?s turn ends." << std::endl;
        { retFlag = END_TURN; return; }; // End computer's turn
    }
}

void handlePlayerAskSetCommand(Player& computer, std::string& rank, Player& player, int& retFlag)
{
    retFlag = 1;
    auto it = computer.claimedSets.end();
    for (size_t i = 0; i < computer.claimedSets.size(); ++i) {
        if (computer.claimedSets[i] == rank) {
            it = computer.claimedSets.begin() + i;
            break;
        }
    }
    if (it != computer.claimedSets.end()) {
        std::cout << "You took the set of " << rank << "s from the computer!" << std::endl;
        player.claimedSets.push_back(rank);
        computer.claimedSets.erase(it);
    }
    else {
        std::cout << "The computer does not have the set of " << rank << "s. Your turn ends." << std::endl;
        { retFlag = END_TURN; return; }; // End player's turn
    }
}

// Checks if the game is ready to move to the second phase
bool IsReadyForSecondPhase(const Deck& deck, const Player& player, const Player& computer)
{
    return (!areThereCardsLeft(deck)) && (player.hand.empty()) && (computer.hand.empty());
}

// Determines the winner of the game
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