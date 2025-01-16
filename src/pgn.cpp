#include "classes.h"
#include <ctime>
#include <sstream>
#include <set>
#include "pgn.h"
#include <filesystem>

PgnNotation::PgnNotation() : m_savedTurn(1), m_whiteHasMoved(false)
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
    if (!m_outFile.is_open())
    {
        throw std::runtime_error("file is not open for writing.");
    }

    if (!m_originalContent.empty() && line[0] != '[')
    {
        if (m_originalContent.back() != '\n' && std::isdigit(line[0]))
        {
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
    try
    {
        if (m_originalContent.empty())
        {
            fileHeader();
            m_originalContent = "[Date \"" + getCurrentDateString() + "\"]\n\n";
        }

        std::string pieceSymbol = getPieceSymbol(type);
        std::string move = specialMove.empty() ? pieceSymbol + std::string(1, fromCol) + std::to_string(fromRow) + " -> " + pieceSymbol + std::string(1, toCol) + std::to_string(toRow) : specialMove;

        std::string output;
        if (color == PieceColor::WHITE)
        {
            output = std::to_string(getCurrentTurn()) + ". " + move + " | ";
        }
        else
        {
            auto lastPipePos = m_originalContent.rfind("|");
            if (lastPipePos != std::string::npos &&
                lastPipePos + 1 < m_originalContent.length() &&
                m_originalContent[lastPipePos + 1] != ' ')
            {
                m_originalContent.insert(lastPipePos + 1, " ");

                m_outFile.close();
                m_outFile.open(m_fileName, std::ios::out | std::ios::trunc);
                m_outFile << m_originalContent;
                m_outFile.flush();
            }
            output = move + "\n";
        }

        std::map<int, std::string> turns;
        std::istringstream iss(m_originalContent);
        std::string line;
        std::string header;

        while (std::getline(iss, line))
        {
            if (line.starts_with("[Date"))
            {
                header = line;
                break;
            }
        }

        while (std::getline(iss, line))
        {
            if (std::isdigit(line[0]))
            {
                int turnNum = std::stoi(line.substr(0, line.find('.')));
                size_t pipePos = line.find("|");
                if (pipePos != std::string::npos && pipePos + 1 < line.length() && line[pipePos + 1] != ' ')
                {
                    line.insert(pipePos + 1, " ");
                }
                turns[turnNum] = line;
            }
        }

        if (color == PieceColor::WHITE)
        {
            turns[getCurrentTurn()] = output.substr(0, output.length() - 1); 
        }
        else
        {
            auto it = turns.find(getCurrentTurn());
            if (it != turns.end())
            {
                it->second += output;
            }
        }

        std::string newContent = header + "\n";
        for (const auto &[turn, moveLine] : turns)
        {
            newContent += moveLine + (moveLine.back() != '\n' ? "\n" : "");
        }

        m_outFile.close();
        m_outFile.open(m_fileName, std::ios::out | std::ios::trunc);
        m_outFile << newContent;
        m_outFile.flush();

        m_originalContent = newContent;
        m_lastMove = {type, fromRow, toRow, fromCol, toCol, color};
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error in writeTurn: " << e.what() << "\n";
    }
}

std::string PgnNotation::getCurrentDateString() const
{
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

    std::string key = std::string(1, col) + std::to_string(color == PieceColor::WHITE ? 0 : 1);
    return m_pieceMoved.count(key) > 0 && m_pieceMoved.at(key);
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

std::vector<std::string> PgnNotation::listSavedGames()
{
    namespace fs = std::filesystem;
    std::vector<std::string> gameFiles;
    const std::string folderName = "games";

    for (const auto &entry : fs::directory_iterator(folderName))
    {
        if (entry.path().extension() == ".txt")
        {
            gameFiles.push_back(entry.path().filename().string());
        }
    }
    return gameFiles;
}

bool PgnNotation::loadGame(const std::string &filename)
{
    if (m_outFile.is_open())
        m_outFile.close();
    if (m_inFile.is_open())
        m_inFile.close();

    m_fileName = "games/" + filename;

    std::ifstream inFile(m_fileName);
    if (!inFile)
    {
        throw std::runtime_error("Failed to open " + filename + " for reading");
    }

    std::string line;
    std::string header;
    std::map<int, std::string> moveLines;

    while (std::getline(inFile, line))
    {
        if (line.empty())
            continue;

        if (line.starts_with("[Date"))
        {
            header = line;
            continue;
        }

        if (line.starts_with("[") || line.starts_with("#"))
        {
            continue;
        }

        if (std::isdigit(line[0]))
        {
            size_t turnNumber = std::stoul(line.substr(0, line.find('.')));
            moveLines[turnNumber] = line;
        }
    }
    inFile.close();

    std::string cleanContent = header + "\n";
    for (const auto &[turn, moveLine] : moveLines)
    {
        cleanContent += moveLine + "\n";
    }

    m_originalContent = cleanContent;

    m_outFile.open(m_fileName, std::ios::out | std::ios::trunc);
    if (!m_outFile)
    {
        throw std::runtime_error("failed to open " + filename + " for writing");
    }
    m_outFile << cleanContent;
    m_outFile.flush();

    m_inFile.open(m_fileName);
    if (!m_inFile)
    {
        throw std::runtime_error("failed to open " + filename + " for reading");
    }

    std::string movedPiecesLine;
    while (std::getline(inFile, line))
    {
        if (line.starts_with("[MovedPieces \""))
        {
            movedPiecesLine = line;
            break;
        }
    }

    if (!movedPiecesLine.empty())
    {
        size_t start = movedPiecesLine.find("\"") + 1;
        size_t end = movedPiecesLine.rfind("\"");
        if (start != std::string::npos && end != std::string::npos)
        {
            std::string pieces = movedPiecesLine.substr(start, end - start);
            std::stringstream ss(pieces);
            std::string piece;
            while (std::getline(ss, piece, ','))
            {
                m_pieceMoved[piece] = true;
            }
        }
    }

    m_pieceMoved.clear();
    m_originalPositions.clear();

    return true;
}

std::vector<std::pair<Position, Position>> PgnNotation::parseMovesFromFile(const std::string &line)
{ 
    std::vector<std::pair<Position, Position>> moves;

    if (line.empty() || line[0] == '[' || line[0] == '#')
    {
        return moves;
    }

    size_t dotPos = line.find('.');
    if (dotPos == std::string::npos)
    {
        return moves;
    }

    std::string movesStr = line.substr(dotPos + 1);

    auto processCastling = [](const std::string &moveStr, PieceColor color) -> std::vector<std::pair<Position, Position>>
    {
        std::vector<std::pair<Position, Position>> castleMoves;
        int row = (color == PieceColor::WHITE) ? 1 : 8;

        if (moveStr.find("O-O-O") != std::string::npos)
        {
            castleMoves.push_back({
                Position('e', row),
                Position('c', row) 
            });
        }
        else if (moveStr.find("O-O") != std::string::npos)
        {
            std::cout << "DEBUG: Processing short castling\n";
            castleMoves.push_back({
                Position('e', row), 
                Position('g', row)  
            });
        }
        return castleMoves;
    };

    auto processMove = [](const std::string &moveStr) -> std::pair<Position, Position>
    {

        if (moveStr.empty() || moveStr.find("O-O") != std::string::npos)
        {
            return std::make_pair(Position('\0', 0), Position('\0', 0));
        }

        size_t arrowPos = moveStr.find("->");
        if (arrowPos == std::string::npos)
        {
            return std::make_pair(Position('\0', 0), Position('\0', 0));
        }

        std::string fromStr = moveStr.substr(0, arrowPos);
        std::string toStr = moveStr.substr(arrowPos + 2);

        fromStr.erase(0, fromStr.find_first_not_of(" \t\r\n"));
        fromStr.erase(fromStr.find_last_not_of(" \t\r\n") + 1);
        toStr.erase(0, toStr.find_first_not_of(" \t\r\n"));
        toStr.erase(toStr.find_last_not_of(" \t\r\n") + 1);

        if (!fromStr.empty() && std::string("KQRBN").find(fromStr[0]) != std::string::npos)
        {
            fromStr = fromStr.substr(1);
        }
        if (!toStr.empty() && std::string("KQRBN").find(toStr[0]) != std::string::npos)
        {
            toStr = toStr.substr(1);
        }

        if (fromStr.length() >= 2 && toStr.length() >= 2)
        {
            return std::make_pair(
                Position(fromStr[0], fromStr[1] - '0'),
                Position(toStr[0], toStr[1] - '0'));
        }

        return std::make_pair(Position('\0', 0), Position('\0', 0));
    };

    size_t pipePos = movesStr.find('|');
    if (pipePos != std::string::npos)
    {
        std::string whiteMove = movesStr.substr(0, pipePos);

        if (whiteMove.find("O-O") != std::string::npos)
        {
            auto castleMoves = processCastling(whiteMove, PieceColor::WHITE);
            moves.insert(moves.end(), castleMoves.begin(), castleMoves.end());
        }
        else
        {
            auto whiteRegularMove = processMove(whiteMove);
            if (whiteRegularMove.first.col != '\0')
            {
                moves.push_back(whiteRegularMove);
            }
        }

        if (pipePos + 1 < movesStr.length())
        {
            std::string blackMove = movesStr.substr(pipePos + 1);

            if (blackMove.find("O-O") != std::string::npos)
            {
                auto castleMoves = processCastling(blackMove, PieceColor::BLACK);
                moves.insert(moves.end(), castleMoves.begin(), castleMoves.end());
            }
            else
            {
                auto blackRegularMove = processMove(blackMove);
                if (blackRegularMove.first.col != '\0')
                {
                    moves.push_back(blackRegularMove);
                }
            }
        }
    }

    return moves;
}

bool PgnNotation::readNextLine(std::string &line)
{
    return std::getline(m_inFile, line).good();
}

void PgnNotation::skipLine()
{
    std::string dummy;
    std::getline(m_inFile, dummy);
}

void PgnNotation::writeResult(const std::string &result)
{
    if (m_outFile.is_open())
    {
        m_outFile << "\nResult: " << result << "\n";
        m_outFile.flush();
    }
}

void PgnNotation::saveTurnState(int turn, bool whiteHasMoved) 
{
    try
    {
        if (m_outFile.is_open())
        {
            m_outFile.close();
        }
        if (m_inFile.is_open())
        {
            m_inFile.close();
        }

        std::string content = m_originalContent;
        content += "\n[TurnState \"" + std::to_string(turn) + "," + (whiteHasMoved ? "1" : "0") + "\"]";

        if (!m_pieceMoved.empty())
        {
            std::string pieces;
            for (const auto &[key, value] : m_pieceMoved)
            {
                if (value)
                {
                    if (!pieces.empty())
                        pieces += ",";
                    pieces += key;
                }
            }
            if (!pieces.empty())
            {
                content += "\n[MovedPieces \"" + pieces + "\"]";
            }
        }

        std::string tempFile = m_fileName + ".tmp";
        std::ofstream tempOut(tempFile);
        if (!tempOut)
        {
            throw std::runtime_error("failed to create temporary file");
        }
        tempOut << content;
        tempOut.close();

        if (std::rename(tempFile.c_str(), m_fileName.c_str()) != 0)
        {
            throw std::runtime_error("failed to save game state");
        }

        m_originalContent = content;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error saving game state: " << e.what() << '\n';
    }
}

bool PgnNotation::loadTurnState(int &turn, bool &whiteHasMoved) const 
{
    size_t pos = m_originalContent.rfind("[TurnState \"");
    if (pos != std::string::npos)
    {
        std::string stateLine = m_originalContent.substr(pos);
        size_t comma = stateLine.find(',');
        size_t quote = stateLine.find('\"');
        if (comma != std::string::npos && quote != std::string::npos)
        {
            try
            {
                turn = std::stoi(stateLine.substr(quote + 1, comma - (quote + 1)));
                whiteHasMoved = (stateLine[comma + 1] == '1');
                return true;
            }
            catch (...)
            {
            }
        }
    }
    return false;
}

bool PgnNotation::hasIncompleteTurn() const
{
    std::istringstream iss(m_originalContent);
    std::string lastValidLine;
    std::string line;

    while (std::getline(iss, line))
    {
        if (line.empty() || line[0] == '[' || line.starts_with("#") || line.starts_with("Result"))
        {
            continue;
        }
        lastValidLine = line;
    }

    size_t dotPos = lastValidLine.find('.');
    if (dotPos == std::string::npos)
    {
        return false;
    }

    try
    {
        int turnNum = std::stoi(lastValidLine.substr(0, dotPos));

        size_t arrowPos = lastValidLine.find("->");
        if (arrowPos == std::string::npos)
        {
            return false;
        }

        size_t pipePos = lastValidLine.find("|");

        if (pipePos != std::string::npos)
        {
            std::string afterPipe = lastValidLine.substr(pipePos + 1);
            afterPipe.erase(0, afterPipe.find_first_not_of(" \t\r\n"));
            afterPipe.erase(afterPipe.find_last_not_of(" \t\r\n") + 1);


            return afterPipe.empty() || afterPipe.find("->") == std::string::npos;
        }

        return true; 
    }
    catch (...)
    {
        return false;
    }
}

std::string PgnNotation::getPieceSymbol(PieceType type)
{
    switch (type)
    {
    case PieceType::KING:
        return "K";
    case PieceType::QUEEN:
        return "Q";
    case PieceType::ROOK:
        return "R";
    case PieceType::BISHOP:
        return "B";
    case PieceType::KNIGHT:
        return "N";
    case PieceType::PAWN:
        return "";
    default:
        return "";
    }
}

void PgnNotation::markPieceMoved(PieceType type, PieceColor color, char col, bool /* isReplay */)
{
    if (type != PieceType::KING && type != PieceType::ROOK)
    {
        return;
    }

    std::string key = std::string(1, col) + std::to_string(color == PieceColor::WHITE ? 0 : 1);

    if ((type == PieceType::KING && col == 'e') ||
        (type == PieceType::ROOK && (col == 'a' || col == 'h')))
    {
        m_pieceMoved[key] = true;
    }
}

void PgnNotation::clearPieceMovementHistory()
{
    m_pieceMoved.clear();
}