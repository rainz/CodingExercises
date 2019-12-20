#include <iostream>
#include <queue>
#include <unordered_map>

using namespace std;

string reorganizeString(string S)
{
    unordered_map<char, int> freqs;
    for (int i = 0; i < S.length(); ++i) {
        char c = S[i];
        ++freqs[c];
    }

    char output[S.length()+1];
    int idx = 0;
    auto cmp = [](pair<char, int> left, pair<char, int> right) { return left.second < right.second; };
    priority_queue<pair<char, int>, vector<pair<char, int>>, decltype(cmp)> pq(cmp);
    for (auto entry: freqs) {
        pq.push(entry);
    }
    char lastChar = 0;
    while (!pq.empty()) {
        pair<char, int> entry = pq.top();
        pq.pop();
        char c = entry.first;
        if (lastChar == c) {
            // Can't use the same entry, get the next one
            if (pq.empty())
                return "";
            pair<char, int> entry2 = pq.top();
            pq.pop();
            pq.push(entry); // put first entry back
            // Decrement 2nd entry and put it back
            c = entry2.first;
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
        output[idx++] = c;
        lastChar = c;
    }
    output[S.length()] = '\0';
    return output;
}

int main(void)
{
    cout << reorganizeString("aab") << endl;
    cout << reorganizeString("aaab") << endl;
    return 0;
}

