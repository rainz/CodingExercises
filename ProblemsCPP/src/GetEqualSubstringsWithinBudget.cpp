#include <iostream>
#include <string>
#include "utils.h"

using namespace std;

int equalSubstring(string s, string t, int maxCost)
{
    int costs[s.length()];
    for (int i = 0; i < s.length(); ++i) {
        costs[i] = s[i] - t[i];
        if (costs[i] < 0)
            costs[i] = -costs[i];
    }

    int start = 0;
    int end = 0;
    int totalCost = 0;
    int maxLen = 0;
    while (end < s.length()) {
        ++end;
        totalCost += costs[end-1];
        while (totalCost > maxCost) {
            totalCost -= costs[start++];
        }
        int newLen = end - start;
        if (newLen > maxLen)
            maxLen = newLen;
    }
    return maxLen;
}

int main(void)
{
    cout << equalSubstring("abcd", "bcdf", 3) << endl;
    cout << equalSubstring("abcd", "cdef", 3) << endl;
}