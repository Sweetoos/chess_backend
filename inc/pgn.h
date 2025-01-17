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

    /// @brief track if the king or rook has moved
    std::unordered_map<std::string, bool> m_pieceMoved;
    std::set<std::string> m_originalPositions;  

    std::string m_originalContent; 
    int m_savedTurn;
    bool m_whiteHasMoved;
    std::string getCurrentDateString() const;  
    std::string getPieceSymbol(PieceType type);

public:
    void setSavedTurn(int turn) { m_savedTurn = turn; }
    void setWhiteHasMoved(bool hasMoved) { m_whiteHasMoved = hasMoved; }
    int getSavedTurn() const { return m_savedTurn; }
    bool getWhiteHasMoved() const { return m_whiteHasMoved; }

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
    std::vector<std::pair<Position, Position>> parseMovesFromFile(const std::string& line);  
    static std::vector<std::string> listSavedGames();
    bool readNextLine(std::string& line);
    void skipLine();
    void writeResult(const std::string& result);  
    void initNewGame();  
    void saveTurnState(int turn, bool whiteHasMoved);  
    bool loadTurnState(int& turn, bool& whiteHasMoved) const;  
    bool hasIncompleteTurn() const;  
    void markPieceMoved(PieceType type, PieceColor color, char col, bool isReplay = false); 
    void clearPieceMovementHistory();
    void initializeOriginalPositions() {
        // those are flags for tagging that kings or rooks moved from their starting positions
        // it's for castling
        m_originalPositions.clear();
        m_originalPositions.insert("e0"); // White king
        m_originalPositions.insert("e1"); // Black king
        m_originalPositions.insert("a0"); // White queenside rook
        m_originalPositions.insert("h0"); // White kingside rook
        m_originalPositions.insert("a1"); // Black queenside rook
        m_originalPositions.insert("h1"); // Black kingside rook
    }
};

#endif

