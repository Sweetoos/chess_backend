cmake_minimum_required(VERSION 3.25)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(run)

add_executable(run
    src/board.cpp
    src/main.cpp
    src/piece.cpp
    src/factory.cpp
    src/chess.cpp
    src/move.cpp
    src/pgn.cpp
)

target_include_directories(run PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -g")
