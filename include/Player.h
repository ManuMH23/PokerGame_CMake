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
    inline virtual int play(int currentHighestBet) = 0;
    inline virtual int bet() = 0;
    inline virtual int call(int currentHighestBet) = 0;
    inline virtual int MakeMove(PlayerMove move, int currentHighestBet) = 0;
    inline virtual WinCondition getPowerLevel() = 0;
    inline string getName() { return name; }
    //virtual void  checkPowerLevel() = 0;
    inline void clearHand() { hand.clear(); }
    inline void getCard(const Card& card);
    inline void fold() { folded = true; }
    inline void unfold() { folded = false; }
    inline bool isFolded() { return folded; }
protected:
    bool folded = false;
    string name;
    int money;
    int currentRoundBet = 0;
    PileOfCards<Card> hand;
    WinCondition winCondition;
    PlayerState state;
};

class HumanPlayer : public Player {
public:
    inline HumanPlayer();
    inline int play(int currentHighestBet) override;
    inline int bet() override;
    inline int call(int currentHighestBet) override;
    inline int MakeMove(PlayerMove move, int currentHighestBet) override;
    inline WinCondition getPowerLevel() override;
    inline void DisplayCards();
};

class ComputerPlayer : public Player {
public:
    inline ComputerPlayer();
    inline ComputerPlayer(const string playerName);
    inline int bet() override;
    inline int call(int currentHighestBet) override;
    inline int play(int currentHighestBet) override;
    inline int MakeMove(PlayerMove move, int currentHighestBet) override;
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

class HandFullException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Hand is full.";
    }
};

#endif //POKERGAME_2_PLAYER_H
