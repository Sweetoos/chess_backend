#pragma once
#include <string>
#include "board.h"
#include "classes.h"

enum PieceColor
{
    WHITE,
    BLACK
};

class Piece
{
protected:
    Board::Square *m_square;
    char m_pieceAcronym;
    bool m_canJump = false;
    PieceColor m_color;

public:
    Piece(PieceColor color) : m_color(color) {} // m_square(nullptr),
    virtual void putPiece(Board::Square *square) = 0;
    virtual void checkAvailableSquares(Board board) = 0;
    virtual char getPieceAcronym() = 0;
    virtual bool canJump() = 0;
    virtual std::string getPieceName() = 0;

    void setSquare(Board::Square *square) { m_square = square; }
    Board::Square *getSquare() { return m_square; }
    PieceColor getPieceColor() const { return m_color; }
};
