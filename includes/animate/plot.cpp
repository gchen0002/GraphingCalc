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


    float domain_x = _info->_domain.x;
    float scale_x = _info->_scale.x;

    
    // x-range visible on the WORK_PANEL
    float math_x_min = (WORK_PANEL / 2.0f - domain_x) / scale_x;
    float math_x_max = (WORK_PANEL / 2.0f + domain_x) / scale_x;

    for (int i = 0; i < _info->_points; i++) {
        float current_math_x;

        current_math_x = math_x_min + static_cast<float>(i) * (math_x_max - math_x_min) / static_cast<float>(_info->_points - 1);

        float math_y = rpn(current_math_x);

        sf::Vector2f screen_point = translate(sf::Vector2f(current_math_x, math_y));
        plot_points.push_back(screen_point);
    }
    
    return plot_points;
}

sf::Vector2f Plot::translate(sf::Vector2f raw){
    // scale
    sf::Vector2f scale = _info->_scale;
    raw.x *= scale.x;
    raw.y *= scale.y;
    // domain
    sf::Vector2f domain = _info->_domain;
    raw.x += domain.x;
    raw.y -= domain.y;
    // translate
    sf::Vector2f ans(raw.x + WORK_PANEL/2, SCREEN_HEIGHT/2 - raw.y);
    return ans;
}


