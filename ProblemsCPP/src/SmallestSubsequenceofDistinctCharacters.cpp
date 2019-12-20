#include <iostream>
#include <string>
#include <unordered_set>
#include <cstring>
#include "utils.h"

using namespace std;

string smallestSubsequence(string text)
{
    int lastIndices[26];
    for (int i = 0; i < text.size(); ++i) {
        lastIndices[text[i]-'a'] = i;
    }
 
    bool used[26];
    memset(used, 0, sizeof(used));
    string result;
    for (int i = 0; i < text.size(); ++i) {
        char c = text[i];
        if (used[c-'a'])
            continue;
        int idx = result.size() - 1;
        while (idx >= 0 && c < result[idx] && i < lastIndices[result[idx]-'a']) {
            used[result[idx]-'a'] = false;
            --idx;
        }
        result.resize(idx+2); // includes the new char
        result[idx+1] = c;
        used[c-'a'] = true;
    }
    return result;
}

int main(void)
{
    cout << smallestSubsequence("cdadabcc") << endl;
    cout << smallestSubsequence("abcd") << endl;
    cout << smallestSubsequence("ecbacba") << endl;
    cout << smallestSubsequence("leetcode") << endl;
    return 0;
}