#include "graph.h"
#include "constants.h"
#include <SFML/Graphics.hpp> 


void Graph::update(int command){
    // cout << "GRAPH-UPDATe" << endl;

    // zooming in 
    if(command == 5){
        _info->_domain.x /= 2.0f;
        _info->_domain.y /= 2.0f;
    }
    // zooming out 
    if(command == 6){
        _info->_domain.x *= 2.0f;
        _info->_domain.y *= 2.0f;
    }
    // panning to the left
    else if(command == 3){
        _info->_domain.x -= 0.25f;
        _info->_domain.y -= 0.25f;
    }
    // panning to the right
    else if(command == 4){
        _info->_domain.x += 0.25f;
        _info->_domain.y += 0.25f;
    }
    //get updated points from plot
    _points = _plotter();
}
void Graph::draw(sf::RenderTarget& target) {
    // cout << "ENTERNING GRAPH GDRAW" << endl;
    // set_info();
    // draw grid
    sf::VertexArray grid = _plotter.plotAxis();
    target.draw(grid);
    // Draw Points from Plot
    sf::CircleShape pointShape(1.0f); // Small circle for each point
    pointShape.setFillColor(sf::Color::Yellow);

    for (int i = 0; i < _points.size(); i++) {
        sf::Vector2f point = _points[i];
        pointShape.setPosition(point); // Set position for each point
        target.draw(pointShape);
    }
    // cout << "ENTERNING GRAPH GDRAW" << endl;
} 

void Graph::set_info(){
    // cout << "exiting plot()" << endl;
}