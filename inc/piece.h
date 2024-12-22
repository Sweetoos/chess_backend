//piece.h
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
    PieceType m_type;

public:
    PieceInterface(PieceColor color, int value, const std::string &symbol, const Position &position, const PieceType &type)
        : m_color(color), m_value(value), m_symbol(symbol), m_position(position), m_type(type) {}

    virtual ~PieceInterface() = default;
    virtual void move(const Position &target) = 0;
    virtual void capture(const Position &target) = 0;
    virtual const Position &getPosition() const = 0;
    virtual const PieceColor &getColor() const = 0;
    virtual int getValue() const = 0;
    virtual std::string getSymbol() const = 0;
    virtual const std::string getFullSymbol() const;
    virtual PieceType getType() const = 0;

};