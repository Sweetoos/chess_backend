#pragma once
#include <map>
#include <list>
#include <functional>
#include "classes.h"

class PieceFactory
{
private:
    std::list<PieceInterface *> m_pieces;
    std::map<PieceType, std::function<PieceInterface *(const Position &, const PieceColor &)>> m_creators;

public:
    PieceFactory();
    ~PieceFactory();
    PieceInterface *createAndStorePiece(const PieceType &type, const Position &position, const PieceColor &color);
    const std::list<PieceInterface *> &getPieces() const { return m_pieces; }
};
