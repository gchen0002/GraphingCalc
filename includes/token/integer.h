#ifndef CHEN_INTEGER_H
#define CHEN_INTEGER_H

#include "token.h"
#include <iostream>
#include <cassert>
#include <stdexcept>
using namespace std;

class Integer : public Token {
    private:
        int _val; 

    public:
        // Constructor
        Integer(int val) : Token(1), _val(val) {}

        // Constructor for char input
        Integer(char val) : Token(1) {
            assert(val >= '0' && val <= '9' && "Invalid char for Integer token: Must be a digit.");
            _val = val - '0';
        }

        
        Integer(const char* s) : Token(1) {
            _val = *s - '0';
        }

        // Returns the type identifier for Number
        int type() const override {
            return Token::type();
        }

        // print method
        void print(ostream& outs = cout) const override {
            outs << _val; 
        }

        // Getter 
        int getValue() const {
            return _val;
        }

};

#endif