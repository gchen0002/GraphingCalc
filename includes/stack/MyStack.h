#ifndef CHEN_MYSTACK_H
#define CHEN_MYSTACK_H

#include <cassert>
#include "../linked_list_functions/linked_list_functions.h"

template <typename T>
class MyStack{
public:
    class Iterator{
    public:
        friend class MyStack;                     //give access to list to access _ptr
        Iterator():_ptr(NULL){};                  //default ctor
        Iterator(node<T>* p):_ptr(p){};        //Point Iterator to where p is pointing to
                T &operator*(){
            return _ptr->_item;
        }                             //dereference operator

        T *operator->(){
            return _ptr;
        }                            //member access operator
        bool is_null(){
            return _ptr == nullptr;
        }                             //true if _ptr is NULL
        friend bool operator!=(const Iterator &left,
                               const Iterator &right){
            return left._ptr != right._ptr;
        } //true if left != right

        friend bool operator==(const Iterator &left,
                               const Iterator &right){
            return left._ptr == right._ptr;
        } //true if left == right

        Iterator &operator++(){
            _ptr = _ptr->_next;
            return *this;
        }                         //member operator:
                                                        //  ++it; or
                                                        //  ++it = new_value

        friend Iterator operator++(Iterator &it,
                                   int unused){
            Iterator temp = it;
            it._ptr = it._ptr->_next;
            return temp;
        }          //friend operator: it++

 
    private:
        node<T>* _ptr;                          //pointer being encapsulated
    };

    MyStack():_top(nullptr), _size(0){};
    MyStack(const MyStack<T>& copyMe){
        if(copyMe._top != nullptr){
            _top = _copy_list(_top, copyMe._top);
            _size = copyMe._size;
        }
    }
    ~MyStack(){
        _clear_list(_top);
    }
    MyStack<T>& operator=(const MyStack<T>& RHS){
        if(this != &RHS){
            _clear_list(_top);
            _top = _copy_list(_top, RHS._top);
            _size = RHS._size;
        }
        return *this;
    }
    T top(){
        assert(!empty() && "Cannot call top() on an empty stack.");
        return _top->_item; 
    }
    bool empty(){
        return _top == nullptr;
    }
    void push(T item){
        _top = _insert_Head(_top, item);
        _size++;
    }
    T pop(){
        assert(!empty() && "Cannot call pop() on an empty stack."); 
        T item = _top->_item;
        _remove_head(_top);
        _size--;
        return item;
    }
    template<typename TT>
    friend ostream& operator<<(ostream& outs, const MyStack<TT>& printMe);

    Iterator begin() const{
        return Iterator(_top);
    };              //Iterator to the head node
    Iterator end() const{
        return Iterator(nullptr);
    };                //Iterator to NULL
    int size() const { return _size; }

private:
    node<T>* _top;
    int _size;
};

template<typename T>
ostream& operator << (ostream& outs, const MyStack<T>& printMe){
    node<T>* walker = printMe._top;
    while(walker != nullptr){
        outs << walker->_item << " ";
        walker = walker->_next;
    }
    return outs;
}
#endif
