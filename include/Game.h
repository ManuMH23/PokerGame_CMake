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
class Game {
public:
    Game(int numberOfPlayers = 5);
    ~Game();
    void playRound();
    void play();
private:
    list<Player*> players;
    PileOfCards<Card> table;
    Deck* deck = nullptr;
};

#endif //POKERGAME_2_GAME_H
