#include "rpn.h"
#include <cassert>   
#include <iostream> 
#include <cmath>     
#include <string>    

// constructor
RPN::RPN(const Queue<Token*>& postfix_q) : _postfix_q(postfix_q) {}

// setter
void RPN::set_input(const Queue<Token*>& postfix_q) {
    _postfix_q = postfix_q;
}


double RPN::operator()(double x_val) {
    // assert for preconditions
    assert(!_postfix_q.empty() && "RPN Error: Input queue is empty.");


    MyStack<double> eval_stack; 


    Queue<Token*>::Iterator it = _postfix_q.begin(); // Iterate through the member queue
    while(it != _postfix_q.end()){
        Token* current_token = *it;

        // handle integers
        if (current_token->type() == 1) { // Integer type
             Integer* num_ptr = static_cast<Integer*>(current_token);
             eval_stack.push(static_cast<double>(num_ptr->getValue()));

        // handle operators
        } else if (current_token->type() == 2) { // Operator type
            Operator* op_ptr = static_cast<Operator*>(current_token);
            string op_sym = op_ptr->getOp();

            // check if there are enough operands using assert
            assert(eval_stack.size() >= 2 && "RPN Error: Insufficient operands for operator.");
            

            // Pop the right operand first, then the left
            double right_operand = eval_stack.pop();
            double left_operand = eval_stack.pop();
            double result = 0.0;
            bool operator_found = false; // Flag to check if operator was valid

            // Perform the calculation based on the operator symbol
            if (op_sym == "+") {
                result = left_operand + right_operand;
                operator_found = true;
            } else if (op_sym == "-") {
                result = left_operand - right_operand;
                operator_found = true;
            } else if (op_sym == "*") {
                result = left_operand * right_operand;
                 operator_found = true;
            } else if (op_sym == "/") {
                // Check for division by zero using assert
                 assert(std::abs(right_operand) >= 1e-10 && "RPN Error: Division by zero.");
                result = left_operand / right_operand;
                 operator_found = true;
            }

            // Assert that a known operator was handled
            assert(operator_found && "RPN Error: Unknown or unsupported operator.");


            // Push the result back onto the stack
            eval_stack.push(result);

        // handle functions/variables (e.g., 'X')
        } else if (current_token->type() == 5) { // Function/Variable type
            Function* func_ptr = static_cast<Function*>(current_token);

            if (func_ptr->getName() == "X") {
                eval_stack.push(x_val);
            } else {
                assert(false && "RPN Error: Unknown function/variable name encountered.");
            }

        // handle unknown token types
        } else {
             // assert failure for unexpected token types in postfix
             assert(false && "RPN Error: Unexpected token type encountered in postfix queue.");
        }

        it++; // Move to the next token
    }

    // after processing all tokens, assert that the final result is the only item on the stack
    assert(eval_stack.size() == 1 && "RPN Error: Invalid postfix expression. Stack did not end with 1 value.");


    // return the final result
    return eval_stack.top();
} 