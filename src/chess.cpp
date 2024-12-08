#include <string>
#include "classes.h"
#include "chess.h"

Chess::Chess(PieceFactory &factory) : m_gm(factory)
{
    m_gm.setupBoard();
}

void Chess::run()
{
    m_gm.displayBoard();
}

void GameManager::setupBoard()
{
    for(char col='a';col<='h';col++)
    {
        m_board.putPiece(m_factory.createAndStorePiece("",Position(col,2),PieceColor::WHITE));
        m_board.putPiece(m_factory.createAndStorePiece("",Position(col,7),PieceColor::BLACK));
    }

    const char* pieces="RNBQKBNR";
    for(int i=0;i<8;i++)
    {
        m_board.putPiece(m_factory.createAndStorePiece(std::string(1,pieces[i]),Position('a'+i,1),PieceColor::WHITE));
        m_board.putPiece(m_factory.createAndStorePiece(std::string(1,pieces[i]),Position('a'+i,8),PieceColor::BLACK));
    }
}

void GameManager::displayBoard() const
{
    m_board.displayBoardConsole();
}
