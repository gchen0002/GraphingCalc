#ifndef VARIABLE_H
#define VARIABLE_H

#include <iostream>
#include <iomanip>
#include "token.h"
#include <cmath>

using namespace std;

class Variable : public Token
{
public:
    Variable() : Token(5) {}
    Variable(const std::string& var = "x") : Token(5), _variable(var) {}
    void print(std::ostream& outs = std::cout) const override {
        outs << _variable;
    }
    
    int type() const override { return Token::type(); }
    std::string get_variable() const { return _variable; }

private:
    std::string _variable = "x";


};

#endif