#include "classes.h"
#include <ctime>
#include <sstream>
#include "pgn.h"
#include <filesystem>

PgnNotation::PgnNotation()
{
    namespace fs=std::filesystem;
    const std::string folderName="games";
    if(!fs::exists(folderName))
    {
        if(fs::create_directory(folderName))
            std::cout<<"folder "<<folderName<<" created"<<'\n';
        else
            std::cerr<<"failed to create "<<folderName<<" folder"<<'\n';
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
    bool append=false;
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
        m_outFile << line + " ";
        m_outFile.flush();      
    }
    else
    {
        throw std::runtime_error("File is not open for writing.");
    }
}

void PgnNotation::writeTurn(const PieceColor &color, const char &fromCol, const int &fromRow, const char &toCol, const int &toRow, const MoveType &moveType)
{
    int turn=getCurrentTurn();
    switch (moveType)
    {
    case MoveType::MOVE:
    {
        appendToFile(toCol+std::to_string(toRow));
        break;
    }
    case MoveType::CAPTURE:
    {

    }
    }
}
