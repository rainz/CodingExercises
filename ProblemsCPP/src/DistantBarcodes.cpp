#include <iostream>
#include <queue>
#include <unordered_map>
#include "utils.h"

using namespace std;

vector<int> rearrangeBarcodes(vector<int>& barcodes)
{
    unordered_map<int, int> freqs;
    for (int num: barcodes) {
        ++freqs[num];
    }

    vector<int> output(barcodes.size());
    int idx = 0;
    auto cmp = [](pair<int, int> left, pair<int, int> right) { return left.second < right.second; };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);
    for (auto entry: freqs) {
        pq.push(entry);
    }
    int lastNum = 0;
    while (!pq.empty()) {
        pair<int, int> entry = pq.top();
        pq.pop();
        int num = entry.first;
        if (lastNum == num) {
            // Can't use the same entry, get the next one
            pair<int, int> entry2 = pq.top();
            pq.pop();
            pq.push(entry); // put first entry back
            // Decrement 2nd entry and put it back
            num = entry2.first;
            int newVal = entry2.second - 1;
            if (newVal > 0) {
                entry2.second = newVal;
                pq.push(entry2);
            }
        } else {
            // Decrement entry and put it back
            int newVal = entry.second - 1;
            if (newVal > 0) {
                entry.second = newVal;
                pq.push(entry);
            }
        }
        output[idx++] = num;
        lastNum = num;
    }
    return output;
}

int main(void)
{
    vector<int> v1{1,1,1,2,2,2};
    printVector(rearrangeBarcodes(v1));
    vector<int> v2{1,1,1,1,2,2,3,3};
    printVector(rearrangeBarcodes(v2));
    return 0;
}

