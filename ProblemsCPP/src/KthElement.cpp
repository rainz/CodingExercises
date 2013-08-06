/*
 * KthElement.cpp
 *
 *  Created on: Aug 24, 2012
 *      Author: Yu
 */

#include <iostream>
#include <cassert>
#include "utils.h"

using namespace std;

static void swapElements(int *array, int idx1, int idx2)
{
  int tmp = array[idx1];
  array[idx1] = array[idx2];
  array[idx2] = tmp;
}

static int partition(int *array, int start, int len)
{
  if (len <= 0)
    return 0;
  int pivot = array[start];
  int idx1 = start, idx2 = start + len - 1;
  while (idx1 < idx2) {
    while (array[idx1] <= pivot && idx1 < idx2)
      ++idx1;
    while (array[idx2] > pivot && idx1 < idx2)
      --idx2;
    swapElements(array, idx1, idx2);
  }
  if (array[idx1] > pivot)
    --idx1;
  swapElements(array, start, idx1);

  return idx1 - start + 1;
}

static int findKth(int *array, int start, int len, int k)
{
  assert(k > 0);
  int lessCount = partition(array, start, len);
  if (lessCount == k)
    return array[start + k - 1];

  if (lessCount > k)
    return findKth(array, start, lessCount, k);
  else
    return findKth(array, start+lessCount, len-lessCount, k-lessCount);
}


void testKthElement()
{
  int array[] = {5, 62, -1, -5, -4, 33, 24};
  int array_len = sizeof(array)/sizeof(array[0]);
  //int lessCount = partition(array, 0, array_len);
  //showArray(array, array_len);
  //cout << "lessCount=" << lessCount << endl;
  for (int i = 0; i < array_len; ++i)
    cout << findKth(array, 0, array_len, i+1) << endl;
}
