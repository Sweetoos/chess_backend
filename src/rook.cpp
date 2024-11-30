#include "rook.h"

char Rook::getPieceAcronym()
{
    return m_acronym;
}

int Rook::getValue()
{
    return m_value;
}


bool Rook::canJump()
{
    return false;
}
