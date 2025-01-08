project(PokerGame_2)

set(CMAKE_CXX_STANDARD 23)
# Add include directories
include_directories(${CMAKE_SOURCE_DIR}/include)
add_executable(PokerGame_2
        main.cpp
        include/Card.h
        include/Enums.h
        include/Game.h
        src/Card.cpp
        src/Game.cpp
        src/Player.cpp
        src/Utilities.cpp)
target_include_directories(PokerGame_2 PRIVATE ${CMAKE_SOURCE_DIR}/include)