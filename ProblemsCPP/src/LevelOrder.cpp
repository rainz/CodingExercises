/*
 * LevelOrder.cpp
 *
 *  Created on: May 12, 2013
 *      Author: Yu
 */

#include <queue>
#include <cstdlib>

using namespace std;


struct TreeLinkNode {
  int val;
  TreeLinkNode *left, *right, *next;
  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};

class LevelOrder {
public:
    /*
     * Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.
     */
    void connect(TreeLinkNode *root) {
        queue<TreeLinkNode*> workQ;
        workQ.push(root);
        if (root)
          workQ.push(NULL);
        TreeLinkNode *prev = NULL;
        while (!workQ.empty()) {
          TreeLinkNode *curr = workQ.front();
          workQ.pop();
          if (prev) prev->next = curr;
          prev = curr;
          if (!curr) {
           if (workQ.back() != NULL)
             workQ.push(NULL);
          }
          else {
            if (curr->left)
              workQ.push(curr->left);
            if (curr->right)
              workQ.push(curr->right);
          }
        }
    }
};
