#include "knight.h"

Knight::Knight(PieceColor color, Board &board, char col, int row) : Piece(color)
{
    putPiece(board.getSquare(col, row));
}
char Knight::getPieceAcronym()
{
    return m_acronym;
}
int Knight::getValue()
{
    return m_value;
}
void Knight::putPiece(Board::Square *square)
{
    m_square = square;
    m_square->setPiece(this);
}
void Knight::checkAvailableSquares(Board board)
{
}
bool Knight::canJump()
{
    return true;
};
