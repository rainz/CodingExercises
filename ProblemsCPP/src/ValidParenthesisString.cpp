#include <iostream>
#include <string>
#include "utils.h"

using namespace std;

bool helper(const string& s, int start, int score)
{
    for (; start < s.length() && s[start] != '*'; ++start) {
        if (s[start] == '(')
            ++score;
        else {
            --score;
            if (score < 0)
                return false;
        }
    }
    if (start < s.length()) {
        // start points to *
        bool ans = helper(s, start+1, score); // try ""
        if (ans)
            return true;
        ans = helper(s, start+1, score+1); // try "("
        if (ans)
            return true;
        --score;
        if (score < 0)
            return false;
        return helper(s, start+1, score);
            
    }
    return (score == 0);
}

bool checkValidString(string s) {
    return helper(s, 0, 0);
}

int main(void)
{
    cout << checkValidString("()") << endl;
    cout << checkValidString("(*)") << endl;
    cout << checkValidString("(*))") << endl;
    return 0;
}