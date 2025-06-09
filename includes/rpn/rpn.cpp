#include "rpn.h"
#include "../token/token.h"
#include "../token/integer.h"
#include "../token/variable.h"
#include "../token/operator.h"
#include "../token/function.h"
#include <cassert>       
#include <string>    


// constructor
RPN::RPN(const Queue<Token*>& postfix_q) : _postfix_q(postfix_q) {}

// setter
void RPN::set_input(const Queue<Token*>& postfix_q) {
    _postfix_q = postfix_q;
}

double RPN::operator()(double x_val) {
    MyStack<double> eval_stack;

    for (Queue<Token*>::Iterator it = _postfix_q.begin(); it != _postfix_q.end(); it++) {
        Token* token = *it;

        if (token->type() == 1) { // INTEGER
            eval_stack.push(static_cast<Integer*>(token)->getValue());
        } else if (token->type() == 5) { // VARIABLE
            eval_stack.push(x_val);
        } else if (token->type() == 2) { // OPERATOR
            Operator* op = static_cast<Operator*>(token);
            if (op->is_unary()) {
                // check if the stack is empty
                if (eval_stack.empty()) throw runtime_error("RPN: not enoughoperands for unary op.");
                double operand = eval_stack.pop();
                // if the operator is a unary operator, push the result to the stack with -
                if (op->get_operator() == "-") eval_stack.push(-operand);
                else if (op->get_operator() == "+") eval_stack.push(operand);
            } else {
                // check if the stack has at least 2 elements
                if (eval_stack.size() < 2) throw runtime_error("RPN: not enough operands for binary op.");
                double right = eval_stack.pop();
                double left = eval_stack.pop();
                string op_str = op->get_operator();
                // if the operator is a binary operator, push the result to the stack
                if (op_str == "+") eval_stack.push(left + right);
                else if (op_str == "-") eval_stack.push(left - right);
                else if (op_str == "*") eval_stack.push(left * right);
                else if (op_str == "/") {
                    // check if the right operand is 0
                    if (right == 0) throw runtime_error("RPN: Division by zero.");
                    eval_stack.push(left / right);
                } // if the operator is a power operator, push the result to the stack
                else if (op_str == "^") eval_stack.push(pow(left, right));
                else throw runtime_error("RPN: Unknown binary operator.");
            }
        } else if (token->type() == 6) { // FUNCTION
            Function* func = static_cast<Function*>(token);
            int num_args = func->get_num_args();
            if (eval_stack.size() < num_args) throw runtime_error("RPN: not enough operands for function.");
            // get the arguments from the stack and push the result to the stack
            Vector<double> args(num_args);
            args.set_size(num_args);
            for (int i = num_args - 1; i >= 0; i--) {
                args[i] = eval_stack.pop();
            }
            // evaluate the function with the arguments using the function's evaluate method
            eval_stack.push(func->evaluate(args));
        }
    }
    // check if the stack has only one element
    if (eval_stack.size() != 1) throw runtime_error("RPN: eval_stack size is not 1 at the end.");
    return eval_stack.top();
} 