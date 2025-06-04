#ifndef CHEN_FUNCTION_H
#define CHEN_FUNCTION_H

#include "token.h"
#include <string>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <iostream>
#include <cassert>


class Function : public Token {
private:
    std::string _func_name;
    int _args_count;

public:
    Function(const string& func_name, int args_count)
        : Token(6), _func_name(func_name), _args_count(args_count) {
        }

    int get_num_args() const { return _args_count; }
    string get_name() const { return _func_name; }

    // Evaluates with already resolved double arguments from RPN
    double evaluate(const vector<double>& args) const {
        if (args.size() != static_cast<size_t>(_args_count)) {
            throw runtime_error("Function '" + _func_name + "' called with " + std::to_string(args.size()) + " arguments, but expects " + std::to_string(_args_count));
        }

        if (_args_count == 1) {
            double arg = args[0];
            if (_func_name == "sin") return std::sin(arg);
            if (_func_name == "cos") return std::cos(arg);
            if (_func_name == "tan") return std::tan(arg);
        } else if (_args_count == 2) {
            double arg1 = args[0];
            double arg2 = args[1]; 
            if (_func_name == "pow") {
                return std::pow(arg1, arg2); 
            }
            
        }
        throw runtime_error("Unknown or unsupported function: " + _func_name + " with arg_count:" + std::to_string(_args_count));
    }
    
    void print(std::ostream& outs = std::cout) const {
        outs << _func_name;
    }
};

#endif // CHEN_FUNCTION_H
