#include "king.h"

King::King(PieceColor color, Board &board, char col, int row):Piece(color)
{
    putPiece(board.getSquare(col, row));
}

char King::getPieceAcronym()
{
    return m_acronym;
}

void King::putPiece(Board::Square *square)
{
    m_square = square;
    m_square->setPiece(this);
}

void King::checkAvailableSquares(Board board)
{
}

bool King::canJump()
{
    return false;
}
