#pragma once
#include "classes.h"
#include <print>
#include "move.h"
#include "pgn.h"  

class GameManager
{
private:
    Board m_board;
    PieceColor m_currentTurnColor = PieceColor::WHITE;
    PieceFactory &m_factory;
    MoveType m_moveType = MoveType::MOVE;
    PgnNotation m_pgn;  
    bool m_promotionFlag = false;

    bool wouldMoveExposeKingToCheck(const Position &from, const Position &to, PieceColor kingColor);
    bool hasLegalMoves(PieceColor color);  

public:
    static int turn;
    bool movePiece(const Position &from, const Position &to, bool isReplay = false);  

    GameManager(PieceFactory &factory) : m_factory(factory) {}
    void setupBoard();
    void displayBoard() const;
    PieceColor getCurrentTurnColor() const { return m_currentTurnColor; }
    void setCurrentTurnColor(PieceColor color) { m_currentTurnColor = color; }
    bool handleCastling(const Position &from, const Position &to);
    PieceType handlePromotion(const Position &pos); 
    bool isSquareUnderAttack(const Position &pos, PieceColor defendingColor) const;
    bool isKingInCheck(PieceColor color) const;
    bool isCheckmate(PieceColor color);
    bool isStalemate(PieceColor color);  
    bool isFirstMove(const PieceInterface *piece);
    PgnNotation& getPgn() { return m_pgn; }  
    std::string promotionTypeToString(PieceType type) const;  
    void resetPromotionFlag() { m_promotionFlag = false; }
    bool getPromotionFlag() const { return m_promotionFlag; }

    bool hasInsufficientMaterial() const;
    bool hasOnlyKing(PieceColor color) const;
    bool hasOnlyKingAndMinorPiece(PieceColor color) const;

    const Board& getBoard() const;
};

class Chess
{
private:
    GameManager m_gm;

public:
    Chess(PieceFactory &factory);
    void run();
};