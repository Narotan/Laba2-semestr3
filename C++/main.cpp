#include <iostream>
#include <string>
#include <limits>
#include "tests/test.h"

using namespace std;

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    while (true) {
        cout << "\n========================================" << endl;
        cout << "Выберите номер задания:" << endl;
        cout << "========================================" << endl;
        cout << "1 - Логические выражения" << endl;
        cout << "2 - Работа с множеством (HashSet) Union" << endl;
        cout << "3 - Работа с множеством (HashSet) Intersection" << endl;
        cout << "4 - Работа с множеством (HashSet) Difference" << endl;
        cout << "5 - Алгоритм Хаффмана (кодирование/декодирование)" << endl;
        cout << "6 - LRU кэш" << endl;
        cout << "0 - Выход" << endl;
        cout << "========================================" << endl;
        cout << "Ваш выбор: ";
        
        int choice;
        cin >> choice;
        
        if (cin.fail()) {
            cout << "Некорректный ввод. Введите число." << endl;
            clearInputBuffer();
            continue;
        }
        
        clearInputBuffer();
        
        switch (choice) {
            case 1:
                runLogicExpression();
                break;
            case 2:
                runHashSetUnion();
                break;
            case 3:
                runHashSetIntersection();
                break;
            case 4:
                runHashSetDifference();
                break;
            case 5:
                runHuffmanEncoding();
                break;
            case 6:
                runLRUCache();
                break;
            case 0:
                cout << "Выход из программы." << endl;
                return 0;
            default:
                cout << "Неверный выбор. Попробуйте снова." << endl;
        }
    }
    
    return 0;
}
