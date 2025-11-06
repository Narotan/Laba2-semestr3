#include "hashset.h"
#include <iostream>
#include <functional>

using namespace std;

HashSet::HashSet(int capacity) : size(0) {
    buckets.resize(capacity, nullptr);
}

HashSet::~HashSet() {
    for (auto bucket : buckets) {
        SetNode* current = bucket;
        while (current != nullptr) {
            SetNode* temp = current;
            current = current->next;
            delete temp;
        }
    }
}

unsigned int HashSet::hash(const string& s) const {
    std::hash<string> hasher;
    return hasher(s);
}

void HashSet::add(const string& value) {
    if (contains(value)) {
        return;
    }
    
    if (static_cast<double>(size) / buckets.size() > 0.75) {
        rehash();
    }
    
    int index = hash(value) % buckets.size();
    SetNode* newNode = new SetNode(value);
    newNode->next = buckets[index];
    buckets[index] = newNode;
    size++;
}

bool HashSet::contains(const string& value) const {
    int index = hash(value) % buckets.size();
    SetNode* current = buckets[index];
    
    while (current != nullptr) {
        if (current->value == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}

void HashSet::remove(const string& value) {
    int index = hash(value) % buckets.size();
    SetNode* current = buckets[index];
    SetNode* prev = nullptr;
    
    while (current != nullptr) {
        if (current->value == value) {
            if (prev == nullptr) {
                buckets[index] = current->next;
            } else {
                prev->next = current->next;
            }
            delete current;
            size--;
            return;
        }
        prev = current;
        current = current->next;
    }
}

void HashSet::rehash() {
    vector<SetNode*> oldBuckets = buckets;
    buckets.clear();
    buckets.resize(oldBuckets.size() * 2, nullptr);
    
    for (auto bucket : oldBuckets) {
        SetNode* current = bucket;
        while (current != nullptr) {
            int index = hash(current->value) % buckets.size();
            SetNode* newNode = new SetNode(current->value);
            newNode->next = buckets[index];
            buckets[index] = newNode;
            current = current->next;
        }
    }
    
    for (auto bucket : oldBuckets) {
        SetNode* current = bucket;
        while (current != nullptr) {
            SetNode* temp = current;
            current = current->next;
            delete temp;
        }
    }
}

void HashSet::print() const {
    for (size_t i = 0; i < buckets.size(); i++) {
        cout << "[" << i << "]: ";
        SetNode* current = buckets[i];
        while (current != nullptr) {
            cout << current->value << " -> ";
            current = current->next;
        }
        cout << "nil" << endl;
    }
}

HashSet* HashSet::unionWith(const HashSet* other) {
    for (auto bucket : other->buckets) {
        SetNode* current = bucket;
        while (current != nullptr) {
            add(current->value);
            current = current->next;
        }
    }
    return this;
}

HashSet* HashSet::intersection(const HashSet* other) const {
    HashSet* newSet = new HashSet(size);
    
    for (auto bucket : buckets) {
        SetNode* current = bucket;
        while (current != nullptr) {
            if (other->contains(current->value)) {
                newSet->add(current->value);
            }
            current = current->next;
        }
    }
    return newSet;
}

HashSet* HashSet::difference(const HashSet* other) const {
    HashSet* newSet = new HashSet(size);
    
    for (auto bucket : buckets) {
        SetNode* current = bucket;
        while (current != nullptr) {
            if (contains(current->value) && !other->contains(current->value)) {
                newSet->add(current->value);
            }
            current = current->next;
        }
    }
    return newSet;
}
