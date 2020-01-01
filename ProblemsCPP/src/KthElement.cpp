/*
 * KthElement.cpp
 *
 *  Created on: Aug 24, 2012
 *      Author: Yu
 */

/*
 * Find the kth largest element in an unsorted array.
 */

#include <iostream>
#include <cassert>
#include "utils.h"

using namespace std;

// Returns size of "greater" section, including pivot
static int partition(vector<int>& nums, int start, int len)
{
  if (len <= 0)
    return 0;
  int pivot = nums[start];
  int largeIdx = start; // point at the last large number idx
  for (int i = start + 1; i < start + len; ++i) {
    if (pivot <= nums[i]) {
      ++largeIdx;
      swap(nums[largeIdx], nums[i]);
    }
  }
  // Make pivot the last one in "greater" section, since all others are >= pivot
  swap(nums[start], nums[largeIdx]);
  return largeIdx - start + 1;
}

static int findKth(vector<int>& nums, int start, int len, int k)
{
    int greaterCount = partition(nums, start, len);
    if (greaterCount == k)
        return nums[start + k - 1];

    if (greaterCount > k)
        return findKth(nums, start, greaterCount-1, k);
    else
        return findKth(nums, start+greaterCount, len-greaterCount, k-greaterCount);
}

int findKthLargest(vector<int>& nums, int k)
{
    return findKth(nums, 0, nums.size(), k);
}

int main(void)
{
    vector<int> input1{3,2,1,5,6,4};
    vector<int> input2{3,2,3,1,2,4,5,5,6};
    cout << findKthLargest(input1, 2) << endl;
    cout << findKthLargest(input2, 4) << endl;

    return 0;
}