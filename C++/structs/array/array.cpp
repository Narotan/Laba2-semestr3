#include "array.h"
#include <cstring>

using namespace std;

Array::Array() : size(0), capacity(4) {
    data = new string*[capacity];
    for (int i = 0; i < capacity; i++) {
        data[i] = nullptr;
    }
}

Array::~Array() {
    for (int i = 0; i < size; i++) {
        if (data[i] != nullptr) {
            delete data[i];
        }
    }
    delete[] data;
}

void Array::resize() {
    int newCap = capacity * 2;
    string** newData = new string*[newCap];
    
    for (int i = 0; i < size; i++) {
        newData[i] = data[i];
    }
    for (int i = size; i < newCap; i++) {
        newData[i] = nullptr;
    }
    
    delete[] data;
    data = newData;
    capacity = newCap;
}

void Array::append(const string& value) {
    if (size >= capacity) {
        resize();
    }
    data[size] = new string(value);
    size++;
}

void Array::insert(int index, const string& value) {
    if (index < 0 || index > size) {
        return;
    }
    if (size >= capacity) {
        resize();
    }
    
    for (int i = size; i > index; i--) {
        data[i] = data[i-1];
    }
    data[index] = new string(value);
    size++;
}

string Array::get(int index) const {
    if (index < 0 || index >= size) {
        return "";
    }
    return *data[index];
}

void Array::set(int index, const string& value) {
    if (index < 0 || index >= size) {
        return;
    }
    *data[index] = value;
}

void Array::remove(int index) {
    if (index < 0 || index >= size) {
        return;
    }
    
    delete data[index];
    for (int i = index; i < size - 1; i++) {
        data[i] = data[i+1];
    }
    data[size-1] = nullptr;
    size--;
}

bool Array::removeByValue(const string& value) {
    for (int i = 0; i < size; i++) {
        if (data[i] != nullptr && *data[i] == value) {
            remove(i);
            return true;
        }
    }
    return false;
}
