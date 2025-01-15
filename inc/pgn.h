#ifndef PGN_H
#define PGN_H
#include "classes.h"
#include <tuple>
#include <utility>
#include <string>
#include <fstream>
#include <vector>
#include <array>
#include <unordered_map>
#include <set>

struct MoveInfo {
    PieceType type;
    int fromRow;
    int toRow;
    char fromCol;
    char toCol;
    PieceColor color;
};

class PgnNotation
{
private:
    /// @brief <turn, white move, black move>
    std::vector<std::string> m_turnList; 
    std::string m_fileName;
    std::string m_move;
    std::ofstream m_outFile;
    std::ifstream m_inFile;

    /// @brief <piece, piece color, last move starting position, last move destination>
    MoveInfo m_lastMove;

    /// @brief Track if the king or rook has moved
    std::unordered_map<std::string, bool> m_pieceMoved;
    std::set<std::string> m_originalPositions;  // Track original positions of moved pieces

    std::string m_originalContent; // Add this line
    int m_savedTurn;
    bool m_whiteHasMoved;
    std::string getCurrentDateString() const;  // Add this helper method
    std::string getPieceSymbol(PieceType type);  // Add this declaration

public:
    PgnNotation();
    ~PgnNotation();
    std::string assignFileName();
    void openFile(const std::string &fileName);
    void fileHeader();
    int getCurrentTurn();
    void appendToFile(const std::string &line);
    void writeTurn(const PieceColor &color, const PieceType &type, const char &fromCol,
                   const int &fromRow, const char &toCol, const int &toRow, const std::string &specialMove);
    MoveInfo getLastMove() const;
    bool hasPieceMoved(const PieceType &type, const PieceColor &color, const char &col) const;
    std::string promotionTypeToString(PieceType type) const;  
    bool loadGame(const std::string& filename);
    std::vector<std::pair<Position, Position>> parseMovesFromFile(const std::string& line);  // Remove currentTurnColor parameter
    static std::vector<std::string> listSavedGames();
    bool readNextLine(std::string& line);
    void skipLine();
    void writeResult(const std::string& result);  // Add this method
    void initNewGame();  // Add this declaration
    void saveTurnState(int turn, bool whiteHasMoved);
    bool loadTurnState(int& turn, bool& whiteHasMoved) const;
    bool hasIncompleteTurn() const;  // Keep as const, we're not modifying any members
    void markPieceMoved(PieceType type, PieceColor color, char col, bool isReplay = false); // Keep only this declaration
    void clearPieceMovementHistory();
    void initializeOriginalPositions() {
        m_originalPositions.clear();
        // Add initial positions for kings and rooks
        m_originalPositions.insert("e0"); // White king
        m_originalPositions.insert("e1"); // Black king
        m_originalPositions.insert("a0"); // White queenside rook
        m_originalPositions.insert("h0"); // White kingside rook
        m_originalPositions.insert("a1"); // Black queenside rook
        m_originalPositions.insert("h1"); // Black kingside rook
    }
};

#endif

