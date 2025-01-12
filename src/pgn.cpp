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
    // Remove automatic file creation from constructor
}

void PgnNotation::initNewGame()
{
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
        // Only append if this line doesn't already exist in the original content
        if (m_originalContent.find(line) == std::string::npos) {
            m_outFile << line;
            m_outFile.flush();
            m_originalContent += line; // Update the stored content
        }
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

std::vector<std::string> PgnNotation::listSavedGames() {
    namespace fs = std::filesystem;
    std::vector<std::string> gameFiles;
    const std::string folderName = "games";
    
    for (const auto& entry : fs::directory_iterator(folderName)) {
        if (entry.path().extension() == ".txt") {
            gameFiles.push_back(entry.path().filename().string());
        }
    }
    return gameFiles;
}

bool PgnNotation::loadGame(const std::string& filename) {
    if (m_outFile.is_open()) {
        m_outFile.close();
    }
    if (m_inFile.is_open()) {
        m_inFile.close();
    }
    
    m_fileName = "games/" + filename;
    
    // First open input file for reading
    m_inFile.open(m_fileName);
    if (!m_inFile) {
        throw std::runtime_error("Failed to open " + filename + " for reading");
    }
    
    // Read the entire file content into memory
    std::string content((std::istreambuf_iterator<char>(m_inFile)),
                        std::istreambuf_iterator<char>());
    m_inFile.close();
    
    // Store original content
    m_originalContent = content;
    
    // Reopen the file for reading from the beginning
    m_inFile.open(m_fileName);
    
    // Open output file in truncation mode (not append mode)
    m_outFile.open(m_fileName, std::ios::out);
    
    if (!m_inFile || !m_outFile) {
        throw std::runtime_error("Failed to open " + filename);
    }
    
    // Write back the original content
    m_outFile << m_originalContent;
    m_outFile.flush();
    
    return true;
}

std::vector<std::pair<Position, Position>> PgnNotation::parseMovesFromFile(const std::string& line, PieceColor /* currentTurnColor */) {
    std::vector<std::pair<Position, Position>> moves;
    std::string fullLine = line;
    
    // Skip empty lines or malformed lines
    if (fullLine.empty() || fullLine.find('.') == std::string::npos) {
        return moves;
    }
    
    // Extract turn number for validation
    size_t dotPos = fullLine.find('.');
    if (dotPos == std::string::npos) {
        return moves;
    }
    
    // Rest of the line after the turn number
    fullLine = fullLine.substr(dotPos + 1);
    
    // Split into white and black moves
    size_t separatorPos = fullLine.find('|');
    std::string whitePart = fullLine.substr(0, separatorPos);
    std::string blackPart = (separatorPos != std::string::npos) ? 
                            fullLine.substr(separatorPos + 1) : "";
    
    // Trim spaces
    whitePart.erase(0, whitePart.find_first_not_of(" \t"));
    whitePart.erase(whitePart.find_last_not_of(" \t") + 1);
    blackPart.erase(0, blackPart.find_first_not_of(" \t"));
    blackPart.erase(blackPart.find_last_not_of(" \t") + 1);
    
    // Parse moves
    auto parseSingleMove = [](const std::string& part) -> std::pair<Position, Position> {
        size_t arrowPos = part.find("->");
        if (arrowPos == std::string::npos) return {{0,0},{0,0}};
        
        std::string fromStr = part.substr(0, arrowPos);
        std::string toStr = part.substr(arrowPos + 2);
        
        // Clean up the strings
        fromStr.erase(0, fromStr.find_first_not_of(" \t"));
        fromStr.erase(fromStr.find_last_not_of(" \t") + 1);
        toStr.erase(0, toStr.find_first_not_of(" \t"));
        toStr.erase(toStr.find_last_not_of(" \t") + 1);
        
        // Remove piece symbols
        if (std::string("KQRBN").find(fromStr[0]) != std::string::npos) fromStr = fromStr.substr(1);
        if (std::string("KQRBN").find(toStr[0]) != std::string::npos) toStr = toStr.substr(1);
        
        if (fromStr.length() >= 2 && toStr.length() >= 2) {
            return {
                Position(fromStr[0], fromStr[1] - '0'),
                Position(toStr[0], toStr[1] - '0')
            };
        }
        return {{0,0},{0,0}};
    };
    
    // Parse white's move
    auto whiteMove = parseSingleMove(whitePart);
    if (whiteMove.first.col != 0) {
        moves.push_back(whiteMove);
    }
    
    // Parse black's move if it exists
    if (!blackPart.empty()) {
        auto blackMove = parseSingleMove(blackPart);
        if (blackMove.first.col != 0) {
            moves.push_back(blackMove);
        }
    }

    return moves;
}

bool PgnNotation::readNextLine(std::string& line) {
    return std::getline(m_inFile, line).good();
}

void PgnNotation::skipLine() {
    std::string dummy;
    std::getline(m_inFile, dummy);
}

void PgnNotation::writeResult(const std::string& result) {
    if (m_outFile.is_open()) {
        m_outFile << "\nResult: " << result << "\n";
        m_outFile.flush();
    }
}