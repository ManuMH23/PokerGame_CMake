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

target_include_directories(${MAIN_EXECUTABLE_NAME} SYSTEM PRIVATE generated/include)

include_directories(include)
include_directories(src)

# Collect all source files from the src directory and main.cpp
file(GLOB SOURCES "src/*.cpp" "main.cpp")

file(GLOB SOURCES2 "include/*.h" "main.cpp")

# Add the executable target with all source files
add_executable(PokerGame main.cpp src/Card.cpp src/Game.cpp src/Player.cpp src/Utilities.cpp)
target_include_directories(PokerGame PRIVATE include)

# Ensure the include directory is part of the build process

# Optional: Link additional libraries if needed
# target_link_libraries(PokerGame_2 PRIVATE <library_name>)

# Print debug information during CMake generation
message(STATUS "Source files: ${SOURCES}")
