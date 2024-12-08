#pragma once
#include "classes.h"
#include <string>

class Rook : public PieceInterface
{
public:
    Rook(PieceColor color, const Position &position)
        : PieceInterface(color, 5, "R", position) {}
    void move(const Position &target) { m_position = target; }
    void capture(const Position &target) { m_position = target; }
    const Position &getPosition() const { return m_position; }
    const PieceColor &getColor() const { return m_color; }
    int getValue() const { return m_value; }
    std::string getSymbol() const { return m_symbol; }
    bool canJump() const { return false; }
};
