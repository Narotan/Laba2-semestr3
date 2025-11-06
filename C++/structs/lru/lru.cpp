#include "lru.h"

using namespace std;

LRUCache::LRUCache(int cap) : capacity(cap), size(0) {
    head = new LRUNode();
    tail = new LRUNode();
    head->next = tail;
    tail->prev = head;
}

LRUCache::~LRUCache() {
    LRUNode* current = head;
    while (current != nullptr) {
        LRUNode* temp = current;
        current = current->next;
        delete temp;
    }
}

void LRUCache::addToHead(LRUNode* node) {
    node->prev = head;
    node->next = head->next;
    head->next->prev = node;
    head->next = node;
}

void LRUCache::removeNode(LRUNode* node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

void LRUCache::moveToHead(LRUNode* node) {
    removeNode(node);
    addToHead(node);
}

LRUNode* LRUCache::removeTail() {
    LRUNode* node = tail->prev;
    removeNode(node);
    return node;
}

void LRUCache::set(int key, int value) {
    auto it = cache.find(key);
    
    if (it != cache.end()) {
        LRUNode* node = it->second;
        node->value = value;
        moveToHead(node);
    } else {
        LRUNode* newNode = new LRUNode(key, value);
        cache[key] = newNode;
        addToHead(newNode);
        size++;
        
        if (size > capacity) {
            LRUNode* tailNode = removeTail();
            cache.erase(tailNode->key);
            delete tailNode;
            size--;
        }
    }
}

int LRUCache::get(int key) {
    auto it = cache.find(key);
    
    if (it == cache.end()) {
        return -1;
    }
    
    LRUNode* node = it->second;
    moveToHead(node);
    return node->value;
}

void LRUCache::print() const {
    LRUNode* current = head->next;
    bool first = true;
    while (current != tail) {
        if (!first) {
            cout << ", ";
        }
        cout << current->key << " -> " << current->value;
        current = current->next;
        first = false;
    }
}
