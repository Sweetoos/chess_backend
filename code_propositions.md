```cpp
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <stdexcept>

// Klasa Point (pomocnicza do przechowywania pozycji)
struct Point {
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
};

// Interfejs IChessPiece (czysto wirtualna klasa)
class IChessPiece {
public:
    virtual ~IChessPiece() = default;
    virtual void move(const Point& target) = 0;
    virtual void capture(const Point& target) = 0;
    virtual const Point& getPosition() const = 0;
    virtual const std::string& getColor() const = 0;
    virtual int getValue() const = 0;       // Wartość punktowa
    virtual std::string getNotation() const = 0; // Litera (lub pusta dla pionka)
};

// Klasa abstrakcyjna AbstractPiece
class AbstractPiece : public IChessPiece {
protected:
    Point position;
    std::string color;  // "white" lub "black"
    int value;          // Wartość punktowa (0 dla króla)
    std::string notation; // Litera w notacji angielskiej

public:
    AbstractPiece(const Point& startPosition, const std::string& color, int value, const std::string& notation)
        : position(startPosition), color(color), value(value), notation(notation) {}

    const Point& getPosition() const override {
        return position;
    }

    const std::string& getColor() const override {
        return color;
    }

    int getValue() const override {
        return value;
    }

    std::string getNotation() const override {
        return notation;
    }

    virtual void move(const Point& target) override {
        position = target;
        std::cout << "Moved to " << target.x << ", " << target.y << "\n";
    }

    virtual void capture(const Point& target) override {
        position = target;
        std::cout << "Captured at " << target.x << ", " << target.y << "\n";
    }
};

// Klasa Pawn (dziedziczenie, brak litery w notacji)
class Pawn : public AbstractPiece {
public:
    Pawn(const Point& startPosition, const std::string& color)
        : AbstractPiece(startPosition, color, 1, "") {}

    void promotion() {
        std::cout << "Pawn promoted at " << position.x << ", " << position.y << "\n";
    }

    void move(const Point& target) override {
        AbstractPiece::move(target);
    }
};

// Klasa Queen (dziedziczenie, litera Q, wartość 9)
class Queen : public AbstractPiece {
public:
    Queen(const Point& startPosition, const std::string& color)
        : AbstractPiece(startPosition, color, 9, "Q") {}
};

// Klasa King (dziedziczenie, brak wartości, litera K)
class King : public AbstractPiece {
public:
    King(const Point& startPosition, const std::string& color)
        : AbstractPiece(startPosition, color, 0, "K") {}
};

// Klasa Knight (dziedziczenie, litera N, wartość 3)
class Knight : public AbstractPiece {
public:
    Knight(const Point& startPosition, const std::string& color)
        : AbstractPiece(startPosition, color, 3, "N") {}
};

// Fabryka abstrakcyjna PieceFactory
class PieceFactory {
public:
    // Klasa wewnętrzna InnerPieceFactory
    class InnerPieceFactory {
    public:
        std::unique_ptr<IChessPiece> createPawn(const Point& position, const std::string& color) {
            return std::make_unique<Pawn>(position, color);
        }

        std::unique_ptr<IChessPiece> createQueen(const Point& position, const std::string& color) {
            return std::make_unique<Queen>(position, color);
        }

        std::unique_ptr<IChessPiece> createKing(const Point& position, const std::string& color) {
            return std::make_unique<King>(position, color);
        }

        std::unique_ptr<IChessPiece> createKnight(const Point& position, const std::string& color) {
            return std::make_unique<Knight>(position, color);
        }
    };

    virtual ~PieceFactory() = default;
    virtual std::unique_ptr<IChessPiece> createPiece(const std::string& type, const Point& position, const std::string& color) = 0;
};

// Fabryka konkretna ConcretePieceFactory
class ConcretePieceFactory : public PieceFactory {
public:
    std::unique_ptr<IChessPiece> createPiece(const std::string& type, const Point& position, const std::string& color) override {
        InnerPieceFactory factory;
        if (type == "Pawn") return factory.createPawn(position, color);
        if (type == "Queen") return factory.createQueen(position, color);
        if (type == "King") return factory.createKing(position, color);
        if (type == "Knight") return factory.createKnight(position, color);
        throw std::invalid_argument("Unknown piece type");
    }
};

// Klasa ChessBoard (plansza)
class ChessBoard {
private:
    std::vector<std::vector<std::unique_ptr<IChessPiece>>> grid;

public:
    ChessBoard() : grid(8, std::vector<std::unique_ptr<IChessPiece>>(8, nullptr)) {}

    void placePiece(std::unique_ptr<IChessPiece> piece, const Point& position) {
        grid[position.x][position.y] = std::move(piece);
        std::cout << "Placed piece at " << position.x << ", " << position.y << "\n";
    }

    void movePiece(const Point& from, const Point& to) {
        if (grid[from.x][from.y]) {
            grid[from.x][from.y]->move(to);
            grid[to.x][to.y] = std::move(grid[from.x][from.y]);
        }
    }

    void printBoard() {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (grid[i][j]) {
                    std::cout << grid[i][j]->getNotation() << " ";
                } else {
                    std::cout << ". ";
                }
            }
            std::cout << "\n";
        }
    }
};

// Klasa ChessGame (zarządzanie grą)
class ChessGame {
private:
    ChessBoard board;
    ConcretePieceFactory factory;

public:
    void start() {
        std::cout << "Game started\n";

        board.placePiece(factory.createPiece("Pawn", {1, 1}, "white"), {1, 1});
        board.placePiece(factory.createPiece("Knight", {0, 1}, "white"), {0, 1});
        board.placePiece(factory.createPiece("Queen", {0, 3}, "white"), {0, 3});
        board.placePiece(factory.createPiece("King", {0, 4}, "white"), {0, 4});
    }

    void play() {
        board.movePiece({1, 1}, {2, 1});
    }

    void end() {
        std::cout << "Game ended\n";
    }
};

// Funkcja główna
int main() {
    ChessGame game;

    game.start(); // Rozpoczęcie gry
    game.play();  // Symulacja rozgrywki
    game.end();   // Zakończenie gry

    return 0;
}
```