//
// Created by Vlad on 1/7/2025.
//

#ifndef POKERGAME_2_CMAKE_ENUMS_H
#define POKERGAME_2_CMAKE_ENUMS_H
#include <list>
#include <string>

using namespace std;

enum TemplateType
{
    PLAYER_HAND = 2,
    COMMUNITY_CARDS = 5
};

enum PlayerType {
    HUMAN,
    COMPUTER
};

enum PlayerState {
    BIG_BLIND,
    SMALL_BLIND,
    DEALER,
    NORMAL
};

enum PlayerMove {
    FOLD,
    CHECK,
    CALL,
    RAISE
};;

enum WinCondition {
    HIGH_CARD,
    ONE_PAIR,
    TWO_PAIRS,
    THREE_OF_A_KIND,
    STRAIGHT,
    FLUSH,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    STRAIGHT_FLUSH,
    ROYAL_FLUSH
};

enum CardType {
    HEARTS,
    DIAMONDS,
    CLUBS,
    SPADES
};

enum CardNumber {
    ACE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
    JOKER
};


const unordered_map<CardType, string> cardTypeString = {
        { HEARTS, "Hearts" },
        { DIAMONDS, "Diamonds" },
        { CLUBS, "Clubs" },
        { SPADES, "Spades" }
};

const unordered_map<CardNumber, string> cardNumberString = {
        { ACE, "Ace" },
        { TWO, "Two" },
        { THREE, "Three" },
        { FOUR, "Four" },
        { FIVE, "Five" },
        { SIX, "Six" },
        { SEVEN, "Seven" },
        { EIGHT, "Eight" },
        { NINE, "Nine" },
        { TEN, "Ten" },
        { JACK, "Jack" },
        { QUEEN, "Queen" },
        { KING, "King" }
};
#endif //POKERGAME_2_ENUMS_H
