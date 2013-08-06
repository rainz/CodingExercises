/*
 * subset.cpp
 *
 *  Created on: Apr 14, 2013
 *      Author: Yu
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;



class Subset {

public:
    vector<vector<int> > subsets(vector<int> &S) {
        vector<vector<int> > answer;
        vector<int> subset;
        sort(S.begin(), S.end());
        helper(S, 0, subset, answer);
        return answer;
    }

private:
    void helper(vector<int> &S, unsigned start, vector<int> &subset, vector<vector<int> > &answer) {
      if (start >= S.size()) { answer.push_back(subset);return;}
      helper(S, start+1, subset, answer);
      subset.push_back(S[start]);
      helper(S, start+1, subset, answer);
      subset.pop_back();
    }
};
