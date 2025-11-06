#ifndef LRU_H
#define LRU_H

#include <map>
#include <iostream>

using namespace std;

struct LRUNode {
    int key;
    int value;
    LRUNode* prev;
    LRUNode* next;
    
    LRUNode() : key(0), value(0), prev(nullptr), next(nullptr) {}
    LRUNode(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
};

class LRUCache {
private:
    int capacity;
    int size;
    map<int, LRUNode*> cache;
    LRUNode* head;
    LRUNode* tail;
    
    void addToHead(LRUNode* node);
    void removeNode(LRUNode* node);
    void moveToHead(LRUNode* node);
    LRUNode* removeTail();
    
public:
    LRUCache(int cap);
    ~LRUCache();
    
    void set(int key, int value);
    int get(int key);
    void print() const;
    
    int getSize() const { return size; }
    int getCapacity() const { return capacity; }
};

#endif // LRU_H
