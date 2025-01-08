//
// Created by Vlad on 1/7/2025.
//

#ifndef POKERGAME_2_CMAKE_PLAYER_H
#define POKERGAME_2_CMAKE_PLAYER_H
#include "Card.h"
#include "Enums.h"
#include <vector>

using namespace std;

class Player {
public:
    inline Player() : folded(false), money(0), winCondition(WinCondition::HIGH_CARD), state(PlayerState::NORMAL) {}
    inline virtual ~Player() = default;
    inline virtual void play() = 0;
    inline virtual void MakeMove(PlayerMove move) = 0;
    inline virtual WinCondition getPowerLevel() = 0;
    //virtual void  checkPowerLevel() = 0;
    inline void clearHand() { hand.clear(); }
    inline void getCard(const Card card) { hand.addCard(card); }
    inline void fold() { folded = true; }
    inline void unfold() { folded = false; }
    inline bool isFolded() { return folded; }
protected:
    bool folded = false;
    string name;
    int money;
    PileOfCards<Card> hand;
    WinCondition winCondition;
    PlayerState state;
};

class HumanPlayer : public Player {
public:
    inline HumanPlayer();
    inline void play() override;
    //void checkPowerLevel() override;
    inline void MakeMove(PlayerMove move) override;
    inline WinCondition getPowerLevel() override;
};

class ComputerPlayer : public Player {
public:
    inline ComputerPlayer();
    inline ComputerPlayer(const string playerName);
    inline void play() override;
    //void checkPowerLevel() override;
    inline void MakeMove(PlayerMove move) override;
    inline WinCondition getPowerLevel() override;

};

class PlayerFactory {
public:
    inline static Player* createPlayer(const PlayerType& type, string name = "")
    {
        if (type == HUMAN)
        {
            return new HumanPlayer();
        }
        else if (type == COMPUTER)
        {
            return new ComputerPlayer(name);
        }
        return nullptr;
    }

    inline static void deletePlayer(Player* player)
    {
        if (player)
        {
            delete player;
        }
    }
};
#endif //POKERGAME_2_PLAYER_H
