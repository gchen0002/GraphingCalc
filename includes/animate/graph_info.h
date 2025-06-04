#ifndef GRAPH_INFO_H
#define GRAPH_INFO_H

#include <SFML/Graphics.hpp>
#include "constants.h"
struct Graph_Info{
        Graph_Info(){
            _window_dimensions = sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT);
            _equation = "y = sin(cos(x))";
            _scale = sf::Vector2f(5, 5);
            _domain = sf::Vector2f(-5,5);
        }
        string _equation;
        sf::Vector2f _window_dimensions, _scale, _domain;
        const float _points = 4000.0f;

};

#endif