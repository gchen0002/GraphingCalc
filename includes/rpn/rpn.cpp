#include "rpn.h"
#include "../token/integer.h"
#include "../token/operator.h"
#include "../token/variable.h"
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
    // assert for preconditions
    assert(!_postfix_q.empty() && "RPN Error: Input queue is empty.");

    MyStack<double> eval_stack;


    // Iterate over postfix queue
    for (Queue<Token*>::Iterator it = _postfix_q.begin(); it != _postfix_q.end(); it++) {
        Token* current_token = *it;

        if (current_token->type() == 1) { // Integer type
            Integer* num_ptr = static_cast<Integer*>(current_token);
            eval_stack.push(static_cast<double>(num_ptr->getValue()));
        } 
        else if (current_token->type() == 2) { // Operator type
            Operator* op_ptr = static_cast<Operator*>(current_token);
            string op_sym = op_ptr->getOp();

            if (eval_stack.size() < 2) {
                assert(false && "RPN Error: Insufficient operands for operator.");
            }
            
            double right_operand = eval_stack.pop();
            double left_operand = eval_stack.pop();
            double result = 0.0;

            if (op_sym == "+") result = left_operand + right_operand;
            else if (op_sym == "-") result = left_operand - right_operand;
            else if (op_sym == "*") result = left_operand * right_operand;
            else if (op_sym == "/") {
                if (std::abs(right_operand) < 1e-9) {  // check for division by zero
                    assert(false && "RPN Error: Division by zero.");
                }
                result = left_operand / right_operand;
            } else if (op_sym == "^") {
                result = std::pow(left_operand, right_operand);
            } else {
                assert(false && "RPN Error: Unknown or unsupported operator.");
            }
            eval_stack.push(result);
        } else if (current_token->type() == 6) { // Function type
            Function* func_ptr = static_cast<Function*>(current_token);
            int num_args = func_ptr->get_num_args();

            if (eval_stack.size() < num_args) {
                assert(false && "RPN Error: Insufficient operands for function.");
            }

            vector<double> args_for_func;
            args_for_func.resize(num_args);

            for (int i = num_args - 1; i >= 0; i--) {
                args_for_func[i] = eval_stack.pop();
            }
            
            double result = func_ptr->evaluate(args_for_func);
            eval_stack.push(result);
        } else if (current_token->type() == 5) { // Variable type ('x')
            Variable* var_ptr = static_cast<Variable*>(current_token);
            if (var_ptr->get_variable() == "x" || var_ptr->get_variable() == "X") { 
                eval_stack.push(x_val);
            } else {
                assert(false && "RPN Error: Unknown variable name.");
            }
        } else if (current_token->type() == 3 || current_token->type() == 4) {
            assert(false && "RPN Error: Parenthesis token encountered in postfix queue.");
        } else { // Catches any other token type need to implement trig functions later
            assert(false && "RPN Error: Unexpected token type encountered in postfix queue.");
        }
    }
    // invalid postfix expression
    if (eval_stack.size() != 1) {
        assert(false && "RPN Error: Invalid postfix expression. Stack did not end with 1 value.");
    }

    return eval_stack.top();
} 