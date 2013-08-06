/*
 * ComboSum.cpp
 *
 *  Created on: May 12, 2013
 *      Author: Yu
 */

#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

class ComboSum {
public:
    vector<vector<int> > answer;

    /*
     * Given a set of candidate numbers (C) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.
     * The same repeated number may be chosen from C unlimited number of times.
     */
    void helper(vector<int> &candidates, int idx, vector<int> &sol, int target) {
      if (target == 0) {
        answer.push_back(sol);
        return;
      }
      if (idx >= candidates.size()) {
        return;
      }

      helper(candidates, idx+1, sol, target);
      int num = candidates[idx];
      if (num <= target) {
        sol.push_back(num);
        helper(candidates, idx, sol, target-num);
        sol.pop_back();
      }
    }
    vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        answer.clear();
        sort(candidates.begin(), candidates.end());
        vector<int> sol;
        helper(candidates, 0, sol, target);
        return answer;
    }

    /*
     * Given a collection of candidate numbers (C) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.
     * Each number in C may only be used once in the combination.
     */
    void helper2(const vector<int> &nums, const vector<int> &freq, int idx, int target, vector<int> &sol, vector<vector<int> > &answer) {
      if (target == 0) {
        answer.push_back(sol);
        return;
      }
      if (target < 0) return;
      if (idx == nums.size()) return;
      int num = nums[idx], maxFreq = freq[idx];
      helper2(nums, freq, idx+1, target, sol, answer);
      int frq = 0;
      int solSize = sol.size();
      do {
        sol.push_back(num);
        target -= num;
        helper2(nums, freq, idx+1, target, sol, answer);
        ++frq;
      } while (target > 0 && frq < maxFreq);
      sol.resize(solSize);
    }
    vector<vector<int> > combinationSum2(vector<int> &num, int target) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        sort(num.begin(), num.end());
        vector<int> nums;
        vector<int> freq;
        int prev = INT_MIN;
        for (int i = 0; i < num.size(); ++i) {
          int curr = num[i];
          if (i == 0 || curr != prev) {
            nums.push_back(curr);
            freq.push_back(1);
          }
          else {
            ++freq[freq.size()-1];
          }
          prev = curr;
        }
        vector<vector<int> > answer;
        vector<int> sol;
        helper2(nums, freq, 0, target, sol, answer);
        return answer;
    }

};
