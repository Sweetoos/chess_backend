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

const std::string PieceInterface::getFullSymbol() const
{
    return (m_color == PieceColor::WHITE ? "W" : "B") + m_symbol;
}
