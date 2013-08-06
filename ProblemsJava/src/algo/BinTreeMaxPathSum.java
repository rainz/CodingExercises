package algo;

/*
 * Given a binary tree, find the maximum path sum.
 * The path may start and end at any node in the tree.
 */
public class BinTreeMaxPathSum {
  class Result {
    public int subSum; // max leg sum of a tree
    public int maxSum;
    public Result(int s, int m) {subSum = s; maxSum = m;}
  }

  public Result helper(TreeNode root) {
      // Note the default value should be MIN_VALUE, not 0. 
      // Otherwise trees with negative values will return 0.
      Result result = new Result(Integer.MIN_VALUE, Integer.MIN_VALUE);
      if (root == null) return result;
      
      Result lResult = helper(root.left);
      Result rResult = helper(root.right);
      
      // Compute max leg sum.
      result.subSum = Math.max(lResult.subSum, rResult.subSum);
      if (result.subSum <= 0) result.subSum = 0;
      result.subSum += root.val;
      
      // Compute max path sum.
      result.maxSum = root.val;
      if (lResult.subSum > 0) result.maxSum += lResult.subSum;
      if (rResult.subSum > 0) result.maxSum += rResult.subSum;
      // So far the max path sum passing through root has been computed.
      // Now compare it with left max and right max.
      int tmpMax = Math.max(lResult.maxSum, rResult.maxSum);
      if (tmpMax > result.maxSum) result.maxSum = tmpMax;
      
      return result;
  }
  
  public int maxPathSum(TreeNode root) {
      Result result = helper(root);
      return result.maxSum;
  }

}
