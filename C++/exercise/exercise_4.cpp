#include "exercise_4.h"

using namespace std;

bool sequenceCheck(const Array& templateArr, const Array& sequence) {
    int left = 0;   // индекс шаблона
    int right = 0;  // индекс последовательности
    
    int lastStarPos = -1;
    int rightBack = -1;
    
    while (right < sequence.getSize()) {
        string tChar = templateArr.get(left);
        string sChar = sequence.get(right);
        
        if (left < templateArr.getSize() && (tChar == sChar || tChar == "?")) {
            left++;
            right++;
        } else if (left < templateArr.getSize() && tChar == "*") {
            lastStarPos = left;
            rightBack = right;
            left++;
        } else if (lastStarPos != -1) {
            left = lastStarPos + 1;
            rightBack++;
            right = rightBack;
        } else {
            return false;
        }
    }
    
    while (left < templateArr.getSize() && templateArr.get(left) == "*") {
        left++;
    }
    
    return left == templateArr.getSize();
}
