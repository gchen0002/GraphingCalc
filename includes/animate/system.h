#ifndef SYSTEM_H
#define SYSTEM_H
#include <vector>
#include <SFML/Graphics.hpp>
#include "graph.h"

using namespace std;
class System
{
public:
    System();
    void Step(int command);
    int Size();
    void Draw(sf::RenderWindow& window);
private:
    Graph_Info* _info;
    Graph _graph;
};

#endif // SYSTEM_H
