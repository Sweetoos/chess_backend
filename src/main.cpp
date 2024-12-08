#include <iostream>
#include "classes.h"

int main()
{
    try
    {
        PieceFactory factory;
        Chess game(factory);
        game.run();
    }
    catch(const std::exception& e)
    {
        std::cerr <<"Error: "<< e.what() << '\n';
    }

}