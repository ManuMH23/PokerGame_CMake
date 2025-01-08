//
// Created by Vlad on 1/7/2025.
//

#ifndef POKERGAME_2_CMAKE_UTILITIES_H
#define POKERGAME_2_CMAKE_UTILITIES_H
#include <unordered_map>
#include "Card.h"
#include "Enums.h"
#include <list>
#include <chrono>

using namespace std;

class Utilities {
public:
    inline static const unordered_map<CardType, string>& getCardTypeString();

    inline static const unordered_map<CardNumber, string>& getCardNumberString();

    inline static const list<string>& getPokerPlayers();

    inline static string cardTypeToString(CardType type);

    inline static string cardNumberToString(CardNumber number);

    inline static list<string> getAIPlayerNames(const list<string>& playerList, int count);

    inline static void waitOneSecond();

    inline static bool isStraight(const std::vector<CardNumber>& numbers, int wildCardCount);
private:
    static const unordered_map<CardType, string> cardTypeString;
    static const unordered_map<CardNumber, string> cardNumberString;
    static const list<string> pokerPlayers;
};
#endif //POKERGAME_2_UTILITIES_H
