#include "classes.h"

bool King::isValidMove(const Position &from, const Position &to, const Board &board) const
{
    int rowDiff = std::abs(to.row - from.row);
    int colDiff = std::abs(to.col - from.col);

    if (rowDiff <= 1 && colDiff <= 1)
    { 
        PieceInterface *target = board.getPieceAt(to);
        return (target == nullptr || target->getColor() != m_color);
    }
    return false;
}