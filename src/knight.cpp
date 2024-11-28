#include "knight.h"

char Knight::getPieceAcronym()
{
    return m_acronym;
}
int Knight::getValue()
{
    return m_value;
}
void Knight::putPiece(Board::Square *square)
{
    m_square = square;
    m_square->setPiece(this);
}
void Knight::checkAvailableSquares(Board board)
{
}
bool Knight::canJump()
{
    return true;
};
