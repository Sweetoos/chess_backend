#include "classes.h"
#include <ctime>
#include <sstream>
#include "pgn.h"
#include <filesystem>

PgnNotation::PgnNotation()
{
    namespace fs = std::filesystem;
    const std::string folderName = "games";
    if (!fs::exists(folderName))
    {
        if (fs::create_directory(folderName))
            std::cout << "folder " << folderName << " created" << '\n';
        else
            std::cerr << "failed to create " << folderName << " folder" << '\n';
    }
    m_fileName = assignFileName();
    openFile(m_fileName);
    fileHeader();
}

PgnNotation::~PgnNotation()
{
    m_outFile.close();
}

std::string PgnNotation::assignFileName()
{
    std::time_t currentTime = std::time(nullptr);
    std::tm *localTime = std::localtime(&currentTime);
    std::ostringstream dateStream;
    dateStream << std::put_time(localTime, "%Y.%m.%d-%H:%M:%S");
    std::string fileName = "games/" + dateStream.str() + ".pgn";
    return fileName;
}

void PgnNotation::openFile(const std::string &fileName)
{
    bool append = false;
    if (m_outFile.is_open())
        m_outFile.close();
    std::ios::openmode mode = append ? std::ios::app : std::ios::out;
    m_outFile.open(fileName, mode);
    if (!m_outFile)
        throw "failed to open " + fileName + " file";
}

void PgnNotation::fileHeader()
{
    std::time_t currentTime = std::time(nullptr);
    std::tm *localTime = std::localtime(&currentTime);
    std::ostringstream dateStream;
    dateStream << std::put_time(localTime, "%Y.%m.%d");
    std::string gameDate = dateStream.str();
    if (m_outFile.is_open())
        m_outFile << "[Date \"" << gameDate << "\"]\n";
}

int PgnNotation::getCurrentTurn()
{
    return GameManager::turn;
}

void PgnNotation::appendToFile(const std::string &line)
{
    if (m_outFile.is_open())
    {
        m_outFile << line;
        m_outFile.flush();
    }
    else
    {
        throw std::runtime_error("File is not open for writing.");
    }
}

// Modify the disambiguation method to return more detailed information


DisambiguationInfo PgnNotation::needsDisambiguation(const Board& board, const Position& from,
    const Position& to, const PieceType& type, const PieceColor& color) const
{
    DisambiguationInfo info;
    
    // Check each piece of the same type and color that could move to the target
    for (int row = 1; row <= 8; row++) {
        for (char col = 'a'; col <= 'h'; col++) {
            // Skip the moving piece itself
            if (col == from.col && row == from.row) {
                continue;
            }
            
            Position otherPos(col, row);
            PieceInterface* otherPiece = board.getPieceAt(otherPos);
            
            // If we found another piece of the same type and color
            if (otherPiece && otherPiece->getType() == type && 
                otherPiece->getColor() == color) {
                
                // Check if it can also move to the target square
                MoveManager mm;
                if (mm.isValidMove(otherPos, to, board, *otherPiece)) {
                    info.needed = true;
                    
                    // If pieces are on the same file, we must disambiguate by rank
                    if (otherPos.col == from.col) {
                        info.needsRank = true;
                    }
                    // If pieces are on the same rank, we must disambiguate by file
                    if (otherPos.row == from.row) {
                        info.needsFile = true;
                    }
                    // If neither, prefer file disambiguation as per chess notation standards
                    if (!info.needsFile && !info.needsRank) {
                        info.needsFile = true;
                    }
                }
            }
        }
    }
    
    return info;
}

void PgnNotation::writeTurn(const PieceColor &color, const PieceType &type, 
    const char &fromCol, const int &fromRow, const char &toCol, const int &toRow, 
    const MoveType &moveType, const Board& board, const PieceType &promotionType)
{
    std::string move;
    std::string pieceSymbol;
    
    switch(type) {
        case PieceType::KING:   pieceSymbol = "K"; break;
        case PieceType::QUEEN:  pieceSymbol = "Q"; break;
        case PieceType::ROOK:   pieceSymbol = "R"; break;
        case PieceType::BISHOP: pieceSymbol = "B"; break;
        case PieceType::KNIGHT: pieceSymbol = "N"; break;
        case PieceType::PAWN:   pieceSymbol = ""; break;
    }

    std::string disambiguation = "";
    if (type != PieceType::PAWN && type != PieceType::KING) {
        auto disambig = needsDisambiguation(board, Position(fromCol, fromRow), 
                                          Position(toCol, toRow), type, color);
        if (disambig.needed) {
            // Always include file disambiguation if needed
            if (disambig.needsFile) {
                disambiguation = std::string(1, fromCol);
            }
            // Add rank disambiguation if needed
            if (disambig.needsRank) {
                disambiguation += std::to_string(fromRow);
            }
        }
    }

    switch (moveType)
    {
    case MoveType::MOVE:
        move = pieceSymbol + disambiguation + std::string(1, toCol) + std::to_string(toRow);
        break;
    case MoveType::CAPTURE:
        if (type == PieceType::PAWN) {
            move = std::string(1, fromCol) + "x" + std::string(1, toCol) + std::to_string(toRow);
        } else {
            move = pieceSymbol + disambiguation + "x" + std::string(1, toCol) + std::to_string(toRow);
        }
        break;
    case MoveType::CASTLE:
        move = (toCol == 'g') ? "O-O" : "O-O-O";
        break;
    case MoveType::CHECK:
        move = pieceSymbol + std::string(1, toCol) + std::to_string(toRow) + "+";
        break;
    case MoveType::MATE:
        move = pieceSymbol + std::string(1, toCol) + std::to_string(toRow) + "#";
        break;
    case MoveType::PROMOTION:
        char promotionPiece;
        switch(promotionType) {
            case PieceType::QUEEN:  promotionPiece = 'Q'; break;
            case PieceType::ROOK:   promotionPiece = 'R'; break;
            case PieceType::BISHOP: promotionPiece = 'B'; break;
            case PieceType::KNIGHT: promotionPiece = 'N'; break;
            default: promotionPiece = 'Q';
        }
        move = std::string(1, toCol) + std::to_string(toRow) + "=" + promotionPiece;
        break;
    }

    if (color == PieceColor::WHITE) {
        std::string turnStr = std::to_string(getCurrentTurn()) + ". ";
        appendToFile(turnStr + move + " ");
    } else {
        appendToFile(move + " ");
    }
}
