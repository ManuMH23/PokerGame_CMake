cmake_minimum_required(VERSION 3.27)
project(PokerGame_2)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include the directories for header files
include_directories(${CMAKE_SOURCE_DIR}/include)

# Collect all source files from the src directory and main.cpp
file(GLOB SOURCES "src/*.cpp" "main.cpp")

file(GLOB SOURCES2 "include/*.h" "main.cpp")

# Add the executable target with all source files
add_executable(PokerGame_2 ${SOURCES} ${SOURCES2})

# Ensure the include directory is part of the build process
target_include_directories(PokerGame_2 PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Optional: Link additional libraries if needed
# target_link_libraries(PokerGame_2 PRIVATE <library_name>)

# Print debug information during CMake generation
message(STATUS "Source files: ${SOURCES}")
