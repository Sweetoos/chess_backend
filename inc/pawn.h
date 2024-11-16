#pragma once
#include "classes.h"
#include <string>

class Pawn : public Piece
{
private:
    char m_acronym = ' ';
    int m_value = 1;
    std::string m_pieceName = "Pawn";

public:
    Pawn(PieceColor color, Board &board, char col, int row);
    // Board::Square &getCurrentPosition(char col, int row);
    // void checkAvailableSquares(Board::Square square);
    char getPieceAcronym() override;
    int getValue();
    void putPiece(Board::Square *square) override;
    void checkAvailableSquares(Board board) override;
    bool canJump() override;
    std::string getPieceName() override { return m_pieceName; }
};
