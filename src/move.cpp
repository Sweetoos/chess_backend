//move.cpp
#include "classes.h"
#include "move.h"
#include <stdlib.h>

bool MoveManager::isValidMove(const Position &from, const Position &to, const Board &board, const PieceInterface &piece) const
{
    PieceType type = piece.getType();
    switch (type)
    {
    case PieceType::PAWN:
        return isPawnMoveValid(from, to, board, piece);
    case PieceType::QUEEN:
        return isQueenMoveValid(from, to, board);
    case PieceType::KING:
        return isKingMoveValid(from, to, board);
    case PieceType::ROOK:
        return isRookMoveValid(from, to, board);
    case PieceType::KNIGHT:
        return isKnightMoveValid(from, to);
    case PieceType::BISHOP:
        return isBishopMoveValid(from, to, board);
    }
    return false;
}

bool MoveManager::isRookMoveValid(const Position &from, const Position &to, const Board &board) const
{
    if (from.col != to.col && from.row != to.row)
        return false;
    return isPathClear(from, to, board);
}

bool MoveManager::isPawnMoveValid(const Position &from, const Position &to, const Board &board, const PieceInterface &piece) const
{
    int direction = piece.getColor() == PieceColor::WHITE ? 1 : -1;
    int startRow = piece.getColor() == PieceColor::WHITE ? 1 : 6;

    // single move
    if (from.col == to.col && to.row == from.row + direction)
        return !board.getPieceAt(to);

    // double move
    if (from.col == to.col && from.row == startRow && to.col == from.col + 2 * direction)
        return !board.getPieceAt(to) && isPathClear(from, to, board);

    // diagonal capture
    // if (std::abs(to.col - from.col) == 1 && to.row == from.row + direction)
    // {
    //     // TODO
    // }
    return false;
}

bool MoveManager::isQueenMoveValid(const Position &from, const Position &to, const Board &board) const
{
    // rook-like move
    if (from.col != to.col && from.row != to.row)
        return false;

    // bishop-like move
    if (std::abs(from.col - to.col) != std::abs(from.row - to.row))
        return false;
    return isPathClear(from, to, board);
}

bool MoveManager::isKingMoveValid(const Position &from, const Position &to, const Board &board) const
{
    int dcol = std::abs(from.col - to.col);
    int drow = std::abs(from.row - to.row);

    if (dcol <= 1 && drow <= 1)
        return true;
    // TODO check
    // TODO castle
    return false;
}

bool MoveManager::isKnightMoveValid(const Position &from, const Position &to) const
{
    int dcol = std::abs(from.col - to.col);
    int drow = std::abs(from.row - to.row);
    return (dcol == 2 && drow == 1) || (dcol == 1 && drow == 2);
}

bool MoveManager::isBishopMoveValid(const Position &from, const Position &to, const Board &board) const
{
    if (std::abs(from.col - to.col) != std::abs(from.row - to.row))
        return false;
    return isPathClear(from, to, board);
}

bool MoveManager::isPawnCaptureValid(const Position &from, const Position &to, const Board &board, const PieceInterface &piece) const
{
    int direction = (piece.getColor() == PieceColor::WHITE) ? 1 : -1;

    if (((to.row == from.row + 1) || (to.row == from.row - 1)) && to.col == from.col + direction)
    {
        // normal capture

        // en passant
    }
    // delete
    return true;
}

bool MoveManager::canCapture(const Position &from, const Position &to, const Board &board, const PieceInterface &piece) const
{
    const auto targetPiece = board.getPieceAt(to);

    if (targetPiece == nullptr || targetPiece->getColor() == piece.getColor())
        return false;

    switch (piece.getType())
    {
    case PieceType::PAWN:
        return isPawnCaptureValid(from, to, board, piece);
    case PieceType::QUEEN:
        return isQueenMoveValid(from, to, board) && isPathClear(from, to, board);
    case PieceType::KING:
        return isKingMoveValid(from, to, board) /* TODO check mechanic */;
    case PieceType::ROOK:
        return isRookMoveValid(from, to, board) && isPathClear(from, to, board);
    case PieceType::KNIGHT:
        return isKnightMoveValid(from, to);
    case PieceType::BISHOP:
        return isBishopMoveValid(from, to, board) && isPathClear(from, to, board);
    }
    return false;
}

/// @brief checks if piece can move to given square
/// @param from current position
/// @param to destination
/// @param board
/// @return
bool MoveManager::isPathClear(const Position &from, const Position &to, const Board &board) const
{
    int colPath = to.col - from.col;
    int rowPath = to.row - from.row;

    // direction
    int stepCol = (colPath == 0) ? 0 : (colPath > 0 ? 1 : -1);
    int stepRow = (rowPath == 0) ? 0 : (rowPath > 0 ? 1 : -1);

    int currentCol = from.col + stepCol;
    int currentRow = from.row + stepRow;

    while (currentCol != to.col || currentRow != to.row)
    {
        if (board.getPieceAt(Position(currentCol, currentRow)))
            return false;
        currentCol += stepCol;
        currentRow += stepRow;
    }
    return true;
}
