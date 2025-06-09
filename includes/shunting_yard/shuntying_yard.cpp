#include "shunting_yard.h"
#include "../token/token.h"      
#include "../token/integer.h"  
#include "../token/variable.h" 
#include "../token/operator.h" 
#include "../token/function.h" 
#include <stdexcept>          



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
    Token* prev_token = nullptr;

    for (Queue<Token*>::Iterator it = infix_q.begin(); it != infix_q.end(); it++) {
        Token* current_token = *it;
        int token_type = current_token->type();

        if (token_type == 1 || token_type == 5) { // INTEGER or VARIABLE
            output_queue.push(current_token);
        } 
        else if (token_type == 3 || token_type == 6) { // LEFT_PAREN or FUNCTION
            operator_stack.push(current_token);
        } 
        else if (token_type == 4) { // RIGHT_PAREN
            if (operator_stack.empty()) {
                throw runtime_error("ShuntingYard Error: Mismatched parentheses - right parenthesis with empty stack.");
            }
            // pop from stack until left parenthesis is found
            Token* temp = operator_stack.pop();
            while (temp->type() != 3) {
                output_queue.push(temp);
                if (operator_stack.empty()) {
                    throw runtime_error("ShuntingYard Error: Mismatched parentheses - no left parenthesis found.");
                }
                temp = operator_stack.pop();
            }
        } 
        else if (token_type == 2) { // OPERATOR
            Operator* current_op = static_cast<Operator*>(current_token);
            
            // Check for unary operator
            if (current_op->get_operator() == "-" || current_op->get_operator() == "+") {
                if (prev_token == nullptr || prev_token->type() == 2 || prev_token->type() == 3) {
                    current_op->set_unary();
                }
            }

            // if the stack is empty, push the operator
            if (operator_stack.empty()) {
                operator_stack.push(current_token);
            }
            // if the top of the stack is a left parenthesis, push the operator
            else if (operator_stack.top()->type() == 3) {
                operator_stack.push(current_token);
            } 
            // if the top of the stack is a function, pop the function and push the operator
            else if (operator_stack.top()->type() == 6) {
                output_queue.push(operator_stack.pop());
                operator_stack.push(current_token);
            } 
            // if the top of the stack is an operator
            else if (operator_stack.top()->type() == 2) {
                Operator* top_op = static_cast<Operator*>(operator_stack.top());
                if (current_op->precedence() < top_op->precedence() || (current_op->precedence() == top_op->precedence() && current_op->get_operator() != "^")) {
                    output_queue.push(operator_stack.pop());
                }
                operator_stack.push(current_token);
            } 
            // if the top of the stack is a function
            else if (operator_stack.top()->type() == 6) {
                operator_stack.push(current_token);
            }
            // if the top of the stack is a left parenthesis
            else if (operator_stack.top()->type() == 3) {
                operator_stack.push(current_token);
            }
        } 
        else {
            throw runtime_error("ShuntingYard Error: Unknown token type: " + to_string(token_type));
        } // update prev token
        prev_token = current_token;
    }
    // check for empty stack & check if the top token is a left parenthesis or right parenthesis
    while (!operator_stack.empty()) {
        Token* top_token = operator_stack.top();
        if (top_token->type() == 3 || top_token->type() == 4) {
            throw runtime_error("ShuntingYard Error: Mismatched parentheses on stack at end.");
        }
        output_queue.push(operator_stack.pop());
    }

    return output_queue;
} 