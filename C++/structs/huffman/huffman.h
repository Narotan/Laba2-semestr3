#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <string>
#include <map>
#include <queue>

using namespace std;

struct HuffmanNode {
    char ch;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;
    
    HuffmanNode(char c, int f) : ch(c), frequency(f), left(nullptr), right(nullptr) {}
};

struct CompareNode {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->frequency > b->frequency;
    }
};

class HuffmanTree {
private:
    HuffmanNode* root;
    map<char, string> codes;
    
    void generateCodes(HuffmanNode* node, const string& code);
    void deleteTree(HuffmanNode* node);
    void printNode(HuffmanNode* node, const string& prefix) const;
    
public:
    HuffmanTree(const string& text);
    ~HuffmanTree();
    
    string encode(const string& text) const;
    string decode(const string& encoded) const;
    void printCodes() const;
    void printTree() const;
    double getCompressionRatio(const string& originalText) const;
};

#endif // HUFFMAN_H
