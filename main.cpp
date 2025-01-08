#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "src/Game.cpp"
#include "src/Player.cpp"
#include "src/Utilities.cpp"
#include "src/Card.cpp"


int main()
{
    PokerGame game(5);
    game.playRound();
}

