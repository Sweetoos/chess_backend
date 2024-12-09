#include "classes.h"
#include "pawn.h"
#include <stdlib.h>

bool Pawn::isValidMove(const Position &from, const Position &to, const Board &board) const
{
    int direction = (m_color == PieceColor::WHITE) ? 1 : -1;
    int rowDiff = to.row - from.row;
    int colDiff = std::abs(to.col - from.col);

    // normal move
    if (colDiff == 0)
    {
        // single move
        if (rowDiff == direction && board.getPieceAt(to) == nullptr)
        {
            return true;
        }

        // double move
        if (rowDiff == 2 * direction && board.getPieceAt(to) == nullptr &&
            board.getPieceAt({from.col, from.row + direction}) == nullptr &&
            ((m_color == PieceColor::WHITE && from.row == 2) || (m_color == PieceColor::BLACK && from.row == 7)))
        {
            return true;
        }
    }

    // capturing
    if (colDiff == 1 && rowDiff == direction)
    {
        PieceInterface *target = board.getPieceAt(to);
        if (target != nullptr && target->getColor() != m_color)
        {
            return true;
        }
    }

    return false;
}
