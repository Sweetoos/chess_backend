```cpp
class GameManager
{
private:
    Board m_board;
    PieceColor m_currentTurn = PieceColor::WHITE; // Zaczynają białe

public:
    void movePiece(const Position &from, const Position &to);
    void displayBoard() const { m_board.display(); }
    PieceColor getCurrentTurn() const { return m_currentTurn; }
};

void GameManager::movePiece(const Position &from, const Position &to)
{
    PieceInterface *piece = m_board.getPieceAt(from);

    if (!piece)
    {
        std::cout << "No piece at " << from.col << from.row << "\n";
        return;
    }

    if (piece->getColor() != m_currentTurn)
    {
        std::cout << "It's not " << (m_currentTurn == PieceColor::WHITE ? "Black" : "White") << "'s turn\n";
        return;
    }

    if (!piece->isValidMove(from, to, m_board))
    {
        std::cout << "Invalid move for " << piece->getFullSymbol() << "\n";
        return;
    }

    PieceInterface *targetPiece = m_board.getPieceAt(to);
    if (targetPiece)
    {
        if (targetPiece->getColor() == piece->getColor())
        {
            std::cout << "Cannot capture your own piece\n";
            return;
        }
        std::cout << "Captured " << targetPiece->getFullSymbol() << "\n";
        m_board.removePiece(to);
    }

    m_board.removePiece(from);
    piece->move(to);
    m_board.putPiece(piece);
    std::cout << "Moved " << piece->getFullSymbol() << " to " << to.col << to.row << "\n";

    // Zmiana tury
    m_currentTurn = (m_currentTurn == PieceColor::WHITE) ? PieceColor::BLACK : PieceColor::WHITE;
}

void Chess::run()
{
    m_gm.displayBoard();
    while (true)
    {
        char fromCol, toCol;
        int fromRow, toRow;

        std::cout << "Current turn: " 
                  << (m_gm.getCurrentTurn() == PieceColor::WHITE ? "White" : "Black") 
                  << "\n";
        std::cout << "Enter move (e.g., e2 e4): ";
        std::cin >> fromCol >> fromRow >> toCol >> toRow;

        try
        {
            Position from(fromCol, fromRow);
            Position to(toCol, toRow);
            m_gm.movePiece(from, to);
            m_gm.displayBoard();
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }
}

//prev

PieceInterface *Board::getPieceAt(const Position &position) const
{
    int col = toIndex(position.col);
    int row = position.row - 1;

    if (col < 0 || col >= 8 || row < 0 || row >= 8)
        throw std::out_of_range("Position out of bounds");

    return m_grid[col][row].getPiece();
}

void Chess::run()
{
    m_gm.displayBoard();
    while (true)
    {
        char fromCol, toCol;
        int fromRow, toRow;

        std::cout << "Enter move (e.g., e2 e4): ";
        std::cin >> fromCol >> fromRow >> toCol >> toRow;

        try
        {
            Position from(fromCol, fromRow);
            Position to(toCol, toRow);
            m_gm.movePiece(from, to);
            m_gm.displayBoard();
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }
}

void GameManager::movePiece(const Position &from, const Position &to)
{
    PieceInterface *piece = m_board.getPieceAt(from);

    if (!piece)
    {
        std::cout << "No piece at " << from.col << from.row << "\n";
        return;
    }

    if (!piece->isValidMove(from, to, m_board))
    {
        std::cout << "Invalid move for " << piece->getFullSymbol() << "\n";
        return;
    }

    PieceInterface *targetPiece = m_board.getPieceAt(to);
    if (targetPiece)
    {
        if (targetPiece->getColor() == piece->getColor())
        {
            std::cout << "Cannot capture your own piece\n";
            return;
        }
        std::cout << "Captured " << targetPiece->getFullSymbol() << "\n";
        m_board.removePiece(to);
    }

    m_board.removePiece(from);
    piece->move(to);
    m_board.putPiece(piece);
    std::cout << "Moved " << piece->getFullSymbol() << " to " << to.col << to.row << "\n";
}

bool Rook::isValidMove(const Position &from, const Position &to, const Board &board) const
{
    if (from.col != to.col && from.row != to.row)
        return false;

    int colDir = (from.col == to.col) ? 0 : (to.col > from.col ? 1 : -1);
    int rowDir = (from.row == to.row) ? 0 : (to.row > from.row ? 1 : -1);

    char col = from.col + colDir;
    int row = from.row + rowDir;

    while (col != to.col || row != to.row)
    {
        if (board.getPieceAt(Position(col, row)) != nullptr)
            return false;

        col += colDir;
        row += rowDir;
    }

    PieceInterface *targetPiece = board.getPieceAt(to);
    return targetPiece == nullptr || targetPiece->getColor() != m_color;
}

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

    // Nowa metoda
    virtual bool isValidMove(const Position &from, const Position &to, const Board &board) const = 0;

    const std::string getFullSymbol() const
    {
        return (m_color == PieceColor::WHITE ? "W" : "B") + m_symbol;
    }
};


bool Pawn::isValidMove(const Position &from, const Position &to, const Board &board) const {
    int direction = (m_color == PieceColor::WHITE) ? 1 : -1; // Białe idą w górę, czarne w dół
    int rowDiff = to.row - from.row;
    int colDiff = abs(to.col - from.col);

    if (colDiff == 0) { // Ruch w linii prostej
        if (rowDiff == direction && board.getPieceAt(to) == nullptr) {
            return true; // Jeden krok do przodu
        }
        if (rowDiff == 2 * direction && 
            board.getPieceAt(to) == nullptr &&
            board.getPieceAt({from.col, from.row + direction}) == nullptr &&
            ((m_color == PieceColor::WHITE && from.row == 2) || 
            (m_color == PieceColor::BLACK && from.row == 7))) {
            return true; // Pierwszy ruch o dwa pola
        }
    } else if (colDiff == 1 && rowDiff == direction) { // Bicie po skosie
        PieceInterface *target = board.getPieceAt(to);
        if (target != nullptr && target->getColor() != m_color) {
            return true;
        }
    }
    return false;
}


void Chess::run()
{
    m_gm.displayBoard();
    while (true)
    {
        std::string fromTo;

        std::cout << "Current turn: " 
                  << (m_gm.getCurrentTurn() == PieceColor::WHITE ? "White" : "Black") 
                  << "\n";

        try
        {
            // Podaj ruch jako np. "e2e4"
            std::cout << "Enter your move (e.g., e2e4): ";
            std::cin >> fromTo;

            if (fromTo.length() != 4)
                throw std::invalid_argument("Invalid move format. Use format like 'e2e4'.");

            char fromCol = fromTo[0];
            int fromRow = fromTo[1] - '0';
            char toCol = fromTo[2];
            int toRow = fromTo[3] - '0';

            Position from(fromCol, fromRow);
            Position to(toCol, toRow);

            // Próba wykonania ruchu
            m_gm.movePiece(from, to);
            m_gm.displayBoard();
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }
}






//lalalala

#include "move_validator.h"
#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include <cmath>

bool MoveValidator::isValidMove(const Position& from, const Position& to, const Board& board, const PieceInterface& piece) const {
    if (dynamic_cast<const Pawn*>(&piece)) {
        return isValidPawnMove(from, to, board, piece);
    } else if (dynamic_cast<const Rook*>(&piece)) {
        return isValidRookMove(from, to, board);
    } else if (dynamic_cast<const Knight*>(&piece)) {
        return isValidKnightMove(from, to);
    } else if (dynamic_cast<const Bishop*>(&piece)) {
        return isValidBishopMove(from, to, board);
    } else if (dynamic_cast<const Queen*>(&piece)) {
        return isValidQueenMove(from, to, board);
    } else if (dynamic_cast<const King*>(&piece)) {
        return isValidKingMove(from, to, board);
    }
    return false;
}

bool MoveValidator::isValidPawnMove(const Position& from, const Position& to, const Board& board, const PieceInterface& piece) const {
    int direction = piece.isWhite() ? 1 : -1;
    int startRow = piece.isWhite() ? 1 : 6;

    // Standard forward move
    if (from.y == to.y && to.x == from.x + direction) {
        return !board.getPieceAt(to); // Target square must be empty
    }

    // Double forward move from starting position
    if (from.y == to.y && from.x == startRow && to.x == from.x + 2 * direction) {
        return !board.getPieceAt(to) && isPathClear(from, to, board);
    }

    // Diagonal capture
    if (std::abs(to.y - from.y) == 1 && to.x == from.x + direction) {
        const PieceInterface* targetPiece = board.getPieceAt(to);
        return targetPiece && targetPiece->isWhite() != piece.isWhite();
    }

    return false;
}

bool MoveValidator::isValidRookMove(const Position& from, const Position& to, const Board& board) const {
    if (from.x != to.x && from.y != to.y) return false; // Must move in straight lines
    return isPathClear(from, to, board);
}

bool MoveValidator::isValidKnightMove(const Position& from, const Position& to) const {
    int dx = std::abs(from.x - to.x);
    int dy = std::abs(from.y - to.y);
    return (dx == 2 && dy == 1) || (dx == 1 && dy == 2); // "L"-shaped moves
}

bool MoveValidator::isValidBishopMove(const Position& from, const Position& to, const Board& board) const {
    if (std::abs(from.x - to.x) != std::abs(from.y - to.y)) return false; // Must move diagonally
    return isPathClear(from, to, board);
}

bool MoveValidator::isValidQueenMove(const Position& from, const Position& to, const Board& board) const {
    if (from.x == to.x || from.y == to.y) {
        return isPathClear(from, to, board); // Rook-like move
    }
    if (std::abs(from.x - to.x) == std::abs(from.y - to.y)) {
        return isPathClear(from, to, board); // Bishop-like move
    }
    return false;
}

bool MoveValidator::isValidKingMove(const Position& from, const Position& to, const Board& board) const {
    int dx = std::abs(from.x - to.x);
    int dy = std::abs(from.y - to.y);

    // King moves one square in any direction
    if (dx <= 1 && dy <= 1) {
        return true;
    }

    // Additional logic for castling (if implemented) would go here

    return false;
}

bool MoveValidator::isPathClear(const Position& from, const Position& to, const Board& board) const {
    int dx = to.x - from.x;
    int dy = to.y - from.y;

    int stepX = (dx == 0) ? 0 : (dx > 0 ? 1 : -1);
    int stepY = (dy == 0) ? 0 : (dy > 0 ? 1 : -1);

    int currentX = from.x + stepX;
    int currentY = from.y + stepY;

    while (currentX != to.x || currentY != to.y) {
        if (board.getPieceAt(Position(currentX, currentY))) {
            return false; // Path is blocked
        }
        currentX += stepX;
        currentY += stepY;
    }

    return true; // Path is clear
}
