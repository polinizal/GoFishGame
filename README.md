# GoFishGame

## **Overview**

This project implements a console-based version of the classic card game "Go Fish." Players compete to collect sets of four cards of the same rank by asking opponents for specific cards. The game ends when all sets have been collected, and the player, owner of all sets, wins!

## **Features**
- Two-player gameplay: The game allows two players to compete.
- Intelligent card handling: The game manages a shuffled deck and player hands.
- Interactive gameplay: Players can ask each other for cards and draw from the deck.
- Score tracking: The game keeps track of collected sets and determines the winner.
## **Code Structure**
- **card.h** and **card.cpp**: Define the Card class for individual card properties and operations.
- **deck.h** and **deck.cpp**: Manage the Deck class for shuffling and dealing cards.
- **player.h** and **player.cpp**: Handle the Player class, including player actions and card management.
- **game.h** and **game.cpp**: Control the overall game logic, including turns, score tracking, and game state.
## **Technologies**
The project is fully written in C++. The following functionalities, helper classes, and libraries were used:
- Structures
- **std::string**
- **std::vector**
- *rand()*, *srand()*, and *time()* found in the **cstdlib** and **ctime** libraries.
## **How to Run**
1. Clone the repository and navigate to the project directory.
2. Open the .vcxproj file with Visual Studio to build and run the project.
3. Follow the on-screen instructions to play the game.
## **Commands**
_Needed commands for the game_
```
1. ask <rank>  // ask 7

2. claim <rank>  // claim 6

3. draw  // to draw a card from the deck

4. GoFish!  // type "GoFish!" if you don't have the requested card 

5. show  // shows the status of your current hand
```
## **Future Improvements**
- *Add support for more than two players.*
- *Implement an AI player for single-player mode.*
- *Enhance the user interface for better gameplay experience.*
- *Add more functionality and logic for computer turns and responses - make it smarter*

***Enjoy playing Go Fish!***


![image](https://github.com/user-attachments/assets/33dcf84e-374b-4a83-9a2d-6fcb1c5d9470)




