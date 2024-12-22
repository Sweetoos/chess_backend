// move.h
#ifndef MOVE_H
#define MOVE_H
#include "classes.h"

class MoveManager
{
private:
    int m_enPassantTurn;
    bool m_isEnPassant = false;
    MoveType m_moveType; 
    std::string m_movePrefix;
    std::string m_moveSuffix;


public:

    // move validators
    bool isValidMove(const Position &from, const Position &to, const Board &board, const PieceInterface &piece) const;
    bool isPawnMoveValid(const Position &from, const Position &to, const Board &board, const PieceInterface &piece) const;
    bool isRookMoveValid(const Position &from, const Position &to, const Board &board) const;
    bool isQueenMoveValid(const Position &from, const Position &to, const Board &board) const;
    bool isKingMoveValid(const Position &from, const Position &to, const Board &board) const;
    bool isKnightMoveValid(const Position &from, const Position &to) const;
    bool isBishopMoveValid(const Position &from, const Position &to, const Board &board) const;

    // capture
    bool canCapture(const Position &from, const Position &to, const Board &board, const PieceInterface &piece) const;
    bool isEnPassant(const PieceInterface &piece, const int turn) const;

    bool isPathClear(const Position &from, const Position &, const Board &board) const;
    void setEnPassantTurn(int turn) { m_enPassantTurn = turn; }
    void setMoveType(MoveType type) { m_moveType = type; }
    MoveType getMoveType() { return m_moveType; }
};

#endif