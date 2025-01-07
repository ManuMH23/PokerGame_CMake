cmake_minimum_required(VERSION 3.27)
project(PokerGame_2)

set(CMAKE_CXX_STANDARD 23)

add_executable(PokerGame_2 main.cpp
        include/Card.h
        include/Enums.h
        include/Game.h
        include/Player.h
        include/Utilities.h
        src/Card.cpp
        src/Game.cpp
        src/Player.cpp
        src/Utilities.cpp)

target_include_directories(PokerGame_2 PRIVATE include)
