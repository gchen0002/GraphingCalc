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
}

//------------------------------------------------------------------
//------------------------------------------------------------------

void System::Step(int command)
{
    // all this is the responsibility of the
    //  individual object:
    shape.move(vel);
    sf::Vector2f pos = shape.getPosition();
    // WORK_PANEL and SCREEN_HEIGHT are floats. shape radius is 10.f.
    // the boundary check should account for the shape's size (diameter = 2 * radius).
    float diameter = shape.getRadius() * 2.f;
    if ((pos.x + diameter) >= WORK_PANEL) // check right edge of circle
        vel.x *= -1;
    if (pos.x <= 0) // check left edge of circle
        vel.x *= -1;
    if ((pos.y + diameter) >= SCREEN_HEIGHT) // check bottom edge of circle
        vel.y *= -1;
    if (pos.y <= 0) // check top edge of circle
        vel.y *= -1;
}

void System::Draw(sf::RenderWindow &window)
{
    // window.clear(); // this clear is redundant, animate::render() already clears.
    window.draw(shape);
}

int System::Size()
{
    return 0; // Or 1 if it represents the single shape for now
}