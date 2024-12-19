#pragma once
#include "classes.h"
#include <print>
#include "move.h"

class GameManager
{
private:
    Board m_board;
    PieceColor m_currentTurnColor = PieceColor::WHITE;
    PieceFactory &m_factory;

public:
    static int turn;
    void movePiece(const Position &from, const Position &to);

    GameManager(PieceFactory &factory) : m_factory(factory) {}
    void setupBoard();
    void displayBoard() const;
    PieceColor getCurrentTurn() const { return m_currentTurnColor; }
};

class Chess
{
private:
    GameManager m_gm;

public:
    Chess(PieceFactory &factory);
    void run();
};