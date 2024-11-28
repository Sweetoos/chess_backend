#include "king.h"

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
