/*
 * perm.cpp
 *
 *  Created on: Apr 14, 2013
 *      Author: Yu
 */

#include <iostream>
#include <vector>
#include <set>

using namespace std;

/*
 * Generate all permutations for numbers in vector "num", where "num" may contain *duplicates*.
 * The algorithm used here has one additional "twist" comparing to algorithm used for permutation without dups:
 * at each position, the same value cannot appear twice.
 * For example: 1,2,2. The dup check code below prevents the following two case:
 * 1. When the first 2 and the second 2 try to swap positions.
 * 2. After 1 swapped with the first 2, 1 tries to swap with the second 2.
 */

void
perm(vector<int> &num, vector<vector<int> >&result, int nStart, int nEnd)
{
  if (nStart < nEnd - 1)
  {
    set<int> used; // used for dup check
    perm(num, result, nStart+1, nEnd);
    used.insert(num[nStart]); // used for dup check
    for (int i = nStart+1; i < nEnd; ++i)
    {
      if (used.find(num[i]) != used.end())
        continue; // dup check
      used.insert(num[i]); // used for dup check
      swap(num[nStart], num[i]);
      perm(num, result, nStart + 1, nEnd);
      swap(num[nStart], num[i]);
    }
  }
  else
    result.push_back(num);
}

void testPerm()
{
  int nums[] = {2,2, 1, 1};
  vector<int> num;
  for (unsigned i = 0; i < sizeof(nums)/sizeof(nums[0]); ++i) num.push_back(nums[i]);

  vector<vector<int> > answer;
  perm(num, answer, 0, num.size());

  for (unsigned i = 0; i < answer.size(); ++i) {
    const vector<int> &v = answer[i];
    for (unsigned j = 0; j < v.size(); ++j) {
      cout << v[j] << ' ';
    }
    cout << endl;
  }
}
