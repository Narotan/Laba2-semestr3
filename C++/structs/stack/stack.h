#ifndef STACK_H
#define STACK_H

#include <string>
#include <iostream>

using namespace std;

struct Node {
    string value;
    Node* next;
    
    Node(const string& val) : value(val), next(nullptr) {}
};

class Stack {
private:
    Node* top;
    
public:
    Stack();
    ~Stack();
    
    void push(const string& value);
    bool pop(string& value);
    bool peek(string& value) const;
    bool isEmpty() const;
    void printAll() const;
    string toString() const;
};

#endif // STACK_H
