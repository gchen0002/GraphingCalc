#ifndef CHEN_MYQUEUE_H
#define CHEN_MYQUEUE_H

#include "../linked_list_functions/linked_list_functions.h"

template <typename T>
class Queue
{
public:
    class Iterator{
    public:
        friend class Queue;          //give access to list to access _ptr
        Iterator():_ptr(nullptr){};                  //default ctor
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
        node<T>* _ptr;               //pointer being encapsulated
    };

    Queue():_front(nullptr), _rear(nullptr), _size(0){}; //default ctor

    Queue(const Queue<T>& copyMe) : _front(nullptr), _rear(nullptr), _size(0) {
        if (copyMe._front != nullptr) {
            _rear = _copy_list(_front, copyMe._front); 
            _size = copyMe._size; 
        }
    }
    ~Queue(){
        _clear_list(_front);
        _front = nullptr;
        _rear = nullptr;
        _size = 0;
    }
    Queue& operator=(const Queue<T>& RHS){
        if(this != &RHS){
            _clear_list(_front);
            _front = nullptr;
            _rear = nullptr;
            _size = 0;

            if (RHS._front != nullptr) {
                _rear = _copy_list(_front, RHS._front);
                _size = RHS._size;
            }
        }
        return *this;
    }

    bool empty(){
        return _front == nullptr;
    }
    T front(){
        // queue is not empty before accessing _front
        assert(!empty() && "Cannot call front() on an empty queue.");
        return _front->_item;
    }

    T back(){
        // check here is for emptiness. 
        assert(!empty() && "Cannot call back() on an empty queue.");
        return _rear->_item;
    }

    void push(T item){
        if (empty()) {
            _front = _insert_Head(_front, item);
            _rear = _front; // Both front and rear point to the single element
        } else {
            _rear = _insert_after(_front, _rear, item); // Insert after the current rear
        }
        _size++;
    }

    T pop(){
        assert(!empty() && "Cannot call pop() on an empty queue.");
        T item = _front->_item;
        _remove_head(_front);
        _size--;
        return item;
    }

    Iterator begin() const{
        return Iterator(_front);
    }            //Iterator to the head node
    Iterator end() const{
        return Iterator(nullptr);
    }              //Iterator to NULL
    void print_pointers(){
        cout << "Queue: Head->";
        node<T>* walker = _front;
        while(walker != nullptr){
            cout << "[" << walker << "]->"; // Print the address of the node
            walker = walker->_next;
        }
        cout << "|||" << endl;
        cout << "_front: " << _front << endl;
        cout << "_rear: " << _rear << endl;
    }
    int size() const { return _size; }
    template<typename TT>
    friend ostream& operator << (ostream& outs, const Queue<TT>& printMe);
private:
    node<T>* _front;
    node<T>* _rear;
    int _size;
};

template<typename T>
ostream& operator << (ostream& outs, const Queue<T>& printMe){
    node<T>* walker = printMe._front;
    while(walker != nullptr){
            outs << walker->_item << " ";
        walker = walker->_next;
    }
    return outs;
}
#endif