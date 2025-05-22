#ifndef PLOT_H
#define PLOT_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "constants.h"
#include "graph_info.h"
#include "../shunting_yard/shunting_yard.h"
#include "../rpn/rpn.h"
#include "../queue/MyQueue.h"


class Plot {
    public:
        Plot(){}
        Plot(Graph_Info* info);
        void set_info(Graph_Info* new_info);
        vector<sf::Vector2f> operator()();
    private:
        Queue<Token*> _post_fix;
        Graph_Info* _info;

};




#endif