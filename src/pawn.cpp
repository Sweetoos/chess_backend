#include "pawn.h"

char Pawn::getPieceAcronym()
{
    return m_acronym;
}

int Pawn::getValue()
{
    return m_value;
}

void Pawn::putPiece(Board::Square *square)
{
    m_square = square;
    m_square->setPiece(this);
}

void Pawn::checkAvailableSquares(Board board)
{
}

bool Pawn::canJump()
{
    return false;
}
