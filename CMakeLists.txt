cmake_minimum_required(VERSION 3.27)
project(PokerGame)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(MAIN_PROJECT_NAME "PokerGame")
set(MAIN_EXECUTABLE_NAME "${MAIN_PROJECT_NAME}")

# Include the directories for header files
include_directories(${CMAKE_SOURCE_DIR}/include)
file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*")
file(GLOB_RECURSE HEADERS RELATIVE ${CMAKE_SOURCE_DIR} "include/*")

# Collect all source files from the src directory and main.cpp
file(GLOB SOURCES "src/*.cpp" "main.cpp")

# Add the executable target with all source files
add_executable(PokerGame main.cpp src/Card.cpp src/Game.cpp src/Player.cpp src/Utilities.cpp)

# Specify include directories for the PokerGame target
target_include_directories(PokerGame PRIVATE include)

# Print debug information during CMake generation
message(STATUS "Source files: ${SOURCES}")