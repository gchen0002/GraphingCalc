#ifndef CHEN_LEFTPAREN_H
#define CHEN_LEFTPAREN_H

#include "token.h"
#include <iostream>

using namespace std;

class LeftParen : public Token {
public:
    // Constructor: Type 3 for Left Parenthesis
    LeftParen() : Token(3) {}

    // Override print method
    void print(ostream& outs = cout) const override {
        outs << "(";
    }

};

#endif // CHEN_LEFTPAREN_H
