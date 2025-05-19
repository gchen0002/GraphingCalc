#ifndef CHEN_FUNCTION_H
#define CHEN_FUNCTION_H

#include "token.h"
#include <string>
#include <iostream>

using namespace std;

class Function : public Token {
private:
    string _name; // To store "X" or function names like "sin", "cos"

public:
    // Constructor: Type 5 for Function
    Function(const string& name) : Token(5), _name(name) {}

    // Override print method
    void print(ostream& outs = cout) const override {
        outs << _name;
    }

    // Getter 
    string getName() const {
        return _name;
    }


};

#endif // CHEN_FUNCTION_H
