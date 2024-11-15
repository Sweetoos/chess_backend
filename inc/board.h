#pragma once
#include "classes.h"

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
        BoardColor m_squareColor;
        explicit Square(char col, int row) : m_col(col), m_row(row) {}
        void setColor(const BoardColor &color);
        BoardColor getColor();
        void setPiece(Piece *piece);
        Piece *getPiece();
    };

private:
    Square *m_square[9][9];
    BoardColor m_color;

public:
    Board();
    ~Board();
    void initPieces();
    void setBoardColors();
    BoardColor getSquareColor(char col, int row);
    void displayBoardConsole();
    Square *getSquare(char col, int row);
    void displayBoardPositions();
};
