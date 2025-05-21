#include "plot.h"
//ctor

Plot::Plot(Graph_Info* info): _info(info){}
//setter
void Plot::set_info(Graph_Info* new_info){
     _info = new_info;
}

vector<sf::Vector2f> Plot::operator()(){
    vector<sf::Vector2f> points;
    points.clear(); // Clear previous points

    // Hardcode points for y = x
    for (int i = 0; i < 10; ++i) {
        float x = 50.0f + (i * 50.0f); 
        float y = x;                     
        points.push_back(sf::Vector2f(x, y));
        points.push_back(sf::Vector2f(x+10, y));
    }
    return points;
}