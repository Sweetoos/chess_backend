// chess.cpp
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
    m_gm.displayBoard();
    while (true)
    {
        std::string move;
        std::println("TURN {0}", GameManager::turn);
        std::println("{0} move", (m_gm.getCurrentTurnColor() == PieceColor::WHITE ? "white" : "black"));
        try
        {
            std::print("enter move: ");
            std::getline(std::cin, move);
            //draw mechanic
            if(move=="draw")
            {
                std::println("Draw!");
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
                    
                    if (m_gm.isKingInCheck(m_gm.getCurrentTurnColor()))
                        std::println("CHECK!");

                    if (m_gm.isCheckmate(m_gm.getCurrentTurnColor()))
                    {
                        std::println("Checkmate! {0} wins!", 
                            (m_gm.getCurrentTurnColor() == PieceColor::BLACK) ? "White" : "Black");
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
            m_gm.displayBoard(); // Display the board even if there is an error
        }
    }
}

bool GameManager::movePiece(const Position &from, const Position &to)
{
    auto *piece = m_board.getPieceAt(from);

    // if there is no piece at given square
    if (piece == nullptr)
        throw std::runtime_error("No piece found at the given position");

    // if chosen piece is of a wrong color
    if (piece->getColor() != m_currentTurnColor)
    {
        std::println("it's not {0}'s turn", (m_currentTurnColor == PieceColor::WHITE) ? "black" : "white");
        return false;
    }

    // castle
    if (piece->getType() == PieceType::KING && std::abs(to.col - from.col) == 2)
    {
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
    }

    // checks if the move is correct
    MoveManager mm(&m_pgn);  // Pass PgnNotation reference here
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
            // Capture the enemy pawn (which is on the same rank as the capturing pawn's starting position)
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
        piece = m_board.getPieceAt(to); // Update the piece pointer to the new piece
        std::string promotionNotation = std::string(1, from.col) + std::to_string(from.row) + " -> " + std::string(1, to.col) + std::to_string(to.row) + "=" + promotionTypeToString(promotionType);
        m_pgn.writeTurn(piece->getColor(), piece->getType(), from.col, from.row, to.col, to.row, promotionNotation);
        m_moveType = MoveType::PROMOTION;
        m_currentTurnColor = (m_currentTurnColor == PieceColor::WHITE) ? PieceColor::BLACK : PieceColor::WHITE;
        if (m_currentTurnColor == PieceColor::WHITE)
            turn++;
        displayBoard(); // Display the board after promotion
        std::println("TURN {0}", GameManager::turn);
        std::println("{0} move", (getCurrentTurnColor() == PieceColor::WHITE ? "white" : "black"));
        std::print("enter move: ");
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
    auto *king = m_board.getPieceAt(from);
    if (!isFirstMove(king) || m_pgn.hasPieceMoved(PieceType::KING, king->getColor(), from.col))
        return false;

    char rookCol = (to.col > from.col) ? 'h' : 'a';
    char newRookCol = (to.col > from.col) ? 'f' : 'd';

    Position rookPos(rookCol, from.row);
    auto *rook = m_board.getPieceAt(rookPos);

    if (!rook || !isFirstMove(rook) || m_pgn.hasPieceMoved(PieceType::ROOK, rook->getColor(), rookCol))
        return false;

    // check if path is clear and not under attack
    int direction = (to.col > from.col) ? 1 : -1;
    char col = from.col + direction;
    while (col != rookCol)
    {
        Position pos(col, from.row);
        if (m_board.getPieceAt(pos) != nullptr || isSquareUnderAttack(pos, king->getColor()))
            return false;
        col += direction;
    }

    // check if king would pass through or land on attacked square
    if (isSquareUnderAttack(from, king->getColor()) || 
        isSquareUnderAttack(to, king->getColor()))
        return false;

    // performing castle
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
    m_promotionFlag=true;
    char promotion;
    do
    {
        std::cout << "Promote pawn to (Q/R/B/N): ";
        std::cin >> promotion;
        promotion = std::toupper(promotion);
    } while (promotion != 'Q' && promotion != 'R' && promotion != 'B' && promotion != 'N');

    PieceColor color = m_board.getPieceAt(pos)->getColor();
    m_board.removePiece(pos, true); // Ensure the pawn is deleted

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
    }
    PieceInterface *newPiece = m_factory.createAndStorePiece(newType, pos, color);
    m_board.putPiece(newPiece);
    return newType;
}

bool GameManager::isSquareUnderAttack(const Position &pos, PieceColor defendingColor) const
{
    MoveManager mm(&m_pgn);  // Fixed: use address-of operator to pass pointer
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
    Position kingPos('a', 1); // default value
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
                for (char toCol = 'a'; toCol <= 'h'; toCol++)
                {
                    Position to(toCol, toRow);
                    MoveManager mm(&m_pgn); // Fix: pass pointer to m_pgn
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
