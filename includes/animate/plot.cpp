#include "plot.h"
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <cctype>      // For isdigit, isspace


// converts string to infix Queue<Token*>
// needs to handle variables, trig later
Queue<Token*> tokenizeExpression(const string& equation) {
    Queue<Token*> infix_queue;
    // cout << "entering tokenize" << endl;
    // cout << equation << "123123123" << endl;
    for (int i = 0; i < equation.length(); i++) {
        char c = equation[i];
        // cout << "looping" << endl;
        if (isspace(c)) { // skip spaces
            continue;
            // cout << "skipping spaces";
        }

        if (isdigit(c)) {
            infix_queue.push(new Integer(c));
            // cout << "isdigit" << endl; 
        }
        // operator case
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            infix_queue.push(new Operator(string(1, c))); 
            // cout << "operators" << endl;
        } else if (c == 'x') { // variable 'x'
            infix_queue.push(new Variable(string(1, c)));
        }

    }
    // cout << "TOKENIZE SUCCCESFFUL" << endl;
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

    // calculate visible x-range directly
    float visible_width = WORK_PANEL / _info->_scale.x;  // how much math we can see horizontally
    float start_x = _info->_domain.x - visible_width / 2;  // leftmost x value
    float end_x = _info->_domain.x + visible_width / 2;    // rightmost x value
    float step_size = visible_width / (_info->_points - 1); // x increment per point

    // Generate points 
    for (int i = 0; i < _info->_points; i++) {
        float x = start_x + i * step_size;
        float y = rpn(x);
        plot_points.push_back(translate(sf::Vector2f(x, y)));
    }
    
    return plot_points;
}

sf::Vector2f Plot::translate(sf::Vector2f math_point) {
    // Center the graph at middle of work panel
    float center_x = WORK_PANEL / 2.0f;
    float center_y = SCREEN_HEIGHT / 2.0f;
    
    // Simple offset calculation from center
    float offset_x = (math_point.x - _info->_domain.x) * _info->_scale.x;
    float offset_y = (math_point.y - _info->_domain.y) * _info->_scale.y;
    
    return sf::Vector2f(center_x + offset_x, center_y - offset_y);  // flip y for screen coords
}


