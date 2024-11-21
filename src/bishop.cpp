#include "classes.h"
#include "bishop.h"



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
