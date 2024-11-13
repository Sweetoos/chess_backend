#include "classes.h"
#include "bishop.h"

Bishop::Bishop(PieceColor color, Board &board, char col, int row):Piece(color)
{
    putPiece(board.getSquare(col,row));
}

char Bishop::getPieceAcronym()
{
    return m_acronym;
}
int Bishop::getValue()
{
    return m_value;
}

void Bishop::putPiece(Board::Square *square)
{
    m_square=square;
    m_square->setPiece(this);
}

void Bishop::checkAvailableSquares(Board board)
{
}

bool Bishop::canJump()
{
    return false;
}
