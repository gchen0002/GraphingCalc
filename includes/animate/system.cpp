#include "system.h"
#include "random.h"
#include "constants.h"
#include <iostream>

System::System()
{
    // _graph & _info is default constructed
}

//------------------------------------------------------------------
//------------------------------------------------------------------

void System::Step(int command)
{
    _graph.update(command); 
}

void System::Draw(sf::RenderWindow &window)
{
    _graph.draw(window); 
}

int System::Size()
{
    return 0; 
}