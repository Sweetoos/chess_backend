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

Board::Board(const Board& other) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            m_grid[i][j] = other.m_grid[i][j];
            PieceInterface* piece = other.m_grid[i][j].getPiece();
            if (piece) {
                m_grid[i][j].setPiece(piece);
            }
        }
    }
}

Board& Board::operator=(const Board& other) {
    if (this != &other) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                PieceInterface* piece = m_grid[i][j].getPiece();
                if (piece) {
                    delete piece;
                }
            }
        }
        
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                m_grid[i][j] = other.m_grid[i][j];
                PieceInterface* piece = other.m_grid[i][j].getPiece();
                if (piece) {
                    m_grid[i][j].setPiece(piece);
                }
            }
        }
    }
    return *this;
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

void Board::removePiece(const Position &position, bool deletePiece)
{
    int col = toIndex(position.col);
    int row = position.row - 1;
    PieceInterface *piece = m_grid[col][row].getPiece();
    if (piece)
    {
        if (deletePiece)
            delete piece;
        m_grid[col][row].clearPiece();
    }
    void removePiece(const Position &position);
}

PieceInterface *Board::getPieceAt(const Position &position) const
{
    int col = toIndex(position.col);
    int row = position.row - 1;

    if (col < 0 || col >= 8 || row < 0 || row >= 8)
        throw std::out_of_range("Position out of bounds");

    return m_grid[col][row].getPiece();
}

void Board::displayBoardConsole(PieceColor perspective) const
{
    bool whiteBottom = (perspective == PieceColor::WHITE);
    
    // Print column headers in correct order
    std::cout << "\n  ";
    if (whiteBottom) {
        std::cout << "A\tB\tC\tD\tE\tF\tG\tH\n";
    } else {
        std::cout << "H\tG\tF\tE\tD\tC\tB\tA\n";
    }

    for (int r = (whiteBottom ? 7 : 0); whiteBottom ? r >= 0 : r < 8; r += (whiteBottom ? -1 : 1))
    {
        std::cout << r + 1 << " ";
        for (int c = (whiteBottom ? 0 : 7); whiteBottom ? c < 8 : c >= 0; c += (whiteBottom ? 1 : -1))
        {
            PieceInterface *piece = m_grid[c][r].getPiece();
            if (piece)
                std::cout << piece->getFullSymbol() << '\t';
            else
                std::cout << ((m_grid[c][r].getColor() == BoardColor::WHITE) ? "Black" : "White") << '\t';
        }
        std::cout << r + 1 << '\n';
    }

    // Print bottom column headers
    std::cout << "\n  ";
    if (whiteBottom) {
        std::cout << "A\tB\tC\tD\tE\tF\tG\tH\n";
    } else {
        std::cout << "H\tG\tF\tE\tD\tC\tB\tA\n";
    }
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
