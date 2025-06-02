#include "shunting_yard.h"
#include "../token/operator.h"
#include "../token/integer.h" 
#include "../token/variable.h" 


ShuntingYard::ShuntingYard() {}

ShuntingYard::ShuntingYard(const Queue<Token*>& infix_q) : _infix_q(infix_q) {}

void ShuntingYard::infix(const Queue<Token*>& infix_q) {
    _infix_q = infix_q;
}

Queue<Token*> ShuntingYard::postfix() {
    return postfix(_infix_q);
}

Queue<Token*> ShuntingYard::postfix(const Queue<Token*>& infix_q) {
    Queue<Token*> output_queue;
    MyStack<Token*> operator_stack;

    for (Queue<Token*>::Iterator it = infix_q.begin(); it != infix_q.end(); it++) {
        Token* token = *it;
        
        if (token->type() == 1) { // Integer
            output_queue.push(token);
        } 
        else if (token->type() == 5) { // Variable 
            output_queue.push(token);
        } 
        else if (token->type() == 2) { // Operator
            Operator* current_op = static_cast<Operator*>(token);
            while (!operator_stack.empty() && operator_stack.top()->type() == 2) {
                Operator* top_op = static_cast<Operator*>(operator_stack.top());
                if (top_op->precedence() >= current_op->precedence()) { // precedence check
                    output_queue.push(operator_stack.pop());
                } else {
                    break;
                }
            }
            operator_stack.push(token);
        }
    }
    // clean up stack for left over operators
    while (!operator_stack.empty()) {
        Token* token_on_stack = operator_stack.top();
        assert(token_on_stack->type() == 2 && "ShuntingYard Error: Expected only operators on stack at the end.");
        output_queue.push(operator_stack.pop());
    }

    return output_queue;
} 