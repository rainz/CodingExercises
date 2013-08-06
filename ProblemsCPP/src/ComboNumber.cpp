/*
 * ComboNumber.cpp
 *
 *  Created on: Mar 13, 2012
 *      Author: Yu
 */
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
        vector<vector<int> > result;
        // The line below is needed only if you want to print numbers in ascending order
        sort(candidates.begin(), candidates.end());
        vector<int> freq(candidates.size());
        int sum = 0;
        while (nextFreq(candidates, freq, sum, target)) {
            if (sum == target)
                appendResult(result, candidates, freq);
        }
        return result;
    }

    void appendResult(vector<vector<int> > &result,
                      const vector<int> &candi,
                      const vector<int> &freq) {
        vector<int> one_sol;
        for (size_t i = 0; i < candi.size(); ++i) {
            for (int j = 0; j < freq[i]; ++j)
                one_sol.push_back(candi[i]);
        }
        result.push_back(one_sol);
    }

    bool nextFreq(const vector<int> &candi, vector<int> &freq, int& sum, int target) {
        int idx = candi.size() - 1;
        do {
            ++freq[idx];
            sum += candi[idx];
            if (sum <= target)
                return true;
            sum -= candi[idx]*freq[idx];
            freq[idx] = 0;
            --idx;
        } while (idx >= 0);
        return false;
    }
};

void testComboNumber()
{
  Solution sol;
  int test_case[] = {7,5,8,12,3,10,9,4,11,6};
  int test_case_count = sizeof(test_case)/sizeof(test_case[0]);
  vector<int> candi(test_case, test_case+test_case_count);
  int target = 21;
  vector<vector<int> > ans = sol.combinationSum(candi, target);
  for (auto &vec: ans) {
    for (auto i: vec)
      cout << i << '+';
    cout << endl;
  }
}
