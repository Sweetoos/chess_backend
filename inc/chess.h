// chess.h
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
    MoveType m_moveType = MoveType::MOVE;
    PgnNotation m_pgn;  // Add this line

public:
    static int turn;
    bool movePiece(const Position &from, const Position &to);  // Changed return type to bool

    GameManager(PieceFactory &factory) : m_factory(factory) {}
    void setupBoard();
    void displayBoard() const;
    PieceColor getCurrentTurnColor() const { return m_currentTurnColor; }
    bool handleCastling(const Position &from, const Position &to);
    PieceType handlePromotion(const Position &pos); 
    bool isSquareUnderAttack(const Position &pos, PieceColor defendingColor) const;
    bool isKingInCheck(PieceColor color) const;
    bool isCheckmate(PieceColor color);
    bool isFirstMove(const PieceInterface *piece);
    PgnNotation& getPgn() { return m_pgn; }  
};

class Chess
{
private:
    GameManager m_gm;

public:
    Chess(PieceFactory &factory);
    void run();
};