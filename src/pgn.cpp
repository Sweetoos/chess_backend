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

void PgnNotation::debugPrintCandidates(const std::vector<PieceInfo>& candidates) const {
    std::cout << "Candidates found: " << candidates.size() << "\n";
    for (const auto& candidate : candidates) {
        std::cout << "Piece at " << candidate.pos.col << candidate.pos.row 
                  << " can make this move\n";
    }
}

std::vector<PieceInfo> PgnNotation::getCandidates(const Board &board, const Position &to,
                                                  const PieceType &type, const PieceColor &color) const
{
    std::vector<PieceInfo> candidates;
    MoveManager mm;

    try {
        // Create a copy of the board to test moves
        Board tempBoard = board;

        // First remove any piece at the destination
        PieceInterface* destPiece = tempBoard.getPieceAt(to);
        if (destPiece) {
            tempBoard.removePiece(to, false);  // Don't delete the piece yet
        }

        // Search for all pieces of the same type and color
        for (int row = 1; row <= 8; row++) {
            for (char col = 'a'; col <= 'h'; col++) {
                Position from(col, row);
                PieceInterface* piece = tempBoard.getPieceAt(from);
                
                if (!piece || piece->getType() != type || piece->getColor() != color) {
                    continue;
                }

                if (mm.isValidMove(from, to, tempBoard, *piece)) {
                    std::cout << "Found valid candidate at " << col << row << "\n";
                    candidates.push_back({from, type, color});
                }
            }
        }

        // Restore the captured piece if there was one
        if (destPiece) {
            tempBoard.putPiece(destPiece);
        }

    } catch (const std::exception& e) {
        std::cerr << "Error in getCandidates: " << e.what() << "\n";
    }

    return candidates;
}

std::string PgnNotation::getDisambiguation(const char &fromCol, const int &fromRow,
                                           const std::vector<PieceInfo> &candidates) const
{
    if (candidates.size() <= 1)
    {
        return ""; // No disambiguation needed
    }

    bool sameFile = false;
    bool sameRank = false;
    int matchingFiles = 0;
    int matchingRanks = 0;

    // Count how many pieces share the same file or rank as the moving piece
    for (const auto &candidate : candidates)
    {
        if (candidate.pos.col == fromCol)
        {
            matchingFiles++;
        }
        if (candidate.pos.row == fromRow)
        {
            matchingRanks++;
        }
    }

    // Determine what type of disambiguation is needed
    if (matchingFiles > 1)
    {
        sameFile = true;
    }
    if (matchingRanks > 1)
    {
        sameRank = true;
    }

    // Build disambiguation string
    std::string disambiguation = "";

    // If pieces are on different files, file is sufficient
    if (candidates.size() > 1 && !sameFile)
    {
        return std::string(1, fromCol);
    }

    // If pieces are on the same file but different ranks
    if (sameFile)
    {
        return std::to_string(fromRow);
    }

    // If both are needed (rare case, but possible)
    if (sameFile && sameRank)
    {
        return std::string(1, fromCol) + std::to_string(fromRow);
    }

    return disambiguation;
}

void PgnNotation::writeTurn(const PieceColor &color, const PieceType &type, const char &fromCol,
                            const int &fromRow, const char &toCol, const int &toRow,
                            const MoveType &moveType, const Board &board,
                            const PieceType &promotionType)
{
    try {
        std::cout << "\n=== DEBUG: writeTurn ===\n";
        std::cout << "Processing move: " << fromCol << fromRow << " to " << toCol << toRow << "\n";

        Position toPos(toCol, toRow);
        auto candidates = getCandidates(board, toPos, type, color);
        
        // Filter out the moving piece
        candidates.erase(
            std::remove_if(candidates.begin(), candidates.end(),
                [&](const PieceInfo& info) {
                    return info.pos.col == fromCol && info.pos.row == fromRow;
                }),
            candidates.end()
        );

        std::cout << "After filtering, candidates remaining: " << candidates.size() << "\n";

        // Get disambiguation if needed
        std::string disambiguation = "";
        if (type != PieceType::PAWN && type != PieceType::KING && !candidates.empty()) {
            disambiguation = getDisambiguation(fromCol, fromRow, candidates);
            std::cout << "Using disambiguation: '" << disambiguation << "'\n";
        }

        std::string pieceSymbol;
        switch (type)
        {
        case PieceType::KING:
            pieceSymbol = "K";
            break;
        case PieceType::QUEEN:
            pieceSymbol = "Q";
            break;
        case PieceType::ROOK:
            pieceSymbol = "R";
            break;
        case PieceType::BISHOP:
            pieceSymbol = "B";
            break;
        case PieceType::KNIGHT:
            pieceSymbol = "N";
            break;
        case PieceType::PAWN:
            pieceSymbol = "";
            break;
        }

        // Create the move notation
        std::string move;
        switch (moveType)
        {
        case MoveType::MOVE:
            move = pieceSymbol + disambiguation + std::string(1, toCol) + std::to_string(toRow);
            break;
        case MoveType::CAPTURE:
            if (type == PieceType::PAWN)
            {
                move = std::string(1, fromCol) + "x" + std::string(1, toCol) + std::to_string(toRow);
            }
            else
            {
                move = pieceSymbol + disambiguation + "x" + std::string(1, toCol) + std::to_string(toRow);
            }
            break;
        case MoveType::CASTLE:
            move = (toCol == 'g') ? "O-O" : "O-O-O";
            break;
        case MoveType::CHECK:
            move = pieceSymbol + disambiguation + std::string(1, toCol) + std::to_string(toRow) + "+";
            break;
        case MoveType::MATE:
            move = pieceSymbol + disambiguation + std::string(1, toCol) + std::to_string(toRow) + "#";
            break;
        case MoveType::PROMOTION:
            move = std::string(1, toCol) + std::to_string(toRow) + "=" +
                   (promotionType == PieceType::QUEEN ? "Q" : promotionType == PieceType::ROOK ? "R"
                                                          : promotionType == PieceType::BISHOP ? "B"
                                                                                               : "N");
            break;
        }

        std::cout << "Final move notation: " << move << "\n";

        // Write the move to the file
        if (color == PieceColor::WHITE)
        {
            appendToFile(std::to_string(getCurrentTurn()) + ". " + move + " ");
        }
        else
        {
            appendToFile(move + " ");
        }
    } catch (const std::exception& e) {
        std::cerr << "Error in writeTurn: " << e.what() << "\n";
    }
}