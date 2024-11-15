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

std::ostream &operator<<(std::ostream &os, const PieceColor &color);
