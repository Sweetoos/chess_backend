#include <string>
#include <iostream>
#include <stdexcept>
#include <print>
#include <array>
#include "classes.h"
#include "chess.h"

/// @brief match turn
int GameManager::turn = 1;

Chess::Chess(PieceFactory &factory) : m_gm(factory)
{
    m_gm.setupBoard();
}

void Chess::run()
{
    std::string command;
    std::cout << "Enter 'new' for new game or 'load' to load saved game: ";
    std::getline(std::cin, command);

    if (command == "load") {
        auto savedGames = PgnNotation::listSavedGames();
        if (savedGames.empty()) {
            std::println("No saved games found.");
            return;
        }

        std::println("Available saved games:");
        for (size_t i = 0; i < savedGames.size(); ++i) {
            std::println("{0}: {1}", i + 1, savedGames[i]);
        }

        std::print("Enter game number to load: ");
        std::string selection;
        std::getline(std::cin, selection);
        
        try {
            int index = std::stoi(selection) - 1;
            if (index >= 0 && index < static_cast<int>(savedGames.size())) {
                if (m_gm.getPgn().loadGame(savedGames[index])) {
                    GameManager::turn = 1; // Reset turn counter
                    m_gm.setupBoard(); // Reset board to initial state
                    m_gm.setCurrentTurnColor(PieceColor::WHITE); // Reset to white's turn
                    
                    std::cout << "DEBUG: Starting game replay\n";
                    
                    std::string line;
                    bool headerSkipped = false;
                    
                    while (m_gm.getPgn().readNextLine(line)) {
                        // Skip header
                        if (!headerSkipped) {
                            if (line.starts_with("[Date")) {
                                headerSkipped = true;
                                continue;
                            }
                        }
                        
                        std::cout << "DEBUG: Processing line: '" << line << "'\n";
                        
                        // Skip metadata and empty lines
                        if (line.empty() || line[0] == '[' || line.starts_with("Result")) {
                            std::cout << "DEBUG: Skipping non-move line\n";
                            continue;
                        }

                        auto moves = m_gm.getPgn().parseMovesFromFile(line);  // Remove currentTurnColor argument
                        std::cout << "DEBUG: Found " << moves.size() << " moves to replay\n";
                        
                        for (const auto& [from, to] : moves) {
                            auto* piece = m_gm.getBoard().getPieceAt(from);
                            std::cout << "DEBUG: Replaying move " << from.col << from.row 
                                    << " to " << to.col << to.row 
                                    << " (piece: " << (piece ? piece->getFullSymbol() : "nullptr") << ")\n";
                            
                            if (!piece) {
                                throw std::runtime_error("No piece at source position");
                            }
                            
                            if (!m_gm.movePiece(from, to)) {
                                throw std::runtime_error("Failed to replay move");
                            }
                            
                            std::cout << "DEBUG: Move replayed successfully\n";
                        }
                    }
                    
                    std::cout << "DEBUG: Loading complete. Checking game state...\n";
                    
                    // Load game state
                    bool whiteHasMoved;
                    int savedTurn;
                    if (m_gm.getPgn().loadTurnState(savedTurn, whiteHasMoved)) {
                        GameManager::turn = savedTurn;
                        m_gm.setCurrentTurnColor(whiteHasMoved ? PieceColor::BLACK : PieceColor::WHITE);
                    }

                    std::println("Game loaded successfully!");
                    m_gm.displayBoard();
                    
                    std::cout << "DEBUG: Final state - Turn: " << GameManager::turn 
                             << ", Color: " << (m_gm.getCurrentTurnColor() == PieceColor::WHITE ? "WHITE" : "BLACK") 
                             << "\n";
                }
            }
        }
        catch (const std::exception& e) {
            std::println("Error loading game: {}", e.what());
            return;
        }
    }
    else if (command == "new") {
        m_gm.getPgn().initNewGame(); // Create file for new game
        m_gm.displayBoard(); // Add this line to display the initial board state
    }
    else {
        std::println("Invalid command. Exiting...");
        return;
    }

    while (true)
    {
        std::string move;
        std::println("TURN {0}", GameManager::turn);
        std::println("{0} move", (m_gm.getCurrentTurnColor() == PieceColor::WHITE ? "white" : "black"));
        try
        {
            std::print("enter move: ");
            std::getline(std::cin, move);
            
            // Draw by agreement
            if(move == "draw")
            {
                std::print("Other player, do you accept the draw? (y/n): ");
                std::string response;
                std::getline(std::cin, response);
                if(response == "y" || response == "yes")
                {
                    std::println("Game drawn by mutual agreement!");
                    m_gm.getPgn().writeResult("1/2-1/2 (Draw by agreement)");
                    break;
                }
                else
                {
                    std::println("Draw declined, continue playing.");
                    continue;
                }
            }

            // Add save game command
            if(move == "save") {
                if (m_gm.getCurrentTurnColor() == PieceColor::BLACK) {
                    // Mark the line as incomplete for Black's turn
                    m_gm.getPgn().appendToFile("\n");
                    // Store the current turn state
                    m_gm.getPgn().saveTurnState(GameManager::turn, true); // true indicates White has moved
                }
                std::println("Game saved!");
                break;
            }

            if (move.length() == 5 && move[2] == ' ') {
                char fromCol = std::tolower(move[0]);
                int fromRow = move[1] - '0';
                char toCol = std::tolower(move[3]);
                int toRow = move[4] - '0';

                if (fromCol < 'a' || fromCol > 'h' || toCol < 'a' || toCol > 'h' || fromRow < 1 || fromRow > 8 || toRow < 1 || toRow > 8)
                    throw std::out_of_range("move is out of bounds; columns must be a-h and rows 1-8");

                Position from(fromCol, fromRow);
                Position to(toCol, toRow);

                if (m_gm.movePiece(from, to)) {
                    m_gm.displayBoard();
                    
                    // Check for insufficient material draw
                    if (m_gm.hasInsufficientMaterial()) {
                        std::println("Draw by insufficient material!");
                        m_gm.getPgn().writeResult("1/2-1/2 (Draw by insufficient material)");
                        break;
                    }
                    
                    if (m_gm.isKingInCheck(m_gm.getCurrentTurnColor()))
                        std::println("CHECK!");

                    if (m_gm.isCheckmate(m_gm.getCurrentTurnColor()))
                    {
                        std::string winner = (m_gm.getCurrentTurnColor() == PieceColor::BLACK) ? "White" : "Black";
                        std::println("Checkmate! {0} wins!", winner);
                        m_gm.getPgn().writeResult(winner == "White" ? "1-0" : "0-1");
                        break;
                    }
                }
            }
            else {
                throw std::invalid_argument("invalid argument, give it in format [{current position} {destination}]\n without piece notation, we will figure it out");
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error: " << e.what() << '\n';
            m_gm.displayBoard(); 
        }
    }
}

bool GameManager::movePiece(const Position &from, const Position &to)
{
    auto *piece = m_board.getPieceAt(from);

    if (piece == nullptr) {
        throw std::runtime_error("No piece found at the given position");
    }

    if (piece->getColor() != m_currentTurnColor)
    {
        std::println("it's not {0}'s turn", (m_currentTurnColor == PieceColor::WHITE) ? "black" : "white");
        return false;
    }

    // Handle castling
    if (piece->getType() == PieceType::KING && std::abs(to.col - from.col) == 2)
    {
        std::cout << "DEBUG: Attempting king castling move\n";
        if (handleCastling(from, to))
        {
            m_moveType = MoveType::CASTLE;
            std::string castleNotation = (to.col > from.col) ? "O-O" : "O-O-O";
            m_pgn.writeTurn(piece->getColor(), piece->getType(), from.col, from.row, to.col, to.row, castleNotation);
            m_currentTurnColor = (m_currentTurnColor == PieceColor::WHITE) ? PieceColor::BLACK : PieceColor::WHITE;
            if (m_currentTurnColor == PieceColor::WHITE)
                turn++;
            return true;
        }
        return false;
    }

    // checks if the move is correct
    MoveManager mm(&m_pgn);  
    if (!mm.isValidMove(from, to, m_board, *piece))
    {
        std::println("invalid move for {0}\n", piece->getFullSymbol());
        return false;
    }

    // captures
    PieceInterface *capturedPiece = m_board.getPieceAt(to);
    bool isCapture = capturedPiece != nullptr;
    bool isEnPassant = false;

    // en passant check
    if (piece->getType() == PieceType::PAWN && !isCapture)
    {
        MoveManager mm(&m_pgn);
        if (mm.isEnPassant(*piece, from, to, m_board))
        {
            isCapture = true;
            isEnPassant = true;
            Position capturedPawnPos(to.col, from.row);
            m_board.removePiece(capturedPawnPos);
            m_moveType = MoveType::CAPTURE;
        }
    }

    // regular capture
    if (isCapture && !isEnPassant)
    {
        m_board.removePiece(to);
        m_moveType = MoveType::CAPTURE;
    }

    // moving piece
    m_board.removePiece(from, false);

    if (piece == nullptr)
        throw std::runtime_error("Error: Attempted to move a null piece");

    piece->move(to);
    m_board.putPiece(piece);
    // pawn promotion
    if (piece->getType() == PieceType::PAWN && (to.row == 1 || to.row == 8))
    {
        PieceType promotionType = handlePromotion(to);
        piece = m_board.getPieceAt(to);
        std::string promotionNotation = std::string(1, from.col) + std::to_string(from.row) + 
                                      " -> " + std::string(1, to.col) + std::to_string(to.row) + 
                                      "=" + promotionTypeToString(promotionType);
        m_pgn.writeTurn(piece->getColor(), piece->getType(), from.col, from.row, to.col, to.row, promotionNotation);
        m_moveType = MoveType::PROMOTION;
        m_currentTurnColor = (m_currentTurnColor == PieceColor::WHITE) ? PieceColor::BLACK : PieceColor::WHITE;
        if (m_currentTurnColor == PieceColor::WHITE)
            turn++;
        return true;  
    }
    else
    {
        m_moveType = isCapture ? MoveType::CAPTURE : MoveType::MOVE;
    }

    // check for check/checkmate
    if (isKingInCheck(m_currentTurnColor == PieceColor::WHITE ? PieceColor::BLACK : PieceColor::WHITE))
    {
        if (isCheckmate(m_currentTurnColor == PieceColor::WHITE ? PieceColor::BLACK : PieceColor::WHITE))
        {
            m_moveType = MoveType::MATE;
        }
        else
        {
            m_moveType = MoveType::CHECK;
        }
    }
    //std::println("moved {0} to {1}{2}",piece->getFullSymbol(),to.col,to.row);
    m_pgn.writeTurn(piece->getColor(), piece->getType(), from.col, from.row, to.col, to.row, "");

    // change turn
    m_currentTurnColor = (m_currentTurnColor == PieceColor::WHITE) ? PieceColor::BLACK : PieceColor::WHITE;
    if (m_currentTurnColor == PieceColor::WHITE)
        turn++;

    return true;
}

bool GameManager::handleCastling(const Position &from, const Position &to)
{
    std::cout << "DEBUG: Handling castling from " << from.col << from.row 
              << " to " << to.col << to.row << "\n";
              
    auto *king = m_board.getPieceAt(from);
    if (!king || king->getType() != PieceType::KING) {
        std::cout << "DEBUG: Not a king at source position\n";
        return false;
    }

    char rookCol = (to.col > from.col) ? 'h' : 'a';
    char newRookCol = (to.col > from.col) ? 'f' : 'd';
    std::cout << "DEBUG: Rook should move from " << rookCol << " to " << newRookCol << "\n";

    Position rookPos(rookCol, from.row);
    auto *rook = m_board.getPieceAt(rookPos);
    
    if (!rook || rook->getType() != PieceType::ROOK) {
        std::cout << "DEBUG: Not a rook at expected position " << rookCol << from.row << "\n";
        return false;
    }

    // Perform castling
    std::cout << "DEBUG: Moving king from " << from.col << from.row 
              << " to " << to.col << to.row << "\n";
    std::cout << "DEBUG: Moving rook from " << rookPos.col << rookPos.row 
              << " to " << newRookCol << rookPos.row << "\n";

    // Move both pieces
    m_board.removePiece(from, false);
    m_board.removePiece(rookPos, false);
    king->move(to);
    rook->move(Position(newRookCol, from.row));
    m_board.putPiece(king);
    m_board.putPiece(rook);

    return true;
}

PieceType GameManager::handlePromotion(const Position &pos)
{
    m_promotionFlag = true;
    char promotion;
    std::string input;
    
    std::cout << "Promote pawn to (Q/R/B/N): ";
    std::getline(std::cin, input);
    while (input.empty() || std::string("QRBN").find(std::toupper(input[0])) == std::string::npos) {
        std::cout << "Invalid input. Promote pawn to (Q/R/B/N): ";
        std::getline(std::cin, input);
    }
    promotion = std::toupper(input[0]);

    PieceColor color = m_board.getPieceAt(pos)->getColor();
    m_board.removePiece(pos, true);

    PieceType newType;
    switch (promotion)
    {
    case 'Q': newType = PieceType::QUEEN; break;
    case 'R': newType = PieceType::ROOK; break;
    case 'B': newType = PieceType::BISHOP; break;
    case 'N': newType = PieceType::KNIGHT; break;
    default: newType = PieceType::QUEEN; break;
    }
    
    PieceInterface *newPiece = m_factory.createAndStorePiece(newType, pos, color);
    m_board.putPiece(newPiece);
    return newType;
}

bool GameManager::isSquareUnderAttack(const Position &pos, PieceColor defendingColor) const
{
    MoveManager mm(&m_pgn);  
    for (int row = 1; row <= 8; row++)
    {
        for (char col = 'a'; col <= 'h'; col++)
        {
            Position from(col, row);
            PieceInterface *attacker = m_board.getPieceAt(from);
            if (attacker && attacker->getColor() != defendingColor)
            {
                if (mm.isValidMove(from, pos, m_board, *attacker))
                    return true;
            }
        }
    }
    return false;
}

bool GameManager::isKingInCheck(PieceColor color) const
{
    Position kingPos('a', 1); 
    for (int row = 1; row <= 8; row++)
    {
        for (char col = 'a'; col <= 'h'; col++)
        {
            PieceInterface *piece = m_board.getPieceAt(Position(col, row));
            if (piece && piece->getType() == PieceType::KING && piece->getColor() == color)
            {
                kingPos = piece->getPosition();
                break;
            }
        }
    }
    return isSquareUnderAttack(kingPos, color);
}
bool GameManager::isCheckmate(PieceColor color)
{
    for (int fromRow = 1; fromRow <= 8; fromRow++)
    {
        for (char fromCol = 'a'; fromCol <= 'h'; fromCol++)
        {
            Position from(fromCol, fromRow);
            PieceInterface *piece = m_board.getPieceAt(from);
            if (!piece || piece->getColor() == color)
                continue;
            for (int toRow = 1; toRow <= 8; toRow++)
            {
                for (char toCol = 'a'; toCol <= 'h'; toCol++)  // Fix syntax error here
                {
                    Position to(toCol, toRow);
                    MoveManager mm(&m_pgn); 
                    if (!mm.isValidMove(from, to, m_board, *piece))
                        continue;
                    PieceInterface *capturedPiece = m_board.getPieceAt(to);
                    m_board.removePiece(to, false);
                    if (capturedPiece)
                        m_board.removePiece(to, false);
                    piece->move(to);
                    m_board.putPiece(piece);

                    // if king is still in check
                    bool isStillInCheck = isKingInCheck(color);

                    // undo move
                    m_board.removePiece(to, false);
                    piece->move(from);
                    m_board.putPiece(piece);
                    if (capturedPiece)
                        m_board.putPiece(capturedPiece);

                    if (!isStillInCheck)
                        return false;
                }
            }
        }
    }
    return true;
}
/// @brief this is a helper function to check if the king or rook has moved to determine if castling is possible
/// @param piece
/// @return
bool GameManager::isFirstMove(const PieceInterface *piece)
{
    if (!piece)
        return false;

    // for white
    if (piece->getColor() == PieceColor::WHITE)
    {
        if (piece->getType() == PieceType::KING)
        {
            return piece->getPosition().col == 'e' && piece->getPosition().row == 1;
        }
        else if (piece->getType() == PieceType::ROOK)
        {
            return (piece->getPosition().col == 'a' && piece->getPosition().row == 1) || (piece->getPosition().col == 'h' && piece->getPosition().row == 1);
        }
    }

    // for black
    if (piece->getColor() == PieceColor::BLACK)
    {
        if (piece->getType() == PieceType::KING)
        {
            return piece->getPosition().col == 'e' && piece->getPosition().row == 8;
        }
        else if (piece->getType() == PieceType::ROOK)
        {
            return (piece->getPosition().col == 'a' && piece->getPosition().row == 8) || (piece->getPosition().col == 'h' && piece->getPosition().row == 8);
        }
    }
    return false;
}

void GameManager::setupBoard()
{
    for (char col = 'a'; col <= 'h'; col++)
    {
        m_board.putPiece(m_factory.createAndStorePiece(PieceType::PAWN, Position(col, 2), PieceColor::WHITE));
        m_board.putPiece(m_factory.createAndStorePiece(PieceType::PAWN, Position(col, 7), PieceColor::BLACK));
    }

    const std::array<PieceType, 8> pieces =
        {
            PieceType::ROOK,
            PieceType::KNIGHT,
            PieceType::BISHOP,
            PieceType::QUEEN,
            PieceType::KING,
            PieceType::BISHOP,
            PieceType::KNIGHT,
            PieceType::ROOK};

    for (int i = 0; i < 8; i++)
    {
        m_board.putPiece(m_factory.createAndStorePiece(pieces[i], Position('a' + i, 1), PieceColor::WHITE));
        m_board.putPiece(m_factory.createAndStorePiece(pieces[i], Position('a' + i, 8), PieceColor::BLACK));
    }
}

void GameManager::displayBoard() const
{
    m_board.displayBoardConsole();
}

std::string GameManager::promotionTypeToString(PieceType type) const
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

bool GameManager::hasInsufficientMaterial() const 
{
    // Case 1: Only kings
    if (hasOnlyKing(PieceColor::WHITE) && hasOnlyKing(PieceColor::BLACK)) {
        return true;
    }
    
    // Case 2: King and minor piece vs King
    if ((hasOnlyKing(PieceColor::WHITE) && hasOnlyKingAndMinorPiece(PieceColor::BLACK)) ||
        (hasOnlyKing(PieceColor::BLACK) && hasOnlyKingAndMinorPiece(PieceColor::WHITE))) {
        return true;
    }
    
    return false;
}

bool GameManager::hasOnlyKing(PieceColor color) const 
{
    int pieceCount = 0;
    bool hasKing = false;
    
    for (int row = 1; row <= 8; row++) {
        for (char col = 'a'; col <= 'h'; col++) {
            PieceInterface* piece = m_board.getPieceAt(Position(col, row));
            if (piece && piece->getColor() == color) {
                pieceCount++;
                if (piece->getType() == PieceType::KING) {
                    hasKing = true;
                }
            }
        }
    }
    
    return hasKing && pieceCount == 1;
}

bool GameManager::hasOnlyKingAndMinorPiece(PieceColor color) const 
{
    int pieceCount = 0;
    bool hasKing = false;
    bool hasMinorPiece = false;
    
    for (int row = 1; row <= 8; row++) {
        for (char col = 'a'; col <= 'h'; col++) {
            PieceInterface* piece = m_board.getPieceAt(Position(col, row));
            if (piece && piece->getColor() == color) {
                pieceCount++;
                if (piece->getType() == PieceType::KING) {
                    hasKing = true;
                }
                else if (piece->getType() == PieceType::BISHOP || 
                         piece->getType() == PieceType::KNIGHT) {
                    hasMinorPiece = true;
                }
            }
        }
    }
    
    return hasKing && hasMinorPiece && pieceCount == 2;
}

const Board& GameManager::getBoard() const { return m_board; }
