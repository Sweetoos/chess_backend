//chess.cpp
#include <string>
#include <iostream>
#include <stdexcept>
#include <print>
#include <array>
#include "classes.h"
#include "chess.h"

/// @brief match turn
int GameManager::turn = 0;

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
        std::println("current turn: {0}", (m_gm.getCurrentTurn() == PieceColor::WHITE ? "white" : "black"));

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
                throw std::out_of_range("Move is out of bounds. Columns must be a-h and rows 1-8.");

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
    PieceInterface *piece = m_board.getPieceAt(from); //also tried auto

    // if there is no piece at given square
    if (piece==nullptr)
    {
        std::println("no piece at {0}{1}", from.col, from.row);
        return;
    }

    // if chosen piece is of a wrong color
    if (piece->getColor() != m_currentTurnColor)
    {
        std::println("it's not {0}'s turn", (m_currentTurnColor == PieceColor::WHITE) ? "black" : "white");
        return;
    }

    // checks if the move is correct
    MoveManager mm;
    if (!mm.isValidMove(from, to, m_board, *piece))
    {
        std::println("invalid move for {0}", piece->getFullSymbol());
        return;
    }

    // capture

    // moving piece
    m_board.removePiece(from);

    std::cout<<"debug, piece is "<<piece<<'\n';
    if (piece == nullptr)
        throw("Error: Attempted to move a null piece");
    std::cout<<"fsfsdf"<<'\n';
    piece->move(to);
    m_board.putPiece(piece);
    std::println("moved {0} to {0}{1}", piece->getFullSymbol(), to.col, to.row);

    // opponent move
    m_currentTurnColor = (m_currentTurnColor == PieceColor::WHITE) ? PieceColor::BLACK : PieceColor::WHITE;
    if (m_currentTurnColor == PieceColor::WHITE)
        turn++;
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
