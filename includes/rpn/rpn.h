#ifndef CHEN_RPN_H
#define CHEN_RPN_H
#include "../queue/MyQueue.h" 
#include "../stack/MyStack.h" 
#include "../token/token.h"
#include "../token/integer.h" 
#include "../token/operator.h" 
#include "../token/function.h"
#include "../token/variable.h"
#include <stdexcept> 
#include <string>    
#include <vector>    
#include <cmath>     



class RPN {
public:
    // constructor
    RPN(const Queue<Token*>& postfix_q); 

    // evaluator
    double operator()(double x_val = 0.0);

    // setter
    void set_input(const Queue<Token*>& postfix_q); 

private:
    Queue<Token*> _postfix_q; 
};

#endif // CHEN_RPN_H