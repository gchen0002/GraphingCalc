#ifndef GRAPH_H
#define GRAPH_H

#include <SFML/Graphics.hpp>
#include "plot.h"
#include "graph_info.h"
#include "../vector/vector_class.h"
using namespace std;
class Graph {
public:
    Graph(){
        //
    }
    Graph(Graph_Info* info): _info(info), _plotter(info){
        //initialize your _poinnts vector from plot
        _points = _plotter(); 
        //after storing _info DONE
    }
    void update(int command);
    void draw(sf::RenderTarget& target);
    void set_info();
private:
    Graph_Info* _info;
    Vector<sf::Vector2f> _points;
    Plot _plotter;
};

#endif // GRAPH_H 