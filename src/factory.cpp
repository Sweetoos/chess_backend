//factory.cpp
#include "classes.h"
#include "factory.h"

PieceFactory::PieceFactory()
{
    m_creators[PieceType::PAWN] = [](const Position &pos, const PieceColor &color)
    {
        return new Pawn(color, pos);
    };
    m_creators[PieceType::ROOK] = [](const Position &pos, const PieceColor &color)
    {
        return new Rook(color, pos);
    };
    m_creators[PieceType::KNIGHT] = [](const Position &pos, const PieceColor &color)
    {
        return new Knight(color, pos);
    };
    m_creators[PieceType::BISHOP] = [](const Position &pos, const PieceColor &color)
    {
        return new Bishop(color, pos);
    };
    m_creators[PieceType::KING] = [](const Position &pos, const PieceColor &color)
    {
        return new King(color, pos);
    };
    m_creators[PieceType::QUEEN] = [](const Position &pos, const PieceColor &color)
    {
        return new Queen(color, pos);
    };
}

PieceFactory::~PieceFactory()
{
    for (auto piece : m_pieces)
    {
        delete piece;
    }
}

PieceInterface *PieceFactory::createAndStorePiece(const PieceType &type, const Position &position, const PieceColor &color)
{
    auto it = m_creators.find(type);
    if (it != m_creators.end())
    {
        PieceInterface *piece = it->second(position, color);
        m_pieces.push_back(piece);
        return piece;
    }

    throw std::invalid_argument("unknown piece type");
}


