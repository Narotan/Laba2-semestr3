#include "stack.h"
#include <sstream>

using namespace std;

Stack::Stack() : top(nullptr) {}

Stack::~Stack() {
    while (top != nullptr) {
        Node* temp = top;
        top = top->next;
        delete temp;
    }
}

void Stack::push(const string& value) {
    Node* newNode = new Node(value);
    newNode->next = top;
    top = newNode;
}

bool Stack::pop(string& value) {
    if (top == nullptr) {
        return false;
    }
    
    value = top->value;
    Node* temp = top;
    top = top->next;
    delete temp;
    return true;
}

bool Stack::peek(string& value) const {
    if (top == nullptr) {
        return false;
    }
    value = top->value;
    return true;
}

bool Stack::isEmpty() const {
    return top == nullptr;
}

void Stack::printAll() const {
    if (top == nullptr) {
        cout << "[]" << endl;
        return;
    }
    
    cout << "[";
    Node* current = top;
    bool first = true;
    while (current != nullptr) {
        if (!first) cout << ", ";
        cout << current->value;
        first = false;
        current = current->next;
    }
    cout << "]" << endl;
}

string Stack::toString() const {
    if (top == nullptr) {
        return "[]";
    }
    
    ostringstream oss;
    oss << "[";
    Node* current = top;
    bool first = true;
    while (current != nullptr) {
        if (!first) oss << ", ";
        oss << current->value;
        first = false;
        current = current->next;
    }
    oss << "]";
    return oss.str();
}
