#include "plot.h"
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <cctype>      // For isdigit, isspace


// converts string to infix Queue<Token*>
// needs to handle spaces, digits, and operators later
Queue<Token*> tokenizeExpression(const std::string& equation) {
    Queue<Token*> infix_queue;
    for (size_t i = 0; i < equation.length(); ++i) {
        char c = equation[i];

        if (isspace(c)) { // skip spaces
            continue;
        }

        if (isdigit(c)) {
            infix_queue.push(new Integer(c)); 
        }
        // operator case
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            infix_queue.push(new Operator(string(1, c))); 
        }
    }
    return infix_queue;
}

void Plot::set_info(Graph_Info* new_info) {
    _info = new_info;
}


std::vector<sf::Vector2f> Plot::operator()() {
    std::vector<sf::Vector2f> plot_points;

    Queue<Token*> infix_q = tokenizeExpression(_info->_equation);
    

    ShuntingYard sy;
    Queue<Token*> postfix = sy.postfix(infix_q);   

    RPN rpn(postfix);  

    // domain
    sf::Vector2f plot_domain = _info->_domain;
    sf::Vector2f old_domain = plot_domain;


    //map cartesian to screen size
    int scale_factor = WORK_PANEL / (plot_domain.y - plot_domain.x);


    for (float x = plot_domain.x ; x <= plot_domain.y; x += 0.003f) {
        sf::Vector2f point(x * scale_factor, rpn(x) * scale_factor);
        plot_points.push_back(cartToSFML(point));
    }

    return plot_points;
}

sf::Vector2f Plot::cartToSFML(sf::Vector2f cartesian){
    // convert cartesian coordinate to SFML
    return sf::Vector2f(cartesian.x + WORK_PANEL / 2, SCREEN_HEIGHT / 2 - cartesian.y);
}