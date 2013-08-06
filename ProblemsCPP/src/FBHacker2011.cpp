#include <iostream>
#include <set>
#include <iomanip>
#include <cstring>

using namespace std;

int FBHackerPeg()
{
  int num_tests;
  cin >> num_tests;

  for (int i = 0; i < num_tests; ++i) {
    int num_rows, num_cols, target_col, num_pairs;
    cin >> num_rows >> num_cols >> target_col >> num_pairs;

    set<pair<int, int> > missing_cols;
    for (int p = 0; p < num_pairs; ++p) {
      int r, c;
      cin >> r >> c;
      missing_cols.insert(make_pair(r, c));
    }

    const int MAP_ROWS = num_rows;
    const int MAP_COLS = num_cols*2 - 1;
    int game_map[MAP_ROWS][MAP_COLS];
    memset(game_map, 0, sizeof(game_map));

    for (int r = 0; r < num_rows; ++r) {
      int offset = r % 2;
      for (int c = 0; c < num_cols - offset; ++c) {
        if (missing_cols.find(make_pair(r, c)) != missing_cols.end())
          continue;
        game_map[r][offset+c*2] = 1;
      }
    }

    double memoize[MAP_ROWS][MAP_COLS];
    for (int r = 0; r < MAP_ROWS; ++r)
      for (int c = 0; c < MAP_COLS; ++c)
        memoize[r][c] = 0;

    int offset = num_rows % 2;
    int col_goal = offset + 2*target_col;

    /*
    for (int r = 0; r < MAP_ROWS; ++r) {
      for (int c = 0; c < MAP_COLS; ++c) {
        cout << game_map[r][c];
      }
      cout << endl;
    }
    for (int c = 0; c < MAP_COLS; ++c)
      cout << (c == col_goal ? 'G' : ' ');

    cout << endl << "=======================================" << endl;
    */

    for (int r = MAP_ROWS - 1; r >= 0; --r) {
      bool even_row = (r % 2 == 0 ? true : false);
      for (int c = 0; c < MAP_COLS; ++c) {
        if (r == MAP_ROWS - 1) {
          memoize[r][c] = (c == col_goal ? 1 : 0);
          continue;
        }

        if (game_map[r][c])
          continue; // peg

        // If position below is empty, use the same probability.
        if (!game_map[r+1][c]) {
          memoize[r][c] = memoize[r+1][c];
          continue;
        }

        bool left_edge = false, right_edge = false;
        if (c <= 0 || (c == 1 && even_row))
          left_edge = true;
        else if (c >= MAP_COLS - 1 || (c == MAP_COLS - 2 && even_row))
          right_edge = true;

        if (left_edge)
          memoize[r][c] = memoize[r+1][c+1];
        else if (right_edge)
          memoize[r][c] = memoize[r+1][c-1];
        else
          memoize[r][c] = (memoize[r+1][c+1] + memoize[r+1][c-1]) / 2;
      }
    }

    double max_prob = 0;
    int max_col = -1;
    for (int c = 0; c < num_cols - 1; ++c) {
      if (max_prob < memoize[0][2*c+1]) {
        max_prob = memoize[0][2*c+1];
        max_col = c;
      }
    }
    cout << "Case #" << i << ": ";
    if (max_col < 0)
      cout << "XXX" << endl;
    else
      cout << max_col << ' ' << setprecision(6) << fixed << max_prob << endl;
    /*
    for (int r = 0; r < MAP_ROWS; ++r) {
      for (int c = 0; c < MAP_COLS; ++c)
        cout << memoize[r][c] << ' ';
      cout << endl;
    }
    */
  }

  return 0;
}
