/*
 * NextPerm.cpp
 *
 *  Created on: Sep 30, 2012
 *      Author: Yu
 */

#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cstring>

#include "utils.h"


using namespace std;

// Wrong

static bool nextPerm(int perm[], int n)
{
  int swap1 = -1, swap2 = -1;
  for (int i = 1; i < n; ++i) {
    if (perm[i] > perm[i - 1]) {
      swap1 = i - 1;
      swap2 = i;
    }
    else if (swap1 >= 0 && swap2 >= 0 && perm[i] < perm[swap2] && perm[i] > perm[swap1]) {
      swap2 = i;
    }
  }

  if (swap1 >= 0) {
    int tmp = perm[swap1];
    perm[swap1] = perm[swap2];
    perm[swap2] = tmp;
    // Reverse the numbers after swap1
    int bgn, end;
    for (bgn = swap1+1, end = n - 1; bgn < end; ++bgn, --end) {
      tmp = perm[bgn];
      perm[bgn] = perm[end];
      perm[end] = tmp;
    }
    return true;
  }

  return false;
}


void testNextPerm()
{
  int perm[] = {1, 2, 3, 4, 5};
  int arr_size = sizeof(perm)/sizeof(perm[0]);
  int perm_copy[arr_size];
  memcpy(perm_copy, perm, sizeof(perm));

  bool hasNext = true;
  int count = 0;
  do {
    showArray(perm, arr_size);
    ++count;
    hasNext = nextPerm(perm, arr_size);
    next_permutation(perm_copy, perm_copy+arr_size);
    if (hasNext && memcmp(perm, perm_copy, sizeof(perm))) {
      cout << "Error!" << endl;
      showArray(perm, arr_size);
      showArray(perm_copy, arr_size);
      break;
    }
  } while (hasNext);
  cout << count << " total." << endl;
}
