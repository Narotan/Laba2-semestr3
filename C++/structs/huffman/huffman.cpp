#include "huffman.h"
#include <iostream>
#include <sstream>

using namespace std;

HuffmanTree::HuffmanTree(const string& text) : root(nullptr) {
    if (text.empty()) {
        return;
    }
    
    // Подсчет частот символов
    map<char, int> frequencies;
    for (char c : text) {
        frequencies[c]++;
    }
    
    // Создание очереди с приоритетом
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareNode> pq;
    
    for (auto& pair : frequencies) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }
    
    // Построение дерева Хаффмана
    while (pq.size() > 1) {
        HuffmanNode* left = pq.top();
        pq.pop();
        HuffmanNode* right = pq.top();
        pq.pop();
        
        HuffmanNode* parent = new HuffmanNode('\0', left->frequency + right->frequency);
        parent->left = left;
        parent->right = right;
        
        pq.push(parent);
    }
    
    root = pq.top();
    
    // Генерация кодов
    generateCodes(root, "");
}

HuffmanTree::~HuffmanTree() {
    deleteTree(root);
}

void HuffmanTree::deleteTree(HuffmanNode* node) {
    if (node == nullptr) {
        return;
    }
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

void HuffmanTree::generateCodes(HuffmanNode* node, const string& code) {
    if (node == nullptr) {
        return;
    }
    
    // Если это лист, сохраняем код
    if (node->left == nullptr && node->right == nullptr) {
        codes[node->ch] = code;
        return;
    }
    
    // Рекурсивно обходим дерево
    generateCodes(node->left, code + "0");
    generateCodes(node->right, code + "1");
}

string HuffmanTree::encode(const string& text) const {
    if (root == nullptr) {
        return "";
    }
    
    ostringstream encoded;
    for (char c : text) {
        auto it = codes.find(c);
        if (it != codes.end()) {
            encoded << it->second;
        }
    }
    return encoded.str();
}

string HuffmanTree::decode(const string& encoded) const {
    if (root == nullptr || encoded.empty()) {
        return "";
    }
    
    ostringstream decoded;
    HuffmanNode* current = root;
    
    for (char bit : encoded) {
        if (bit == '0') {
            current = current->left;
        } else if (bit == '1') {
            current = current->right;
        }
        
        if (current->left == nullptr && current->right == nullptr) {
            decoded << current->ch;
            current = root;
        }
    }
    
    return decoded.str();
}

void HuffmanTree::printCodes() const {
    if (codes.empty()) {
        cout << "Нет кодов для отображения" << endl;
        return;
    }
    
    cout << "Коды символов Хаффмана:" << endl;
    for (const auto& pair : codes) {
        cout << pair.first << ": " << pair.second << endl;
    }
}

void HuffmanTree::printTree() const {
    cout << "Дерево Хаффмана:" << endl;
    printNode(root, "");
}

void HuffmanTree::printNode(HuffmanNode* node, const string& prefix) const {
    if (node == nullptr) {
        return;
    }
    
    if (node->left == nullptr && node->right == nullptr) {
        cout << prefix << "'" << node->ch << "' (freq: " << node->frequency << ")" << endl;
        return;
    }
    
    cout << prefix << "* (freq: " << node->frequency << ")" << endl;
    
    if (node->left != nullptr) {
        printNode(node->left, prefix + "  ");
    }
    if (node->right != nullptr) {
        printNode(node->right, prefix + "  ");
    }
}

double HuffmanTree::getCompressionRatio(const string& originalText) const {
    if (originalText.empty()) {
        return 0;
    }
    
    int originalBits = originalText.length() * 8;
    int encodedBits = encode(originalText).length();
    
    if (encodedBits == 0) {
        return 0;
    }
    
    return static_cast<double>(originalBits) / encodedBits;
}
