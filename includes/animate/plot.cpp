#include "plot.h"
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <cctype>      // For isdigit, isalpha, isspace


Queue<Token*> tokenizeExpression(const string& equation) {
    Queue<Token*> infix_queue;
    
    for (int i = 0; i < equation.length(); i++) {
        char c = equation[i];

        if (isspace(c)) { // Skip spaces
            continue;
        } 
        else if (isdigit(c)) { // Number (integer)
            string num_str;
            num_str += c;
            while (i + 1 < equation.length() && isdigit(equation[i+1])) {
                num_str += equation[++i];
            }
            infix_queue.push(new Integer(stoi(num_str))); 
        } 
        else if (isalpha(c)) { // variable or function
            string var_or_func;
            var_or_func += c;
            while (i + 1 < equation.length() && isalpha(equation[i+1])) {
                var_or_func += equation[++i];
            }

            if (var_or_func == "x" || var_or_func == "X") {
                infix_queue.push(new Variable(var_or_func));
            } else if (var_or_func == "sin") {
                infix_queue.push(new Function("sin", 1));
            } else if (var_or_func == "cos") {
                infix_queue.push(new Function("cos", 1));
            } else if (var_or_func == "tan") {
                infix_queue.push(new Function("tan", 1));
            } else if (var_or_func == "pow") {
                infix_queue.push(new Function("pow", 2));
            } else if (var_or_func == "atan2") {
                infix_queue.push(new Function("atan2", 2));
            }
        } 
        else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') { // Operators
            infix_queue.push(new Operator(string(1, c)));
        } 
        else if (c == '(') { // Left Parenthesis
            infix_queue.push(new Token(3)); 
        } 
        else if (c == ')') { // Right Parenthesis
            infix_queue.push(new Token(4)); 
        } 
    }
    return infix_queue;
}

void Plot::set_info(Graph_Info* new_info) {
    _info = new_info;
}


vector<sf::Vector2f> Plot::operator()() {
    vector<sf::Vector2f> plot_points;
    // tokenize the equation
    Queue<Token*> infix_q = tokenizeExpression(_info->_equation);
    
    // shuntingyard and rpn
    ShuntingYard sy;
    Queue<Token*> postfix_q = sy.postfix(infix_q);   
    RPN rpn(postfix_q);  

    float xmin = _info->_domain.x;
    float xmax = _info->_domain.y;
    
    int num_points = _info->_points;

    // increment
    float increment = (xmax - xmin) / (num_points);

    for (int i = 0; i < num_points; i++) {
        float x = xmin + i * increment;
        float y = rpn(x);
        plot_points.push_back(translate(sf::Vector2f(x, y)));
    }
    
    return plot_points;
}

sf::Vector2f Plot::translate(sf::Vector2f raw) {
    // screen dimensions
    sf::Vector2f screen_dimensions = sf::Vector2f(WORK_PANEL/2, SCREEN_HEIGHT/2);
    // graph origin
    double origin_x = (_info->_domain.y + _info->_domain.x) / 2;
    double origin_y = 0;
    sf::Vector2f graph_origin = sf::Vector2f(origin_x, origin_y);

    // increment
    double graph_increment = (_info->_domain.y - _info->_domain.x) / (_info->_points);
    double x_increment = WORK_PANEL / (_info->_points);
    double y_increment = SCREEN_HEIGHT / (_info->_points);

    // screen coords = x/y + ((difference of x/y of the graph_origin) / increment) * x/y increment
    double screen_x = screen_dimensions.x + ((raw.x - graph_origin.x) / graph_increment) * x_increment;
    double screen_y = screen_dimensions.y + ((graph_origin.y - raw.y) / graph_increment) * y_increment;
    return sf::Vector2f(screen_x, screen_y);
}

sf::VertexArray Plot::plotAxis(){
    // x-axis and y-axis
    sf::Vector2f translated = translate(sf::Vector2f(0, 0));
    // 2 points for each axis
    sf::VertexArray grid_axis(sf::PrimitiveType::Lines, 4);
    
    // x-axis
    
    grid_axis[0].position = sf::Vector2f(0,translated.y);
    grid_axis[0].color = sf::Color::White;
    grid_axis[1].position = sf::Vector2f(WORK_PANEL, translated.y);
    grid_axis[1].color = sf::Color::White;

    // y-axis
    
    grid_axis[2].position = sf::Vector2f(translated.x, 0);
    grid_axis[2].color = sf::Color::White;
    grid_axis[3].position = sf::Vector2f(translated.x, SCREEN_HEIGHT);
    grid_axis[3].color = sf::Color::White;

    return grid_axis;

}
