//
// Created by Vlad on 1/7/2025.
//

#ifndef POKERGAME_2_UTILITIES_H
#define POKERGAME_2_UTILITIES_H
#include <unordered_map>
#include "Card.h"
#include "Enums.h"
#include <list>
#include <chrono>

using namespace std;

class Utilities {
public:
    static const unordered_map<CardType, string>& getCardTypeString();

    static const unordered_map<CardNumber, string>& getCardNumberString();

    static const list<string>& getPokerPlayers();

    static string cardTypeToString(CardType type);

    static string cardNumberToString(CardNumber number);

    static list<string> getAIPlayerNames(const list<string>& playerList, int count);

    static void waitOneSecond();

    static bool isStraight(const std::vector<CardNumber>& numbers, int wildCardCount);
private:
    static const unordered_map<CardType, string> cardTypeString;
    static const unordered_map<CardNumber, string> cardNumberString;
    static const list<string> pokerPlayers;
};
#endif //POKERGAME_2_UTILITIES_H
