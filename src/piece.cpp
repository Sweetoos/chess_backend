#include "classes.h"
#include <iostream>
#include "piece.h"

std::ostream &operator<<(std::ostream &os, const PieceColor &color)
{
    switch (color)
    {
    case PieceColor::WHITE:
        os << "W";
        break;
    case PieceColor::BLACK:
        os << "B"; 
        break;
    }
    return os;
}
void Piece::putPiece(Board::Square *square)
{
    m_square=square;
    m_square->setPiece(this);
}
void Piece::setPosition(char col, int row)
{
    m_col=col;
    m_row=row;
}