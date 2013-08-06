/*
 * Interleave.cpp
 *
 *  Created on: May 9, 2013
 *      Author: Yu
 */

#include <string>
#include <iostream>
#include <cstring>

using namespace std;

class Interleave {
public:
    string s1, s2, s3;
    int len1, len2, len3;
    /********* Recursion solution **************/
    bool helper(int p1, int p2) {
      if (p1 + p2 >= len3) return true;
      bool match = false;
      if (s1[p1] == s3[p1+p2])
        match = helper(p1+1, p2);
      if (match) return true;
      if (s2[p2] == s3[p1+p2])
        match = helper(p1, p2+1);
      return match;
    }
    bool isInterleaveRecursive(string s1, string s2, string s3) {
        this->s1 = s1; this->s2 = s2; this->s3 = s3;
        len1 = s1.length();
        len2 = s2.length();
        len3 = s3.length();
        if (len1 + len2 != len3) return false;
        return helper(0, 0);
    }
    /*******************************************/

    /********Dynamic Programming solution****************/
    bool isInterleave(string s1, string s2, string s3) {
        this->s1 = s1; this->s2 = s2; this->s3 = s3;
        len1 = s1.length();
        len2 = s2.length();
        len3 = s3.length();
        if (len1 + len2 != len3) return false;
        bool dp[len1+1][len2+1]; // include '\0' character
        memset(dp, 0, sizeof(dp));
        dp[len1][len2] = true; // two empty strings
        // Fill last column (ie, s2 at '\0')
        for (int row = len1-1; row >= 0; --row) {
          dp[row][len2] = (dp[row+1][len2] && s1[row] == s3[len2+row]);
        }
        // Fill last row (ie, s1 at '\0')
        for (int col = len2-1; col >= 0; --col) {
          dp[len1][col] = (dp[len1][col+1] && s2[col] == s3[len1+col]);
        }
        // Fill the rest of the table
        for (int row = len1-1; row >= 0; --row) {
          for (int col = len2-1; col >= 0; --col) {
            char c3 = s3[row+col];
            dp[row][col] = (s1[row] == c3 && dp[row+1][col]) ||
                           (s2[col] == c3 && dp[row][col+1]);
          }
        }
        return dp[0][0];
    }
    /******************************************************/
};

void testInterleave()
{
  Interleave inter;
  bool result = inter.isInterleave("ab", "bc", "bbac"); // should return false.
  cout << "Result is " << (result ? "true" : "false");
}
