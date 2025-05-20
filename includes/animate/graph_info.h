#ifndef GRAPH_INFO_H
#define GRAPH_INFO_H

#include <SFML/Graphics.hpp>
#include "graph.h"
#include "constants.h"
struct Graph_Info{
        Graph_Info(){
            _window_dimensions = sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT);
            // empty for now
            _equation = "";
            _scale = sf::Vector2f(0, 0);
            _domain = sf::Vector2f(0,0);
            _points = 0;
        }
        string _equation;
        sf::Vector2f _window_dimensions, _scale, _domain;
        int _points;

};

#endif