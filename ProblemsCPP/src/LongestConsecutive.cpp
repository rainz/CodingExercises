/*
 * LongestConsecutive.cpp
 *
 *  Created on: May 5, 2013
 *      Author: Yu
 */

#include <unordered_set>
#include<vector>

using namespace std;

/*
 * Given an unsorted array of integers, find the length of the longest consecutive elements sequence.
 * For example,
 * Given [100, 4, 200, 1, 3, 2],
 * The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.
 */
class LongestConsecutive {
public:
    int longestConsecutive(vector<int> &num) {
        unordered_set<int> numSet;
        for (int i = 0; i < num.size(); ++i)
          numSet.insert(num[i]);
        int maxLen = 0;
        while (!numSet.empty()) {
          int start = *(numSet.begin());
          int end = start;
          numSet.erase(numSet.begin());
          unordered_set<int>::iterator it;
          while (true) {
            it = numSet.find(end+1);
            if (it == numSet.end())
              break;
            numSet.erase(it);
            ++end;
          }
          while (true) {
            it = numSet.find(start-1);
            if (it == numSet.end())
              break;
            numSet.erase(it);
            --start;
          }
          int len = end - start + 1;
          if (len > maxLen) maxLen = len;
        }
        return maxLen;
    }
};
