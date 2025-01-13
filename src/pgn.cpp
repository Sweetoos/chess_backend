#include "classes.h"
#include <ctime>
#include <sstream>
#include <set>  // Add this include
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
    fileHeader();  // This will write the date header
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
    if (!m_outFile.is_open()) {
        throw std::runtime_error("File is not open for writing.");
    }

    // Clean up the content before appending
    if (!m_originalContent.empty() && line[0] != '[') {
        // If the last character isn't a newline and this is a new turn, add one
        if (m_originalContent.back() != '\n' && std::isdigit(line[0])) {
            m_outFile << '\n';
            m_originalContent += '\n';
        }
    }

    m_outFile << line;
    m_outFile.flush();
    m_originalContent += line;
}

void PgnNotation::writeTurn(const PieceColor &color, const PieceType &type, const char &fromCol,
                            const int &fromRow, const char &toCol, const int &toRow, const std::string &specialMove)
{
    try {
        // Ensure header exists at the beginning
        if (m_originalContent.empty()) {
            fileHeader();
            m_originalContent = "[Date \"" + getCurrentDateString() + "\"]\n\n";  // Add extra newline after header
        }

        // Format the new move
        std::string pieceSymbol = getPieceSymbol(type);
        std::string move = specialMove.empty() ? 
            pieceSymbol + std::string(1, fromCol) + std::to_string(fromRow) + 
            " -> " + pieceSymbol + std::string(1, toCol) + std::to_string(toRow) :
            specialMove;

        std::string output;
        if (color == PieceColor::WHITE) {
            output = std::to_string(getCurrentTurn()) + ". " + move + " | ";  // Space already added after |
        } else {
            // Add space after the last | when writing black's move
            auto lastPipePos = m_originalContent.rfind("|");
            if (lastPipePos != std::string::npos && 
                lastPipePos + 1 < m_originalContent.length() && 
                m_originalContent[lastPipePos + 1] != ' ') {
                // Insert space after pipe if it's missing
                m_originalContent.insert(lastPipePos + 1, " ");
                
                // Update file with the space
                m_outFile.close();
                m_outFile.open(m_fileName, std::ios::out | std::ios::trunc);
                m_outFile << m_originalContent;
                m_outFile.flush();
            }
            output = move + "\n";
        }

        // Parse existing content and rebuild with proper formatting
        std::map<int, std::string> turns;
        std::istringstream iss(m_originalContent);
        std::string line;
        std::string header;

        // First, get the header
        while (std::getline(iss, line)) {
            if (line.starts_with("[Date")) {
                header = line;
                break;
            }
        }

        // Then process the moves
        while (std::getline(iss, line)) {
            if (std::isdigit(line[0])) {
                int turnNum = std::stoi(line.substr(0, line.find('.')));
                // Ensure there's a space after each |
                size_t pipePos = line.find("|");
                if (pipePos != std::string::npos && pipePos + 1 < line.length() && line[pipePos + 1] != ' ') {
                    line.insert(pipePos + 1, " ");
                }
                turns[turnNum] = line;
            }
        }

        // Update or add the current turn
        if (color == PieceColor::WHITE) {
            turns[getCurrentTurn()] = output.substr(0, output.length() - 1); // Remove trailing space
        } else {
            auto it = turns.find(getCurrentTurn());
            if (it != turns.end()) {
                it->second += output;
            }
        }

        // Rebuild content
        std::string newContent = header + "\n";
        for (const auto& [turn, moveLine] : turns) {
            newContent += moveLine + (moveLine.back() != '\n' ? "\n" : "");
        }

        // Write back to file
        m_outFile.close();
        m_outFile.open(m_fileName, std::ios::out | std::ios::trunc);
        m_outFile << newContent;
        m_outFile.flush();
        
        m_originalContent = newContent;
        m_lastMove = {type, fromRow, toRow, fromCol, toCol, color};
    }
    catch (const std::exception &e) {
        std::cerr << "Error in writeTurn: " << e.what() << "\n";
    }
}

std::string PgnNotation::getCurrentDateString() const {
    std::time_t currentTime = std::time(nullptr);
    std::tm *localTime = std::localtime(&currentTime);
    std::ostringstream dateStream;
    dateStream << std::put_time(localTime, "%Y.%m.%d");
    return dateStream.str();
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
    if (m_outFile.is_open()) m_outFile.close();
    if (m_inFile.is_open()) m_inFile.close();
    
    m_fileName = "games/" + filename;
    std::cout << "DEBUG: Loading game from file: " << m_fileName << "\n";
    
    // Read file content
    std::ifstream inFile(m_fileName);
    if (!inFile) {
        throw std::runtime_error("Failed to open " + filename + " for reading");
    }
    
    // Process and clean the content
    std::string line;
    std::string header;
    std::map<int, std::string> moveLines; // Use map to automatically handle duplicates
    std::cout << "DEBUG: Starting to read file content\n";
    
    while (std::getline(inFile, line)) {
        std::cout << "DEBUG: Read line: '" << line << "'\n";
        
        // Skip empty lines
        if (line.empty()) continue;

        // Handle header
        if (line.starts_with("[Date")) {
            header = line;
            std::cout << "DEBUG: Found header: " << header << "\n";
            continue;
        }

        // Skip metadata lines
        if (line.starts_with("[") || line.starts_with("#")) {
            std::cout << "DEBUG: Skipping metadata line\n";
            continue;
        }

        // Process move lines
        if (std::isdigit(line[0])) {
            size_t turnNumber = std::stoul(line.substr(0, line.find('.')));
            moveLines[turnNumber] = line; // Map automatically replaces duplicates
            std::cout << "DEBUG: Storing move for turn " << turnNumber << ": " << line << "\n";
        }
    }
    inFile.close();

    // Create clean content
    std::string cleanContent = header + "\n";
    for (const auto& [turn, moveLine] : moveLines) {
        cleanContent += moveLine + "\n";
    }

    std::cout << "DEBUG: Final cleaned content:\n" << cleanContent << "END CONTENT\n";

    // Store cleaned content
    m_originalContent = cleanContent;
    
    // Reopen file for writing with cleaned content
    m_outFile.open(m_fileName, std::ios::out | std::ios::trunc);
    if (!m_outFile) {
        throw std::runtime_error("Failed to open " + filename + " for writing");
    }
    m_outFile << cleanContent;
    m_outFile.flush();
    
    // Open for reading
    m_inFile.open(m_fileName);
    if (!m_inFile) {
        throw std::runtime_error("Failed to open " + filename + " for reading");
    }
    
    return true;
}

std::vector<std::pair<Position, Position>> PgnNotation::parseMovesFromFile(const std::string& line, PieceColor /* currentTurnColor */) {
    std::cout << "DEBUG: Starting to parse moves from line: '" << line << "'\n";
    std::vector<std::pair<Position, Position>> moves;
    
    if (line.empty() || line[0] == '[' || line[0] == '#') {
        std::cout << "DEBUG: Skipping non-move line\n";
        return moves;
    }
    
    size_t dotPos = line.find('.');
    if (dotPos == std::string::npos) {
        std::cout << "DEBUG: No turn number found\n";
        return moves;
    }
    
    std::string movesStr = line.substr(dotPos + 1);
    std::cout << "DEBUG: Processing moves: '" << movesStr << "'\n";
    
    auto processMove = [](const std::string& moveStr) -> std::pair<Position, Position> {
        std::cout << "DEBUG: Processing move: '" << moveStr << "'\n";
        
        // Skip empty or special moves
        if (moveStr.empty() || moveStr.find("O-O") != std::string::npos) {
            return std::make_pair(Position('\0', 0), Position('\0', 0));
        }
        
        size_t arrowPos = moveStr.find("->");
        if (arrowPos == std::string::npos) {
            std::cout << "DEBUG: No arrow found\n";
            return std::make_pair(Position('\0', 0), Position('\0', 0));
        }
        
        std::string fromStr = moveStr.substr(0, arrowPos);
        std::string toStr = moveStr.substr(arrowPos + 2);
        
        // Clean up strings
        fromStr.erase(0, fromStr.find_first_not_of(" \t\r\n"));
        fromStr.erase(fromStr.find_last_not_of(" \t\r\n") + 1);
        toStr.erase(0, toStr.find_first_not_of(" \t\r\n"));
        toStr.erase(toStr.find_last_not_of(" \t\r\n") + 1);
        
        // Remove piece symbols
        if (!fromStr.empty() && std::string("KQRBN").find(fromStr[0]) != std::string::npos) {
            fromStr = fromStr.substr(1);
        }
        if (!toStr.empty() && std::string("KQRBN").find(toStr[0]) != std::string::npos) {
            toStr = toStr.substr(1);
        }
        
        std::cout << "DEBUG: Cleaned moves - From: '" << fromStr << "', To: '" << toStr << "'\n";
        
        if (fromStr.length() >= 2 && toStr.length() >= 2) {
            return std::make_pair(
                Position(fromStr[0], fromStr[1] - '0'),
                Position(toStr[0], toStr[1] - '0')
            );
        }
        
        return std::make_pair(Position('\0', 0), Position('\0', 0));
    };
    
    // Split and process moves
    size_t pipePos = movesStr.find('|');
    if (pipePos != std::string::npos) {
        // Process white's move
        auto whiteMove = processMove(movesStr.substr(0, pipePos));
        if (whiteMove.first.col != '\0') {
            moves.push_back(whiteMove);
        }
        
        // Process black's move
        auto blackMove = processMove(movesStr.substr(pipePos + 1));
        if (blackMove.first.col != '\0') {
            moves.push_back(blackMove);
        }
    }
    
    std::cout << "DEBUG: Parsed " << moves.size() << " moves\n";
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

void PgnNotation::saveTurnState(int turn, bool whiteHasMoved) {
    m_savedTurn = turn;
    m_whiteHasMoved = whiteHasMoved;
    
    // Ensure we're writing to a clean state
    m_outFile.close();
    
    // Clean up the content first
    std::string content;
    std::set<std::string> uniqueMoves;
    std::istringstream iss(m_originalContent);
    std::string line;

    // First, collect unique moves and header
    while (std::getline(iss, line)) {
        if (line.starts_with("[Date")) {
            content = line + "\n";
            continue;
        }
        if (line.empty() || line.starts_with("[") || line.starts_with("#")) {
            continue;
        }
        if (std::isdigit(line[0]) && uniqueMoves.insert(line).second) {
            content += line + "\n";
        }
    }
    
    // Remove any trailing whitespace
    while (!content.empty() && std::isspace(content.back())) {
        content.pop_back();
    }
    
    // Add the new TurnState
    content += "\n[TurnState \"" + std::to_string(turn) + "," + 
               (whiteHasMoved ? "1" : "0") + "\"]";
    
    // Write back the cleaned content
    m_outFile.open(m_fileName, std::ios::out | std::ios::trunc);
    if (!m_outFile) {
        throw std::runtime_error("Failed to open file for writing");
    }
    
    m_outFile << content;
    m_outFile.flush();
    
    // Update original content
    m_originalContent = content;
}

bool PgnNotation::loadTurnState(int& turn, bool& whiteHasMoved) const {
    // Look for the turn state in the original content
    size_t pos = m_originalContent.rfind("[TurnState \"");
    if (pos != std::string::npos) {
        std::string stateLine = m_originalContent.substr(pos);
        size_t comma = stateLine.find(',');
        size_t quote = stateLine.find('\"');
        if (comma != std::string::npos && quote != std::string::npos) {
            try {
                turn = std::stoi(stateLine.substr(quote + 1, comma - (quote + 1)));
                whiteHasMoved = (stateLine[comma + 1] == '1');
                return true;
            } catch (...) {
                // Parse error, ignore
            }
        }
    }
    return false;
}

// Replace hasIncompleteTurn implementation:
bool PgnNotation::hasIncompleteTurn() const {
    // We'll go line by line from the end of the file
    std::istringstream iss(m_originalContent);
    std::string lastValidLine;
    std::string line;
    
    while (std::getline(iss, line)) {
        // Skip empty lines and metadata
        if (line.empty() || line[0] == '[' || line.starts_with("#") || line.starts_with("Result")) {
            continue;
        }
        lastValidLine = line;
    }
    
    std::cout << "DEBUG: Final line found: '" << lastValidLine << "'\n";
    
    // Check if line contains a turn number
    size_t dotPos = lastValidLine.find('.');
    if (dotPos == std::string::npos) {
        std::cout << "DEBUG: No turn number found\n";
        return false;
    }
    
    try {
        int turnNum = std::stoi(lastValidLine.substr(0, dotPos));
        std::cout << "DEBUG: Turn number: " << turnNum << "\n";
        
        // Look for white's move
        size_t arrowPos = lastValidLine.find("->");
        if (arrowPos == std::string::npos) {
            std::cout << "DEBUG: No move found\n";
            return false;
        }
        
        // Look for separator and check what comes after it
        size_t pipePos = lastValidLine.find("|");
        std::cout << "DEBUG: Pipe position: " << (pipePos == std::string::npos ? "not found" : std::to_string(pipePos)) << "\n";
        
        if (pipePos != std::string::npos) {
            // Check what comes after the pipe
            std::string afterPipe = lastValidLine.substr(pipePos + 1);
            // Trim whitespace
            afterPipe.erase(0, afterPipe.find_first_not_of(" \t\r\n"));
            afterPipe.erase(afterPipe.find_last_not_of(" \t\r\n") + 1);
            
            std::cout << "DEBUG: Content after pipe: '" << afterPipe << "'\n";
            
            // If there's nothing meaningful after the pipe, it's an incomplete turn
            return afterPipe.empty() || afterPipe.find("->") == std::string::npos;
        }
        
        return true; // No pipe found but move exists = incomplete turn
        
    } catch (...) {
        std::cout << "DEBUG: Failed to parse turn number\n";
        return false;
    }
}

// Add this helper method
std::string PgnNotation::getPieceSymbol(PieceType type) {
    switch (type) {
        case PieceType::KING:   return "K";
        case PieceType::QUEEN:  return "Q";
        case PieceType::ROOK:   return "R";
        case PieceType::BISHOP: return "B";
        case PieceType::KNIGHT: return "N";
        case PieceType::PAWN:   return "";
        default:                return "";
    }
}