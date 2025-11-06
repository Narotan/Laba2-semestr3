#ifndef HASHSET_H
#define HASHSET_H

#include <vector>

using namespace std;

struct SetNode {
    string value;
    SetNode* next;
    
    SetNode(const string& val) : value(val), next(nullptr) {}
};

class HashSet {
private:
    vector<SetNode*> buckets;
    int size;
    
    unsigned int hash(const string& s) const;
    void rehash();
    
public:
    HashSet(int capacity);
    ~HashSet();
    
    void add(const string& value);
    bool contains(const string& value) const;
    void remove(const string& value);
    void print() const;
    
    // Операции над множествами
    HashSet* unionWith(const HashSet* other);
    HashSet* intersection(const HashSet* other) const;
    HashSet* difference(const HashSet* other) const;
    
    int getSize() const { return size; }
    int getCapacity() const { return buckets.size(); }
};

#endif 
