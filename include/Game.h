//
// Created by Vlad on 1/7/2025.
//

#ifndef POKERGAME_2_CMAKE_GAME_H
#define POKERGAME_2_CMAKE_GAME_H
#include <list>
#include <string>
#include "Player.h"
#include "Utilities.h"
#include "Enums.h"
#include "Card.h"

using namespace std;
class PokerGame {
public:
    inline PokerGame(int numberOfPlayers = 5);
    inline ~PokerGame();
    inline void playRound();
    inline void play();
    inline void displayCardsOnTable();
    inline bool isOnlyOnePlayerLeft();
    inline void displayWinner();
private:
    list<Player*> players;
    CommunityCards* table = nullptr;
    Deck* deck = nullptr;
};

#endif //POKERGAME_2_GAME_H
