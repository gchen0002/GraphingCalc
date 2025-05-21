#ifndef GRAPH_H
#define GRAPH_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "plot.h"
using namespace std;
class Graph {
public:
    Graph();
    void update(int command);
    void draw(sf::RenderTarget& target);
    void set_info();
private:
    Graph_Info* _info;
    vector<sf::Vector2f> _points;
    Plot _plotter;
};

#endif // GRAPH_H 