//board.cpp
#include "classes.h"
#include <iostream>
#include <string>
#include <list>
#include "board.h"
#include <array>

Board::Board()
{
    for (int col = 0; col < 8; col++)
    {
        for (int row = 0; row < 8; row++)
        {
            BoardColor color = ((row + col) % 2 == 0) ? BoardColor::WHITE : BoardColor::BLACK;
            m_grid[col][row] = Square(color);
        }
    }
}

Board::~Board()
{
    // not needed for m_grid deletion
}

void Board::putPiece(PieceInterface *piece)
{
    int col = toIndex(piece->getPosition().col);
    int row = piece->getPosition().row - 1;
    m_grid[col][row].setPiece(piece);
}

void Board::removePiece(const Position &position)
{
    int col = toIndex(position.col);
    int row = position.row - 1;
    PieceInterface *piece = m_grid[col][row].getPiece();
    if (piece)
    {
        delete piece;
        m_grid[col][row].clearPiece();
    }
}

PieceInterface *Board::getPieceAt(const Position &position) const
{
    int col = toIndex(position.col);
    int row = position.row - 1;

    if (col < 0 || col >= 8 || row < 0 || row >= 8)
        throw std::out_of_range("Position out of bounds");

    return m_grid[col][row].getPiece();
}

void Board::displayBoardConsole() const
{
    std::cout << "\n   A\tB\tC\tD\tE\tF\tG\tH\n";
    for (int r = 7; r >= 0; r--)
    {
        std::cout << r + 1 << " ";
        for (int c = 0; c < 8; c++)
        {
            PieceInterface *piece = m_grid[c][r].getPiece();
            if (piece)
                std::cout << piece->getFullSymbol() << '\t';
            else
                std::cout << ((m_grid[c][r].getColor() == BoardColor::WHITE) ? "Black" : "White") << '\t';
        }
        std::cout << r + 1 << '\n';
    }
    std::cout << "\n   A\tB\tC\tD\tE\tF\tG\tH\n";
}

void Board::Square::setPiece(PieceInterface *piece)
{
    m_piece = piece;
}

PieceInterface *Board::Square::getPiece() const
{
    return m_piece;
}

void Board::Square::clearPiece()
{
    m_piece = nullptr;
}

BoardColor Board::Square::getColor() const
{
    return m_squareColor;
}

int Board::toIndex(char col) const
{
    col = std::tolower(col);
    if (col < 'a' || col > 'h')
    {
        throw std::out_of_range("Column out of range!");
    }
    return col - 'a';
}
