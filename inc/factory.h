#pragma once
#include "classes.h"
#include "bishop.h"

class PieceFactory
{
public:
    virtual Piece *createPiece(PieceColor color, char col, int row) = 0;
    virtual ~PieceFactory() = default;
};

class BishopFactory : public PieceFactory
{
    Piece *createPiece(PieceColor color, char row, int col){
        return new Bishop(color, col,row);
    }
};