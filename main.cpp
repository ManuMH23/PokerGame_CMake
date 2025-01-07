#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "include/Game.h"
#include "src/Game.cpp"
#include "src/Player.cpp"
#include "src/Utilities.cpp"
#include "src/Card.cpp"



int main()
{
    Game game(5);
    game.play();
}

