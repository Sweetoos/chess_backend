#ifndef PGN_H
#define PGN_H
#include "classes.h"
#include <tuple>
#include <utility>
#include <string>
#include <fstream>
#include <vector>
#include <array>

struct DisambiguationInfo
{
    bool needed;
    bool needsFile;
    bool needsRank;
    DisambiguationInfo(bool n = false, bool f = false, bool r = false) 
        : needed(n), needsFile(f), needsRank(r) {}
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
    std::tuple<PieceType, PieceColor, std::string, std::string> m_lastMove;

public:
    PgnNotation();
    ~PgnNotation();
    std::string assignFileName();
    void openFile(const std::string &fileName);
    void fileHeader();
    int getCurrentTurn();
    //void writeTurnToFile();
    void appendToFile(const std::string &line);
    void writeTurn(const PieceColor &color, const PieceType &type, const char &fromCol, 
                  const int &fromRow, const char &toCol, const int &toRow, 
                  const MoveType &moveType, const Board& board,
                  const PieceType &promotionType = PieceType::QUEEN);
    DisambiguationInfo needsDisambiguation(const Board& board, const Position& from, 
                                           const Position& to, const PieceType& type, 
                                           const PieceColor& color) const;
};

#endif

