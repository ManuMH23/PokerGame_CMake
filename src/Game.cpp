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

    table = PileOfCards<Card>(COMMUNITY_CARDS);
}

PokerGame::~PokerGame() {
    for (auto player : players) {
        PlayerFactory::deletePlayer(player);
    }
}

void PokerGame::playRound() {
    deck->shuffle();
    for (auto player : players) {
        player->clearHand();
    }

    for (int i = 0; i < 2; i++) {
        for (auto player : players) {
            player->getCard(deck->draw());
        }
    }

    for (auto player : players) {
        Utilities::waitOneSecond();
        if (!player->isFolded()) {
            player->play();
        }
    }
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


