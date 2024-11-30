#pragma once
#include "classes.h"
#include <list>
#include "factory.h"


class Board
{
public:
    struct Square
    {
        char m_col;
        int m_row;
        Piece *m_piece;

        BoardColor m_squareColor;
        Square(char col, int row) : m_col(col), m_row(row), m_piece(nullptr) {}
        void setColor(const BoardColor &color);
        BoardColor getColor();
        void setPiece(Piece *piece);
        Piece *getPiece();
    };

private:
    Square *m_square[9][9];
    //BoardColor m_color;

public:
    Board();
    ~Board();
    void initPieces();
    void addPiece(Piece *piece);
    void setBoardColors();
    void displayBoardConsole();
    BoardColor getSquareColor(char col, int row);
    Square *getSquare(char col, int row);
    void displayBoardPositions();
};
