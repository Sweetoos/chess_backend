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
    std::cout << "enter 'new' for new game or 'load' to load saved game: ";
    std::getline(std::cin, command);

    if (command == "load")
    {
        auto savedGames = PgnNotation::listSavedGames();
        if (savedGames.empty())
        {
            std::println("no saved games found.");
            return;
        }

        std::println("available saved games:");
        for (size_t i = 0; i < savedGames.size(); ++i)
        {
            std::println("{0}: {1}", i + 1, savedGames[i]);
        }

        std::print("enter game number to load: ");
        std::string selection;
        std::getline(std::cin, selection);

        try
        {
            int index = std::stoi(selection) - 1;
            if (index >= 0 && index < static_cast<int>(savedGames.size()))
            {
                if (m_gm.getPgn().loadGame(savedGames[index]))
                {
                    GameManager::turn = 1;                       
                    m_gm.setupBoard();                           
                    m_gm.setCurrentTurnColor(PieceColor::WHITE); 
                    m_gm.getPgn().clearPieceMovementHistory();   

                    std::string line;
                    bool headerSkipped = false;

                    while (m_gm.getPgn().readNextLine(line))
                    {
                        if (!headerSkipped)
                        {
                            if (line.starts_with("[Date"))
                            {
                                headerSkipped = true;
                                continue;
                            }
                        }

                        if (line.empty() || line[0] == '[' || line.starts_with("Result"))
                        {
                            continue;
                        }

                        auto moves = m_gm.getPgn().parseMovesFromFile(line); 

                        for (const auto &[from, to] : moves)
                        {
                            auto *piece = m_gm.getBoard().getPieceAt(from);

                            if (!piece)
                            {
                                throw std::runtime_error("no piece at source position");
                            }

                            if (!m_gm.movePiece(from, to, true))
                            {
                                throw std::runtime_error("failed to replay move");
                            }
                        }
                    }

                    // loading
                    bool whiteHasMoved;
                    int savedTurn;
                    if (m_gm.getPgn().loadTurnState(savedTurn, whiteHasMoved))
                    {
                        GameManager::turn = savedTurn;
                        m_gm.setCurrentTurnColor(whiteHasMoved ? PieceColor::BLACK : PieceColor::WHITE);
                    }

                    std::println("game loaded successfully\n");
                    m_gm.displayBoard();
                }
            }
        }
        catch (const std::exception &e)
        {
            std::println("error loading game: {}", e.what());
            return;
        }
    }
    else if (command == "new")
    {
        m_gm.getPgn().initNewGame(); 
        m_gm.displayBoard();         
    }
    else
    {
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

            // draw by agreement
            if (move == "draw")
            {
                std::print("other player, do you accept the draw? (y/n): ");
                std::string response;
                std::getline(std::cin, response);
                if (response == "y" || response == "yes")
                {
                    std::println("game drawn by mutual agreement!");
                    m_gm.getPgn().writeResult("1/2-1/2 (draw by agreement)");
                    break;
                }
                else
                {
                    std::println("draw declined, continue playing.");
                    continue;
                }
            }

            if (move == "save")
            {
                if (m_gm.getCurrentTurnColor() == PieceColor::BLACK)
                {
                    m_gm.getPgn().appendToFile("\n");
                    m_gm.getPgn().saveTurnState(GameManager::turn, true); 
                }
                std::println("Game saved!");
                break;
            }

            if (move.length() == 5 && move[2] == ' ')
            {
                char fromCol = std::tolower(move[0]);
                int fromRow = move[1] - '0';
                char toCol = std::tolower(move[3]);
                int toRow = move[4] - '0';

                if (fromCol < 'a' || fromCol > 'h' || toCol < 'a' || toCol > 'h' || fromRow < 1 || fromRow > 8 || toRow < 1 || toRow > 8)
                    throw std::out_of_range("move is out of bounds; columns must be a-h and rows 1-8");

                Position from(fromCol, fromRow);
                Position to(toCol, toRow);

                if (m_gm.movePiece(from, to, false))
                {
                    m_gm.displayBoard();

                    // check if game is over
                    if (m_gm.isCheckmate(m_gm.getCurrentTurnColor())) {
                        std::string winner = (m_gm.getCurrentTurnColor() == PieceColor::BLACK) ? "White" : "Black";
                        std::println("game gver - checkmate! {0} wins!", winner);
                        break;  // exit game loop on checkmate
                    }

                    // check for insufficient material draw
                    if (m_gm.hasInsufficientMaterial())
                    {
                        std::println("draw by insufficient material!");
                        m_gm.getPgn().writeResult("1/2-1/2 (draw by insufficient material)");
                        break;
                    }

                    if (m_gm.isKingInCheck(m_gm.getCurrentTurnColor()))
                        std::println("CHECK!");

                    if (m_gm.isCheckmate(m_gm.getCurrentTurnColor()))
                    {
                        std::string winner = (m_gm.getCurrentTurnColor() == PieceColor::BLACK) ? "White" : "Black";
                        std::println("checkmate! {0} wins!", winner);
                        m_gm.getPgn().writeResult(winner == "White" ? "1-0" : "0-1");
                        break;
                    }
                }
            }
            else
            {
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

bool GameManager::wouldMoveExposeKingToCheck(const Position &from, const Position &to, PieceColor kingColor) {
    PieceInterface* movingPiece = m_board.getPieceAt(from);
    PieceInterface* capturedPiece = m_board.getPieceAt(to);
    
    m_board.removePiece(from, false);
    if (capturedPiece) {
        m_board.removePiece(to, false);
    }
    movingPiece->move(to);
    m_board.putPiece(movingPiece);
    
    bool wouldBeInCheck = isKingInCheck(kingColor);
    
    m_board.removePiece(to, false);
    movingPiece->move(from);
    m_board.putPiece(movingPiece);
    if (capturedPiece) {
        m_board.putPiece(capturedPiece);
    }
    
    return wouldBeInCheck;
}

bool GameManager::movePiece(const Position &from, const Position &to, bool isReplay)
{
    auto *piece = m_board.getPieceAt(from);

    if (piece == nullptr) {
        throw std::runtime_error("no piece found at the given position");
    }

    if (!isReplay && piece->getColor() != m_currentTurnColor) {
        std::println("it's not {0}'s turn", (m_currentTurnColor == PieceColor::WHITE) ? "black" : "white");
        return false;
    }

    if (!isReplay && wouldMoveExposeKingToCheck(from, to, piece->getColor())) {
        std::println("This move would leave/place your king in check!");
        return false;
    }

    // handle castling
    if (piece->getType() == PieceType::KING && std::abs(to.col - from.col) == 2) {
        if (handleCastling(from, to)) {
            m_moveType = MoveType::CASTLE;
            if (!isReplay) {
                std::string castleNotation = (to.col > from.col) ? "O-O" : "O-O-O";
                m_pgn.writeTurn(piece->getColor(), piece->getType(), from.col, from.row, to.col, to.row, castleNotation);
            }
            m_currentTurnColor = (m_currentTurnColor == PieceColor::WHITE) ? PieceColor::BLACK : PieceColor::WHITE;
            if (m_currentTurnColor == PieceColor::WHITE)
                turn++;
            return true;
        }
        return false;
    }

    // regular move handling
    MoveManager mm(&m_pgn);
    if (!mm.isValidMove(from, to, m_board, *piece))
    {
        std::println("invalid move for {0}\n", piece->getFullSymbol());
        return false;
    }

    // handle captures
    PieceInterface *capturedPiece = m_board.getPieceAt(to);
    bool isCapture = capturedPiece != nullptr;
    bool isEnPassant = false;

    // en passant check
    if (piece->getType() == PieceType::PAWN && !isCapture)
    {
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

    // move the piece
    m_board.removePiece(from, false);
    piece->move(to);
    m_board.putPiece(piece);

    // only mark pieces as moved after successful regular move
    if (!isReplay && (piece->getType() == PieceType::KING || piece->getType() == PieceType::ROOK))
    {
        m_pgn.markPieceMoved(piece->getType(), piece->getColor(), from.col, false);
    }

    // handle pawn promotion
    if (piece->getType() == PieceType::PAWN && (to.row == 1 || to.row == 8))
    {
        PieceType promotionType = handlePromotion(to);
        piece = m_board.getPieceAt(to);
        std::string promotionNotation = std::string(1, from.col) + std::to_string(from.row) +
                                        " -> " + std::string(1, to.col) + std::to_string(to.row) +
                                        "=" + promotionTypeToString(promotionType);
        if (!isReplay)
        {
            m_pgn.writeTurn(piece->getColor(), piece->getType(), from.col, from.row, to.col, to.row, promotionNotation);
        }
        m_moveType = MoveType::PROMOTION;
    }
    else if (!isReplay)
    {
        m_pgn.writeTurn(piece->getColor(), piece->getType(), from.col, from.row, to.col, to.row, "");
    }

    m_currentTurnColor = (m_currentTurnColor == PieceColor::WHITE) ? PieceColor::BLACK : PieceColor::WHITE;
    if (m_currentTurnColor == PieceColor::WHITE)
        turn++;

    PieceColor oppositeColor = (m_currentTurnColor == PieceColor::WHITE) ? PieceColor::BLACK : PieceColor::WHITE;
    if (isKingInCheck(oppositeColor)) {
        if (isCheckmate(oppositeColor)) {
            m_pgn.writeTurn(piece->getColor(), piece->getType(), from.col, from.row, to.col, to.row, "");
            
            std::string winner = (oppositeColor == PieceColor::BLACK) ? "White" : "Black";
            std::println("Checkmate! {0} wins!", winner);
            m_pgn.writeResult(winner == "White" ? "1-0" : "0-1");
            
        }
    }

    return true;
}

bool GameManager::handleCastling(const Position &from, const Position &to)
{
    auto *king = m_board.getPieceAt(from);
    if (!king || king->getType() != PieceType::KING) {
        return false;
    }

    if (from.col != 'e' ||
        (king->getColor() == PieceColor::WHITE && from.row != 1) ||
        (king->getColor() == PieceColor::BLACK && from.row != 8) ||
        m_pgn.hasPieceMoved(PieceType::KING, king->getColor(), from.col)) {
        return false;
    }

    char rookCol = (to.col > from.col) ? 'h' : 'a';
    char newRookCol = (to.col > from.col) ? 'f' : 'd';
    Position rookPos(rookCol, from.row);
    auto *rook = m_board.getPieceAt(rookPos);

    if (!rook || rook->getType() != PieceType::ROOK ||
        m_pgn.hasPieceMoved(PieceType::ROOK, king->getColor(), rookCol)) {
        return false;
    }

    int step = (to.col > from.col) ? 1 : -1;
    for (char col = from.col + step; col != rookCol; col += step) {
        if (m_board.getPieceAt(Position(col, from.row)) ||
            isSquareUnderAttack(Position(col, from.row), king->getColor())) {
            return false;
        }
    }

    m_board.removePiece(from, false);
    m_board.removePiece(rookPos, false);
    king->move(to);
    rook->move(Position(newRookCol, from.row));
    m_board.putPiece(king);
    m_board.putPiece(rook);

    m_pgn.markPieceMoved(PieceType::KING, king->getColor(), from.col, false);
    m_pgn.markPieceMoved(PieceType::ROOK, king->getColor(), rookCol, false);

    return true;
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
    if (!isKingInCheck(color)) {
        return false;
    }

    MoveManager mm(&m_pgn);
    
    for (int fromRow = 1; fromRow <= 8; fromRow++) {
        for (char fromCol = 'a'; fromCol <= 'h'; fromCol++) {
            Position from(fromCol, fromRow);
            PieceInterface* piece = m_board.getPieceAt(from);
            
            if (!piece || piece->getColor() != color) {
                continue;
            }

            for (int toRow = 1; toRow <= 8; toRow++) {
                for (char toCol = 'a'; toCol <= 'h'; toCol++) {
                    Position to(toCol, toRow);
                    
                    if (!mm.isValidMove(from, to, m_board, *piece)) {
                        continue;
                    }
                    
                    PieceInterface* capturedPiece = m_board.getPieceAt(to);
                    m_board.removePiece(from, false);
                    if (capturedPiece) {
                        m_board.removePiece(to, false);
                    }
                    piece->move(to);
                    m_board.putPiece(piece);

                    bool stillInCheck = isKingInCheck(color);

                    m_board.removePiece(to, false);
                    piece->move(from);
                    m_board.putPiece(piece);
                    if (capturedPiece) {
                        m_board.putPiece(capturedPiece);
                    }

                    if (!stillInCheck) {
                        return false;  
                    }
                }
            }
        }
    }
    return true;  
}

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
    m_board.displayBoardConsole(m_currentTurnColor); 
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
    // case 1: only kings
    if (hasOnlyKing(PieceColor::WHITE) && hasOnlyKing(PieceColor::BLACK))
    {
        return true;
    }

    // case 2: king and minor piece (knight and bishop) vs king
    if ((hasOnlyKing(PieceColor::WHITE) && hasOnlyKingAndMinorPiece(PieceColor::BLACK)) ||
        (hasOnlyKing(PieceColor::BLACK) && hasOnlyKingAndMinorPiece(PieceColor::WHITE)))
    {
        return true;
    }

    return false;
}

bool GameManager::hasOnlyKing(PieceColor color) const
{
    int pieceCount = 0;
    bool hasKing = false;

    for (int row = 1; row <= 8; row++)
    {
        for (char col = 'a'; col <= 'h'; col++)
        {
            PieceInterface *piece = m_board.getPieceAt(Position(col, row));
            if (piece && piece->getColor() == color)
            {
                pieceCount++;
                if (piece->getType() == PieceType::KING)
                {
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

    for (int row = 1; row <= 8; row++)
    {
        for (char col = 'a'; col <= 'h'; col++)
        {
            PieceInterface *piece = m_board.getPieceAt(Position(col, row));
            if (piece && piece->getColor() == color)
            {
                pieceCount++;
                if (piece->getType() == PieceType::KING)
                {
                    hasKing = true;
                }
                else if (piece->getType() == PieceType::BISHOP ||
                         piece->getType() == PieceType::KNIGHT)
                {
                    hasMinorPiece = true;
                }
            }
        }
    }

    return hasKing && hasMinorPiece && pieceCount == 2;
}

const Board &GameManager::getBoard() const { return m_board; }

PieceType GameManager::handlePromotion(const Position &pos)
{
    m_promotionFlag = true;
    char promotion;
    std::string input;

    std::cout << "promote pawn to (Q/R/B/N): ";
    std::getline(std::cin, input);
    while (input.empty() || std::string("QRBN").find(std::toupper(input[0])) == std::string::npos)
    {
        std::cout << "invalid input. promote pawn to (Q/R/B/N): ";
        std::getline(std::cin, input);
    }
    promotion = std::toupper(input[0]);

    PieceColor color = m_board.getPieceAt(pos)->getColor();
    m_board.removePiece(pos, true);

    PieceType newType;
    switch (promotion)
    {
    case 'Q':
        newType = PieceType::QUEEN;
        break;
    case 'R':
        newType = PieceType::ROOK;
        break;
    case 'B':
        newType = PieceType::BISHOP;
        break;
    case 'N':
        newType = PieceType::KNIGHT;
        break;
    default:
        newType = PieceType::QUEEN;
        break; 
    }

    PieceInterface *newPiece = m_factory.createAndStorePiece(newType, pos, color);
    m_board.putPiece(newPiece);
    return newType;
}
