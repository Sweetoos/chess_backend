#pragma once
#include "classes.h"
#include "bishop.h"
#include "rook.h"
#include "queen.h"
#include "pawn.h"
#include "knight.h"
#include "king.h"

class PieceFactory
{
public:
    virtual Piece *createPiece(PieceColor color, char col, int row) = 0;
    virtual ~PieceFactory() = default;
};

class BishopFactory : public PieceFactory
{
public:
    Piece *createPiece(PieceColor color, char row, int col)
    {
        return new Bishop(color, col, row);
    }
};
class RookFactory : public PieceFactory
{
public:
    Piece *createPiece(PieceColor color, char row, int col)
    {
        return new Rook(color, col, row);
    }
};
class QueenFactory : public PieceFactory
{
public:
    Piece *createPiece(PieceColor color, char row, int col)
    {
        return new Queen(color, col, row);
    }
};
class KnightFactory : public PieceFactory
{
public:
    Piece *createPiece(PieceColor color, char row, int col)
    {
        return new Knight(color, col, row);
    }
};
class PawnFactory : public PieceFactory
{
public:
    Piece *createPiece(PieceColor color, char row, int col)
    {
        return new Pawn(color, col, row);
    }
};
class KingFactory : public PieceFactory
{
public:
    Piece *createPiece(PieceColor color, char row, int col)
    {
        return new King(color, col, row);
    }
};