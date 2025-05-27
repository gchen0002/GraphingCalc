#include "graph.h"
#include "constants.h"
#include <SFML/Graphics.hpp> 


void Graph::update(int command){
    cout << "GRAPH-UPDATe" << endl;
    // blank for now
}
void Graph::draw(sf::RenderTarget& target) {
    set_info();

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
} 

void Graph::set_info(){
    _points = Plot(); 
}