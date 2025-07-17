#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
template <typename T>
class LinkedList {
private:
    
    struct Node {
        T data;
        Node* next;

        Node(T val) : data(val), next(nullptr) {}
    };

    Node* head; 
    int count; 
