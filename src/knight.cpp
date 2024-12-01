#include "classes.h"

char Knight::getPieceAcronym()
{
    return m_acronym;
}
int Knight::getValue()
{
    return m_value;
}



bool Knight::canJump()
{
    return true;
};
