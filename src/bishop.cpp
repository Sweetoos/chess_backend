#include "classes.h"
#include "bishop.h"
#include <stdlib.h>

bool Bishop::isValidMove(const Position &from, const Position &to, const Board &board) const
{
    int rowDiff = std::abs(to.row - from.row);
    int colDiff = std::abs(to.col - from.col);

    // move isn't diagonal
    if (rowDiff != colDiff)
        return false;

    int colDir = (to.col > from.col) ? 1 : -1;
    int rowDir = (to.row > from.row) ? 1 : -1;

    for (int col = from.col + colDir, row = from.row + rowDir; col != to.col && row != to.row; col += colDir, row += rowDir)
    {
        if (board.getPieceAt({col, row}) != nullptr)
            return false;
    }
    PieceInterface *target = board.getPieceAt(to);
    return (target == nullptr || target->getColor() != m_color);
}