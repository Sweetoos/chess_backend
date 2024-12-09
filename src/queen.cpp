#include "classes.h"

bool Queen::isValidMove(const Position &from, const Position &to, const Board &board) const
{
    int rowDiff = std::abs(to.row - from.row);
    int colDiff = std::abs(to.col - from.col);

    if (rowDiff == colDiff || rowDiff == 0 || colDiff == 0)
    {
        // rook-like movement
        int colDir = (colDiff == 0) ? 0 : (to.col > from.col ? 1 : -1);
        int rowDir = (rowDiff == 0) ? 0 : (to.row > from.row ? 1 : -1);

        // bishop-like movement
        for (int col = from.col + colDir, row = from.row + rowDir;
             col != to.col || row != to.row; col += colDir, row += rowDir)
        {
            if (board.getPieceAt({col, row}) != nullptr)
            {
                return false;
            }
        }

        PieceInterface *target = board.getPieceAt(to);
        return (target == nullptr || target->getColor() != m_color);
    }
    return false;
}
