#include "classes.h"
#include "rook.h"

bool Rook::isValidMove(const Position &from, const Position &to, const Board &board) const
{
    if (from.col != to.col && from.row != to.row)
        return false;

    int colDir = (from.col == to.col) ? 0 : (to.col > from.col ? 1 : -1);
    int rowDir = (from.row == to.row) ? 0 : (to.row > from.row ? 1 : -1);

    char col=from.col+colDir;
    int row=from.col+rowDir;

    while(col!=to.col||row!=to.row)
    {
        if(board.getPieceAt(Position(col,row))!=nullptr)
            return false;
        
        col+=colDir;
        row+=rowDir;
    }

    PieceInterface *targetPiece=board.getPieceAt(to);
    return targetPiece==nullptr||targetPiece->getColor()!=m_color;
}