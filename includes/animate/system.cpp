#include "system.h"
#include "random.h"
#include "constants.h"
#include <iostream>

System::System()
{
    Random r;
    int xpos = 100;
    int ypos = 100;
    // the shape of the object, along with its velocity, acceleration,
    // position, etc. should be part of the individual object.
    shape = sf::CircleShape(10.f); // Use .f for float literal
    shape.setPosition(sf::Vector2f(static_cast<float>(xpos), static_cast<float>(ypos)));
    vel = sf::Vector2f(static_cast<float>(r.Next(-5, 5)), static_cast<float>(r.Next(-5, 5))); // random velocity
    int r_ = r.Next(0, 255);
    int g_ = r.Next(0, 255);
    int b_ = r.Next(0, 255);
    shape.setFillColor(sf::Color(static_cast<std::uint8_t>(r_), static_cast<std::uint8_t>(g_), static_cast<std::uint8_t>(b_))); // sf::Color takes Uint8
    // _graph is default constructed
}

//------------------------------------------------------------------
//------------------------------------------------------------------

void System::Step(int command)
{
    _graph.update(); // Call graph's update method
}

void System::Draw(sf::RenderWindow &window)
{
    _graph.draw(window); // Call graph's draw method
}

int System::Size()
{
    return 0; // Or 1 if it represents the single shape for now
}