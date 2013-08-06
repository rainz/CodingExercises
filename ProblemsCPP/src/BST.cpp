//============================================================================
// Name        : BST.cpp
// Author      :
// Version     :
// Copyright   :
// Description :
//============================================================================

#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>

#include <cstdlib>
#include <ctime>
#include <cassert>

using namespace std;

template <class T>
struct BSTNode
{
  BSTNode(const T& val) : value(val), left(NULL), right(NULL), parent(NULL) {}
  T value;
  BSTNode *left;
  BSTNode *right;
  BSTNode *parent;
};

template <class T>
class BST
{
public:
  BST() : m_root(NULL), m_node_count(0) {}
  BST(const vector<T>& preOrder)
  {
    m_node_count = preOrder.size();

    m_root = m_build_from_preorder(preOrder.begin(), preOrder.end());
  }
  BST(const BST<T>& other)
  {
    m_root = m_duplicate_tree(other.m_root);
    m_node_count = other.m_node_count;
  }

  ~BST()
  {
    m_free_subtree(m_root);
  }

  BST& operator=(const BST& other)
  {
    if (this == &other)
      return *this;

    m_root = m_duplicate_tree(other.m_root);
    m_node_count = other.m_node_count;
    return *this;
  }

  bool operator== (const BST& other)
  {
    return m_compare_subtree(m_root, other.m_root);
  }

  bool operator!= (const BST& other)
  {
    return !(*this == other);
  }

  bool findValue(const T& val) const
  {
    return (m_find_node(val) ? true : false);
  }

  bool insertValue(const T& val)
  {
    BSTNode<T> *new_node = new BSTNode<T>(val);
    if (!new_node)
    {
      cout << "Failed to insert a new node" << endl;
      return false;
    }
    if (!m_root)
    {
      m_root = new_node;
      ++ m_node_count;
      return true;
    }

    m_insert_helper(m_root, new_node);
    return true;
  }

  bool deleteValue(const T& val)
  {
    BSTNode<T> *node = m_find_node(val);
    if (!node)
      return false;

    if (node->left && node->right)
    {
      BSTNode<T> *max_left = m_find_max(node->left);
      assert(max_left);
      swap(max_left->value, node->value);
      node = max_left;
    }

    // Now one of node's children must be NULL
    BSTNode<T>* replacement = node->left ? node->left : node->right;
    BSTNode<T> *parent = node->parent;
    if (parent)
    {
      if (node == parent->left)
        parent->left = replacement;
      else
        parent->right = replacement;
    }
    else
    {
      assert(node == m_root);
      m_root = replacement;
    }
    if (replacement)
      replacement->parent = parent;
    delete node;
    --m_node_count;

    return true;
  }

  T minValue() const
  {
    return m_find_min(m_root)->value;
  }

  T maxValue() const
  {
    return m_find_max(m_root)->value;
  }

  bool findPredecessor(const T& val, T& pred) const
  {
    BSTNode<T> node_val(val);
    BSTNode<T> *node = m_root, *pred_node = NULL;
    while (node)
    {
      if (pred_node && node->value <= pred_node->value)
        node = node->right;
      else if (node->value < val)
      {
        pred_node = node;
        node = node->right;
      }
      else
        node = node->left;
    }
    if (pred_node)
    {
      pred = pred_node->value;
      return true;
    }
    else
      return false;
  }

  bool findSuccessor(const T& val, T& succ) const
  {
    BSTNode<T> node_val(val);
    BSTNode<T> *node = m_root, *succ_node = NULL;
    while (node)
    {
      if (succ_node && node->value >= succ_node->value)
        node = node->left;
      else if (node->value > val)
      {
        succ_node = node;
        node = node->left;
      }
      else
        node = node->right;
    }
    if (succ_node)
    {
      succ = succ_node->value;
      return true;
    }
    else
      return false;
  }

  // This method assumes these two values present in the BST
  T findCommonAncestor(const T& val1, const T& val2) const
  {
    const T& large_val = max(val1, val2);
    const T& small_val = min(val1, val2);
    BSTNode<T> *node = m_root;
    while (node)
    {
      if (node->value <= large_val)
      {
        if (node->value >= small_val)
          return node->value;
        else
          node = node->right;
      }
      else
        node = node->left;
    }

    return m_root->value;
  }

  bool verifyIntegrity() const
  {
    if (m_root && m_root->parent != NULL)
      return false;

    BSTNode<T> *max_node = NULL, *min_node = NULL;
    bool bRet = m_verify_helper(m_root, max_node, min_node);
    if (!bRet)
      return false;
    if (max_node != m_find_max(m_root))
    {
      cout << "ERROR: max_node incorrect!" << endl;
      return false;
    }
    if (min_node != m_find_min(m_root))
    {
      cout << "ERROR: max_node incorrect!" << endl;
      return false;
    }

    return true;
  }

  int getCount() const { return m_node_count; }

  void printTree()
  {
    deque<BSTNode<T> *> printQ;

    int node_count = 1, node_left = 0, non_null = 0;
    if (m_root)
    {
      printQ.push_back(m_root);
      node_left = 1;
    }
    while (!printQ.empty())
    {
      BSTNode<T> *node = printQ.front();
      printQ.pop_front();
      -- node_left;
      if (!node)
      {
        printQ.push_back(NULL);
        printQ.push_back(NULL);
        cout << "*,";
      }
      else
      {
        printQ.push_back(node->left);
        printQ.push_back(node->right);
        if (node->left)
          ++ non_null;
        if (node->right)
            ++ non_null;
        cout << node->value << ',';
      }
      if (node_left <= 0)
      {
        // Done with this level
        cout << endl;
        if (non_null <= 0)
          break; // no more nodes, done
        // Prepare for the next level
        non_null = 0;
        node_count *= 2;
        node_left = node_count;
      }
    }
  }

  void getValuesInOrder(vector<T>& out)
  {
    out.clear();
    m_append_nodes_inorder(out, m_root);
  }

  void getValuesPreOrder(vector<T>& out)
  {
    out.clear();
    m_append_nodes_preorder(out, m_root);
  }

  void getValuesPostOrder(vector<T>& out)
  {
    out.clear();
    m_append_nodes_postorder(out, m_root);
  }

private:
  BSTNode<T> *m_root;
  int m_node_count;

  static void m_free_subtree(BSTNode<T> *node)
  {
    if (!node)
      return;

    m_free_subtree(node->left);
    m_free_subtree(node->right);
    delete node;
  }

  static bool m_compare_subtree(const BSTNode<T> *tree1, const BSTNode<T> *tree2)
  {
    // Check for self comparison or both being NULL
    if (tree1 == tree2)
      return true;

    // Check if only one of them is NULL
    if (!tree1 || !tree2)
      return false;

    if (tree1->value != tree2->value)
      return false;

    if (!m_compare_subtree(tree1->left, tree2->left))
      return false;

    return m_compare_subtree(tree1->right, tree2->right);
  }

  void m_insert_helper(BSTNode<T> *root, BSTNode<T> *node)
  {
    assert(root);
    assert(node);

    if (root->value == node->value)
    {
      // No duplicate values allowed in BST
      cout << "Not inserting duplicate value " << node->value << endl;
      delete node;
      return;
    }
    if (root->value > node->value)
    {
      if (!root->left) {
        root->left = node;
        node->parent = root;
        ++ m_node_count;
      }
      else
        m_insert_helper(root->left, node);
    }
    else
    {
      if (!root->right) {
        root->right = node;
        node->parent = root;
        ++ m_node_count;
      }
      else
        m_insert_helper(root->right, node);
    }

    return;
  }

  BSTNode<T>* m_duplicate_tree(const BSTNode<T>* node)
  {
    BSTNode<T>* new_node = NULL;
    if (node)
    {
      new_node = new BSTNode<T>(node->value);
      if (!new_node)
      {
        cout << "Cannot copy tree, out of memory!!!!!!!!!!!!" << endl;
        return NULL;
      }
      new_node->left = m_duplicate_tree(node->left);
      if (new_node->left)
        new_node->left->parent = new_node;
      new_node->right = m_duplicate_tree(node->right);
      if (new_node->right)
        new_node->right->parent = new_node;
    }
    return new_node;
  }

  static void m_append_nodes_inorder(vector<T>& out, BSTNode<T>* tree)
  {
    if (!tree)
      return;

    m_append_nodes_inorder(out, tree->left);
    out.push_back(tree->value);
    m_append_nodes_inorder(out, tree->right);
  }

  static void m_append_nodes_preorder(vector<T>& out, BSTNode<T>* tree)
  {
    if (!tree)
      return;

    out.push_back(tree->value);
    m_append_nodes_preorder(out, tree->left);
    m_append_nodes_preorder(out, tree->right);
  }

  static void m_append_nodes_postorder(vector<T>& out, BSTNode<T>* tree)
  {
    if (!tree)
      return;

    m_append_nodes_postorder(out, tree->left);
    m_append_nodes_postorder(out, tree->right);
    out.push_back(tree->value);
  }

  BSTNode<T> * m_build_from_preorder(typename vector<T>::const_iterator begin,
                                     typename vector<T>::const_iterator end)
  {
    BSTNode<T>* node = NULL;

    if (begin == end)
      return node;

    node = new BSTNode<T>(*begin);
    if (!node)
    {
      cout << "Failed to create a new node" << endl;
      return node;
    }

    const T& current = *begin;
    ++begin;
    if (begin == end)
      return node;

    const typename vector<T>::const_iterator rightBegin = lower_bound(begin, end, current);
    node->left = m_build_from_preorder(begin, rightBegin);
    if (node->left)
      node->left->parent = node;
    node->right = m_build_from_preorder(rightBegin, end);
    if (node->right)
      node->right->parent = node;
    return node;
  }

  bool m_verify_helper(BSTNode<T>* root, BSTNode<T>* &max_node, BSTNode<T>* &min_node) const
  {
    if (!root)
    {
      max_node = NULL;
      min_node = NULL;
      return true;
    }
    BSTNode<T>* tmp_node;
    if (!m_verify_helper(root->left, tmp_node, min_node))
      return false;
    if (!min_node)
      min_node = root;
    else
    {
      // If there is a min node, there must be a max node
      assert(tmp_node);
      if (tmp_node->value >= root->value)
      {
        cout << "ERROR: max left node " << tmp_node->value
             << " >= node " << root->value << endl;
        return false;
      }
      if (root->left->parent != root)
      {
        cout << "ERROR: parent pointer of left node " << root->left->value
             << " is corrupted."<< endl;
        return false;
      }
    }
    if (!m_verify_helper(root->right, max_node, tmp_node))
      return false;
    if (!max_node)
      max_node = root;
    else
    {
      // If there is a max node, there must be a min node
      assert(tmp_node);
      if (tmp_node->value <= root->value)
      {
        cout << "ERROR: min right node " << tmp_node->value
             << " <= node " << root->value << endl;
        return false;
      }
      if (root->right->parent != root)
      {
        cout << "ERROR: parent pointer of right node " << root->right->value
             << " is corrupted."<< endl;
        return false;
      }
    }

    return true;
  }

  BSTNode<T> * m_find_node(const T& val) const
  {
    BSTNode<T> *current = m_root;

    while (current)
    {
      if (current->value == val)
        break;
      current = current->value < val ? current->right : current->left;
    }

    return current;
  }

  BSTNode<T>* m_find_min(BSTNode<T>* root) const
  {
    if (root) {
      while (root->left)
        root = root->left;
    }
    return root;
  }

  BSTNode<T>* m_find_max(BSTNode<T>* root) const
  {
    if (root) {
      while (root->right)
        root = root->right;
    }
    return root;
  }

};

void testBST()
{
  vector<int> test_data;
  srand(time(NULL));

  cout << "Test data: ";
  const static unsigned NUM_TEST_DATA = 30;
  while (test_data.size() < NUM_TEST_DATA)
  {
    int rand_num = rand()%(NUM_TEST_DATA*2);
    if (find(test_data.begin(), test_data.end(), rand_num) == test_data.end())
    {
      cout << rand_num << ',';
      test_data.push_back(rand_num);
    }
  }
  cout << endl;

  BST<int> bst;
  for (unsigned i = 0; i < test_data.size(); ++i)
  {
    bst.insertValue(test_data[i]);
  }
  cout << "BST now has " << bst.getCount() << " nodes, "
       << (bst.verifyIntegrity() ? "verified" : "corrupted")
       << endl;

  BST<int> bst2(bst);

  cout << "Testing ==: " << (bst2 == bst ? "good" : "bad") << ", "
       << (bst2.verifyIntegrity() ? "verified" : "corrupted")
       << endl;

  vector<int> tree_data;

  bst.getValuesInOrder(tree_data);
  cout << "getValuesInOrder() returned " << tree_data.size() << " values:" << endl;
  for (unsigned i = 0; i < tree_data.size(); ++i)
  {
    cout << tree_data[i] << ',';
  }
  cout << endl;

  bst.getValuesPreOrder(tree_data);
  cout << "getValuesPreOrder() returned " << tree_data.size() << " values:" << endl;
  for (unsigned i = 0; i < tree_data.size(); ++i)
  {
    cout << tree_data[i] << ',';
  }
  cout << endl;

  cout << "Testing construction of BST from a pre-order vector: ";
  BST<int> bst3(tree_data);
  cout << (bst3 == bst ? "good" : "bad") << ", "
       << (bst3.verifyIntegrity() ? "verified" : "corrupted")
       << endl;

  bst.getValuesPostOrder(tree_data);
  cout << "getValuesPostOrder() returned " << tree_data.size() << " values:" << endl;
  for (unsigned i = 0; i < tree_data.size(); ++i)
  {
    cout << tree_data[i] << ',';
  }
  cout << endl;

  cout << "Testing delete..." << endl;
  bool bVerify = true;
  for (unsigned i = 0; bVerify && i < test_data.size(); ++i)
  {
    bst2.deleteValue(test_data[i]);
    bVerify = bst2.verifyIntegrity();
    cout << "Deleting " << test_data[i]
         << ", " << bst2.getCount() << " values left, "
         << (bVerify ? "good" : "bad") << endl;
  }

  cout << "Testing predecessors..." << endl;
  sort(test_data.rbegin(), test_data.rend());
  for (unsigned i = 0; i < test_data.size(); ++i)
  {
    int pred = -999;
    if (bst.findPredecessor(test_data[i], pred))
      cout << "Predecessor of " << test_data[i]
         << " is " << pred
         << (i < test_data.size() - 1 && pred == test_data[i+1] ? ", good" : ", bad")
         << endl;
    else
      cout << "Predecessor of " << test_data[i]
         << " doesn't exist, "
         << (i == test_data.size() - 1 ? "good" : "bad")<< endl;
  }

  cout << "Testing successors..." << endl;
  sort(test_data.begin(), test_data.end());
  for (unsigned i = 0; i < test_data.size(); ++i)
  {
    int pred = -999;
    if (bst.findSuccessor(test_data[i], pred))
      cout << "Successor of " << test_data[i]
         << " is " << pred
         << (i < test_data.size() - 1 && pred == test_data[i+1] ? ", good" : ", bad")
         << endl;
    else
      cout << "Successor of " << test_data[i]
         << " doesn't exist, "
         << (i == test_data.size() - 1 ? "good" : "bad")<< endl;
  }

  random_shuffle(test_data.begin(), test_data.end());
  cout << "Common ancestor of " << test_data[0] << " and "
       << test_data[1] << " is " << bst.findCommonAncestor(test_data[0], test_data[1])
       << endl;
  cout << "Printing tree..." << endl;
  bst.printTree();

  cout << "Done." << endl;
  return;
}
