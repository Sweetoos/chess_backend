//pawn.h
#pragma once
#include "classes.h"
#include <string>
#include <iostream>

class Pawn : public PieceInterface
{
public:
    Pawn(PieceColor color, const Position &position)
        : PieceInterface(color, 1, "", position, PieceType::PAWN) {}
    void move(const Position &target) override 
    {
        std::cout << m_position.col<<m_position.row << target.col<<target.row << '\n';
        m_position = target; 
        std::cout << m_position.col<<m_position.row << target.col<<target.row << '\n';
    }
    void capture(const Position &target) override { m_position = target; }
    const Position &getPosition() const override { return m_position; }
    const PieceColor &getColor() const override { return m_color; }
    int getValue() const override { return m_value; }
    std::string getSymbol() const override { return m_symbol; }
    PieceType getType() const override { return m_type; }
};
