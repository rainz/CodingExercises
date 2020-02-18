/*
 * perm.cpp
 *
 *  Created on: Apr 14, 2013
 *      Author: Yu
 */

#include <iostream>
#include <vector>
#include <string>
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

/*
 * Given string which contains only '<' and/or '>', Insert numbers 1 to n such that all comparisons are true
 * (only return one if multiple results exist)
 * Example:
 * Input: "><>><"
 * Output: "6>2<5>4>1<3"
 */
bool perm_order_helper(vector<int> &nums, int start, const string &order) {
  if (start == nums.size())
    return true;
  for (int i = start; i < nums.size(); ++i) {
    int numS = nums[start];
    int numI = nums[i];
    bool canSwap = start == 0;
    if (!canSwap) {
      char cmp = order[start-1];
      if (cmp == '>' && nums[start-1] > numI)
        canSwap = true;
      else if (cmp == '<' && nums[start-1] < numI)
        canSwap = true;
    }
    if (!canSwap)
      continue;
    nums[start] = numI;
    nums[i] = numS;
    if (perm_order_helper(nums, start+1, order))
      return true;
    nums[start] = numS;
    nums[i] = numI;
  }
  return false;
}

string perm_order(const string &order) {
  int N = order.length() + 1;
  vector<int> nums;
  for (int i = 1; i <= N; ++i)
    nums.push_back(i);
  perm_order_helper(nums, 0, order);
  string ans;
  ans += to_string(nums[0]);
  for (int i = 1; i < N; ++i) {
    ans += order[i-1];
    ans += to_string(nums[i]);
  }
  return ans;
}
void test_perm_order() {
  string s = "><>><";
  string ans = perm_order(s);
  cout << ans << endl;
}

int main(void) {
  test_perm_order();
  return 0;
}
