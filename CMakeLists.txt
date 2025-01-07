cmake_minimum_required(VERSION 3.27)
project(PokerGame_2)

set(CMAKE_CXX_STANDARD 23)

# Add include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add executable and source files
add_executable(PokerGame_2
        main.cpp
        include/Card.h
        include/Enums.h
        include/Game.h
        include/Player.h
        include/Utilities.h
        src/Card.cpp
        src/Game.cpp
        src/Player.cpp
        src/Utilities.cpp
)

# Link libraries if any (e.g., standard libraries)
# target_link_libraries(PokerGame_2 PRIVATE <library_name>)

# Ensure include directories are set correctly
target_include_directories(PokerGame_2 PRIVATE ${CMAKE_SOURCE_DIR}/include)