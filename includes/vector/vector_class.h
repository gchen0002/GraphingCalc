#ifndef CHEN_H_VECTOR_CLASS_H
#define CHEN_H_VECTOR_CLASS_H

#include <iostream>
#include <stdexcept>  // for out_of_range
#include <iomanip>
using namespace std;

template <class T>
class Vector{
public:

    Vector(int capacity = 100);
    Vector(T *arr, int size);
    // big three:
    Vector(const Vector& oldVector);
    Vector& operator=(const Vector& rhs);
    ~Vector();
    //member access functions:
    T& operator [](int index);
    const T& operator [](int index) const;

    T& at(int index);              //return reference to item at position index
    const T& at(int index) const;  //return a const item at position index

    T& front();                         //return item at position 0.
    T& back();                          //return item at the last position


    //Push and Pop functions:
    Vector& operator +=(const T& item); //push_back
    void push_back(const T& item);      //append to the end
    T pop_back();                       //remove last item and return it


    //Insert and Erase:
    void insert(int insert_here, const T& insert_this); //insert at pos
    void erase(int erase_this_index);        //erase item at position
    int index_of(const T& item);             //search for item. retur index.

    //size and capacity:
    void set_size(int size);              //enlarge the vector to this size
    void set_capacity(int capacity);      //allocate this space
    int size() const {return _size;}  //return _size
    int capacity() const {return _capacity;} //return _capacity

    bool empty() const;                    //return true if vector is empty

    //OUTPUT:
    template <class U>
    friend ostream& operator <<(ostream& outs, const Vector<U>& _a);
private:
    T* _arr;
    int _capacity;
    int _size;
};

// Add all implementations here:
template <class T>
Vector<T>::Vector(int capacity):_capacity(capacity), _size(0){
    _arr = new T[capacity];
}

template <class T>
Vector<T>::Vector(T* arr, int size):_capacity(size+2), _size(size){
    _arr = new T[_capacity];
    T* newArrWalker = _arr;
    T* arrWalker = arr;
    for(int i = 0; i < _size; i++){
        *newArrWalker = *arrWalker;
        newArrWalker++;
        arrWalker++;
    }
}

template <class T>
Vector<T>::Vector(const Vector& oldVector) {
    _capacity = oldVector._capacity;
    _size = oldVector._size;
    _arr = new T[_capacity];  // Create new array
    
    // Deep copy the elements
    for(int i = 0; i < _size; i++) {
        _arr[i] = oldVector._arr[i];
    }
}

template <class T>
Vector<T>& Vector<T>::operator=(const Vector& rhs){
    if(this == &rhs){
        return *this;
    }
    delete[] _arr;  // Delete old array 
    _capacity = rhs._capacity;
    _size = rhs._size;
    _arr = new T[_capacity];  // Create new array
    
    // copy the elements
    for(int i = 0; i < _size; i++) {
        _arr[i] = rhs._arr[i];
    }
    return *this;
}

template <class T>
Vector<T>::~Vector(){
    delete[] _arr;
}

template <class T>
T& Vector<T>::operator[](int index){
    return *(_arr + index);
}

template <class T>
const T& Vector<T>::operator[](int index) const{
    return *(_arr + index);
}

template <class T>
T& Vector<T>::at(int index){
    if(index < 0 || index > _size-1) throw out_of_range("Index out of range");
    return *(_arr + index);
}

template <class T>
const T& Vector<T>::at(int index) const {
    if(index < 0 || index > _size-1) throw out_of_range("Index out of range");
    return *(_arr + index);
}

template <class T>
T& Vector<T>::front() {
    return *_arr;
}

template <class T>
T& Vector<T>::back() {
    return *(_arr + _size-1);  
}

template <class T>
Vector<T>& Vector<T>::operator+=(const T& item) {
    if(_size >= _capacity) {
        Vector<T> temp(_arr, _size);  
        temp._capacity = _capacity * 2;
        *this = temp;
    }
    *(_arr + _size) = item;
    _size++;
    return *this;
}

template <class T>
void Vector<T>::push_back(const T& item) {
    *this += item;
}

template <class T>
T Vector<T>::pop_back() {
    T value = this->at(_size-1);  
    _size--;
    return value;
}

template <class T>
void Vector<T>::insert(int insert_here, const T& insert_this) {
    if(_size >= _capacity) {
        set_capacity(_capacity+1);
    }
    
    // Shift elements right
    for(int i = _size; i > insert_here; i--) {
        _arr[i] = _arr[i-1];
    }
    
    _arr[insert_here] = insert_this;
    _size++;
}

template <class T>
void Vector<T>::erase(int erase_this_index) {
    T* walker = _arr + erase_this_index;
    T* next = walker + 1;
    while(next < _arr + _size) {
        *walker = *next;
        walker++;
        next++;
    }
    _size--;
}

template <class T>
int Vector<T>::index_of(const T& item) {
    T* walker = _arr;
    for(int i = 0; i < _size; i++){
        if(*walker == item) return i;
        walker++;
    }
    return -1;
}

template <class T>
void Vector<T>::set_size(int size) {
    if(size <= _capacity){  
        _size = size;
    }
}

template <class T>
void Vector<T>::set_capacity(int capacity) {
    if(capacity == _capacity) return; // exit
    T* temp = new T[capacity];
    // copy elements, but only up to new capacity or current size
    for(int i = 0; i < min(capacity, _size); i++) {
        temp[i] = _arr[i];
    }
    
    delete[] _arr;  // Delete old array
    _arr = temp;
    _capacity = capacity;
    if(capacity < _size) _size = capacity;  // Adjust size if new capacity is smaller
}

template <class T>
bool Vector<T>::empty() const {
    return _size == 0;
}


template <class U>
ostream& operator <<(ostream& outs, const Vector<U>& _a) {
    outs << "(" << _a.size() << "/" << _a.capacity() << ") " << " [";
    for(int i = 0; i < _a.size(); i++){
        outs << setw(5) << _a.at(i);
    }
    outs << "]";
    return outs;
}

#endif