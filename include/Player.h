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
    Player() : folded(false), money(0), winCondition(WinCondition::HIGH_CARD), state(PlayerState::NORMAL) {}
    virtual ~Player() = default;
    virtual void play() = 0;
    virtual void MakeMove(PlayerMove move) = 0;
    virtual WinCondition getPowerLevel() = 0;
    //virtual void  checkPowerLevel() = 0;
    void clearHand() { hand.clear(); }
    void getCard(const Card card) { hand.addCard(card); }
    void fold() { folded = true; }
    void unfold() { folded = false; }
    bool isFolded() { return folded; }
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
    HumanPlayer();
    void play() override;
    //void checkPowerLevel() override;
    void MakeMove(PlayerMove move) override;
    WinCondition getPowerLevel() override;
};

class ComputerPlayer : public Player {
public:
    ComputerPlayer();
    ComputerPlayer(const string playerName);
    void play() override;
    //void checkPowerLevel() override;
    void MakeMove(PlayerMove move) override;
    WinCondition getPowerLevel() override;

};

class PlayerFactory {
public:
    static Player* createPlayer(const PlayerType& type, string name = "")
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

    static void deletePlayer(Player* player)
    {
        if (player)
        {
            delete player;
        }
    }
};
#endif //POKERGAME_2_PLAYER_H
