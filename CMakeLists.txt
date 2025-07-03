cmake_minimum_required(VERSION 3.29)
project(Memory_Game_20241217T180055Z_001)

set(CMAKE_CXX_STANDARD 14)

include_directories("Memory Game")

add_executable(Memory_Game_20241217T180055Z_001
    "Memory Game/BonusCard.h"
    "Memory Game/Card.h"
    "Memory Game/Deck.h"
    "Memory Game/Game.h"
    "Memory Game/Main.cpp"
    "Memory Game/PenaltyCard.h"
    "Memory Game/Player.h"
    "Memory Game/StandardCard.h")
