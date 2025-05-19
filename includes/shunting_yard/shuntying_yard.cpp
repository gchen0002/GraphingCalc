#include "shunting_yard.h"
#include "../token/operator.h"

ShuntingYard::ShuntingYard() {}

ShuntingYard::ShuntingYard(const Queue<Token*>& infix_q) : _infix_q(infix_q) {}

void ShuntingYard::infix(const Queue<Token*>& infix_q) {
    _infix_q = infix_q;
}

Queue<Token*> ShuntingYard::postfix() {
    return postfix(_infix_q);
}

Queue<Token*> ShuntingYard::postfix(const Queue<Token*>& infix_q) {
    Queue<Token*> output;
    MyStack<Token*> operators;

    for (Queue<Token*>::Iterator it = infix_q.begin(); it != infix_q.end(); it++) {
        Token* token = *it;
        
        if (token->type() == 1) { // Integer
            output.push(token);
        }
        else if (token->type() == 2) { // Operator
            Operator* op = static_cast<Operator*>(token);
            while (!operators.empty() && operators.top()->type() == 2) {
                Operator* top_op = static_cast<Operator*>(operators.top());
                if (top_op->precedence() >= op->precedence()) {
                    output.push(operators.pop());
                } else {
                    break;
                }
            }
            operators.push(token);
        }
        else if (token->type() == 3) { // Left Parenthesis
            operators.push(token);
        }
        else if (token->type() == 4) { // Right Parenthesis
            while (!operators.empty() && operators.top()->type() != 3) {
                output.push(operators.pop());
            }
            if (!operators.empty() && operators.top()->type() == 3) {
                operators.pop(); // Remove left parenthesis
            }
        }
        else if (token->type() == 5) { // Function/Variable
            output.push(token);
        }
    }

    // Pop remaining operators
    while (!operators.empty()) {
        output.push(operators.pop());
    }

    return output;
} 