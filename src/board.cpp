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
    // Rooks
    Piece *aWhiteRook = new Rook(PieceColor::WHITE, *this, 'A', 1);
    Piece *hWhiteRook = new Rook(PieceColor::WHITE, *this, 'H', 1);

    Piece *aBlackRook = new Rook(PieceColor::BLACK, *this, 'A', 8);
    Piece *hBlackRook = new Rook(PieceColor::BLACK, *this, 'H', 8);

    // Knights
    Piece *bWhiteKnight = new Knight(PieceColor::WHITE, *this, 'B', 1);
    Piece *gWhiteKnight = new Knight(PieceColor::WHITE, *this, 'G', 1);

    Piece *bBlackKnight = new Knight(PieceColor::BLACK, *this, 'B', 8);
    Piece *gBlackKnight = new Knight(PieceColor::BLACK, *this, 'G', 8);

    // Bishops
    Piece *cWhiteBishop = new Bishop(PieceColor::WHITE, *this, 'C', 1);
    Piece *fWhiteBishop = new Bishop(PieceColor::WHITE, *this, 'F', 1);

    Piece *cBlackBishop = new Bishop(PieceColor::BLACK, *this, 'C', 8);
    Piece *fBlackBishop = new Bishop(PieceColor::BLACK, *this, 'F', 8);
    
    // Queens
    Piece *WhiteQueen=new Queen(PieceColor::WHITE, *this,'D',1);
    Piece *BlackQueen=new Queen(PieceColor::BLACK, *this,'D',8);

    // Kings
    Piece *WhiteKing=new King(PieceColor::WHITE, *this,'E',1);
    Piece *BlackKing=new King(PieceColor::BLACK, *this,'E',8);

    //White pawns
    Piece *aWhitePawn = new Pawn(PieceColor::WHITE, *this, 'A', 2);
    Piece *bWhitePawn = new Pawn(PieceColor::WHITE, *this, 'B', 2);
    Piece *cWhitePawn = new Pawn(PieceColor::WHITE, *this, 'C', 2);
    Piece *dWhitePawn = new Pawn(PieceColor::WHITE, *this, 'D', 2);
    Piece *eWhitePawn = new Pawn(PieceColor::WHITE, *this, 'E', 2);
    Piece *fWhitePawn = new Pawn(PieceColor::WHITE, *this, 'F', 2);
    Piece *gWhitePawn = new Pawn(PieceColor::WHITE, *this, 'G', 2);
    Piece *hWhitePawn = new Pawn(PieceColor::WHITE, *this, 'H', 2);

    //Black pawns
    Piece *aBlackPawn = new Pawn(PieceColor::BLACK, *this, 'A', 7);
    Piece *bBlackPawn = new Pawn(PieceColor::BLACK, *this, 'B', 7);
    Piece *cBlackPawn = new Pawn(PieceColor::BLACK, *this, 'C', 7);
    Piece *dBlackPawn = new Pawn(PieceColor::BLACK, *this, 'D', 7);
    Piece *eBlackPawn = new Pawn(PieceColor::BLACK, *this, 'E', 7);
    Piece *fBlackPawn = new Pawn(PieceColor::BLACK, *this, 'F', 7);
    Piece *gBlackPawn = new Pawn(PieceColor::BLACK, *this, 'G', 7);
    Piece *hBlackPawn = new Pawn(PieceColor::BLACK, *this, 'H', 7);
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
