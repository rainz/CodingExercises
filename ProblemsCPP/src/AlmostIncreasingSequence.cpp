#include <iostream>
#include <vector>
#include <climits>
#include "utils.h"

using namespace std;

/*
 * Given a sequence of integers as an array, determine
 * whether it is possible to obtain a strictly increasing sequence
 * by removing no more than one element from the array.
 */

bool almostIncreasingSequence(const vector<int> &sequence) {
    int removeCnt = 0;
    int prev = 0, curr = 1;
    while (curr < sequence.size()) {
        int n1 = sequence[prev], n2 = sequence[curr];
        if (n2 > n1) {
            prev = curr;
            ++curr;
            continue;
        }
        ++removeCnt;
        if (removeCnt > 1)
            return false;
        int n0 = curr >= 2 ? sequence[curr-2] : INT_MIN;
        int n3 = curr < sequence.size()-1 ? sequence[curr+1] : INT_MAX;
        if (n1 > n0 && n1 < n3) {
            // prev unchanged
            ++curr;
        } else if (n2 > n0 && n2 < n3) {
            prev = curr;
            ++curr;
        } else {
            // both have to be remove, which exceeds removal limit
            return false;
        }
    }
    return true;
}

int main(void)
{
    vector<int> test{1, 3, 2, 1};
    cout << almostIncreasingSequence(test) << endl;
    return 0;
}