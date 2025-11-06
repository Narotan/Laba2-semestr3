#ifndef ARRAY_H
#define ARRAY_H

#include <string>

using namespace std;

class Array {
private:
    string** data;
    int size;
    int capacity;
    
    void resize();
    
public:
    Array();
    ~Array();
    
    int getSize() const { return size; }
    bool empty() const { return size == 0; }
    
    void append(const string& value);
    void insert(int index, const string& value);
    string get(int index) const;
    void set(int index, const string& value);
    void remove(int index);
    bool removeByValue(const string& value);
};

#endif // ARRAY_H
