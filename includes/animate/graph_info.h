#ifndef GRAPH_INFO_H
#define GRAPH_INFO_H

#include <SFML/Graphics.hpp>
#include "constants.h"
#include <iostream>
#include <fstream>
struct Graph_Info{
        Graph_Info(){
            _window_dimensions = sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT);
            _equation = "y = sin(cos(x))";
            _scale = sf::Vector2f(5, 5);
            _domain = sf::Vector2f(-5,5);
            _history.push_back(_equation);

            // get history from history.txt
            ifstream infile("history.txt");
            // check is history.txt exists if not creats one.
            if(!infile.is_open()){
                ofstream ofile("history.txt");
                ofile.close();
                ifstream infile("history.txt");
            }
            string line;
            while(getline(infile, line)){
                _history.push_back(line);
                cout << "PUSHING TO HISTORY" << endl;
            }
            infile.close();
        }
        string _equation;
        sf::Vector2f _window_dimensions, _scale, _domain;
        const float _points = 4000.0f;
        vector<string> _history;
};

#endif