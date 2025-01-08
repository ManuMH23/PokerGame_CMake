#include "../include/Game.h"
#include <iostream>

using namespace std;


PokerGame::PokerGame(int numberOfPlayers) {
    auto names = Utilities::getAIPlayerNames(Utilities::getPokerPlayers(), numberOfPlayers - 1);

    for (auto name : names) {
        players.push_back(PlayerFactory::createPlayer(COMPUTER, name));
    }

    players.push_back(PlayerFactory::createPlayer(HUMAN));

    deck = Deck::getInstance();

    table = CommunityCards::getInstance();
}

PokerGame::~PokerGame() {
    for (auto player : players) {
        PlayerFactory::deletePlayer(player);
    }
}

void PokerGame::displayCardsOnTable() {
    cout << "Cards on the table: " << table << endl;
}

bool PokerGame::isOnlyOnePlayerLeft() {
    int count = 0;
    for (auto player : players) {
        if (!player->isFolded()) {
            count++;
        }
    }
    return count == 1;
}

void PokerGame::playRound() {
    try{
    deck->shuffle();
    for (auto player : players) {
        player->clearHand();
    }
    for (auto player : players) {
        player->unfold();
    }


    unordered_map<Player*, int> bets;


    for (int i = 0; i < 2; i++) {
        for (auto player : players) {
            player->getCard(deck->draw());
        }
    }
    int TotalMoney = 0;
    int currentHighestBet = 0;

    for (auto player : players) {
        Utilities::waitOneSecond();
        if (!player->isFolded()) {
            int extraMoney = player->play(currentHighestBet);
            TotalMoney += extraMoney;
            bets[player] += extraMoney;
            if (extraMoney > currentHighestBet) {
                currentHighestBet = extraMoney;
            }
        }
    }

    table->clear();

    for (int i = 0; i < 3; i++) {
        table->addCard(deck->draw());
    }

    table->displayCards();

    for (auto player : players) {
        Utilities::waitOneSecond();
        if (!player->isFolded()) {
            int extraMoney = player->play(currentHighestBet);
            TotalMoney += extraMoney;
            bets[player] += extraMoney;
            if (extraMoney > currentHighestBet) {
                currentHighestBet = extraMoney;
            }
        }
    }



    table->addCard(deck->draw());

    table->displayCards();

    for (auto player : players) {
        Utilities::waitOneSecond();
        if (!player->isFolded()) {
            int extraMoney = player->play(currentHighestBet);
            TotalMoney += extraMoney;
            bets[player] += extraMoney;
            if (extraMoney > currentHighestBet) {
                currentHighestBet = extraMoney;
            }
        }
    }

    table->addCard(deck->draw());

    table->displayCards();

    for (auto player : players) {
        Utilities::waitOneSecond();
        if (!player->isFolded()) {
            int extraMoney = player->play(currentHighestBet);
            TotalMoney += extraMoney;
            bets[player] += extraMoney;
            if (extraMoney > currentHighestBet) {
                currentHighestBet = extraMoney;
            }
        }
    }

    for (auto player : players) {
        if (!player->isFolded()) {
            cout << player->getName() << " has ";
            cout << Utilities::getWinConditionString(player->getPowerLevel()) << endl;
        }
    }

    }
    catch (exception& e) {
        cout << "An exception occurred. Exception: " << e.what() << endl;
    }
}

void PokerGame::displayWinner() {
    Player* winner = nullptr;
    for (auto player : players) {
        if (!player->isFolded()) {
            if (winner == nullptr) {
                winner = player;
            } else {
                if (player->getPowerLevel() > winner->getPowerLevel()) {
                    winner = player;
                }
            }
        }
    }
    cout << "The winner is " << winner->getName() << endl;
}

void PokerGame::play() {
    while (true) {
        playRound();
        cout << "Do you want to play another round? (y/n): ";
        char answer;
        cin >> answer;
        if (answer != 'y') {
            break;
        }
    }
}


