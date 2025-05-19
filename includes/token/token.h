#ifndef CHEN_TOKEN_H
#define CHEN_TOKEN_H
#include <iostream>
#include <string> 
using namespace std;

class Token{
private:
    int _type; // 1 for Number, 2 for Operator, 3 for left parenthesis, 4 for right parenthesis

public:
    // Constructor 
    Token(int type) : _type(type) {}

    // Virtual destructor 
    virtual ~Token() {}

    // virtual getter
    virtual int type() const {
        return _type;
    }

    // virtual print function for debugging
    virtual void print(ostream& outs = cout) const {
        outs << "TOKEN"; 
    }

    friend ostream& operator<<(ostream& outs, const Token* token_ptr) {
        if (token_ptr) {
            token_ptr->print(outs);
        } else {
            outs << "NULL_TOKEN_PTR";
        }
        return outs;
    }

    friend ostream& operator<<(ostream& outs, const Token& token) {
        token.print(outs);
        return outs;
    }
};

#endif