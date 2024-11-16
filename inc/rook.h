#pragma once
#include "classes.h"
#include <string>

class Rook : public Piece
{
private:
    char m_acronym = 'R';
    int m_value = 5;
    std::string m_pieceName = "Rook";
    bool m_moved;

public:
    Rook(PieceColor color, Board &board, char col, int row);
    // Board::Square &getCurrentPosition(char col, int row);
    // void checkAvailableSquares(Board::Square square);
    char getPieceAcronym() override;
    int getValue();
    void putPiece(Board::Square *square) override;
    void checkAvailableSquares(Board board) override;
    bool canJump() override;
    std::string getPieceName() override { return m_pieceName; }
};
