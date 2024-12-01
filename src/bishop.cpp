#include "classes.h"

char Bishop::getPieceAcronym()
{
    return m_acronym;
}
int Bishop::getValue()
{
    return m_value;
}

bool Bishop::canJump()
{
    return false;
}
