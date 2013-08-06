package algo;

import java.util.ArrayList;

public class UniqBSTs {

  /* Given n, how many structurally unique BST's (binary search trees) that store values 1...n? */
  public int numTrees(int n) {
      int[] dp = new int[n+1];
      dp[0] = 1;
      dp[1] = 1;
      
      for (int i = 2; i <= n; ++i) {
          dp[i] = 0;
          for (int root = 0; root < i; ++root) {
              dp[i] += dp[root]*dp[i-1-root];
          }
      }
      
      return dp[n];
  }
  
  /* Given n, generate all structurally unique BST's (binary search trees) that store values 1...n. */
  private ArrayList<TreeNode> helper(int start, int end) {
      ArrayList<TreeNode> results = new ArrayList<TreeNode>();
      if (start == end) {
          results.add(null);
          return results;
      }
      for (int i = start; i < end; ++i) {
          ArrayList<TreeNode> leftResults = helper(start, i);
          ArrayList<TreeNode> rightResults = helper(i+1, end);
          for (TreeNode lNode: leftResults) {
              for (TreeNode rNode: rightResults) {
                  TreeNode node = new TreeNode(i);
                  node.left = lNode;
                  node.right = rNode;
                  results.add(node);
              }
          }
      }
      return results;
  }
  public ArrayList<TreeNode> generateTrees(int n) {
      return helper(1, n+1);
  }
  
}
