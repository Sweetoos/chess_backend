# Chess game backend

___

This is a Chess project for university. I had to implement there some kind of inheritance, polymorphism, virtual classes and nested classes.
I implemented additionally function to print all the moves to the text file and to read from it (there are still some problems because of some special moves like en passant, castling and promotion). If you will play without reading and saving from the beginning to the end, all mechanics work (ok, I've recently came back to chess and didn't know that if the game isn't finished for I guess 25 moves since the last pawn on the board have been beaten the result is a draw and didn't know that you can't checkmate with 2 knights and king)

# What I used

- CMake
- C++23
- Ninja-build

# What did I learn from this project?

- SOLID
- Abstract factory pattern
- How to write C++ projects with OOP better

# What is missing

- Fix the bugs mentioned at the beginning
- GUI (playing on CLI is not comfortable)
- Some kind of AI (for example minmax algorithm would work fine here; I didn't want to include Stockfish here)
