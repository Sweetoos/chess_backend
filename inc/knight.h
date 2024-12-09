#pragma once
#include "classes.h"
#include <string>

class Knight : public PieceInterface
{
public:
    Knight(PieceColor color, const Position &position)
        : PieceInterface(color, 3, "N", position) {}
    void move(const Position &target) override { m_position = target; }
    void capture(const Position &target) override { m_position = target; }
    const Position &getPosition() const override { return m_position; }
    const PieceColor &getColor() const override { return m_color; }
    int getValue() const override { return m_value; }
    std::string getSymbol() const override { return m_symbol; }

    bool isValidMove(const Position &from, const Position &to, const Board &board) const override;
};
