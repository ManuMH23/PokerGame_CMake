#include "../include/Player.h"
#include <iostream>
#include <map>

HumanPlayer::HumanPlayer()
{
    string playerName;
    cout << "Enter your name: ";
    cin >> playerName;
    this->name = playerName;
    this->money = 10000;
    this->hand = PileOfCards<Card>(PLAYER_HAND);
}

void HumanPlayer::play()
{

}

void HumanPlayer::MakeMove(PlayerMove move)
{

}

WinCondition HumanPlayer::getPowerLevel()
{
    return HIGH_CARD;
}

ComputerPlayer::ComputerPlayer()
{
    string playerName;
    cout << "Enter the name of the AI player: ";
    cin >> playerName;
    this->name = playerName;
    this->money = 10000;
}

ComputerPlayer::ComputerPlayer(const string playerName)
{
    this->name = playerName;
    this->money = 10000;

}

void ComputerPlayer::play()
{
    if (hand.isEmpty()) {
        std::cerr << "Computer player " << name << " does not have the correct number of cards." << std::endl;
        return;
    }

    std::cout << "Computer player " << name << " is making a decision." << std::endl;

    int handStrength = getPowerLevel();

    // Make a decision based on hand strength
    if (handStrength > 7) {
        std::cout << "Computer player " << name << " decides to raise." << std::endl;
        MakeMove(RAISE);
    } else if (handStrength > 4) {
        std::cout << "Computer player " << name << " decides to call." << std::endl;
        MakeMove(CALL);
    } else {
        std::cout << "Computer player " << name << " decides to fold." << std::endl;
        MakeMove(FOLD);
    }
}


void ComputerPlayer::MakeMove(PlayerMove move)
{

}


WinCondition ComputerPlayer::getPowerLevel() {
        std::map<Card, int> pairs;
        std::map<CardType, int> suitCount;
        int wildCardCount = 0;
        CommunityCards* table = CommunityCards::getInstance();
        auto tableCards = table->getCards();

        for (int i = 0; i < tableCards.size(); i++) {
            if (tableCards.at(i).isWild()) {
                wildCardCount++;
            } else {
                pairs[tableCards.at(i)]++;
                suitCount[tableCards.at(i).getType()]++;
            }
        }

        for (int i = 0; i < hand.size(); i++) {
            if (hand.at(i).isWild()) {
                wildCardCount++;
            } else {
                pairs[hand.at(i)]++;
                suitCount[hand.at(i).getType()]++;
            }
        }

        for (const auto& suit : suitCount) {
            if (suit.second + wildCardCount >= 5) {
                // Check for straight flush and royal flush
                std::vector<CardNumber> numbers;
                for (const auto& pair : pairs) {
                    if (pair.first.getType() == suit.first) {
                        numbers.push_back(pair.first.getNumber());
                    }
                }
                std::sort(numbers.begin(), numbers.end());

                if (Utilities::isStraight(numbers, wildCardCount)) {
                    if (numbers.back() == KING) {
                        return ROYAL_FLUSH;
                    }
                    return STRAIGHT_FLUSH;
                }
                return FLUSH;
            }
        }

        std::vector<CardNumber> allNumbers;
        for (const auto& pair : pairs) {
            allNumbers.push_back(pair.first.getNumber());
        }
        std::sort(allNumbers.begin(), allNumbers.end());
        if (Utilities::isStraight(allNumbers, wildCardCount)) {
            return STRAIGHT;
        }

        int pairsCount = 0, threeOfAKind = 0, fourOfAKind = 0;
        for (const auto& pair : pairs) {
            if (pair.second == 2) {
                pairsCount++;
            } else if (pair.second == 3) {
                threeOfAKind++;
            } else if (pair.second == 4) {
                fourOfAKind++;
            }
        }

        if (wildCardCount > 0) {
            if (fourOfAKind > 0) {
                fourOfAKind += wildCardCount;
            } else if (threeOfAKind > 0) {
                threeOfAKind += wildCardCount;
                if (threeOfAKind > 3) {
                    fourOfAKind++;
                    threeOfAKind -= 3;
                }
            } else if (pairsCount > 0) {
                pairsCount += wildCardCount;
                if (pairsCount > 2) {
                    threeOfAKind++;
                    pairsCount -= 2;
                }
            } else {
                pairsCount += wildCardCount;
            }
        }

        if (fourOfAKind > 0) {
            return FOUR_OF_A_KIND;
        } else if (threeOfAKind > 0 && pairsCount > 0) {
            return FULL_HOUSE;
        } else if (threeOfAKind > 0) {
            return THREE_OF_A_KIND;
        } else if (pairsCount > 1) {
            return TWO_PAIRS;
        } else if (pairsCount > 0) {
            return ONE_PAIR;
        } else {
            return HIGH_CARD;
        }
    }


