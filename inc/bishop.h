#pragma once
#include "classes.h"
#include <string>

class Bishop : public Piece
{
private:
    char m_acronym = 'B';
    int m_value = 3;
    std::string m_pieceName = "Bishop";

public:
    Bishop(PieceColor color, char col, int row): Piece(color, col,row){}
    // Board::Square &getCurrentPosition(char col, int row);
    // void checkAvailableSquares(Board::Square square);
    char getPieceAcronym() override;
    int getValue();
    void putPiece(Board::Square *square) override;
    void checkAvailableSquares(Board board) override;
    bool canJump() override;
    std::string getPieceName() override { return m_pieceName; }
};
