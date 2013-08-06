package algo;

public class EditDistance {
  public int minDistance(String word1, String word2) {
    int len1 = word1.length(), len2 = word2.length();
    
    int dp[][] = new int[len1+1][len2+1];
    for (int i = 0; i < len1+1; ++i)
      dp[i][len2] = len1-i;
    for (int i = 0; i < len2+1; ++i)
      dp[len1][i] = len2-i;
    
    
    for (int row = len1-1; row >= 0; --row) {
        for (int col = len2-1; col >= 0; --col) {
            if (word1.charAt(row) == word2.charAt(col)) {
                dp[row][col] = dp[row+1][col+1];
            }
            else {
                int minDist = Math.min(dp[row][col+1], dp[row+1][col]);
                minDist = Math.min(minDist, dp[row+1][col+1]);
                dp[row][col] = 1 + minDist;
            }
        }
    }
    
    return dp[0][0];
  }

}
