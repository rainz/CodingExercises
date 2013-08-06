/*
 * SortedList2BST.cpp
 *
 *  Created on: May 15, 2013
 *      Author: Yu
 */

#include <cstdlib>

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

struct TreeNode {
  int val;
   TreeNode *left;
   TreeNode *right;
   TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

// Given a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.
class SortedList2BST {
public:
    ListNode *getMid(ListNode *start, ListNode *end) {
      if (start->next == end) return start;
      if (start->next->next == end) return start;
      ListNode* slow = start;
      ListNode* fast = start->next;
      while (fast != end) {
        slow = slow->next;
        fast = fast->next;
        if (fast != end)
          fast = fast->next;
      }
      return slow;
    }
    TreeNode *helper(ListNode *start, ListNode *end) {
      if (start == end) return NULL;
      ListNode *currList = getMid(start, end);
      TreeNode *curr = new TreeNode(currList->val);
      curr->left = helper(start, currList);
      curr->right = helper(currList->next, end);
      return curr;
    }
    TreeNode *sortedListToBST(ListNode *head) {
        return helper(head, NULL);
    }
};
