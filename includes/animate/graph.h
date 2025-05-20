#ifndef GRAPH_H
#define GRAPH_H

#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;
class Graph {
public:
    Graph();
    void update();
    void draw(sf::RenderTarget& target);

private:
    vector<sf::Vector2f> _points;
};

#endif // GRAPH_H 