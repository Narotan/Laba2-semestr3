#ifndef EXERCISE_7_H
#define EXERCISE_7_H

#include "../structs/lru/lru.h"
#include <vector>
#include <string>

using namespace std;

struct Query {
    string operation;  
    int key;
    int value; 
    
    Query(const string& op, int k, int v = 0) 
        : operation(op), key(k), value(v) {}
};

vector<int> runLRUCache(int capacity, const vector<Query>& queries);

#endif
