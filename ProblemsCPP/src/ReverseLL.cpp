/*
 * ReverseLL.cpp
 *
 *  Created on: May 19, 2013
 *      Author: Yu
 */

#include <cstdlib>

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class ReverseLL {
public:
    /* Reverse between (and include) the mth and nth elements (1-based) in the linked list */
    ListNode *reverseBetween(ListNode *head, int m, int n) {
        if (!head) return NULL;

        ListNode *newHead = head;
        int idx = 1;
        ListNode *curr = head;
        ListNode *prev = NULL;
        while (idx < m && curr != NULL) {
          prev = curr;
          curr = curr->next;
          ++idx;
        }

        /* The first element being reversed will be the tail
         * of the reversed section.
         */
        ListNode *reverseTail = curr;
        /* Save the node before the reversed section */
        ListNode *beforeReverse = prev;

        // Start reversing
        prev = NULL;
        while (idx <= n && curr != NULL) {
          ListNode *next = curr->next;
          curr->next = prev;
          prev = curr;
          curr = next;
          ++idx;
        }

        // Link to the list before
        if (beforeReverse != NULL) {
            beforeReverse->next = prev;
        }
        else {
          newHead = prev;
        }

        // Link to the list after
        reverseTail->next = curr;

        return newHead;
    }
};
