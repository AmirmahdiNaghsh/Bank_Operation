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
public:
    LinkedList() : head(nullptr), count(0) {}

    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

        void add(T item) {
        Node* newNode = new Node(item);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
        count++; 
    }
