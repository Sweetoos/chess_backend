#pragma once
#include "classes.h"
#include <list>

class PieceFactory
{
private:
    static std::list<Piece *> pieces;

public:
    static Piece *createPiece(char symbol, PieceColor color, char col, int row)
    {
        Piece *piece = nullptr;
        switch (symbol)
        {
        case 'B':
            piece = new Bishop(color, col, row);
            break;
        case 'R':
            piece = new Rook(color, col, row);
            break;
        case ' ':
            piece = new Pawn(color, col, row);
            break;
        case 'K':
            piece = new King(color, col, row);
            break;
        case 'N':
            piece = new Knight(color, col, row);
            break;
        case 'Q':
            piece = new Queen(color, col, row);
            break;
        default:
            return nullptr;
        }

        if (piece != nullptr)
            pieces.push_back(piece);

        return piece;
    }

    static void removePiece(Piece *piece)
    {
        pieces.remove(piece);
        delete piece;
    }

    static void clearPieces()
    {
        for (auto piece : pieces)
            delete piece;
        pieces.clear();
    }

    static const std::list<Piece*> getPieces()
    {
        return pieces;
    }

    ~PieceFactory()
    {
        clearPieces();
    }
};