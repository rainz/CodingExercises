/*
 * Spiral.cpp
 *
 *  Created on: Aug 11, 2012
 *      Author: Yu
 */

#include <iostream>
#include <vector>
#include <utility>

using namespace std;

void spiralPrint(int *arr, int M, int N)
{
  vector< pair<int, int> > dirs;
  dirs.push_back(make_pair(0, 1));
  dirs.push_back(make_pair(1, 0));
  dirs.push_back(make_pair(0, -1));
  dirs.push_back(make_pair(-1, 0));

  int row_min = 1, row_max = M - 1, col_min = 0, col_max = N - 1;
  int element_count = M*N, count = 0;
  int row = 0, col = 0, dir = 0;
  while (count < element_count) {
    cout << arr[row*N + col] << endl;
    ++count;
    switch(dir) {
    case 0:
      if (col >= col_max) {
        dir = (dir + 1) % 4;
        --col_max;
      }
      break;
    case 1:
      if (row >= row_max) {
        dir = (dir + 1) % 4;
        --row_max;
      }
      break;
    case 2:
      if (col <= col_min) {
        dir = (dir + 1) % 4;
        ++col_min;
      }
      break;
    case 3:
      if (row <= row_min) {
        dir = (dir + 1) % 4;
        ++row_min;
      }
      break;
    }
    row += dirs[dir].first;
    col += dirs[dir].second;
  }
}

void testSpiralPrint()
{
  int test1[1][1] = {{1}};
  int test2[1][3] = {{1, 2, 3}};
  int test3[4][1] = {{1},
                     {2},
                     {3},
                     {4}
  };
  int test4[5][3] = {
      {1,  2,  3},
      {4,  5,  6},
      {7,  8,  9},
      {10, 11, 12},
      {13, 14, 15}
  };

  cout << endl << "Test case 1:" << endl;
  //spiralPrint(&(test1[0][0]), 1, 1);
  cout << endl << "Test case 2:" << endl;
  //spiralPrint(&(test2[0][0]), 1, 3);
  cout << endl << "Test case 3:" << endl;
  //spiralPrint(&(test3[0][0]), 4, 1);
  cout << endl << "Test case 4:" << endl;
  spiralPrint(&(test4[0][0]), 5, 3);
}
