#include "exercise_7.h"
#include <iostream>

using namespace std;

vector<int> runLRUCache(int capacity, const vector<Query>& queries) {
    LRUCache cache(capacity);
    vector<int> results;
    
    cout << "Cache Size = " << capacity << endl;
    
    for (size_t i = 0; i < queries.size(); i++) {
        const Query& query = queries[i];
        
        if (query.operation == "SET") {
            cache.set(query.key, query.value);
            cout << "SET " << query.key << " " << query.value << " : ";
            cache.print();
            cout << endl;
        } else if (query.operation == "GET") {
            int result = cache.get(query.key);
            cout << "GET " << query.key << " : " << result;
            if (result != -1) {
                cout << " (";
                cache.print();
                cout << ")";
            }
            cout << endl;
            results.push_back(result);
        }
    }
    
    return results;
}
