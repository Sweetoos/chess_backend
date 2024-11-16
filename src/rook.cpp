#include "rook.h"

Rook::Rook(PieceColor color, Board &board, char col, int row):Piece(color)
{
    putPiece(board.getSquare(col,row));
}

char Rook::getPieceAcronym()
{
    return m_acronym;
}

int Rook::getValue()
{
    return m_value;
}

void Rook::putPiece(Board::Square *square)
{
    m_square = square;
    m_square->setPiece(this);
}

void Rook::checkAvailableSquares(Board board)
{
}

bool Rook::canJump()
{
    return false;
}
