#include "graph.h"
#include "constants.h"
#include <SFML/Graphics.hpp> 

Graph::Graph() {

}

void Graph::update() {
    _points.clear(); // Clear previous points

    // Hardcode points for y = x
    for (int i = 0; i < 10; ++i) {
        float x = 50.0f + (i * 50.0f); 
        float y = x;                     
        _points.push_back(sf::Vector2f(x, y));
    }
}

void Graph::draw(sf::RenderTarget& target) {
    sf::CircleShape pointShape(3.0f); // Small circle for each point
    pointShape.setFillColor(sf::Color::Yellow);

    for (const auto& point : _points) {
        pointShape.setPosition(point); // Set position for each point
        target.draw(pointShape);
    }
} 