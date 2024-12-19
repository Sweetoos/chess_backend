#ifndef MOVE_H
#define MOVE_H

class MoveManager
{
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
    bool isPawnCaptureValid(const Position &from, const Position &to, const Board &board, const PieceInterface &piece) const;

    bool isPathClear(const Position &from, const Position &, const Board &board) const;
};

#endif