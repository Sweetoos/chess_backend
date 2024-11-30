#pragma once
#include "classes.h"
#include <string>

class Knight : public Piece
{
private:
    char m_acronym = 'N';
    int m_value = 3;
    std::string m_pieceName = "Knight";

public:
    Knight(PieceColor color, char col, int row): Piece(color, col,row){}
    // Board::Square &getCurrentPosition(char col, int row);
    // void checkAvailableSquares(Board::Square square);
    char getPieceAcronym() override;
    int getValue();
    //void checkAvailableSquares(Board board) override;
    bool canJump() override;
    std::string getPieceName() override { return m_pieceName; }
};
