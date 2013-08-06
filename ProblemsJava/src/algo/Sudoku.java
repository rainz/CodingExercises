package algo;

public class Sudoku {
  /* Write a program to solve a Sudoku puzzle by filling the empty cells.
   * Empty cells are indicated by the character '.'.
   * You may assume that there will be only one unique solution.
   */
  boolean check(char[][] board, int row, int col)
  {
    char thisVal = board[row][col];
    for (int i = 0; i < board.length; ++i)
    {
      if (i == col)
        continue;
      if (thisVal == board[row][i])
        return false;
    }
    for (int i = 0; i < board.length; ++i)
    {
      if (i == row)
        continue;
      if (thisVal == board[i][col])
        return false;
    }
    int row0 = row / 3 * 3, col0 = col / 3 * 3;
    for (int i = 0; i < 9; ++i)
    {
      int r = row0 + i / 3, c = col0 + i % 3;
      if (r == row && c == col)
        continue;
      if (thisVal == board[r][c])
        return false;
    }
    return true;
  }

  boolean helper(char[][] board, int idx)
  {
    int totalSize = board.length * board.length;
    if (idx >= totalSize)
      return true;
    int row = idx / board.length, col = idx % board.length;
    if (board[row][col] != '.')
      return helper(board, idx + 1);
    for (char c = '1'; c <= '9'; ++c)
    {
      board[row][col] = c;
      if (check(board, row, col) && helper(board, idx + 1))
        return true;
    }
    board[row][col] = '.';
    return false;
  }

  public void solveSudoku(char[][] board)
  {
    helper(board, 0);
  }
  
  /* Determine if a Sudoku is valid.
   * The Sudoku board could be partially filled, where empty cells are filled with the character '.'.
   */
  public boolean isValidSudoku(char[][] board) {
      // Check each row
      for (int row = 0; row < board.length; ++row) {
          boolean [] flags = new boolean[9];
          for (int col = 0; col < board.length; ++col) {
              char c = board[row][col];
              if (c == '.') continue;
              int digit = c - '0';
              if (flags[digit-1]) return false;
              flags[digit-1] = true;
          }
      }
      
      // Check each column
      for (int col = 0; col < board.length; ++col) {
          boolean [] flags = new boolean[9];
          for (int row = 0; row < board.length; ++row) {
              char c = board[row][col];
              if (c == '.') continue;
              int digit = c - '0';
              if (flags[digit-1]) return false;
              flags[digit-1] = true;
          }
      }
      
      // Check each box
      for (int row0 = 0; row0 < board.length; row0 += 3) {
          for (int col0 = 0; col0 < board.length; col0 += 3) {
              boolean [] flags = new boolean[9];
              for (int idx = 0; idx < 9; ++idx) {
                  int row = row0 + idx/3, col = col0 + idx%3;
                  char c = board[row][col];
                  if (c == '.') continue;
                  int digit = c - '0';
                  if (flags[digit-1]) return false;
                  flags[digit-1] = true;
              }
          }
      }
      
      return true;
  }
}
