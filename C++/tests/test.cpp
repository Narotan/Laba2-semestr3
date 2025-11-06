#include "test.h"
#include "../exercise/exercise_1.h"
#include "../exercise/exercise_5.h"
#include "../exercise/exercise_7.h"
#include "../structs/set/hashset.h"
#include <iostream>
#include <iomanip>

using namespace std;


void runLogicExpression() {
    string expr = "((!1 | 0) & (1 ^ 0))";
    try {
        string result = logicExpWithStack(expr);
        cout << "answer: " << result << endl;
    } catch (const exception& e) {
        cout << "error: problem with calculation: " << e.what() << endl;
    }
}

void runHashSetUnion() {
    HashSet* mainSet = new HashSet(11);
    HashSet* otherSet = new HashSet(11);
    
    string numbers1[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
    string numbers2[] = {"11", "12", "13", "14", "15", "16", "17", "18", "19", "20"};
    
    for (const auto& n : numbers1) {
        mainSet->add(n);
    }
    cout << "main set: " << endl;
    mainSet->print();
    
    for (const auto& n : numbers2) {
        otherSet->add(n);
    }
    cout << "other set: " << endl;
    otherSet->print();
    
    cout << "main set after Union operation: " << endl;
    mainSet->unionWith(otherSet);
    mainSet->print();
    
    delete mainSet;
    delete otherSet;
}

void runHashSetIntersection() {
    HashSet* mainSet = new HashSet(11);
    HashSet* otherSet = new HashSet(11);
    
    string numbers1[] = {"1", "2", "3", "4", "5"};
    string numbers2[] = {"11", "12", "3", "15", "1"};
    
    for (const auto& n : numbers1) {
        mainSet->add(n);
    }
    cout << "main set: " << endl;
    mainSet->print();
    
    for (const auto& n : numbers2) {
        otherSet->add(n);
    }
    cout << "other set: " << endl;
    otherSet->print();
    
    cout << "main set after Intersection operation: " << endl;
    HashSet* newSet = mainSet->intersection(otherSet);
    newSet->print();
    
    delete mainSet;
    delete otherSet;
    delete newSet;
}

void runHashSetDifference() {
    HashSet* mainSet = new HashSet(11);
    HashSet* otherSet = new HashSet(11);
    
    string numbers1[] = {"1", "2", "3", "4", "5"};
    string numbers2[] = {"11", "12", "3", "15", "1"};
    
    for (const auto& n : numbers1) {
        mainSet->add(n);
    }
    cout << "main set: " << endl;
    mainSet->print();
    
    for (const auto& n : numbers2) {
        otherSet->add(n);
    }
    cout << "other set: " << endl;
    otherSet->print();
    
    cout << "main set after Difference operation: " << endl;
    HashSet* newSet = mainSet->difference(otherSet);
    newSet->print();
    
    delete mainSet;
    delete otherSet;
    delete newSet;
}

void runHuffmanEncoding() {
    cout << "\n=== Тест алгоритма Хаффмана ===" << endl;
    
    string testString = "hellp";
    cout << "\nИсходная строка: " << testString << endl;
    
    auto [encoded, decoded, tree] = huffmanEncodeDecode(testString);
    
    cout << "\nКоды символов:" << endl;
    tree->printCodes();
    
    cout << "\nРезультаты кодирования:" << endl;
    cout << "  Закодированная строка: " << encoded << endl;
    cout << "  Длина закодированной строки: " << encoded.length() << " бит" << endl;
    cout << "  Декодированная строка: " << decoded << endl;
    
    if (testString == decoded) {
        cout << "Декодирование успешно" << endl;
    } else {
        cout << "Ошибка декодирования" << endl;
    }
    
    int originalBits = testString.length() * 8;
    int compressedBits = encoded.length();
    double ratio = tree->getCompressionRatio(testString);
    
    cout << "\nСтатистика сжатия:" << endl;
    cout << "  Оригинальный размер: " << originalBits << " бит (" 
              << testString.length() << " символов * 8 бит)" << endl;
    cout << "  Сжатый размер: " << compressedBits << " бит" << endl;
    cout << fixed << setprecision(2);
    cout << "  Коэффициент сжатия: " << ratio << endl;
    cout << "  Экономия места: " << (1 - 1/ratio) * 100 << "%" << endl;
    
    cout << "\n=== Дополнительные примеры ===" << endl;
    string testCases[] = {
        "hello world",
        "aaaaabbbbbcccccddddd",
        "Go programming language"
    };
    
    for (int i = 0; i < 3; i++) {
        cout << "\nПример " << (i + 1) << ": " << testCases[i] << endl;
        auto [enc, dec, t] = huffmanEncodeDecode(testCases[i]);
        cout << "  Коды символов:" << endl;
        t->printCodes();
        cout << "  Закодировано: " << enc << endl;
        cout << "  Декодировано: " << dec << endl;
        cout << "  Совпадает с исходной строкой: " << (testCases[i] == dec ? "true" : "false") << endl;
        cout << "  Коэффициент сжатия: " << t->getCompressionRatio(testCases[i]) << endl;
        delete t;
    }
    
    delete tree;
}

void runLRUCache() {
    vector<Query> queries = {
        Query("SET", 1, 2),
        Query("SET", 2, 3),
        Query("SET", 1, 5),
        Query("SET", 4, 5),
        Query("SET", 6, 7),
        Query("GET", 4, 0),
        Query("SET", 1, 2),
        Query("GET", 3, 0)
    };
    
    vector<int> results = runLRUCache(2, queries);
    
    cout << "Вывод: ";
    for (size_t i = 0; i < results.size(); i++) {
        if (i > 0) cout << " ";
        cout << results[i];
    }
    cout << endl;
}
