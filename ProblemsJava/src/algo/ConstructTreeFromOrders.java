package algo;

public class ConstructTreeFromOrders {

  /* Given inorder and postorder traversal of a tree, construct the binary tree.
   * You may assume that duplicates do not exist in the tree.
   */
  private TreeNode helperInPost(int[] inorder, int istart, int[] postorder, int pstart, int len) {
      if (len == 0) return null;
      int nodeVal = postorder[pstart+len-1];
      int nodeIdx = istart;
      while (nodeIdx < istart+len && inorder[nodeIdx] != nodeVal) ++nodeIdx;
      TreeNode node = new TreeNode(nodeVal);
      int leftLen = nodeIdx - istart;
      node.left = helperInPost(inorder, istart, postorder, pstart, leftLen);
      node.right = helperInPost(inorder, nodeIdx+1, postorder, pstart+leftLen, len - leftLen - 1);
      return node;
  }
  public TreeNode buildTreeFromInPost(int[] inorder, int[] postorder) {
      return helperInPost(inorder, 0, postorder, 0, inorder.length);        
  }
 
  /* Given preorder and inorder traversal of a tree, construct the binary tree.
   * You may assume that duplicates do not exist in the tree.
   */
  private TreeNode helperPreIn(int[] preorder, int pstart, int[] inorder, int istart, int len) {
    if (len == 0) return null;
    int nodeVal = preorder[pstart];
    int nodeIdx = istart;
    while (nodeIdx < istart+len && inorder[nodeIdx] != nodeVal) ++nodeIdx;
    TreeNode node = new TreeNode(nodeVal);
    int leftLen = nodeIdx - istart;
    node.left = helperPreIn(preorder, pstart+1, inorder, istart, leftLen);
    node.right = helperPreIn(preorder, pstart+1+leftLen, inorder, istart+1+leftLen, len - leftLen - 1);
    return node;
  }
  
  public TreeNode buildTreeFromPreIn(int[] preorder, int[] inorder) {
      return helperPreIn(preorder, 0, inorder, 0, preorder.length);
  }
}
