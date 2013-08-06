/*
 * combo.cpp
 *
 *  Created on: May 6, 2013
 *      Author: Yu
 */
#include<vector>

using namespace std;

class Combo {
public:
    void helper(int n, int k, int start, vector<int> &sol, vector<vector<int> > &answer) {
      if (k == 0) {
        answer.push_back(sol);
        return;
      }
      if (start > n) return;
      helper(n, k, start+1, sol, answer);
      sol.push_back(start);
      helper(n, k-1, start+1, sol, answer);
      sol.pop_back();
    }
    vector<vector<int> > combine(int n, int k) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<vector<int> > answer;
        vector<int> sol;
        helper(n, k, 1, sol, answer);
        return answer;
    }
};
