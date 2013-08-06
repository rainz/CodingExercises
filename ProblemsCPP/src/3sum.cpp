/*
 * 3sum.cpp
 *
 *  Created on: Apr 21, 2013
 *      Author: Yu
 */

#include <vector>
#include <algorithm>

using namespace std;

// Find all solutions for 3sum while avoiding dup solutions.

class ThreeSum {
public:
    vector<vector<int> > threeSum(vector<int> &num) {
        const int SUM = 0;
        vector<vector<int> > answer;
        vector<int> solution(3);
        int total = num.size();
        if (total < 3) return answer;
        sort(num.begin(), num.end());
        for (int i1 = 0; i1 < total - 2; ++i1) {
          if (i1 > 0 && num[i1] == num[i1-1]) continue; // avoid dups
          int i2 = i1 + 1, i3 = total - 1;
          int sum23 = SUM  - num[i1]; // target sum for 2nd & 3rd numbers
          while (i2 < i3) {
            if (i2 > i1+1 && num[i2] == num[i2-1]) {
              ++i2; continue; // avoid dups
            }
            if (i3 < total - 1 && num[i3] == num[i3+1]) {
              --i3; continue; // avoid dups
            }

            int sum = num[i2] + num[i3];
            if (sum == sum23) {
              solution[0] = num[i1];
              solution[1] = num[i2];
              solution[2] = num[i3];
              answer.push_back(solution);
              ++i2;
              --i3;
              continue;
            }
            else if (sum < sum23) {
             ++i2; continue;
            }
            else {
              --i3; continue;
            }
          }
        }
        return answer;
    }
};
