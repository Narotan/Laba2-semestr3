#ifndef EXERCISE_5_H
#define EXERCISE_5_H

#include "../structs/huffman/huffman.h"
#include <string>
#include <tuple>

using namespace std;

tuple<string, string, HuffmanTree*> huffmanEncodeDecode(const string& text);

#endif 
