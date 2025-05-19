#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H

#include "../token/token.h"
#include "../queue/MyQueue.h"
#include "../stack/MyStack.h"

class ShuntingYard {
public:
    ShuntingYard();
    ShuntingYard(const Queue<Token*>& infix_q);
    void infix(const Queue<Token*>& infix_q);
    Queue<Token*> postfix();
    Queue<Token*> postfix(const Queue<Token*>& infix_q);

private:
    Queue<Token*> _infix_q;
};

#endif // SHUNTING_YARD_H