#ifndef CHEN_NODE_H
#define CHEN_NODE_H
#include <iostream>
using namespace std;
template <typename T>
struct node
{
    T _item;
    node *_next;
    // constructor
    node(T value) : _item(value), _next(nullptr)
    {
        // constructor
    }
    friend ostream& operator <<(ostream& outs, const node<T>& printMe){
        outs << "[" << printMe._item << "]" << "->";
        return outs;
    }
}
;

#endif