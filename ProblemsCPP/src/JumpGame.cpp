/*
 * JumpGame.cpp
 *
 *  Created on: Apr 28, 2013
 *      Author: Yu
 */

#include <algorithm>

using namespace std;

class JumpGame {
public:
  /*
   * Given an array of non-negative integers, you are initially positioned at the first index of the array.
   * Each element in the array represents your maximum jump length at that position.
   * Determine if you are able to reach the last index.
   *
   */
    bool canJump(int A[], int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int furthest = 0, curr = 0;
        while (curr <= furthest && curr < n) {
          furthest = max(furthest, curr+A[curr]);
          ++curr;
        }
        return furthest >= n-1;
    }

    /* Return the minimum number of jumps needed to reach the last index. */
    int jump(int A[], int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (n == 0) return 0;
        int steps = 0, curr = 1, furthest = A[0];
        while (curr < n) {
          int nextFurthest = curr;
          while (curr <= furthest) {
            if (curr+A[curr] > nextFurthest)
              nextFurthest = curr+A[curr];
            ++curr;
          }
          furthest = nextFurthest;
          ++steps;
        }
        return steps;
    }
};
