#ifndef CHEN_LINKED_LIST_FUNCTIONS_H
#define CHEN_LINKED_LIST_FUNCTIONS_H

#include <iostream>
#include "../../includes/node/node.h"
using namespace std;

// Linked List General Functions:
template <typename ITEM_TYPE>
void _print_list(node<ITEM_TYPE> *head){
    cout << "head:";
    for (node<ITEM_TYPE> *walker = head; walker != nullptr; walker = walker->_next)
    {
        cout << "[" << walker->_item << "]";
        cout << "-> ";
    }
    cout << "|||" << endl;
}

// recursive fun! :)
template <typename ITEM_TYPE>
void _print_list_backwards(node<ITEM_TYPE> *head);

template <typename T>
node<T> *_search_list(node<T> *&head, const T *find_me)
{
    for (node<T> *walker = head; walker != nullptr; walker = walker->_next)
    {
        if (walker->_item == *find_me)
        {
            return walker;
        }
    }
    // not found
    return nullptr;
}

// Function to insert at the head of the linked list
template <typename T>
node<T> *_insert_Head(node<T> *&head, const T &item)
{
    node<T> *newNode = new node<T>(item);
    newNode->_next = head;
    head = newNode;
    return newNode;
}

template <typename ITEM_TYPE>
ITEM_TYPE _remove_head(node<ITEM_TYPE> *&head) {
    if (head == nullptr) {
        return ITEM_TYPE();
    }
    node<ITEM_TYPE>* temp = head;
    ITEM_TYPE item = head->_item;
    head = head->_next;
    delete temp;
    return item;
}

// insert after ptr
template <typename ITEM_TYPE>
node<ITEM_TYPE> *_insert_after(node<ITEM_TYPE> *&head,
                               node<ITEM_TYPE> *after_this,
                               ITEM_TYPE insert_this){
    if (after_this == nullptr) return nullptr;
    node<ITEM_TYPE> *newNode = new node<ITEM_TYPE>(insert_this);
    node<ITEM_TYPE> *tempNext = after_this->_next;
    newNode->_next = tempNext;
    after_this->_next = newNode;
    return newNode;
}

// insert before ptr
template <typename ITEM_TYPE>
node<ITEM_TYPE> *_insert_before(node<ITEM_TYPE> *&head,
                                node<ITEM_TYPE> *before_this,
                                ITEM_TYPE insert_this){
    if (before_this == nullptr) return nullptr;
    if (before_this == head) {
        return _insert_Head(head, insert_this);
    }
    node<ITEM_TYPE>* prev = _previous_node(head, before_this);
    if (prev == nullptr) return nullptr;
    return _insert_after(head, prev, insert_this);
}

// ptr to previous node
template <typename T>
node<T> *_previous_node(node<T> *head, node<T> *prev_to_this)
{
    // if the prev_to_this is the head
    if (head == nullptr || prev_to_this == nullptr || head == prev_to_this)
    {
        return nullptr;
    }

    for (node<T> *walker = head; walker != nullptr; walker = walker->_next)
    {
        if (walker->_next == prev_to_this)
            return walker;
    }
    return nullptr;
}

// delete, return item
template <typename ITEM_TYPE>
ITEM_TYPE _delete_node(node<ITEM_TYPE> *&head,
                       node<ITEM_TYPE> *delete_this){
    if (head == nullptr || delete_this == nullptr) {
        return ITEM_TYPE();
    }

    // Special case: deleting the head
    if (head == delete_this) {
        ITEM_TYPE item = head->_item;
        node<ITEM_TYPE>* temp = head;
        head = head->_next;
        delete temp;
        return item;
    }

    // Find the node before delete_this
    node<ITEM_TYPE>* prev = _previous_node(head, delete_this);
    if (prev == nullptr) {
        return ITEM_TYPE(); // node not found in list
    }

    // Update links and delete
    ITEM_TYPE item = delete_this->_item;
    prev->_next = delete_this->_next;
    delete delete_this;
    return item;
}
template <typename ITEM_TYPE>
void delete_list(node<ITEM_TYPE>*& head){
    while(head){
        ITEM_TYPE something = _delete_node(head, head);
    }
    delete head;
}
// duplicate the list...
template <typename ITEM_TYPE>
node<ITEM_TYPE> *_copy_list(node<ITEM_TYPE> *head){
    if (head == nullptr) return nullptr;

    node<ITEM_TYPE>* newHead = new node<ITEM_TYPE>(head->_item);
    node<ITEM_TYPE>* curr = head->_next;
    node<ITEM_TYPE>* temp = newHead;

    while (curr != nullptr) {
        temp->_next = new node<ITEM_TYPE>(curr->_item);
        temp = temp->_next;
        curr = curr->_next;
    }

    return newHead;
}

// duplicate list and return the last node of the copy
template <typename T>
node<T> *_copy_list(node<T> *&dest, const node<T> *src){
    if(src == nullptr) {
        dest = nullptr;
        return nullptr;
    }
    node<T>* newHead = new node<T>(src->_item);
    node<T>* curr = src->_next;
    node<T>* temp = newHead;

    while (curr != nullptr) {
        temp->_next = new node<T>(curr->_item);
        temp = temp->_next;
        curr = curr->_next;
    }
    dest = newHead;
    return temp;
}

// delete all the nodes
template <typename ITEM_TYPE>
void _clear_list(node<ITEM_TYPE> *&head) {
    while (head != nullptr) {
        _delete_node(head, head); // Repeatedly delete the head node
    }
}

//_item at this position
template <typename ITEM_TYPE>
ITEM_TYPE &_at(node<ITEM_TYPE> *head, int pos);

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
//      Sorted List Routines. order: 0: ascending, order: other: descending
//                              Assume a Sorted List
//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

template <typename ITEM_TYPE>
node<ITEM_TYPE> *_insert_sorted(node<ITEM_TYPE> *&head, // insert
                                ITEM_TYPE item,
                                bool ascending = true){
    if(head == nullptr){
        head = _insert_head(head, item);
        return head;
    }
    node<ITEM_TYPE>* curr = head;
    if(ascending){ //ascending == true
        while(curr != nullptr){
            if(item > curr->_item){
                head = _insert_after(head, curr, item);
                return head;
            }
            curr = curr->_next;
        }
    } else { // ascending == false so descending order
        while(curr != nullptr){
            if(item < curr->_item){
                head = _insert_before(head, curr, item);
                return head;
            }
            curr = curr->_next;
        }
    }
    return nullptr;
}

// insert or add if a dup
template <typename ITEM_TYPE>
node<ITEM_TYPE> *_insert_sorted_and_add(node<ITEM_TYPE> *&head,
                                        ITEM_TYPE item,
                                        bool ascending = true);
// node after which this item goes order: 0 ascending
template <typename ITEM_TYPE>
node<ITEM_TYPE> *_where_this_goes(node<ITEM_TYPE> *head,
                                  ITEM_TYPE item,
                                  bool ascending = true) {
    if (head == nullptr) {
        return nullptr; // List is empty, insert at head
    }

    node<ITEM_TYPE> *walker = head;
    node<ITEM_TYPE> *prev = nullptr;

    if (ascending) {
        // Check if insert at head
        if (item < head->_item) {
             return nullptr;
        }
        // Traverse to find the node BEFORE where item should go
        while (walker != nullptr && walker->_item <= item) {
            prev = walker;
            walker = walker->_next;
        }
    } else { // Descending
        // Check if insert at head
        if (item > head->_item) {
             return nullptr;
        }
        // Traverse to find the node BEFORE where item should go
        while (walker != nullptr && walker->_item >= item) {
            prev = walker;
            walker = walker->_next;
        }
    }
    return prev; // Return the node after which to insert
}

// Last Node in the list
template <typename ITEM_TYPE>
node<ITEM_TYPE> *_last_node(node<ITEM_TYPE> *head){
    if(head == nullptr) return nullptr; 
    node<ITEM_TYPE>* curr = head;
    while(curr->_next != nullptr){
        curr = curr->_next;
    }
    return curr;
} // never use this function.

#endif