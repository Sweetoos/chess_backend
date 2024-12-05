#pragma once
#include "classes.h"
#include <list>

class Piece;

class Board
{
public:
    class Square
    {
    private:
        char m_col;
        int m_row;
        Piece *m_piece;

    public:
        Square(char col, int row) : m_col(col), m_row(row), m_piece(nullptr) {}
        BoardColor m_squareColor;
        void setColor(const BoardColor &color);
        BoardColor getColor();
        void setPiece(Piece *piece);
        Piece *getPiece();
        char getColumn() const {return m_col;}
        int getrow() const {return m_row;}
    };

private:
    Square *m_square[9][9];
    // BoardColor m_color;

public:
    Board();
    ~Board();
    void putPiece(int col, int row, Piece *piece);
    void initPieces();
    void setBoardColors();
    void displayBoardConsole();
    BoardColor getSquareColor(char col, int row);
    Square *getSquare(char col, int row);
    void displayBoardPositions();
};
