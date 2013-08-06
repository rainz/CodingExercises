/*
 * NthPerm.cpp
 *
 *  Created on: May 2, 2013
 *      Author: Yu
 */

#include <iostream>
#include <string>

using namespace std;

// Not working yet. In progress.

class NthPerm {
public:
  int fact[10];
  char numbers[9];
  string getPermutation(int n, int k) {
    --k;
    fact[0] = 1;
    for (int i = 1; i <= n; ++i)
    {
      fact[i] = fact[i - 1] * i;
      numbers[i - 1] = '0' + i;
    }
    string answer;
    while (n > 0)
    {
      int val = k / fact[n - 1];
      answer += numbers[val];
      k %= fact[n - 1];
      for (int i = val; i < n - 1; ++i)
      {
        numbers[i] = numbers[i + 1];
      }
      --n;
    }
    return answer;
  }

};


void testNthPerm()
{
  NthPerm perm;
  cout << perm.getPermutation(2, 1) << endl;
}
