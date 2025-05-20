#ifndef PLOT_H
#define PLOT_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "graph.h"
#include "constants.h"
#include "graph_info.h"
#include "../linked_list_functions/linked_list_functions.h"
#include "../shunting_yard/shunting_yard.h"
#include "../rpn/rpn.h"



class Plot {
    public:
        Plot(Graph_Info* info): _info(info){}
    private:
        Graph_Info* _info;

};




#endif