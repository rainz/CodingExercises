/*
 * WordSearch.cpp
 *
 *  Created on: Apr 26, 2013
 *      Author: Yu
 */

// Didn't pass Leetcode. Output result is different???

#include <iostream>
#include <vector>
#include <string>

using namespace std;

static int offsets[4][2] = {
  {-1, 0},
  {1, 0},
  {0, -1},
  {0, 1}
};

class WordSearch {
public:
    vector<vector<bool> > visitedMap;
    string target;
    int rows;
    int cols;
    bool search(vector<vector<char> > &board, int r, int c, int idx) {
      if (idx == target.length()) return true;
      for (int dir = 0; dir < 4; ++dir) {
        r += offsets[dir][0];
        c += offsets[dir][1];
        if (r >= 0 && r < rows && c >= 0 && c < cols &&
            board[r][c] == target[idx] && !visitedMap[r][c]) {
          visitedMap[r][c] = true;
          if (search(board, r, c, idx+1))
            return true;
          visitedMap[r][c] = false;
        }
        r -= offsets[dir][0];
        c -= offsets[dir][1];
      }
      return false;
    }
    bool exist(vector<vector<char> > &board, string word) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (word.length() == 0) return true;
        visitedMap.clear();
        target = word;
        rows = board.size();
        if (rows == 0) return false;
        cols = board[0].size();
        if (cols == 0) return false;
        visitedMap.resize(rows);
        for (int i = 0; i < rows; ++i) {
          for (int j = 0; j < cols; ++j) {
            visitedMap[i].push_back(false);
          }
        }
        for (int i = 0; i < rows; ++i) {
          for (int j = 0; j < cols; ++j) {
            if (board[i][j] == word[0]) {
              visitedMap[i][j] = true;
              if (search(board, i, j, 1)) return true;
              visitedMap[i][j] = false;
            }
          }
        }
        return false;
    }
};


void testWordSearch()
{
  WordSearch ws;
  vector<vector<char> > board;
  vector<char> row0;
  row0.push_back('a');
  row0.push_back('b');
  board.push_back(row0);
  row0.clear();
  row0.push_back('c');
  row0.push_back('d');
  board.push_back(row0);
  string word("cdba");
  if (ws.exist(board, word)) {
    cout << word << " exists!" << endl;
  }
  else {
    cout << word << " doesn't exist!" << endl;
  }
}
