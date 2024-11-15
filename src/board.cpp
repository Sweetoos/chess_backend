#include "classes.h"
#include "board.h"
#include <iostream>
#include <string>

Board::Board()
{
    for (int c = 1; c <= 8; c++)
    {
        for (int r = 1; r <= 8; r++)
        {

            char column = 'A' + (c - 1);
            int row = 9 - r;
            m_square[c][r] = new Square(column, row);
        }
    }
    setBoardColors();
    initPieces();
}

Board::~Board()
{
    for (int c = 1; c <= 8; c++)
    {
        for (int r = 1; r <= 8; r++)
        {
            delete m_square[c][r]->getPiece();
            delete m_square[c][r];
        }
    }
}

void Board::initPieces()
{
    // Bishops
    Piece *cWhiteBishop = new Bishop(PieceColor::WHITE, *this, 'C', 1);
    Piece *fWhiteBishop = new Bishop(PieceColor::WHITE, *this, 'F', 1);

    Piece *cBlackBishop = new Bishop(PieceColor::BLACK, *this, 'C', 8);
    Piece *fBlackBishop = new Bishop(PieceColor::BLACK, *this, 'F', 8);
}

void Board::setBoardColors()
{
    for (int col = 1; col <= 8; col++)
    {
        for (int row = 1; row <= 8; row++)
        {
            m_color = ((row + col) % 2 == 0) ? BoardColor::WHITE : BoardColor::BLACK;
            m_square[col][row]->setColor(m_color);
        }
    }
}

BoardColor Board::getSquareColor(char col, int row)
{
    int colInt = col - 'A' + 1;
    if (row < 1 || row > 8 || colInt < 1 || colInt > 8)
    {
        throw std::out_of_range("Incorrect square index");
    }
    return m_square[colInt][row]->getColor();
}

void Board::displayBoardConsole()
{
    for (int r = 1; r <= 8; r++)
    {
        for (int c = 1; c <= 8; c++)
        {
            Piece *piece = m_square[c][r]->getPiece();
            if (piece)
                std::cout << piece->getPieceColor() << piece->getPieceAcronym() << '\t';
            else
            {
                BoardColor color = m_square[c][r]->getColor();
                std::cout << ((color == BoardColor::WHITE) ? "White" : "Black") << '\t';
            }
        }
        std::cout << '\n';
    }
}

Board::Square *Board::getSquare(char col, int row)
{
    int colInt = col - 'A' + 1;
    if (row < 1 || row > 8 || colInt < 1 || colInt > 8)
    {
        throw std::out_of_range("Incorrect square index");
    }
    return m_square[colInt][row];
}

void Board::Square::setColor(const BoardColor &color)
{
    m_squareColor = color;
}

BoardColor Board::Square::getColor()
{
    return m_squareColor;
}

void Board::Square::setPiece(Piece *piece)
{
    m_piece = piece;
}

Piece *Board::Square::getPiece()
{
    return m_piece;
}

void Board::displayBoardPositions()
{
    for (char col = 'A'; col <= 'H'; col++)
    {
        for (int row = 1; row <= 8; row++)
        {
            std::cout << col << row << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}
