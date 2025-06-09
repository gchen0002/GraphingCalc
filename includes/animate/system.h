#ifndef SYSTEM_H
#define SYSTEM_H
#include "../vector/vector_class.h"
#include <SFML/Graphics.hpp>
#include "graph.h"

using namespace std;
class System
{
public:
    System();
    System(Graph_Info* info): _info(info), _graph(info) {}
    void Step(int command);
    int Size();
    void Draw(sf::RenderWindow& window);
private:
    Graph_Info* _info;
    Graph _graph;
};

#endif // SYSTEM_H
