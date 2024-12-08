#pragma once
#include <string>
#include <iostream>
#include "classes.h"

class PieceInterface
{
protected:
    PieceColor m_color;
    int m_value;
    std::string m_symbol;
    Position m_position;

public:
    PieceInterface(PieceColor color, int value, const std::string &symbol, const Position &position)
        : m_color(color), m_value(value), m_symbol(symbol), m_position(position) {}

    virtual ~PieceInterface() = default;
    virtual void move(const Position &target) = 0;
    virtual void capture(const Position &target) = 0;
    virtual const Position &getPosition() const = 0;
    virtual const PieceColor &getColor() const = 0;
    virtual int getValue() const = 0;
    virtual std::string getSymbol() const = 0;
    virtual bool canJump() const = 0;
    virtual const std::string getFullSymbol() const
    {
        return (m_color == PieceColor::WHITE ? "W" : "B") + m_symbol;
    }
};

// class Piece : public PieceInterface
// {
// protected:
//     Position m_position;
//     PieceColor m_color;
//     int m_value;
//     std::string m_notation;
//     bool m_canJump;

// public:
//     Piece(const Position &startPositon, const PieceColor &color, int value, const std::string &notation)
//         : m_position(startPositon), m_color(color), m_value(value), m_notation(notation) {}

//     const Position &getPosition() const override;
//     const PieceColor &getColor() const override;
//     int getValue() const override;
//     std::string getNotation() const override;
//     void move(const Position &target) override;
//     void capture(const Position &target) override;
//     bool canJump() const override;
// };
