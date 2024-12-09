#pragma once
#include "classes.h"
#include <print>

class GameManager
{
private:
    Board m_board;
    PieceFactory &m_factory;

public:
    static int turn;
    GameManager(PieceFactory &factory) : m_factory(factory) {}
    void setupBoard();
    //void movePiece(const Position &from, const Position &to);
    void displayBoard() const;
};

class Chess
{
private:
    GameManager m_gm;

public:
    Chess(PieceFactory &factory);
    void run();
};