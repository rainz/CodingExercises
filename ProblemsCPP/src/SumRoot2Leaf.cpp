/*
 * SumRoot2Leaf.cpp
 *
 *  Created on: May 5, 2013
 *      Author: Yu
 */

#include <cstdlib>

/*
 * Given a binary tree containing digits from 0-9 only, each root-to-leaf path could represent a number.
 * An example is the root-to-leaf path 1->2->3 which represents the number 123.
 * Find the total sum of all root-to-leaf numbers.
 *
 */
struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

class SumRoot2Leaf {
public:
    void helper(TreeNode *node, int number, int& sum) {
      if (!node) return;
      number = 10*number+node->val;
      if (!node->left && !node->right) {
        sum += number;
        return;
      }
      helper(node->left, number, sum);
      helper(node->right, number, sum);
    }
    int sumNumbers(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int sum = 0, number = 0;
        helper(root, number, sum);
        return sum;
    }
};
