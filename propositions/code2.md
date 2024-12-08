```cpp
#pragma once
#include <array>
#include <memory>
#include "PieceInterface.h"
#include "Position.h"

class Board {
public:
    // Klasa wewnętrzna reprezentująca pole szachownicy
    class Square {
    private:
        PieceInterface *m_piece;
        bool m_isWhite; // Kolor pola

    public:
        Square(bool isWhite) : m_piece(nullptr), m_isWhite(isWhite) {}

        void setPiece(PieceInterface *piece) { m_piece = piece; }
        void clearPiece() { m_piece = nullptr; }
        PieceInterface *getPiece() const { return m_piece; }
        bool isWhite() const { return m_isWhite; }
    };

    using Grid = std::array<std::array<Square, 8>, 8>;

private:
    Grid m_grid;

public:
    Board();
    void putPiece(std::unique_ptr<PieceInterface> piece, const Position &pos);
    PieceInterface *getPieceAt(const Position &pos) const;
    void removePiece(const Position &pos);
    void displayBoardConsole() const;

private:
    int toIndex(char col) const { return col - 'A'; }
};

#include "Board.h"
#include <iostream>

Board::Board() {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            bool isWhite = (row + col) % 2 == 0;
            m_grid[col][row] = Square(isWhite);
        }
    }
}

void Board::putPiece(std::unique_ptr<PieceInterface> piece, const Position &pos) {
    int col = toIndex(pos.col);
    int row = pos.row - 1;
    m_grid[col][row].setPiece(piece.release());
}

PieceInterface *Board::getPieceAt(const Position &pos) const {
    int col = toIndex(pos.col);
    int row = pos.row - 1;
    return m_grid[col][row].getPiece();
}

void Board::removePiece(const Position &pos) {
    int col = toIndex(pos.col);
    int row = pos.row - 1;
    m_grid[col][row].clearPiece();
}

void Board::displayBoardConsole() const {
    for (int row = 7; row >= 0; --row) {
        for (int col = 0; col < 8; ++col) {
            const Square &square = m_grid[col][row];
            if (PieceInterface *piece = square.getPiece()) {
                std::cout << "P\t"; // Tylko dla pionka
            } else {
                std::cout << (square.isWhite() ? ".\t" : "#\t");
            }
        }
        std::cout << "\n";
    }
}

#pragma once

enum class PieceColor { WHITE, BLACK };

struct Position {
    char col;
    int row;
    Position(char c, int r) : col(c), row(r) {}
};

#pragma once
#include "Position.h"

class PieceInterface {
public:
    virtual ~PieceInterface() = default;
    virtual void move(const Position &target) = 0;
    virtual const Position &getPosition() const = 0;
    virtual const PieceColor &getColor() const = 0;
};

#pragma once
#include "PieceInterface.h"

class Pawn : public PieceInterface {
private:
    Position m_position;
    PieceColor m_color;

public:
    Pawn(const Position &startPosition, const PieceColor &color)
        : m_position(startPosition), m_color(color) {}

    void move(const Position &target) override;
    const Position &getPosition() const override { return m_position; }
    const PieceColor &getColor() const override { return m_color; }
};

#pragma once
#include <functional>
#include <unordered_map>
#include "PieceInterface.h"
#include "Position.h"

class PieceFactory {
private:
    std::unordered_map<std::string, std::function<PieceInterface *(const Position &, const PieceColor &)>> m_creators;

public:
    PieceFactory();
    std::unique_ptr<PieceInterface> createPiece(const std::string &type, const Position &position, const PieceColor &color);
};

#pragma once
#include "Board.h"
#include "PieceFactory.h"

class GameManager {
private:
    Board m_board;
    PieceFactory &m_factory;

public:
    GameManager(PieceFactory &factory) : m_factory(factory) {}
    void setupBoard();
    void movePiece(const Position &from, const Position &to);
    void displayBoard() const;
};

#pragma once
#include "GameManager.h"
#include "PieceFactory.h"

class Chess {
private:
    GameManager m_gameManager;

public:
    Chess(PieceFactory &factory);
    void run();
};

#include "Pawn.h"
#include <iostream>

void Pawn::move(const Position &target) {
    std::cout << "Pawn moved from " << m_position.col << m_position.row
              << " to " << target.col << target.row << "\n";
    m_position = target;
}

#include "PieceFactory.h"
#include "Pawn.h"

PieceFactory::PieceFactory() {
    m_creators["Pawn"] = [](const Position &pos, const PieceColor &color) {
        return new Pawn(pos, color);
    };
}

std::unique_ptr<PieceInterface> PieceFactory::createPiece(const std::string &type, const Position &position, const PieceColor &color) {
    if (m_creators.find(type) != m_creators.end()) {
        return std::unique_ptr<PieceInterface>(m_creators[type](position, color));
    }
    throw std::invalid_argument("Unknown piece type: " + type);
}

#include "GameManager.h"
#include <iostream>

void GameManager::setupBoard() {
    for (char col = 'A'; col <= 'H'; ++col) {
        m_board.putPiece(m_factory.createPiece("Pawn", Position(col, 2), PieceColor::WHITE), Position(col, 2));
        m_board.putPiece(m_factory.createPiece("Pawn", Position(col, 7), PieceColor::BLACK), Position(col, 7));
    }
}

void GameManager::movePiece(const Position &from, const Position &to) {
    PieceInterface *piece = m_board.getPieceAt(from);
    if (!piece) {
        throw std::runtime_error("No piece at given position");
    }
    piece->move(to);
    m_board.putPiece(std::unique_ptr<PieceInterface>(piece), to);
    m_board.removePiece(from);
}

void GameManager::displayBoard() const {
    m_board.displayBoardConsole();
}

#include "Chess.h"

Chess::Chess(PieceFactory &factory) : m_gameManager(factory) {
    m_gameManager.setupBoard();
}

void Chess::run() {
    m_gameManager.displayBoard();
}

#include "Chess.h"
#include "PieceFactory.h"

int main() {
    try {
        PieceFactory factory;
        Chess chess(factory);
        chess.run();
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}
