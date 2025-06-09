#ifndef PLOT_H
#define PLOT_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "graph_info.h"
#include "../shunting_yard/shunting_yard.h"
#include "../rpn/rpn.h"
#include "../token/token.h"
#include "../vector/vector_class.h"

class Plot {
    public:
        Plot(){}
        Plot(Graph_Info* info): _info(info){}
        void set_info(Graph_Info* new_info);
        Queue<Token*> tokenizeExpression(const string& equation);
        sf::Vector2f translate(sf::Vector2f raw);
        Vector<sf::Vector2f> operator()();
        sf::VertexArray plotAxis();
        
    private:
        Queue<Token*> _post_fix;
        Graph_Info* _info;
        Vector<sf::Vector2f> _points;
};




#endif