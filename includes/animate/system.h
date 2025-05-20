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
//    vector<Particle> system;
    sf::CircleShape shape;
    sf::Vector2f vel;
    Graph _graph;
};

#endif // SYSTEM_H
