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
    std::string fileName = "games/" + dateStream.str() + ".txt";
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

void PgnNotation::writeTurn(const PieceColor &color, const PieceType &type, const char &fromCol,
                            const int &fromRow, const char &toCol, const int &toRow, const std::string &specialMove)
{
    try
    {
        std::string pieceSymbol;
        switch (type)
        {
        case PieceType::KING:   pieceSymbol = "K"; break;
        case PieceType::QUEEN:  pieceSymbol = "Q"; break;
        case PieceType::ROOK:   pieceSymbol = "R"; break;
        case PieceType::BISHOP: pieceSymbol = "B"; break;
        case PieceType::KNIGHT: pieceSymbol = "N"; break;
        case PieceType::PAWN:   pieceSymbol = ""; break;
        }

        std::string move;
        if (!specialMove.empty()) {
            // For castling or promotion
            move = specialMove;
        }
        else {
            move = pieceSymbol + std::string(1, fromCol) + std::to_string(fromRow) + 
                  " -> " + pieceSymbol + std::string(1, toCol) + std::to_string(toRow);
        }

        if (color == PieceColor::WHITE) {
            appendToFile(std::to_string(getCurrentTurn()) + ". " + move + " | ");
        }
        else {
            appendToFile(move + "\n");
        }

        m_lastMove = {type, fromRow, toRow, fromCol, toCol, color};
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error in writeTurn: " << e.what() << "\n";
    }
}

MoveInfo PgnNotation::getLastMove() const
{
    return m_lastMove;
}

bool PgnNotation::hasPieceMoved(const PieceType &type, const PieceColor &color, const char &col) const
{
    if (type != PieceType::KING && type != PieceType::ROOK)
    {
        return false;
    }
    std::string key = std::string(1, col) + std::to_string(static_cast<int>(color));
    auto it = m_pieceMoved.find(key);
    if (it != m_pieceMoved.end())
    {
        return it->second;
    }
    return false;
}

std::string PgnNotation::promotionTypeToString(PieceType type) const
{
    switch (type)
    {
    case PieceType::QUEEN:
        return "Q";
    case PieceType::ROOK:
        return "R";
    case PieceType::BISHOP:
        return "B";
    case PieceType::KNIGHT:
        return "N";
    default:
        return "";
    }
}