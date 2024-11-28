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
            delete m_square[c][r];
        }
    }
    for (auto piece : m_pieces)
        delete piece;
}

void Board::initPieces()
{
    // factories
    BishopFactory bishopFactory;
    RookFactory rookFactory;
    QueenFactory queenFactory;
    KnightFactory knightFactory;
    PawnFactory pawnFactory;
    KingFactory kingFactory;

    //  Rooks
    addPiece(rookFactory.createPiece(PieceColor::WHITE, 'A', 1));
    addPiece(rookFactory.createPiece(PieceColor::WHITE, 'H', 1));
    addPiece(rookFactory.createPiece(PieceColor::BLACK, 'A', 8));
    addPiece(rookFactory.createPiece(PieceColor::BLACK, 'H', 8));
    
    // Knights
    addPiece(knightFactory.createPiece(PieceColor::WHITE, 'B', 1));
    addPiece(knightFactory.createPiece(PieceColor::WHITE, 'G', 1));
    addPiece(knightFactory.createPiece(PieceColor::BLACK, 'B', 8));
    addPiece(knightFactory.createPiece(PieceColor::BLACK, 'G', 8));

    // Bishops
    addPiece(bishopFactory.createPiece(PieceColor::WHITE, 'C', 1));
    addPiece(bishopFactory.createPiece(PieceColor::WHITE, 'F', 1));
    addPiece(bishopFactory.createPiece(PieceColor::BLACK, 'C', 8));
    addPiece(bishopFactory.createPiece(PieceColor::BLACK, 'F', 8));


    // Queens
    addPiece(queenFactory.createPiece(PieceColor::WHITE, 'D', 1));
    addPiece(queenFactory.createPiece(PieceColor::BLACK, 'D', 8));

    // Kings
    addPiece(kingFactory.createPiece(PieceColor::WHITE, 'E', 1));
    addPiece(kingFactory.createPiece(PieceColor::BLACK, 'E', 8));

    // White pawns
    addPiece(pawnFactory.createPiece(PieceColor::WHITE, 'A', 2));
    addPiece(pawnFactory.createPiece(PieceColor::WHITE, 'B', 2));
    addPiece(pawnFactory.createPiece(PieceColor::WHITE, 'C', 2));
    addPiece(pawnFactory.createPiece(PieceColor::WHITE, 'D', 2));
    addPiece(pawnFactory.createPiece(PieceColor::WHITE, 'E', 2));
    addPiece(pawnFactory.createPiece(PieceColor::WHITE, 'F', 2));
    addPiece(pawnFactory.createPiece(PieceColor::WHITE, 'G', 2));
    addPiece(pawnFactory.createPiece(PieceColor::WHITE, 'H', 2));

    // Black pawns
    addPiece(pawnFactory.createPiece(PieceColor::BLACK, 'A', 7));
    addPiece(pawnFactory.createPiece(PieceColor::BLACK, 'B', 7));
    addPiece(pawnFactory.createPiece(PieceColor::BLACK, 'C', 7));
    addPiece(pawnFactory.createPiece(PieceColor::BLACK, 'D', 7));
    addPiece(pawnFactory.createPiece(PieceColor::BLACK, 'E', 7));
    addPiece(pawnFactory.createPiece(PieceColor::BLACK, 'F', 7));
    addPiece(pawnFactory.createPiece(PieceColor::BLACK, 'G', 7));
    addPiece(pawnFactory.createPiece(PieceColor::BLACK, 'H', 7));
}

void Board::addPiece(Piece *piece)
{
    m_pieces.push_back(piece);
    Square *square = getSquare(piece->getColumn(), piece->getRow());
    if (square)
        square->m_piece = piece;
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
