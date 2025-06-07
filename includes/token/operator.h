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
    bool _is_unary;

public:
    // Constructor: Type 2 for Operator
    Operator(const string& op) : Token(2), _op(op), _is_unary(false) {
        // Basic validation for supported operators
        if (op != "+" && op != "-" && op != "*" && op != "/" && op != "^") { // Added ^ for future
             // For now, allow any string, ShuntingYard/RPN will validate known ops
        }
    }

    // Override print method
    void print(ostream& outs = cout) const override {
        outs << _op; // Print the operator symbol
    }

    string get_operator() const {
        return _op;
    }

    bool is_unary() const {
        return _is_unary;
    }

    void set_unary() {
        _is_unary = true;
    }

    // Get operator precedence
    int precedence() const {
        if (_is_unary) {
            return 4; // Unary operators have high precedence
        }
        if (_op == "^") { 
            return 5; // highest precedence
        } 
        if (_op == "*" || _op == "/") {
            return 2;
        } 
        if (_op == "+" || _op == "-") {
            return 1;
        }
        return 0; 
    }

};

#endif // CHEN_OPERATOR_H
