#include <iostream>
#include "classes.h"

int main()
{
    try
    {
        Chess game;
        game.run();
    }
    catch(const std::exception& e)
    {
        std::cerr <<"Error: "<< e.what() << '\n';
    }

}