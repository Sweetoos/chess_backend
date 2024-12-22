#ifndef PGN_H
#define PGN_H
#include "classes.h"
#include <tuple>
#include <utility>
#include <string>
#include <fstream>
#include <vector>
#include <array>

class PgnNotation
{
private:
    /// @brief <turn, white move, black move>
    std::vector<std::string> m_turnList;
    std::string m_fileName;
    std::string m_move;
    std::ofstream m_outFile;
    bool m_saveOption;

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
    void writeTurn(const PieceColor &color, const char &fromCol, const int &fromRow, const char &toCol, const int &toRow, const MoveType &moveType);
};

#endif

