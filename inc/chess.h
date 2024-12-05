#pragma once
#include "classes.h"
#include <print>

class Chess
{
private:
    Board m_board;

public:
    Chess() : m_board()
    {
        m_board.initPieces();
    }
    void run()
    {
        m_board.displayBoardPositions();
        std::println("");
        m_board.displayBoardConsole();
    }
};