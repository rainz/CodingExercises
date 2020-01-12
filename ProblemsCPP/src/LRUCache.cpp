#include <iostream>
#include <unordered_map>
#include <list>
#include "utils.h"

using namespace std;
class LRUCache {
public:
    LRUCache(int capacity) {
        cap = capacity;
    }
    
    int get(int key) {
        auto it = cache.find(key);
        if (it == cache.end())
            return -1;
            
        linked.splice(linked.begin(), linked, it->second);
        return it->second->second;
        /*
        auto list_it = it->second;
        auto pair = *list_it;
        linked.erase(list_it);
        linked.push_back(pair); // can also use splice instead of erase & push_back
        list_it = prev(linked.end()); // std::prev, std::next
        cache[key] = list_it;
        return list_it->second;
        */
    }
    
    void put(int key, int value) {
        auto it = cache.find(key);
        
        if (it != cache.end())
            linked.erase(it->second);
        linked.push_front(make_pair(key, value));
        cache[key] = linked.begin();
        if (cache.size() > cap) {
            int k = linked.rbegin()->first;
            linked.pop_back();
            cache.erase(k);
        }
        /*
        if (it != cache.end()) {
            auto list_it = it->second;
            auto pair = *list_it;
            pair.second = value;
            linked.erase(list_it);
            linked.push_back(pair); // can also use splice instead of erase & push_back
            cache[key] = prev(linked.end()); // std::prev, std::next
        } else {
            if (cache.size() >= cap) {
                auto oldest = linked.front();
                linked.pop_front();
                cache.erase(oldest.first);
            }
            linked.push_back(make_pair(key, value));
            cache[key] = prev(linked.end());
        }
        */
    }

private:
    unordered_map<int, list<pair<int, int>>::iterator> cache;
    list<pair<int, int>> linked;
    int cap;
};

int main(void)
{
    LRUCache cache( 2 /* capacity */ );
    cache.put(1, 1);
    cache.put(2, 2);
    cout << cache.get(1) << endl;       // returns 1
    cache.put(3, 3);    // evicts key 2
    cout << cache.get(2) << endl;       // returns -1 (not found)
    cache.put(4, 4);    // evicts key 1
    cout << cache.get(1) << endl;       // returns -1 (not found)
    cout << cache.get(3) << endl;       // returns 3
    cout << cache.get(4) << endl;       // returns 4
    return 0;
}