#include "plot.h"
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <cctype>      // For isdigit, isspace


// converts string to infix Queue<Token*>
// needs to handle spaces, digits, and operators later
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
        } else continue;
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
    Queue<Token*> postfix = sy.postfix(infix_q);   
    // cout << "shunting yard success" << endl;
    RPN rpn(postfix);  
    // cout << "rpn success" << endl;

    
    float x = 0;
    float y = rpn();
    for(int i = 0; i < _info->_points; i++){
        x = 10.0f * i;
        sf::Vector2f translated = translate(sf::Vector2f(x,y));
        // cout << translated.x << " " << translated.y << endl;
        plot_points.push_back(translated);
    }
    // cout << "points success" << endl;
    return plot_points;
}

sf::Vector2f Plot::translate(sf::Vector2f raw){
    // scale
    sf::Vector2f scale = _info->_scale;
    raw.x *= scale.x;
    raw.y *= scale.y;
    // domain
    sf::Vector2f domain = _info->_domain;

    sf::Vector2f ans(raw.x + WORK_PANEL/2, SCREEN_HEIGHT/2 - raw.y);
    return ans;
}


