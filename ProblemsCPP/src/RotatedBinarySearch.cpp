/*
 * RotatedBinarySearch.cpp
 *
 *  Created on: Jan 15, 2012
 *      Author: Yu
 */

#include <vector>

using namespace std;

class RotateBinarySearch {
public:
  int searchNoDup(const vector<int>& A, int target) {
        int upper = A.size()-1, lower = 0;
        while (lower <= upper) { // need =, example: {1}, 1
            int mid = (lower+upper)/2;
            int val = A[mid];
            if (val == target) return mid;
            if (val >= A[lower]) {
                if (target < val && target >= A[lower]) { // need =, example {1,3,5},1
                    upper = mid-1;
                }
                else {
                    lower = mid+1;
                }
                continue;
            }
            if (target > val && target <= A[upper]) {
                lower = mid+1;
            }
            else {
                upper = mid-1;
            }
        }
        return -1;
    }
};

