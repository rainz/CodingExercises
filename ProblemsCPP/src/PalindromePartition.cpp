/*
 * PalindromePartition.cpp
 *
 *  Created on: May 6, 2013
 *      Author: Yu
 */

#include <string>
#include <vector>

using namespace std;

class PalindromePartition {
public:
    vector<vector<int> > dp;
    vector<vector<string> > answer;

    /*
     * Given a string s, partition s such that every substring of the partition is a palindrome.
     * Return all possible palindrome partitioning of s.
     */

    void helper(const string& s, int idx, vector<string>& sol) {
        if (idx >= s.length()) {
            answer.push_back(sol);
            return;
        }
        for (int i = idx; i < s.length(); ++i) {
            if (!dp[idx][i]) continue;
            sol.push_back(s.substr(idx, i-idx+1));
            helper(s, i+1, sol);
            sol.pop_back();
        }
    }
    vector<vector<string>> partition(string s) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        answer.clear();
        dp.clear();
        int len = s.length();
        dp.resize(len);
        for (int i = 0; i < len; ++i)
          dp[i].resize(len);

        // Base case: string length=1
        for (int i = 0; i < len; ++i)
          dp[i][i] = 1;
        // All other string lengths
        for (int l = 2; l <= len; ++l) {
            for (int start = 0; start+l-1 < len; ++start) {
                int end = start+l-1;
                if (s[start] != s[end]) {
                    dp[start][end] = 0;
                    continue;
                }
                dp[start][end] = end > start+1 ? dp[start+1][end-1] : 1;
            }
        }

        vector<string> sol;
        helper(s, 0, sol);
        return answer;
    }
};
