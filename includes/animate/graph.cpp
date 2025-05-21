#include "graph.h"
#include "constants.h"
#include <SFML/Graphics.hpp> 

void Graph::update(int command){
    cout << "GRAPH-UPDATe" << endl;
    // blank for now
}
void Graph::draw(sf::RenderTarget& target) {
    sf::CircleShape pointShape(3.0f); // Small circle for each point
    pointShape.setFillColor(sf::Color::Yellow);

    for (const auto& point : _points) {
        pointShape.setPosition(point); // Set position for each point
        target.draw(pointShape);
    }
} 

void Graph::set_info(){
    _points = Plot();
}