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
    PgnNotation pgn;
    while (true)
    {
        std::string move;
        std::println("TURN {0}", GameManager::turn);
        std::println("{0} move", (m_gm.getCurrentTurnColor() == PieceColor::WHITE ? "white" : "black"));
        if (m_gm.getCurrentTurnColor() == PieceColor::WHITE)
            pgn.appendToFile(std::to_string(GameManager::turn) + ".");
        try
        {
            std::print("enter move: ");
            std::getline(std::cin, move);
            if (move.length() != 5)
                throw std::invalid_argument("invalid argument, give it in format [{current position} {destination}]\n without piece notation, we will figure it out");

            if (move[2] != ' ')
                throw std::invalid_argument("invalid argument, no space between positions");
            char fromCol = std::tolower(move[0]);
            int fromRow = move[1] - '0';
            char toCol = std::tolower(move[3]);
            int toRow = move[4] - '0';

            if (fromCol < 'a' || fromCol > 'h' || toCol < 'a' || toCol > 'h' || fromRow < 1 || fromRow > 8 || toRow < 1 || toRow > 8)
                throw std::out_of_range("move is out of bounds; columns must be a-h and rows 1-8");

            Position from(fromCol, fromRow);
            Position to(toCol, toRow);

            m_gm.movePiece(from, to);
            m_gm.displayBoard();
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error: " << e.what() << '\n';
        }
    }
}

void GameManager::movePiece(const Position &from, const Position &to)
{
    auto *piece = m_board.getPieceAt(from);

    // if there is no piece at given square
    if (piece == nullptr)
        throw std::runtime_error("No piece found at the given position");

    // if chosen piece is of a wrong color
    if (piece->getColor() != m_currentTurnColor)
    {
        std::println("it's not {0}'s turn", (m_currentTurnColor == PieceColor::WHITE) ? "black" : "white");
        return;
    }

    // castle
    if (piece->getType() == PieceType::KING && std::abs(to.col - from.col) == 2)
    {
    }

    // checks if the move is correct
    MoveManager mm;
    if (!mm.isValidMove(from, to, m_board, *piece))
    {
        std::println("invalid move for {0}", piece->getFullSymbol());
        return;
    }

    // moving piece
    m_board.removePiece(from, false);

    if (piece == nullptr)
        throw("Error: Attempted to move a null piece");

    piece->move(to);
    m_board.putPiece(piece);
    std::println("moved {0} to {1}{2}", piece->getFullSymbol(), to.col, to.row);
    PgnNotation pgn;
    m_moveType = MoveType::MOVE;
    pgn.writeTurn(piece->getColor(), from.col, from.row, to.col, to.row, m_moveType);

    // opponent moves
    m_currentTurnColor = (m_currentTurnColor == PieceColor::WHITE) ? PieceColor::BLACK : PieceColor::WHITE;
    if (m_currentTurnColor == PieceColor::WHITE)
        turn++;
}

bool GameManager::handleCastling(const Position &from, const Position &to)
{
    auto *king = m_board.getPieceAt(from);
    if (!isFirstMove(king))
        return false;

    char rookCol = (to.col > from.col) ? 'h' : 'a';
    char newRookCol = (to.col > from.col) ? 'f' : 'd';

    Position rookPos(rookCol, from.row);
    auto *rook = m_board.getPieceAt(rookPos);

    if (!rook || !isFirstMove(rook))
        return false;

    int direction = (to.col > from.col) ? 1 : -1;
    for (char col = from.col + direction; col != rookCol; col += direction)
    {
        Position pos(col, newRookCol);
        if (m_board.getPieceAt(pos) != nullptr || isSquareUnderAttack(pos, king->getColor()))
            return false;
    }

    // performing castle
    m_board.removePiece(from, false);
    m_board.removePiece(rookPos, false);
    king->move(to);
    rook->move(Position(newRookCol, from.row));
    m_board.putPiece(king);
    m_board.putPiece(rook);

    return true;
}
void GameManager::handlePromotion(const Position &pos)
{
    char promotion;
    do
    {
        std::cout << "Promote pawn to (Q/R/B/N): ";
        std::cin >> promotion;
        promotion = std::toupper(promotion);
    } while (promotion != 'Q' && promotion != 'R' && promotion != 'B' && promotion != 'N');

    PieceInterface *pawn = m_board.getPieceAt(pos);
    PieceColor color = pawn->getColor();
    m_board.removePiece(pos);

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
}

bool GameManager::isSquareUnderAttack(const Position &pos, PieceColor defendingColor) const
{
    MoveManager mm;
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
                    MoveManager mm;
                    if (!mm.isValidMove(from, to, m_board, *piece))
                        continue;
                    PieceInterface *capturedPiece = m_board.getPieceAt(to);
                    m_board.removePiece(to, false);
                    if(capturedPiece) m_board.removePiece(to, false);
                    piece->move(to);
                    m_board.putPiece(piece);

                    // if king is still in check
                    bool isStillInCheck = isKingInCheck(color);

                    // undo move
                    m_board.removePiece(to, false);
                    piece->move(from);
                    m_board.putPiece(piece);
                    if (capturedPiece) m_board.putPiece(capturedPiece);

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
    if(!piece) return false;

    // for white
    if(piece->getColor() == PieceColor::WHITE)
    {
        if(piece->getType() == PieceType::KING)
        {
            return piece->getPosition().col == 'e' && piece->getPosition().row == 1;
        }
        else if(piece->getType() == PieceType::ROOK)
        {
            return (piece->getPosition().col == 'a' && piece->getPosition().row == 1) || (piece->getPosition().col == 'h' && piece->getPosition().row == 1);
        }
    }

    // for black
    if(piece->getColor() == PieceColor::BLACK)
    {
        if(piece->getType() == PieceType::KING)
        {
            return piece->getPosition().col == 'e' && piece->getPosition().row == 8;
        }
        else if(piece->getType() == PieceType::ROOK)
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
