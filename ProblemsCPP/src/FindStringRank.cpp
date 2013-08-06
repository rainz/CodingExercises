/*
 * FindStringRank.cpp
 *
 *  Created on: Jan 5, 2012
 *      Author: Yu
 */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <stack>
#include <map>
#include <set>
#include <utility>
#include <cstring>
#include <climits>

using namespace std;

///////////////////////////////////////////////////////////////////////////////////
// Find String problem from interviewstreet.com

const static size_t BOUNDARY_LEN = 1;

/*********** Brute force way ***********************/

static void appendSubstring(const string &str, set<string> &substrings)
{
  int len = str.length();
  for (int sub_len = 1; sub_len <= len; ++sub_len)
    for (int i = 0; i + sub_len <= len; ++i) {
      substrings.insert(str.substr(i, sub_len));
    }
}

void findStringRankBruteForce()
{
  int num_strings;

  cin >> num_strings;
  set<string> all_strings;
  for (int i = 0; i < num_strings; ++i) {
    string tmp_str;
    cin >> tmp_str;
    all_strings.insert(tmp_str).second;
  }

  set<string> all_substrings;
  for (set<string>::const_iterator it = all_strings.begin();
      it != all_strings.end(); ++it) {
    appendSubstring(*it, all_substrings);
  }

  cout << "Substring count: " << all_substrings.size() << endl;
  return;

  vector<set<string>::const_iterator> strings_order;
  for (set<string>::const_iterator it = all_substrings.begin();
      it != all_substrings.end(); ++it) {
    strings_order.push_back(it);
  }

  int num_queries;
  cin >> num_queries;
  for (int i = 0; i < num_queries; ++i) {
    size_t query;
    cin >> query;
    if (query > strings_order.size()) {
      cout << "INVALID" << endl;
      continue;
    }
    cout << *strings_order[query-1] << endl;
  }
}

/************** End brute force way *************************/

/************** Generate test cases *************************/
static void testCases(const char* file_name, int max_strings = -1)
{
  set<string> strs;
  ifstream in_file(file_name);
  int num_words = 0;
  while (in_file.good()) {
    if (max_strings >= 0 && num_words >= max_strings)
      break;
    string word;
    in_file >> word;
    if (word.length() <= 0)
      continue;
    bool bGood = true;
    for (size_t i = 0; i < word.length(); ++i) {
      if (!isalpha(word[i])) {
        bGood = false;
        break;
      }
      if (isupper(word[i]))
        word[i] = tolower(word[i]);
    }
    if (bGood) {
      if (strs.insert(word).second)
        ++num_words;
    }
  }

  int num_queries = 10000;
  vector<int> queries;
  int queries_size = 0;
  while (queries_size < num_queries - 1) {
    int q = rand() % 100000 + 1;
    queries.push_back(q);
    ++queries_size;
  }
  queries.push_back(INT_MAX); // insert an "INVALID" query

  cout << num_words << endl;
  for (set<string>::const_iterator it = strs.begin();
       it != strs.end(); ++it)
    cout << *it << endl;
  cout << num_queries << endl;
  for (vector<int>::const_iterator it = queries.begin();
       it != queries.end(); ++it)
    cout << *it << endl;
}
/********************************************************/

typedef pair<unsigned, unsigned> CompactLink;
const static unsigned LETTER_COUNT = 26;
struct TrieNode {
  unsigned rank;
  TrieNode* links[LETTER_COUNT];
  vector<CompactLink> compactLinks;

  TrieNode(): rank(0)
  {
    memset(links, 0, sizeof(links));
  }
};

static void printTrieDOTHelper(const TrieNode *root, string &out)
{
  const static string EMPTY_STR = "EMPTY";
  unsigned len = out.length();
  for (size_t i = 0; i < LETTER_COUNT; ++i) {
    const TrieNode *pNode = root->links[i];
    if (!pNode)
      continue;
    out.resize(len);
    const string &node_str = (len > 0 ? out : EMPTY_STR);
    cout << "  " << node_str << '_' << root->rank << "->";
    char c = 'a' + i;
    out += c;
    cout << out << '_' << pNode->rank << " [label=\"" << c << "\"];" << endl;
    printTrieDOTHelper(pNode, out);
  }
}

static void printTrieDOT(const TrieNode *root)
{
  cout << "digraph trie" << endl << '{' << endl;
  string tmp;
  printTrieDOTHelper(root, tmp);
  cout << "}" << endl;
}

static void deleteTrie(TrieNode *root)
{
  if (!root)
    return;
  for (size_t i = 0; i < LETTER_COUNT; ++i) {
    deleteTrie(root->links[i]);
  }
  delete root;
}

static void insertString(TrieNode *root, const char* str)
{
  //cerr << "Inserting string " << str << endl;
  TrieNode *pNode = root;
  const char* pChar = str;
  while (*pChar) {
    unsigned idx = *pChar - 'a';
    TrieNode *pNext = pNode->links[idx];
    if (!pNext) {
      pNext = new TrieNode();
      pNode->links[idx] = pNext;
    }
    pNode = pNext;
    ++pChar;
  }
}

static void insertAllSuffix(TrieNode *root, const char* str)
{
  const char* pChar = str;
  //cerr << "Inserting suffix for " << str << endl;
  while (*pChar)
    insertString(root, pChar++);
}

// Returns max rank of this Trie
static unsigned setRanksAndCompactForTrie(TrieNode *root)
{
  unsigned max_rank = root->rank;
  vector<CompactLink> &vec = root->compactLinks;
  vec.clear();
  for (size_t i = 0; i < LETTER_COUNT; ++i) {
    TrieNode *pNode = root->links[i];
    if (!pNode)
      continue;
    ++max_rank;
    pNode->rank = max_rank;
    vec.push_back(make_pair(pNode->rank, i));
    max_rank = setRanksAndCompactForTrie(pNode);
  }

  return max_rank;
}

static void findRankInTrie(const TrieNode *root, unsigned target_rank, string &result)
{
  CompactLink target(target_rank, LETTER_COUNT);
  const TrieNode *pNode = root;
  while (pNode->rank != target_rank) {
    const vector<CompactLink> &cl = pNode->compactLinks;
    if (cl.empty())
      break;
    vector<CompactLink>::const_iterator it = lower_bound(cl.begin(), cl.end(), target);
    --it;
    unsigned idx = it->second;
    result += (char)('a' + idx);
    pNode = pNode->links[idx];
  }
  if (result.empty() || pNode->rank != target_rank)
    result = "INVALID";
}


void findStringRankByTrie()
{
  int num_strings;
  cin >> num_strings;
  vector<string> all_strings(num_strings);
  TrieNode *root = new TrieNode();
  for (int i = 0; i < num_strings; ++i) {
    cin >> all_strings[i];
    insertAllSuffix(root, all_strings[i].c_str());
  }
  setRanksAndCompactForTrie(root);

  //printTrieDOT(root);

  int num_queries;
  cin >> num_queries;
  vector<int> all_queries(num_queries);
  for (int i = 0; i < num_queries; ++i) {
    cin >> all_queries[i];
    unsigned rank = all_queries[i];
    string result;
    findRankInTrie(root, rank, result);
    cout << result << endl;
  }

  deleteTrie(root);
}
