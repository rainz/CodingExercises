/*
 * KthSortedArrays.cpp
 *
 *  Created on: Jan 14, 2012
 *      Author: Yu
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <climits>

using namespace std;

static int bruteForce(const vector<int>& v1, const vector<int>& v2, int kth)
{
  int idx1 = 0, idx2 = 0;
  int ret = -1;
  if (kth > v1.size() + v2.size())
    return ret;
  while (idx1 + idx2 < kth)
  {
    if (idx1 >= v1.size())
      ret = v2[idx2++];
    else if (idx2 >= v2.size())
      ret = v1[idx1++];
    else if (v1[idx1] < v2[idx2])
      ret = v1[idx1++];
    else
      ret = v2[idx2++];
  }
  return ret;
}

struct VectorBS {
  const vector<int>& vec;
  int start_idx;
  int end_idx;
  int start_rank;
  int end_rank;
  VectorBS(const vector<int>& v, int k) : vec(v),
                                          start_idx(0),
                                          end_idx(min((int)vec.size()-1, k)),
                                          start_rank(0),
                                          end_rank(INT_MAX)
  {
  }
  int getMidIdx() { return (start_idx + end_idx + 1)/2; }
};

static int binarySearch(const vector<int>& v1, const vector<int>& v2, int kth)
{
  int ret = -1;
  if (kth > v1.size() + v2.size())
    return ret;

  VectorBS vec1(v1, kth), vec2(v2, kth);
  vec1.end_rank = vec2.end_rank = vec1.end_idx + vec2.end_idx;

  while (vec1.start_idx < vec1.end_idx || vec2.start_idx < vec2.end_idx) {
    int mid1 = vec1.getMidIdx();
    int mid2 = vec2.getMidIdx();
    bool v1greater= (vec1.vec[mid1] > vec2.vec[mid2]);
    VectorBS &greaterV = v1greater ? vec1 : vec2;
    VectorBS &lesserV = v1greater ? vec2 : vec1;
    greaterV.end_idx = greaterV.getMidIdx();
    lesserV.start_idx = lesserV.getMidIdx();
  }
  // To be continued...


  return ret;
}

void testKthSortedArrays()
{
  vector<int> v1, v2;

  srand(time(NULL));

  for (int i = 0; i < 2; ++i) {
    vector<int> &vec = (i == 0 ? v1 : v2);
    int len = 5 + rand() % 10;
    for (int l = 0; l < len; ++l) {
      vec.push_back(rand() % 200);
    }
    sort(vec.begin(), vec.end());
    for (size_t l = 0; l < vec.size(); ++l)
      cout << vec[l] << ',';
    cout << endl;
  }
  int kth = rand() % (v1.size() + v2.size()) + 1;
  cout << "Bruteforce: #" << kth << " is " << bruteForce(v1, v2, kth) << endl;
}
