#include "queen.h"

char Queen::getPieceAcronym()
{
    return m_acronym;
}

int Queen::getValue()
{
    return m_value;
}

void Queen::putPiece(Board::Square *square)
{
    m_square=square;
    m_square->setPiece(this);
}

void Queen::checkAvailableSquares(Board board)
{
}

bool Queen::canJump()
{
    return false;
}
