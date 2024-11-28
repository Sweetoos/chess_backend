#pragma once

#include "classes.h"
#include <string>

class King : public Piece
{
private:
    char m_acronym = 'K';
    std::string m_pieceName = "King";

public:
    King(PieceColor color, char col, int row): Piece(color, col,row){}
    // Board::Square &getCurrentPosition(char col, int row);
    // void checkAvailableSquares(Board::Square square);
    char getPieceAcronym() override;
    void putPiece(Board::Square *square) override;
    void checkAvailableSquares(Board board) override;
    bool canJump() override;
    std::string getPieceName() override { return m_pieceName; }
};