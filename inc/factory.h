#pragma once
#include <map>
#include <list>
#include <functional>
#include "classes.h"

class PieceFactory
{
private:
    std::list<PieceInterface *> m_pieces; 
    std::map<std::string, std::function<PieceInterface *(const Position &, const PieceColor &)>> m_creators;

public:
    PieceFactory()
    {
        m_creators[""] = [](const Position &pos, const PieceColor &color)
        {
            return new Pawn(color, pos);
        };
        m_creators["R"] = [](const Position &pos, const PieceColor &color)
        {
            return new Rook(color, pos);
        };
        m_creators["N"] = [](const Position &pos, const PieceColor &color)
        {
            return new Knight(color, pos);
        };
        m_creators["B"] = [](const Position &pos, const PieceColor &color)
        {
            return new Bishop(color, pos);
        };
        m_creators["K"] = [](const Position &pos, const PieceColor &color)
        {
            return new King(color, pos);
        };
        m_creators["Q"] = [](const Position &pos, const PieceColor &color)
        {
            return new Queen(color, pos);
        };
    }

    ~PieceFactory()
    {
        for (auto piece : m_pieces)
        {
            delete piece;
        }
    }

    PieceInterface *createAndStorePiece(const std::string &type, const Position &position, const PieceColor &color)
    {
        auto it = m_creators.find(type);
        if (it != m_creators.end())
        {
            PieceInterface *piece = it->second(position, color);
            m_pieces.push_back(piece);
            return piece;
        }
        throw std::invalid_argument("Unknown piece type: " + type);
    }

    const std::list<PieceInterface *> &getPieces() const
    {
        return m_pieces;
    }

};
