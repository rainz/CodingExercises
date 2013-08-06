#include <vector>

using namespace std;

class UniqPath {
public:
    int uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid) {
        const int rows = obstacleGrid.size();
        if (rows == 0) return 0;
        const int cols = obstacleGrid[0].size();
        if (cols == 0) return 0;

        vector<vector<int> > dp = obstacleGrid;
        for (int r = rows - 1; r >= 0; --r) {
          for (int c = cols - 1; c >= 0; --c) {
            if (obstacleGrid[r][c])
              dp[r][c] = 0;
            else if (r == rows - 1 && c == cols - 1)
              dp[r][c] = 1;
            else if (r == rows - 1)
              dp[r][c] = dp[r][c+1];
            else if (c == cols - 1)
              dp[r][c] = dp[r+1][c];
            else
              dp[r][c] = dp[r+1][c] + dp[r][c+1];
          }
        }
        return dp[0][0];
    }
};
