```cpp
// board.h
#pragma once
#include <vector>
#include <memory>
#include <stdexcept>
#include "piece.h"

enum class BoardColor { WHITE, BLACK };

class Board {
public:
    // Klasa wewnętrzna Square
    class Square {
        char m_col;
        int m_row;
        BoardColor m_color;
        std::shared_ptr<Piece> m_piece;

    public:
        Square(char col, int row, BoardColor color)
            : m_col(col), m_row(row), m_color(color), m_piece(nullptr) {}

        void setPiece(std::shared_ptr<Piece> piece) { m_piece = piece; }
        std::shared_ptr<Piece> getPiece() const { return m_piece; }
        BoardColor getColor() const { return m_color; }
        char getColumn() const { return m_col; }
        int getRow() const { return m_row; }
    };

private:
    std::vector<std::vector<std::shared_ptr<Square>>> m_squares;

public:
    Board();
    Square* getSquare(char col, int row);
    void displayBoard() const;
    void placePiece(char col, int row, std::shared_ptr<Piece> piece);
    void initializeDefaultSetup();
};

```

```cpp
//board.cpp
#include "board.h"
#include <iostream>

Board::Board() {
    for (char col = 'A'; col <= 'H'; ++col) {
        std::vector<std::shared_ptr<Square>> column;
        for (int row = 1; row <= 8; ++row) {
            BoardColor color = ((col - 'A') + row) % 2 == 0 ? BoardColor::WHITE : BoardColor::BLACK;
            column.push_back(std::make_shared<Square>(col, row, color));
        }
        m_squares.push_back(column);
    }
}

Board::Square* Board::getSquare(char col, int row) {
    if (col < 'A' || col > 'H' || row < 1 || row > 8) {
        throw std::out_of_range("Invalid square coordinates");
    }
    return m_squares[col - 'A'][row - 1].get();
}

void Board::placePiece(char col, int row, std::shared_ptr<Piece> piece) {
    Square* square = getSquare(col, row);
    square->setPiece(piece);
}

void Board::displayBoard() const {
    for (int row = 8; row >= 1; --row) {
        for (char col = 'A'; col <= 'H'; ++col) {
            Square* square = m_squares[col - 'A'][row - 1].get();
            auto piece = square->getPiece();
            if (piece) {
                std::cout << piece->getPieceColor() << piece->getPieceAcronym() << " ";
            } else {
                std::cout << ". ";
            }
        }
        std::cout << std::endl;
    }
}

void Board::initializeDefaultSetup() {
    // Wykorzystaj PieceFactory lub bezpośrednio twórz obiekty figurek
    // np.:
    placePiece('A', 2, std::make_shared<Pawn>(PieceColor::WHITE, 'A', 2));
    // ... Dodaj resztę
}

```

```cpp
//piece.h
#pragma once
#include <string>

enum class PieceColor { WHITE, BLACK };

class Piece {
protected:
    PieceColor m_color;
    char m_col;
    int m_row;

public:
    Piece(PieceColor color, char col, int row)
        : m_color(color), m_col(col), m_row(row) {}
    virtual ~Piece() = default;

    virtual char getPieceAcronym() = 0;
    virtual bool canJump() = 0;
    virtual std::string getPieceName() = 0;

    PieceColor getPieceColor() const { return m_color; }
    char getColumn() const { return m_col; }
    int getRow() const { return m_row; }
    void setPosition(char col, int row) {
        m_col = col;
        m_row = row;
    }
};
```

```cpp
//chess.h
#pragma once
#include "board.h"

class Application {
private:
    Board m_board;

public:
    Application() : m_board() {
        m_board.initializeDefaultSetup();
    }

    void run() {
        m_board.displayBoard();
        // Tu można dodać logikę gry
    }
};
```

```cpp
//main.cpp
#include "application.h"

int main() {
    try {
        Application app;
        app.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}

```