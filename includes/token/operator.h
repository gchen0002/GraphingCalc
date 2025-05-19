#ifndef CHEN_OPERATOR_H
#define CHEN_OPERATOR_H

#include "token.h"
#include <string>
#include <iostream>
#include <stdexcept> // For potential errors

using namespace std;

class Operator : public Token {
private:
    string _op;

public:
    // Constructor: Type 2 for Operator
    Operator(const string& op) : Token(2), _op(op) {
        // Basic validation for supported operators
        if (op != "+" && op != "-" && op != "*" && op != "/" && op != "^") { // Added ^ for future
             // For now, allow any string, ShuntingYard/RPN will validate known ops
        }
    }

    // Override print method
    void print(ostream& outs = cout) const override {
        outs << _op; // Print the operator symbol
    }

    // Getter for the operator symbol
    string getOp() const {
        return _op;
    }

    // Get operator precedence
    int precedence() const {
        if (_op == "+" || _op == "-") {
            return 1;
        } else if (_op == "*" || _op == "/") {
            return 2;
        } else if (_op == "^") { 
            return 3;
        }
        return 0; 
    }

};

#endif // CHEN_OPERATOR_H
