#include "exercise_1.h"
#include "../structs/stack/stack.h"
#include <iostream>
#include <stdexcept>

using namespace std;

int priority(const string& op) {
    if (op == "!") return 3;
    if (op == "&") return 2;
    if (op == "|" || op == "^") return 1;
    return 0;
}

void doOperation(const string& op, Stack& values) {
    if (op == "!") {
        string value;
        if (!values.pop(value)) {
            cerr << "error: stack is empty for ! operation" << endl;
            values.push("1");
            return;
        }
        
        if (value == "0") {
            values.push("1");
        } else if (value == "1") {
            values.push("0");
        } else {
            cerr << "error: invalid value for ! operation: " << value << endl;
            values.push("1");
        }
    } else if (op == "&" || op == "|" || op == "^") {
        string right, left;
        if (!values.pop(right) || !values.pop(left)) {
            cerr << "error: not enough values for operation " << op << endl;
            values.push("1");
            return;
        }
        
        if (op == "&") {
            if (left == "1" && right == "1") {
                values.push("1");
            } else {
                values.push("0");
            }
        } else if (op == "|") {
            if (left == "1" || right == "1") {
                values.push("1");
            } else {
                values.push("0");
            }
        } else if (op == "^") {
            if ((left == "1" && right == "0") || (left == "0" && right == "1")) {
                values.push("1");
            } else {
                values.push("0");
            }
        }
    } else {
        throw runtime_error("error: unknown operator");
    }
}

string logicExpWithStack(const string& expression) {
    string expr;
    for (char c : expression) {
        if (c != ' ') {
            expr += c;
        }
    }
    
    Stack valueStack;
    Stack operatorStack;
    
    for (char c : expr) {
        string ch(1, c);
        
        if (c == '0' || c == '1') {
            valueStack.push(ch);
        } else if (c == '(') {
            operatorStack.push(ch);
        } else if (c == ')') {
            string top;
            while (true) {
                if (!operatorStack.peek(top)) {
                    throw runtime_error("error: mismatched parentheses");
                }
                if (top == "(") {
                    operatorStack.pop(top);
                    break;
                }
                string op;
                operatorStack.pop(op);
                doOperation(op, valueStack);
            }
        } else if (c == '!' || c == '&' || c == '|' || c == '^') {
            string top;
            bool hasTop = operatorStack.peek(top);
            
            if (!hasTop || top == "(" || priority(ch) > priority(top)) {
                operatorStack.push(ch);
            } else {
                string newOp;
                if (operatorStack.pop(newOp)) {
                    doOperation(newOp, valueStack);
                    operatorStack.push(ch);
                }
            }
        } else {
            cerr << "error: unknown value: " << c << endl;
        }
    }
    
    string dummy;
    while (operatorStack.peek(dummy)) {
        string op;
        operatorStack.pop(op);
        doOperation(op, valueStack);
    }
    
    string result;
    valueStack.pop(result);
    return result;
}
