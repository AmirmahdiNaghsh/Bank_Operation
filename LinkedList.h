#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <functional>


using namespace std;

template <typename T>
class LinkedList {
private:
    struct Node {
        T data; 
        Node* next;

        Node(T val) : data(val), next(nullptr) {}
        Node* getNext() const { return next; }
        T getData() const { return data; }
    };

    Node* head; 
    int count; 

public:
    Node* getHead() const { return head; }

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

    int getCount() const {
        return count;
    }

    void display() const {
        if (head == nullptr) {
            cout << "List is Empty." << endl;
            return;
        }
        Node* current = head;
        int itemNumber = 1;
        while (current != nullptr) {
            cout << "--- Item Number " << itemNumber++ << " ---" << endl;
            current->data->displayInfo(); 
            cout << endl;
            current = current->next;
        }
    }

    T find(function<bool(T)> predicate) const {
        Node* current = head;
        while (current != nullptr) {
            if (predicate(current->data)) {
                return current->data;
            }
            current = current->next;
        }
        return nullptr;
    }
    
    bool remove(function<bool(T)> predicate) {
        if (head == nullptr) {
            return false; 
        }

        if (predicate(head->data)) {
            Node* tempNode = head;
            head = head->next; 
            delete tempNode;  
            count--;
            return true;
        }

        Node* current = head;
        while (current->next != nullptr) {
            if (predicate(current->next->data)) {
                Node* nodeToDelete = current->next;
                current->next = nodeToDelete->next;
                delete nodeToDelete; 
                count--;
                return true;
            }
            current = current->next;
        }

        return false;
    }
};

#endif