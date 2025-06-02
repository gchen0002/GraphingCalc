#include "graph.h"
#include "constants.h"
#include <SFML/Graphics.hpp> 


void Graph::update(int command){
    // cout << "GRAPH-UPDATe" << endl;

    // zooming in 
    if(command == 5){
        _info->_domain = sf::Vector2f(_info->_domain.x+2.0f, _info->_domain.y-2.0f);
    }
    // zooming out 
    if(command == 6){
        _info->_domain = sf::Vector2f(_info->_domain.x-2.0f, _info->_domain.y+2.0f);
    }
    // panning to the left
    else if(command == 3){
        _info->_domain = sf::Vector2f(_info->_domain.x-0.25f, _info->_domain.y-0.25f);
    }
    // panning to the right
    else if(command == 4){
        _info->_domain = sf::Vector2f(_info->_domain.x+0.25f, _info->_domain.x+0.25f);
    }
    //get updated points from plot
    _points = _plotter();
}
void Graph::draw(sf::RenderTarget& target) {
    // cout << "ENTERNING GRAPH GDRAW" << endl;
    // set_info();

    // 2 points for each axis
    sf::VertexArray grid_axis(sf::PrimitiveType::Lines, 4);

    // x-axis
    float x_axis_y_position = SCREEN_HEIGHT / 2.0f;
    grid_axis[0].position = sf::Vector2f(0, x_axis_y_position);
    grid_axis[0].color = sf::Color::White;
    grid_axis[1].position = sf::Vector2f(WORK_PANEL, x_axis_y_position);
    grid_axis[1].color = sf::Color::White;

    // y-axis
    float y_axis_x_position = WORK_PANEL / 2.0f;
    grid_axis[2].position = sf::Vector2f(y_axis_x_position, 0);
    grid_axis[2].color = sf::Color::White;
    grid_axis[3].position = sf::Vector2f(y_axis_x_position, SCREEN_HEIGHT);
    grid_axis[3].color = sf::Color::White;

    target.draw(grid_axis);

    // Draw Points from Plot
    sf::CircleShape pointShape(3.0f); // Small circle for each point
    pointShape.setFillColor(sf::Color::Yellow);

    for (const auto& point : _points) {
        pointShape.setPosition(point); // Set position for each point
        target.draw(pointShape);
    }
    // cout << "ENTERNING GRAPH GDRAW" << endl;
} 

void Graph::set_info(){
    // cout << "exiting plot()" << endl;
}