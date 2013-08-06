/*
 * PhoneLetter.cpp
 *
 *  Created on: May 7, 2013
 *      Author: Yu
 */

#include <string>
#include <vector>
#include <cstring>

using namespace std;

class Solution {
public:
    vector<string> answer;
    void helper(const string &digits, int idx, string& result) {
        if (idx >= digits.length()) {
          answer.push_back(result);
          return;
        }
        static const char *mapping[] = {
          "","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"
        };
        int num = digits[idx] - '0';
        const char *str = mapping[num];
        int len = strlen(str);
        result += ' '; // place holder for the new character
        for (int i = 0; i < len; ++i) {
          result[idx] = str[i];
          helper(digits, idx+1, result);
        }
        result.resize(idx);
    }
    vector<string> letterCombinations(string digits) {
        string result;
        answer.clear();
        helper(digits, 0, result);
        return answer;
    }
};
