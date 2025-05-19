#ifndef CHEN_RIGHTPAREN_H
#define CHEN_RIGHTPAREN_H

#include "token.h"
#include <iostream>

using namespace std;

class RightParen : public Token {
public:
    // Constructor: Type 4 for Right Parenthesis
    RightParen() : Token(4) {}

    // Override print method
    void print(ostream& outs = cout) const override {
        outs << ")";
    }

    // RightParen is also identified mainly by its type.
};

#endif // CHEN_RIGHTPAREN_H
