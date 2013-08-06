/*
 * SortLinkedList.cpp
 *
 *  Created on: Apr 14, 2013
 *      Author: Yu
 */

#include <iostream>
#include <vector>
#include <algorithm>

#include <cstdlib>
#include <ctime>

#include "utils.h"

using namespace std;

struct Node {
  Node(int v): val(v), next(NULL)
  {}
  int val;
  Node *next;
};

static Node* getMiddle(Node* start)
{
  if (start == NULL)
    return NULL;
  Node dummy(-1);
  dummy.next = start;
  Node *slow = &dummy;
  Node *fast = slow;
  while (fast != NULL) {
    fast = fast->next;
    if (fast != NULL) {
      slow = slow->next;
      fast = fast->next;
    }
  }
  return slow;
}

static Node* sortLL(Node* start)
{
  if (start == NULL || start->next == NULL)
    return start;

  Node *mid = getMiddle(start);
  // Split the list.
  Node* ptr2 = mid->next;
  mid->next = NULL;
  Node *ptr1 = sortLL(start);
  ptr2 = sortLL(ptr2);
  Node* head = ptr1;

  // Merge second list into first list.
  // This is more complicated than necessary.
  Node* prev1 = NULL;
  while (ptr2 != NULL) {
    // Search for insertion point.
    while (ptr1 != NULL && ptr1->val < ptr2->val) {
      prev1 = ptr1;
      ptr1 = ptr1->next;
    }
    if (prev1) {
      prev1->next = ptr2;
    }
    else {
      head = ptr2;
    }
    if (ptr1 == NULL) {
      break; // ptr2 and all nodes afterwards are greater, so we are done.
    }
    // Include all list 2 nodes which are <=ptr1->val in the insertion.
    Node *prev2 = ptr2;
    ptr2 = ptr2->next;
    while (ptr2 != NULL && ptr2->val <= ptr1->val) {
      prev2 = ptr2;
      ptr2 = ptr2->next;
    }
    prev2->next = ptr1;
  }

  return head;
}

static int deleteList(Node *n)
{
  int count = 0;
  while (n != NULL) {
    Node *next = n->next;
    delete(n);
    ++count;
    n = next;
  }
  return count;
}

void testSortLinkedList()
{
  srand(time(NULL));
  int min_test_len = 0, max_test_len = 30;
  for (int len = min_test_len; len <= max_test_len; ++len) {
    vector<int> toCompare;
    // Generate a random linked list with length=len
    Node *head = NULL, *tail = NULL;
    for (int i = 0; i < len; ++i) {
      int val = rand() % 15;
      toCompare.push_back(val);
      Node *n = new Node(val);
      if (tail == NULL)
        head = n;
      else
        tail->next = n;
      tail = n;
    }
    cout << "Sorting:" << endl;
    showVector(toCompare);
    sort(toCompare.begin(), toCompare.end());
    Node *n = sortLL(head);
    for (unsigned i = 0; i < toCompare.size(); ++i, n = n->next) {
      if (toCompare[i] != n->val) {
        cerr << "Error in comparison!!!" << endl;
        Node *n = head;
        while (n) {
          cerr << n->val << ", ";
          n = n->next;
        }
        cerr << endl;
        break;
      }
    }
    deleteList(head);
  }
  cout << "Done." << endl;
}
