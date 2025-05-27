#ifndef GRAPH_H
#define GRAPH_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "plot.h"
#include "graph_info.h"
using namespace std;
class Graph {
public:
    Graph(){}
    Graph(Graph_Info* info): _info(info){}
    void update(int command);
    void draw(sf::RenderTarget& target);
    void set_info();
private:
    Graph_Info* _info;
    vector<sf::Vector2f> _points;
    Plot Plot;
};

#endif // GRAPH_H 