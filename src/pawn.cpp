#include "classes.h"

char Pawn::getPieceAcronym()
{
    return m_acronym;
}

int Pawn::getValue()
{
    return m_value;
}



bool Pawn::canJump()
{
    return false;
}
