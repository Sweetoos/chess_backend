#include <string>
#include <iostream>
#include <stdexcept>
#include <print>
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
            std::cin >> move;

            if (move.length() != 5)
                throw std::invalid_argument("invalid argument, give it in format {current position} {destination}\n without piece notation, we will figure it out");

            if (move[2] != ' ')
                throw std::invalid_argument("invalid argument, no space between positions");
            char fromCol = move[0];
            int fromRow = move[1];
            char toCol = move[3];
            int toRow = move[4];

            Position from(fromCol, fromRow);
            Position to(toCol, toRow);

            m_gm.movePiece(from,to);
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
    PieceInterface *piece = m_board.getPieceAt(from);

    if (!piece)
    {
        std::println("no piece at {0}{1}", from.col, from.row);
        return;
    }

    if (piece->getColor() != m_currentTurnColor)
    {
        std::println("it's not {0}'s turn", (m_currentTurnColor == PieceColor::WHITE) ? "black" : "white");
        return;
    }

    if (!piece->isValidMove(from, to, m_board))
    {
        std::println("invalid move for {0}", piece->getFullSymbol());
        return;
    }

    m_board.removePiece(from);
    piece->move(to);
    m_board.putPiece(piece);
    std::println("moved {0} to {0}{1}", piece->getFullSymbol(), to.col, to.row);

    // opponent move
    m_currentTurnColor = (m_currentTurnColor == PieceColor::WHITE) ? PieceColor::BLACK : PieceColor::WHITE;
}

void GameManager::setupBoard()
{
    for (char col = 'a'; col <= 'h'; col++)
    {
        m_board.putPiece(m_factory.createAndStorePiece("", Position(col, 2), PieceColor::WHITE));
        m_board.putPiece(m_factory.createAndStorePiece("", Position(col, 7), PieceColor::BLACK));
    }

    const char *pieces = "RNBQKBNR";
    for (int i = 0; i < 8; i++)
    {
        m_board.putPiece(m_factory.createAndStorePiece(std::string(1, pieces[i]), Position('a' + i, 1), PieceColor::WHITE));
        m_board.putPiece(m_factory.createAndStorePiece(std::string(1, pieces[i]), Position('a' + i, 8), PieceColor::BLACK));
    }
}

void GameManager::displayBoard() const
{
    m_board.displayBoardConsole();
}
