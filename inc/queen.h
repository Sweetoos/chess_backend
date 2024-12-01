#pragma once
#include "classes.h"
#include <string>

class Queen : public Piece
{
private:
    char m_acronym = 'Q';
    int m_value = 9;
    std::string m_pieceName = "Queen";

public:
    Queen(PieceColor color, char col, int row): Piece(color, col,row){}
    // Board::Square &getCurrentPosition(char col, int row);
    // void checkAvailableSquares(Board::Square square);
    char getPieceAcronym() override;
    int getValue();
    //void checkAvailableSquares(Board board) override;
    bool canJump() override;
    std::string getPieceName() override { return m_pieceName; }
};