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

#include "board.h"
#include "piece.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "rook.h"

std::ostream &operator<<(std::ostream &os, const PieceColor &color);
