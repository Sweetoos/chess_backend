#include <iostream>
#include "classes.h"
#include <print>

int main()
{
    try
    {
        PieceFactory factory;
        Chess game(factory);
        game.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << "error from main: " << e.what() << '\n';
    }
}