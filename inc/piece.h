#pragma once
#include "board.h"
#include <string>
#include <iostream>
#include "classes.h"

class Piece
{
protected:
    char m_pieceAcronym;
    bool m_canJump = false;
    PieceColor m_color;
    char m_col;
    int m_row;
    Board::Square *m_square;

public:
    Piece(PieceColor color, char col, int row) : m_color(color), m_col(col), m_row(row) {} // m_square(nullptr)
    virtual ~Piece() = default;
    void putPiece(Board::Square *square);
    //virtual void checkAvailableSquares(Board board) = 0;
    virtual char getPieceAcronym() = 0;

    /// @brief not all pieces can jump like knight
    /// @return canJump
    virtual bool canJump() = 0;

    virtual std::string getPieceName() = 0;

    void setSquare(Board::Square *square) { m_square = square; }
    Board::Square *getSquare() { return m_square; }
    PieceColor getPieceColor() const { return m_color; }
    void setPosition(char col, int row);
    char getColumn() const { return m_col; }
    int getRow() const { return m_row; }
};
