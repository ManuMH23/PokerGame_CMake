#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "include/Game.h"
#include "src/Game.cpp"
#include "include/Utilities.h"
#include "src/Utilities.cpp"
#include "include/Player.h"
#include "src/Player.cpp"
#include "include/Enums.h"
#include "include/Card.h"
#include "src/Card.cpp"


int main()
{
    Game game(5);
    game.play();
}

