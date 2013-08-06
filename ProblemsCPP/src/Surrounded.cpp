/*
 * Surrounded.cpp
 *
 *  Created on: May 6, 2013
 *      Author: Yu
 */

#include <vector>
#include <utility>

using namespace std;
/*
 * Given a 2D board containing 'X' and 'O', capture all regions surrounded by 'X'.
 * A region is captured by flipping all 'O's into 'X's in that surrounded region .
 */

class Surrounded {
public:
    int rows;
    int cols;
    /****************** Backtrack & recursion. Passes small cased but not big cases. ********************/
    bool surrounded(vector<vector<char>> &board, int i, int j, vector<pair<int, int> > &region) {
      if (i < 0 || j < 0 || i >= rows || j >= cols)
        return false; // reached edge of board. not surrounded
      if (board[i][j] != 'O') return true;
      board[i][j] = 'V'; // visited
      region.push_back(make_pair(i, j));
      if (!surrounded(board, i+1, j, region) ||
          !surrounded(board, i-1, j, region) ||
          !surrounded(board, i, j+1, region) ||
          !surrounded(board, i, j-1, region))
          return false;
      return true;
    }
    void solveSmall(vector<vector<char>> &board) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        rows = board.size();
        if (rows == 0) return;
        cols = board[0].size();
        if (cols == 0) return;
        for (int i = 0; i < rows; ++i) {
          for (int j = 0; j < cols; ++j) {
            if (board[i][j] != 'O') continue;
            vector<pair<int, int> > region;
            if (surrounded(board, i, j, region)) {
              for (int r = 0; r < region.size(); ++r)
                board[region[r].first][region[r].second] = 'X';
            }
          }
        }
        for (int i = 0; i < rows; ++i) {
          for (int j = 0; j < cols; ++j) {
            if (board[i][j] == 'V')
              board[i][j] = 'O';
          }
        }
    }
    /*******************************************************************************************/

    /****************** BFS solution. Passes big cases. ********************/
    void checkRegion(vector<vector<char> > &board, int i, int j) {
      vector<pair<int, int> > region;
      region.push_back(make_pair(i, j));
      bool surrounded = true;
      int posIdx = 0;
      while (posIdx < region.size()) {
        pair<int, int>& pos = region[posIdx];
        posIdx++;
        int r = pos.first, c = pos.second;
        if (r < 0 || c < 0 || r >= rows || c >= cols) {
          surrounded = false; // reached edge of board. not surrounded
          continue;
        }
        if (board[r][c] != 'O') continue;
        board[r][c] = 'V'; // visited
        region.push_back(make_pair(r+1, c));
        region.push_back(make_pair(r-1, c));
        region.push_back(make_pair(r, c+1));
        region.push_back(make_pair(r, c-1));
      }
      if (surrounded == false) return;
      for (int x = 0; x < region.size(); ++x) {
        pair<int, int>& pos = region[x];
        int r = pos .first, c = pos .second;
        if (r < 0 || c < 0 || r >= rows || c >= cols) continue;
        board[r][c] = 'X';
      }
    }
    void solve(vector<vector<char>> &board) {
        rows = board.size();
        if (rows == 0) return;
        cols = board[0].size();
        if (cols == 0) return;
        for (int i = 0; i < rows; ++i) {
          for (int j = 0; j < cols; ++j) {
            if (board[i][j] != 'O') continue;
            checkRegion(board, i, j);
          }
        }
        for (int i = 0; i < rows; ++i) {
          for (int j = 0; j < cols; ++j) {
            if (board[i][j] == 'V')
              board[i][j] = 'O';
          }
        }
    }
    /**********************************************************/
};

