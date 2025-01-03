// move.cpp
#include "classes.h"
#include "move.h"
#include <stdlib.h>
#include <iostream>

bool MoveManager::isValidMove(const Position &from, const Position &to, const Board &board, const PieceInterface &piece) const
{
    std::cout << "Checking move validity from " << from.col << from.row 
              << " to " << to.col << to.row << "\n";

    PieceInterface *targetPiece = board.getPieceAt(to);
    if (targetPiece != nullptr && targetPiece->getColor() == piece.getColor()) {
        std::cout << "Invalid: Target square occupied by same color piece\n";
        return false;
    }

    PieceType type = piece.getType();
    bool result = false;

    switch (type) {
        case PieceType::PAWN:
        {
            bool isValid = isPawnMoveValid(from, to, board, piece);
            // promotion
            result = isValid;
            break;
        }
        case PieceType::QUEEN:
            result = isQueenMoveValid(from, to, board);
            break;
        case PieceType::KING:
            result = isKingMoveValid(from, to);
            break;
        case PieceType::ROOK:
            result = isRookMoveValid(from, to, board);
            break;
        case PieceType::KNIGHT:
            result = isKnightMoveValid(from, to);
            std::cout << "Knight move is " << (result ? "valid" : "invalid") << "\n";
            break;
        case PieceType::BISHOP:
            result = isBishopMoveValid(from, to, board);
            break;
    }

    return result;
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

    // single move
    if (from.col == to.col && to.row == from.row + direction)
        return !board.getPieceAt(to);

    // double move
    int startingRank = (piece.getColor() == PieceColor::WHITE) ? 2 : 7;
    if (from.row == startingRank && to.col == from.col && to.row == from.row + 2 * direction)
    {
        Position intermediatePos(from.col, from.row + direction);
        return board.getPieceAt(to) == nullptr && board.getPieceAt(intermediatePos) == nullptr;
    }

    // diagonal capture
    if (to.row == from.row + direction && std::abs(to.col - from.col) == 1)
    {
        PieceInterface *targetPiece = board.getPieceAt(to);
        return targetPiece != nullptr && targetPiece->getColor() != piece.getColor();
    }

    // en passant capture
    if (
        (piece.getType() == PieceType::PAWN) &&
        (((piece.getColor() == PieceColor::WHITE) && (piece.getPosition().row == 5)) ||
         ((piece.getColor() == PieceColor::BLACK) && (piece.getPosition().row == 4))) &&
        (to.row == from.row + direction && std::abs(to.col - from.col) == 1))
    {
    }
    return false;
}

bool MoveManager::isQueenMoveValid(const Position &from, const Position &to, const Board &board) const
{
    // rook-like move
    bool isRookMove = (from.col == to.col || from.row == to.row);

    // bishop-like move
    bool isBishopMove = (std::abs(from.col - to.col) == std::abs(from.row - to.row));

    if (!isRookMove && !isBishopMove)
        return false;

    return isPathClear(from, to, board);
}

bool MoveManager::isKingMoveValid(const Position &from, const Position &to) const
{
    int dcol = std::abs(from.col - to.col);
    int drow = std::abs(from.row - to.row);

    if (dcol <= 1 && drow <= 1)
        return true;
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

bool MoveManager::canCapture(const Position &from, const Position &to, const Board &board, const PieceInterface &piece) const
{
    const auto targetPiece = board.getPieceAt(to);

    if (targetPiece == nullptr || targetPiece->getColor() == piece.getColor())
        return false;

    switch (piece.getType())
    {
    case PieceType::PAWN:
        return isPawnMoveValid(from, to, board, piece);
    case PieceType::QUEEN:
        return isQueenMoveValid(from, to, board) && isPathClear(from, to, board);
    case PieceType::KING:
        return isKingMoveValid(from, to);
    case PieceType::ROOK:
        return isRookMoveValid(from, to, board) && isPathClear(from, to, board);
    case PieceType::KNIGHT:
        return isKnightMoveValid(from, to);
    case PieceType::BISHOP:
        return isBishopMoveValid(from, to, board) && isPathClear(from, to, board);
    }
    return false;
}

bool MoveManager::isEnPassant(const PieceInterface &piece, const Position &from, const Position &to, const Board &board) const
{
    if (piece.getType() != PieceType::PAWN)
        return false;

    int enPassantRow = (piece.getColor() == PieceColor::WHITE) ? 5 : 4;
    if (to.row != enPassantRow)
        return false;

    Position enemyPawnPos(to.col, from.row);
    PieceInterface *enemyPawn = board.getPieceAt(enemyPawnPos);

    return enemyPawn && enemyPawn->getType() == PieceType::PAWN && enemyPawn->getColor() != piece.getColor();
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