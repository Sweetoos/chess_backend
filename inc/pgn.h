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

    /// @brief <piece, piece color, last move starting position, last move destination>
    MoveInfo m_lastMove;

    /// @brief Track if the king or rook has moved
    std::unordered_map<std::string, bool> m_pieceMoved;

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
};

#endif

