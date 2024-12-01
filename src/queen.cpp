#include "classes.h"

char Queen::getPieceAcronym()
{
    return m_acronym;
}

int Queen::getValue()
{
    return m_value;
}



bool Queen::canJump()
{
    return false;
}
