#include <iostream>
#include "classes.h"

int main()
{
    try
    {
        Board board;
        board.displayBoardPositions();
        std::cout << '\n';
        board.displayBoardConsole();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

}