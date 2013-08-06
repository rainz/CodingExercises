/*
 * DecodeWays.cpp
 *
 *  Created on: Apr 30, 2013
 *      Author: Yu
 */

#include <string>
#include <cstdlib>

using namespace std;

class DecodeWays {
public:
  /*
   * A message containing letters from A-Z is being encoded to numbers using the following mapping:
   * 'A' -> 1
   * 'B' -> 2
   * ...
   * 'Z' -> 26
   * Given an encoded message containing digits, determine the total number of ways to decode it.
   */

    int helper(const string &s, int idx) {
      char c1 = s[idx];
      if (c1 == '0') return 0;
      if (c1 == '\0') return 1;
      int ret = helper(s, idx+1);
      char c2 = s[idx+1];
      if (c2 != '\0' && (c1-'0')*10+(c2-'0') <= 26)
        ret += helper(s, idx+2);
      return ret;
    }
    int numDecodingsRecursive(string s) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (s == "") return 0;
        return helper(s, 0);
    }

    int numDecodingsDP(string s) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (s.length() == 0) return 0;
        // Allocate one extra element for empty string.
        int *dp = (int*)malloc((s.length()+1)*sizeof(int));
        int idx = s.length();
        dp[idx--] = 1;
        dp[idx] = (s[idx] == '0' ? 0 : 1);
        --idx;
        while (idx >= 0) {
          char c1 = s[idx];
          if (c1 == '0')
            dp[idx] = 0;
          else {
           dp[idx] = dp[idx+1];
           if ((c1-'0')*10+(s[idx+1]-'0') <= 26)
             dp[idx] += dp[idx+2];
          }
          --idx;
        }
        int answer = dp[0];
        free(dp);
        return answer;
    }
};
