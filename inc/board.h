// board.h
#pragma once
#include "classes.h"
#include <list>
#include <array>

class Board
{
public:
    class Square
    {
    private:
        BoardColor m_squareColor;
        PieceInterface *m_piece;

    public:
        Square() : m_squareColor(BoardColor::WHITE), m_piece(nullptr) {}
        Square(BoardColor color) : m_squareColor(color), m_piece(nullptr) {}
        void setPiece(PieceInterface *piece);
        PieceInterface *getPiece() const;
        void clearPiece();
        BoardColor getColor() const;
    };

private:
    std::array<std::array<Square, 8>, 8> m_grid;

public:
    Board();
    ~Board();
    Board(const Board& other); // Add copy constructor declaration
    Board& operator=(const Board& other);  // Add assignment operator

    void putPiece(PieceInterface *piece);
    void removePiece(const Position &position);
    void removePiece(const Position &position, bool deletePiece);
    PieceInterface *getPieceAt(const Position &position) const;
    void displayBoardConsole() const;

private:
    int toIndex(char col) const;
};
