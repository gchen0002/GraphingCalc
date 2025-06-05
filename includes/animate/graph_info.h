#ifndef GRAPH_INFO_H
#define GRAPH_INFO_H

#include <SFML/Graphics.hpp>
#include "constants.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
struct Graph_Info{
        Graph_Info(){
            _window_dimensions = sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT);
            _equation = "y = cos(x)";
            _scale = sf::Vector2f(5, 5);
            _domain = sf::Vector2f(-5,5);
            setHistory();
            cout << "History: " << _history.size() << " items" << endl;
        }

        void setHistory(){
            // makes surehistory.txt exists and load from it
            ifstream infile("history.txt");
            if(!infile.is_open()){
                ofstream ofile("history.txt"); // Create if not exists
                ofile.close();
                // open again
                infile.open("history.txt"); 
            }
            _history.clear(); // clear existing history before loading from file to prevent duplicates
            string line;
            while(getline(infile, line)){
                if (!line.empty()) { 
                    _history.push_back(line);
                }
            }
            infile.close();
            
            // check if the current _equation is in _history
            bool found = false;
            for (const string& eq : _history) {
                if (eq == _equation) {
                    found = true;
                    break;
                }
            }
            // If not found, add it to _history and append to history.txt
            if (!found) {
                _history.push_back(_equation);
                // open in append mode to avoid clearing the file
                ofstream outfile("history.txt", ios::app); 
                if (outfile.is_open()) {
                    outfile << _equation << endl;
                    outfile.close();
                }
            }
        }
        string _equation;
        sf::Vector2f _window_dimensions, _scale, _domain;
        const float _points = 4000.0f;
        vector<string> _history;
};

#endif