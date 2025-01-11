#ifndef MOVE_H
#define MOVE_H
#include "classes.h"
#include "pgn.h" 

class MoveManager
{
private:
    int m_enPassantTurn;
    MoveType m_moveType=MoveType::MOVE; 
    std::string m_movePrefix;
    std::string m_moveSuffix;
    const PgnNotation* m_pgn; 

public:
    MoveManager(const PgnNotation* pgn) : m_pgn(pgn) {} 

    // move validators
    bool isValidMove(const Position &from, const Position &to, const Board &board, const PieceInterface &piece) const;
    bool isPawnMoveValid(const Position &from, const Position &to, const Board &board, const PieceInterface &piece) const;
    bool isRookMoveValid(const Position &from, const Position &to, const Board &board) const;
    bool isQueenMoveValid(const Position &from, const Position &to, const Board &board) const;
    bool isKingMoveValid(const Position &from, const Position &to) const;
    bool isKnightMoveValid(const Position &from, const Position &to) const;
    bool isBishopMoveValid(const Position &from, const Position &to, const Board &board) const;

    // capture
    bool canCapture(const Position &from, const Position &to, const Board &board, const PieceInterface &piece) const;
    bool isEnPassant(const PieceInterface &piece, const Position &from, const Position &to, const Board &board) const;

    bool isPathClear(const Position &from, const Position &to, const Board &board) const;
    void setEnPassantTurn(int turn) { m_enPassantTurn = turn; }
    void setMoveType(MoveType type) { m_moveType = type; }
    MoveType getMoveType() { return m_moveType; }
};

#endif