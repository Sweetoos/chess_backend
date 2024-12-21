//classes.h
#pragma once

enum class PieceColor
{
    WHITE,
    BLACK
};

enum class BoardColor
{
    WHITE,
    BLACK
};

enum class PieceType
{
    PAWN,
    BISHOP,
    KING,
    KNIGHT,
    QUEEN,
    ROOK
};

struct Position
{
    char col;
    int row;
    Position(char col, int row) : col(col), row(row) {}
};

#include "piece.h"
#include "board.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "rook.h"
#include "factory.h"
#include "chess.h"

std::ostream &operator<<(std::ostream &os, const PieceColor &color);
