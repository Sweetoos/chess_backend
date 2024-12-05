#include "classes.h"
#include <iostream>
#include <string>
#include <list>
#include "board.h"
#include <array>

std::list<Piece *> PieceFactory::pieces;
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
            delete m_square[c][r];
        }
    }
}

/// @brief put piece on the board
void Board::putPiece(int col, int row, Piece *piece)
{
    if (row < 1 || row > 8 || col < 1 || col > 8)
    {
        throw std::out_of_range("Incorrect square index (putPiece)");
    }
    m_square[col][row]->setPiece(piece);
}

/// @brief initialize all pieces on the board
void Board::initPieces()
{
    // white pawns
    for (char col = 'A'; col <= 'H'; col++)
    {
        int numericCol = col - 'A' + 1;
        putPiece(numericCol, 2, PieceFactory::createPiece(' ', PieceColor::WHITE, col, 2));
    }

    // black pawns
    for (char col = 'A'; col <= 'H'; col++)
    {
        int numericCol = col - 'A' + 1;
        putPiece(numericCol, 7, PieceFactory::createPiece(' ', PieceColor::BLACK, col, 7));
    }

    // figures
    char pieces[] = {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'};
    for (int i = 0; i < 8; i++)
    {
        putPiece(i + 1, 1, PieceFactory::createPiece(pieces[i], PieceColor::WHITE, 'A' + i, 1));
        putPiece(i + 1, 8, PieceFactory::createPiece(pieces[i], PieceColor::BLACK, 'A' + i, 8));
    }
}

void Board::setBoardColors()
{
    for (int col = 1; col <= 8; col++)
    {
        for (int row = 1; row <= 8; row++)
        {
            m_square[col][row]->setColor(((row + col) % 2 == 0) ? BoardColor::WHITE : BoardColor::BLACK);
        }
    }
}

BoardColor Board::getSquareColor(char col, int row)
{
    int colInt = col - 'A' + 1;
    if (row < 1 || row > 8 || colInt < 1 || colInt > 8)
    {
        throw std::out_of_range("Incorrect square index (getSquareColor)");
    }
    return m_square[colInt][row]->getColor();
}

void Board::displayBoardConsole()
{
    for (int r = 8; r >= 1; r--)
    {
        for (int c = 1; c <= 8; c++)
        {
            Piece *piece = m_square[c][r]->getPiece();
            if (piece)
                std::cout << piece->getPieceColor() << piece->getPieceAcronym() << '\t';
            else
            {
                BoardColor color = m_square[c][r]->getColor();
                std::cout << ((color == BoardColor::WHITE) ? "Black" : "White") << '\t';
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
        throw std::out_of_range("Incorrect square index (getSquare)");
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
    std::cout << "\n   A\tB\tC\tD\tE\tF\tG\tH\n";

    for (int r = 8; r >= 1; r--)
    {
        std::cout << r << " ";
        for (int c = 1; c <= 8; c++)
        {
            Piece *piece = m_square[c][r]->getPiece();
            if (piece)
                std::cout << piece->getPieceColor() << piece->getPieceAcronym() << '\t';
            else
            {
                BoardColor color = m_square[c][r]->getColor();
                std::cout << ((color == BoardColor::WHITE) ? " . " : " . ") << '\t';
            }
        }
        std::cout << " " << r << '\n';
    }

    std::cout << "   A\tB\tC\tD\tE\tF\tG\tH\n";
}