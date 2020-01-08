#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm> 
#include "utils.h"

using namespace std;

vector<string> commonChars(vector<string>& A)
{
    unordered_map<char, int> allFreqs;
    bool initialized = false;
    for (string s: A) {
        unordered_map<char, int> freqs;
        for (int i = 0; i < s.length(); ++i) {
            ++freqs[s[i]];
        }
        if (!initialized) {
            allFreqs = move(freqs);
            initialized = true;
        }
        else {
            for (auto it = allFreqs.begin(); it != allFreqs.end(); ++it) {
                it->second = min(it->second, freqs[it->first]);
            }
        }
    }
    vector<string> ans;
    for (auto it = allFreqs.begin(); it != allFreqs.end(); ++it) {
        for (int i = 0; i < it->second; ++i) {
            string s(1, it->first);
            ans.push_back(s);
        }
    }
    return ans;
}

int main(void)
{
    vector<string> input1{"bella","label","roller"};
    printVector(commonChars(input1));
    vector<string> input2{"cool","lock","cook"};
    printVector(commonChars(input2));
    return 0;
}
