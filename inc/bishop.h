//bishop.h
#pragma once
#include "classes.h"
#include <string>

class Bishop : public PieceInterface
{
public:
    Bishop(PieceColor color, const Position &position)
        : PieceInterface(color, 3, "B", position, PieceType::BISHOP) {}
    void move(const Position &target) override { m_position = target; }
    void capture(const Position &target) override { m_position = target; }
    const Position &getPosition() const override { return m_position; }
    const PieceColor &getColor() const override { return m_color; }
    int getValue() const override { return m_value; }
    std::string getSymbol() const override { return m_symbol; }
    PieceType getType() const override { return m_type; }
};
