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
    // virtual void Print(ostream& outs);
    Variable(const string& var = "X") : Token(5), _variable(var) {}
    void Print(ostream& outs)
    {
        outs << _variable << endl;
    }
    
    void type() { }
    string getValue() { return _variable; }

private:
    string _variable = "X";


};

#endif