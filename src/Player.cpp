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

void HumanPlayer::DisplayCards()
{
    cout << "Your cards: " << hand << endl;
}

int HumanPlayer::play(int currentHighestBet)
{
    CommunityCards* table = nullptr;
    table = CommunityCards::getInstance();

    table->displayCards();

    DisplayCards();

    int returnValue = 0;

    cout << "Enter your move: ";
    cout << "1. Fold" << endl;
    cout << "2. Check" << endl;
    cout << "3. Call" << endl;
    cout << "4. Raise" << endl;
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 4) {
        cout << "Invalid choice. Please try again." << endl;
        cin >> choice;
    }
    PlayerMove move;
    switch (choice) {
        case 1:
            move = FOLD;
            break;
        case 2:
            move = CHECK;
            break;
        case 3:
            move = CALL;
            break;
        case 4:
            move = RAISE;
            break;

    }
    MakeMove(move, currentHighestBet);
    return returnValue;
}

int HumanPlayer::MakeMove(PlayerMove move, int currentHighestBet)
{
    int returnValue = 0;
    switch (move) {
        case FOLD:
            fold();
            break;
        case CHECK:
            break;
        case CALL:
            returnValue = call(currentHighestBet);
            break;
        case RAISE:
            returnValue = bet();
            break;
    }
    return returnValue;
}

int HumanPlayer::bet() {
    int betAmount;
    cout << "Enter the amount you want to bet: ";
    cin >> betAmount;
    while (betAmount < 0 || betAmount > money) {
        cout << "Invalid bet amount. Please try again." << endl;
        cin >> betAmount;
    }
    money -= betAmount;
    currentRoundBet += betAmount;
    cout << name << " bets " << betAmount << ". Remaining money: " << money << endl;
    return betAmount;
}

int HumanPlayer::call(int currentHighestBet) {
    int callAmount = currentHighestBet - currentRoundBet;
    money -= callAmount;
    currentRoundBet += callAmount;
    cout << name << " calls " << callAmount << ". Remaining money: " << money << endl;
    return callAmount;
}

WinCondition HumanPlayer::getPowerLevel()
{
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

int ComputerPlayer::play(int currentHighestBet)
{
    int returnValue = 0;

    if (hand.isEmpty()) {
        std::cerr << "Computer player " << name << " does not have the correct number of cards." << std::endl;
        return 0;
    }

    std::cout << "Computer player " << name << " is making a decision." << std::endl;

    int handStrength = getPowerLevel();

    // Make a decision based on hand strength
    if (handStrength > 3) {
        std::cout << "Computer player " << name << " decides to raise." << std::endl;
        returnValue = MakeMove(RAISE, currentHighestBet);
    } else if (handStrength > 1) {
        std::cout << "Computer player " << name << " decides to call." << std::endl;
        returnValue = MakeMove(CALL, currentHighestBet);
    } else {

        if (currentHighestBet <= currentRoundBet)
        {
            returnValue = call(currentHighestBet);
        }
        else
        {
            std::cout << "Computer player " << name << " decides to fold." << std::endl;
            returnValue = MakeMove(FOLD, currentHighestBet);
        }
    }
return returnValue;
}


int ComputerPlayer::MakeMove(PlayerMove move, int currentHighestBet)
{
    int returnValue = 0;

    switch (move) {
        case FOLD:
            fold();
            break;
        case CHECK:
            break;
        case CALL:
            returnValue = call(0);
            break;
        case RAISE:
            returnValue = bet();
            break;
    }
    return returnValue;
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

int ComputerPlayer::bet() {
    int betAmount = money / 10; // Simple logic: bet 10% of remaining money
    money -= betAmount;
    currentRoundBet += betAmount;
    std::cout << name << " bets " << betAmount << ". Remaining money: " << money << std::endl;
    return betAmount;
}

int ComputerPlayer::call(int currentHighestBet) {
    int callAmount = currentHighestBet - currentRoundBet;
    money -= callAmount;
    currentRoundBet += callAmount;
    std::cout << name << " calls " << callAmount << ". Remaining money: " << money << std::endl;
    return callAmount;
}



void Player::getCard(const Card& card) {
    if (hand.size() >= 2) {
        throw HandFullException();
    }
    hand.addCard(card);
}
