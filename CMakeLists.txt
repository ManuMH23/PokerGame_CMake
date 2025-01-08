cmake_minimum_required(VERSION 3.27)
project(PokerGame_2)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)



# Add executable and source files
add_executable(PokerGame_2
        main.cpp
        src/Card.cpp
        src/Game.cpp
        src/Player.cpp
        src/Utilities.cpp
)

# Ensure include directories are set correctly
target_include_directories(PokerGame_2 ${CMAKE_SOURCE_DIR}/include)