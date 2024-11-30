#include "classes.h"
#include "piece.h"
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
            delete m_square[c][r];
        }
    }
}

void Board::initPieces()
{

    // Rooks
    PieceFactory::createPiece('R',PieceColor::WHITE, 'A', 1);
    PieceFactory::createPiece('R',PieceColor::WHITE, 'H', 1);
    PieceFactory::createPiece('R',PieceColor::BLACK, 'A', 8);
    PieceFactory::createPiece('R',PieceColor::BLACK, 'H', 8);

    // Knights
    PieceFactory::createPiece('N',PieceColor::WHITE, 'B', 1);
    PieceFactory::createPiece('N',PieceColor::WHITE, 'G', 1);
    PieceFactory::createPiece('N',PieceColor::BLACK, 'B', 8);
    PieceFactory::createPiece('N',PieceColor::BLACK, 'G', 8);

    // Bishops
    PieceFactory::createPiece('B',PieceColor::WHITE, 'C', 1);
    PieceFactory::createPiece('B',PieceColor::WHITE, 'F', 1);
    PieceFactory::createPiece('B',PieceColor::BLACK, 'C', 8);
    PieceFactory::createPiece('B',PieceColor::BLACK, 'F', 8);

    // Queens
    PieceFactory::createPiece('Q',PieceColor::WHITE, 'D', 1);
    PieceFactory::createPiece('Q',PieceColor::BLACK, 'D', 8);

    // Kings
    PieceFactory::createPiece('K',PieceColor::WHITE, 'E', 1);
    PieceFactory::createPiece('K',PieceColor::BLACK, 'E', 8);
    
    // White pawns
    PieceFactory::createPiece(' ',PieceColor::WHITE, 'A', 2);
    PieceFactory::createPiece(' ',PieceColor::WHITE, 'B', 2);
    PieceFactory::createPiece(' ',PieceColor::WHITE, 'C', 2);
    PieceFactory::createPiece(' ',PieceColor::WHITE, 'D', 2);
    PieceFactory::createPiece(' ',PieceColor::WHITE, 'E', 2);
    PieceFactory::createPiece(' ',PieceColor::WHITE, 'F', 2);
    PieceFactory::createPiece(' ',PieceColor::WHITE, 'G', 2);
    PieceFactory::createPiece(' ',PieceColor::WHITE, 'H', 2);

    // Black pawns
    PieceFactory::createPiece(' ',PieceColor::BLACK, 'A', 7);
    PieceFactory::createPiece(' ',PieceColor::BLACK, 'B', 7);
    PieceFactory::createPiece(' ',PieceColor::BLACK, 'C', 7);
    PieceFactory::createPiece(' ',PieceColor::BLACK, 'D', 7);
    PieceFactory::createPiece(' ',PieceColor::BLACK, 'E', 7);
    PieceFactory::createPiece(' ',PieceColor::BLACK, 'F', 7);
    PieceFactory::createPiece(' ',PieceColor::BLACK, 'G', 7);
    PieceFactory::createPiece(' ',PieceColor::BLACK, 'H', 7);
}



void Board::setBoardColors()
{
    for (int col = 1; col <= 8; col++)
    {
        for (int row = 1; row <= 8; row++)
        {
            m_square[col][row]->setColor(((row+col)%2==0)? BoardColor::WHITE:BoardColor::BLACK);
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
