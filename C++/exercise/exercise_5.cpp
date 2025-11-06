#include "exercise_5.h"

using namespace std;

tuple<string, string, HuffmanTree*> huffmanEncodeDecode(const string& text) {
    // Создаем дерево Хаффмана на основе входной строки
    HuffmanTree* tree = new HuffmanTree(text);
    
    string encoded = tree->encode(text);
    
    string decoded = tree->decode(encoded);
    
    return make_tuple(encoded, decoded, tree);
}
