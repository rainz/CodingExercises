#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include "utils.h"

using namespace std;

vector<string> topKFrequent(vector<string>& words, int k) {
    unordered_map<string, int> freqs;
    for (string s: words)
        ++freqs[s];
    auto cmp = [](pair<string, int>x, pair<string, int> y){ 
        return x.second != y.second? x.second < y.second : x.first > y.first;
    };
    priority_queue<pair<string, int>, vector<pair<string, int>>, decltype(cmp)> pq(cmp);
    for (auto it = freqs.cbegin(); it != freqs.cend(); ++it)
        pq.push(*it);
    vector<string> ans;
    for (int i = 0; i < k; ++i) {
        const string &str = pq.top().first;
        ans.push_back(str);
        pq.pop();
    }
    return ans;
}

int main(void)
{
    vector<string> input1{"i", "love", "leetcode", "i", "love", "coding"};
    printVector(topKFrequent(input1, 2));
    vector<string> input2{"the", "day", "is", "sunny", "the", "the", "the", "sunny", "is", "is"};
    printVector(topKFrequent(input2, 4));
    return 0;
}
