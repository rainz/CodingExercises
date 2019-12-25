#include <iostream>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <climits>
#include "utils.h"

using namespace std;

int sortedDigits(int n)
{
    string str;
    int num = n;
    int zeroCount = 0;
    while (num > 0) {
        int digit = num % 10;
        if (digit != 0)
            str += '0' + digit;
        else
            ++zeroCount;
        num /= 10;
    }
    sort(str.begin(), str.end());

    string zeros(zeroCount, '0');
    string sortedStr = str.substr(0, 1) + zeros + str.substr(1);
    return atoi(sortedStr.c_str());
}

bool reorderedPowerOf2(int N) {
    unordered_set<int> p2Sorted;
    int p2 = 1;
    for (int shift = 0; shift < 31; ++shift) {
        p2Sorted.insert(sortedDigits(p2 << shift));
    }
    return p2Sorted.find(sortedDigits(N)) != p2Sorted.end();
}

int main(void) {
    cout << reorderedPowerOf2(1) << endl;
    cout << reorderedPowerOf2(10) << endl;
    cout << reorderedPowerOf2(16) << endl;
    cout << reorderedPowerOf2(24) << endl;
    cout << reorderedPowerOf2(46) << endl;
    return 0;
}