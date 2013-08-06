//============================================================================
// Name        : ProblemsCPP.cpp
// Author      : 
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <sstream>
#include <algorithm>
#include <map>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <math.h>
#include <string.h>
#include <time.h>
#include <limits.h>

#include <unordered_map>

#include "utils.h"

#include "ProblemsCPP.h"

using namespace std;


/////////////////////////////////////////////////////////////////////
// 3-way partition

static void partition3Way(int *array, int array_size)
{
  if (array_size <= 0)
    return;

  int pivot = array[0];
  int mid_begin = 0, mid_end = array_size - 1;

  for (int i = 1; i <= mid_end; ++i)
  {
    showArray(array, array_size);
    if (array[i] > pivot)
    {
      swap(array[i], array[mid_end]);
      --mid_end;
      --i;
    }
    else if (array[i] < pivot)
    {
      swap(array[i], array[mid_begin]);
      ++mid_begin;
    }
  }

}

static void testPartitioneWay()
{
  int test_data[] = {8, 12, 13, 5, 10, 8, 3, 3, 7, 8, 5, 13, 21, 8, 42, 1};
  int test_size = sizeof(test_data)/sizeof(test_data[0]);
  partition3Way(test_data, test_size);

  showArray(test_data, test_size);
}


///////////////////////////////////////////////////////////////////////////////////////////////
// Given a string representing an integer, return the string representing the next integer

static void nextNum(const char *str, char *out)
{
  stack<char> next_num;
  int len = strlen(str);

  int carry = 0, incr = 1;
  for (int idx = len - 1; idx >= 0; --idx) {
    char digit = str[idx] + incr + carry;
    incr = 0;
    if (digit > '9') {
      digit = '0';
      carry = 1;
    }
    else
      carry = 0;
    next_num.push(digit);
  }
  if (carry)
    next_num.push('0' + carry);

  int idx = 0;
  while (!next_num.empty()) {
    out[idx++] = next_num.top();
    next_num.pop();
  }
  out[idx] = '\0';
}

static void testNextNum(int max_print = 1000)
{
  char buf[256];
  strcpy(buf, "0");
  for (int i = 1; i <= max_print; ++i) {
    nextNum(buf, buf);
    cout << buf << endl;
    if (atoi(buf) != i) {
      cout << "Error at " << i << endl;
      break;
    }
  }

}


///////////////////////////////////////////////////////////////////////////////////////////////
// Given a string consist of 'a' to 'z' and a max len, return the string representing the next
// string, or false if the end is reached.

static bool nextStr(const char *str, char *out, int max_len)
{
  stack<char> next_str;
  bool bEnd = true;
  int len = 0;
  // Check string length and if we've reached the end.
  for (const char *c = str; *c != '\0'; ++c) {
    ++len;
    if (*c != 'z')
      bEnd = false;
  }
  if (len >= max_len && bEnd)
    return false; // end reached

  if (len < max_len) {
    strcpy(out, str);
    out[len] = 'a';
    out[len+1] = '\0';
    return true;
  }

  int carry = 0, incr = 1;
  for (int idx = len - 1; idx >= 0; --idx) {
    char c = str[idx] + incr + carry;
    incr = 0;
    if (c > 'z')
      carry = 1;
    else {
      carry = 0;
      next_str.push(c);
    }
  }

  int idx = 0;
  while (!next_str.empty()) {
    out[idx++] = next_str.top();
    next_str.pop();
  }
  out[idx] = '\0';

  return true;
}

static void testNextStr(int max_len = 2)
{
  char buf[256];
  buf[0] = '\0';
  while (nextStr(buf, buf, max_len)) {
    cout << "'" << buf << "'" << endl;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Print all valid permutations of n pairs of parentheses.

void printPairsHelper(int pairs, int left_paren, int right_paren, char* output)
{
  int idx = left_paren + right_paren;
  if (idx == 2*pairs) {
    cout << output << endl;
    return;
  }
  if (left_paren < pairs) {
    output[idx] = '(';
    printPairsHelper(pairs, left_paren+1, right_paren, output);
  }
  if (right_paren < pairs && right_paren < left_paren) {
    output[idx] = ')';
    printPairsHelper(pairs, left_paren, right_paren+1, output);
  }
}

void printPairs(int pairs)
{
  int output_len = 2*pairs;
  char *output = new char[output_len+1];
  memset(output, 0, output_len+1);
  int left_paren = 1;
  int right_paren = 0;
  output[0] = '(';
  printPairsHelper(pairs, left_paren, right_paren, output);

  delete [] output;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Simple regular expression matching:
// '.' means any single character, '*' means 0 to any number of the previous character.
// So ".*" matches any string

bool regexMatch(const char *str, const char *reg, int str_idx = 0, int reg_idx = 0)
{
  if (reg[reg_idx] == '\0')
    return (str[str_idx] == '\0');
  bool bCurrentMatch = (str[str_idx] == reg[reg_idx] ||
                        (str[str_idx] != '\0' && reg[reg_idx] == '.'));

  // If next char is not '*', just do direct comparison and move forward.
  if (reg[reg_idx+1] != '*') {
    if (!bCurrentMatch)
      return false;
    return regexMatch(str, reg, str_idx+1, reg_idx+1);
  }

  // Next char is '*', current char matches, we can move forward in the original char,
  // but not the regex, because we can have something like aab vs a*b.
  // We can move forward in the regex only when the char in str does not match that in regex,
  // as in the case at the end of this function.
  if (bCurrentMatch && regexMatch(str, reg, str_idx+1, reg_idx))
    return true;

  // Next char is '*', current char does not match
  // In this case we can skip the current char and '*' and compare with the rest.
  return regexMatch(str, reg, str_idx, reg_idx+2);
}

struct MatchTestCase {
  string str;
  string expr;
  bool result;
};
void testRegex()
{
  MatchTestCase testCases[] = {
      {"a", "*", false},
      {"aa", "*", false},
      {"abcd", "abcd*", true},
      {"abcddd", "abcd*", true},
      {"abc", "abcd*", true},
      {"abc", "abc.", false},
      {"abcxz", "abc.*", true},
      {"abcd", "ab.d", true},
      {"b", "a*aab", false},
      {"aab", "a*aab", true},
      {"aaaaab", "a*aab", true},
      {"aaaaab", "aa*aab", true},
      {"bcd", "a*bcd", true},
      {"bcd", ".bcd", false},
      {"abcd", "abde", false},
      {"a", "abcd", false},
      {"a", "aa*", true},
      {"abcde", "abcd", false}
  };

  for (unsigned i = 0; i < sizeof(testCases)/sizeof(testCases[0]); ++i) {
    const MatchTestCase& tc = testCases[i];
    bool result = regexMatch(tc.str.c_str(), tc.expr.c_str());
    bool testResult = (tc.result == result);
    cout << "Testing '" << tc.str << "' vs '" << tc.expr << "', " << (result ? "true" : "false") << ", "
         << (testResult ? "success" : "fail") << endl;
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////
// Wild card matching with '*' and '?'
// Time limit exceeded on Leetcode large cases.
bool
isMatch(const char *s, const char *p)
{
  while (*s != '\0' && *p != '\0' && (*s == *p || *p == '?'))
  {
    ++s;
    ++p;
    continue;
  }

  if (*s == '\0')
  {
    while (*p != '\0')
    {
      if (*p != '*')
        return false;
      ++p;
    }
    return true;
  }
  if (*p == '\0' || *p != '*')
    return false;

  // Test all possible cases for *
  ++p; // skip the '*'
  do
  {
    if (isMatch(s, p))
      return true;
    ++s;
  }
  while (*s != '\0');
  return isMatch(s, p);
}

void dutchFlag(vector<int> &A)
{
  int n = A.size();
  int i = 0; // 0 pointer
  int j = n - 1; // 1 pointer
  int k = n - 1; // 2 pointer
  while (i <= j)
  {
    if (A[i] == 2)
    {
      swap(A[k], A[i]);
      k--;
      if (k < j)
        j = k;
    }
    else if (A[i] == 1)
    {
      swap(A[i], A[j]);
      j--;
    }
    else
      i++;
  }
}

void dutchFlagTest()
{
  srand(time(NULL));
  int testCount = 5, testSize = 15;
  for (int i = 0; i < testCount; ++i) {
    vector<int> testData;
    vector<int> testDataVerify;
    for (int j = 0; j < testSize; ++j) {
      int tmp = rand() % 3;
      testData.push_back(tmp);
      testDataVerify.push_back(tmp);
    }
    cout << "Before:" << endl;
    showVector(testData);
    dutchFlag(testData);
    sort(testDataVerify.begin(), testDataVerify.end());
    cout << "After:" << endl;
    showVector(testData);
    cout << (testData == testDataVerify ? "Success." : "Failed!!!!!!!!!!!!!!!!!!") << endl;
  }
}

// Divide without multiplication, division and mod operator
// Passed Leetcode
int divide(int a, int b) {
    bool neg = (a > 0 && b < 0 || a < 0 && b > 0);
    // Convert to unsigned because abs(INT_MIN) is 1 larger than INT_MAX
    unsigned dividend = abs(a);
    unsigned divisor = abs(b);
    if (dividend < divisor) return 0;
    int shift = 1;
    long long div = divisor;
    while (dividend >= (div << 1)) {
      div <<= 1;
      shift <<= 1;
    }
    long long result = (shift | divide((int)(dividend - div), (int)divisor));
    return (int)(neg ? -result : result);
}

static void testDivide() {
  int testCase[][2] = {
      {100, 3},
      {-100, 5},
      {101, 3},
      {100, 100},
      {0, 100},
      {INT_MAX, 1},
      {INT_MIN, 1}
  };

  for (int i = 0; i < sizeof(testCase)/sizeof(testCase[0]); ++i) {
    int a = testCase[i][0], b = testCase[i][1];
    cout << "Testing " << a << "/" << b << endl;
    int result = divide(a, b);
    if (a/b != result) {
      cout << "Failed! " << a/b << " vs " << result << endl;
      break;
    }
  }
}

static string multiply(const string& num1, const string& num2) {
  int len1 = num1.length(), len2 = num2.length();
  int lenProduct = len1+len2;
  string product(lenProduct, '0');
  for (int i = 0; i < len1; ++i) {
    int digit1 = num1[len1-1-i] - '0';
    int carry = 0;
    for (int j = 0; j < len2; ++j) {
      int digit2 = num2[len2-1-j]-'0';
      int prod = digit1 * digit2  + carry;
      char &p = product[lenProduct-1-i-j];
      prod += p - '0';
      carry = prod / 10;
      prod = prod % 10;
      p = '0' + prod;
    }
    // Don't forget the last carry!
    if (carry > 0) {
      char &p = product[lenProduct-1-i-len2];
      p += carry;
    }
  }
  int start = 0;
  // Remove leading 0's not only for the unused highest digit, but also for cases like 1234 x 0.
  while (product[start] == '0' &&
         start < lenProduct - 1 /* don't remove the last 0 when result is 0 */)
    ++start;
  return product.substr(start);
}

static void testMultiply() {
  string testCases[][2] = {
      {"9", "8"},
      {"99", "8"},
      {"1111", "11"},
      {"1000000", "1000"},
      {"19034", "4203"},
      {"5349", "33000"},
      {"98765", "1234"},
      {"10101", "909"},
      {"99", "99999"},
      {"42342", "0"},
      {"0", "0"}
  };
  for (int i = 0; i < sizeof(testCases)/sizeof(testCases[0]); ++i) {
    string &num1 = testCases[i][0];
    string &num2 = testCases[i][1];
    int prod = atoi(num1.c_str())*atoi(num2.c_str());
    stringstream ss;
    ss << prod;
    string result = multiply(num1, num2);
    cout << num1 << 'x' << num2 << " should be " << prod;
    if (result == ss.str())
      cout << ", good." << endl;
    else
      cout << ", wrong: " << result << endl;
  }
}


static int maxSubArray(int A[], int n) {
    long long maxSum = INT_MIN;
    long long ending = INT_MIN;
    for (int i = 0; i < n; ++i) {
      ending += A[i];
      if (ending < A[i])
        ending = A[i];
      if (ending > maxSum)
        maxSum = ending;
    }
    return (int)maxSum;
}

// LeetCode triangle problem.
static int minimumTotal(vector<vector<int> > &triangle) {
    int rows = triangle.size();
    if (rows == 0) return 0;
    --rows; // convert to 0-based;
    vector<int> sums = triangle[rows]; // start with bottom row
    --rows; // 2nd bottom row
    while (rows >= 0) {
      for (int i = 0; i <= rows; ++i) {
        sums[i] = triangle[rows][i]+min(sums[i], sums[i+1]);
      }
      --rows;
    }
    return sums[0];
}

// Rotate an nxn matrix 90 degrees clockwise.
static void rotate90(vector<vector<int> > &matrix) {
    int N = matrix.size();
    if (N <= 1) return;
    int left = 0, right = N-1, top = 0, bottom = N-1;
    while (left < right) {
      int side = right - left;
      for (int len = 0; len < side; ++len) {
        swap(matrix[top][left+len], matrix[top+len][right]);
        swap(matrix[top][left+len], matrix[bottom][right-len]);
        swap(matrix[top][left+len], matrix[bottom-len][left]);
      }
      ++left; --right;
      ++top; --bottom;
    }

}

// Given two sorted integer arrays A and B, merge B into A as one sorted array. Assume A has enough space.
static void mergeB2A(int A[], int m, int B[], int n) {
    int idx = m+n-1;
    int idxA = m - 1, idxB = n - 1;
    while (idxB >= 0) {
      if (idxA >= 0 && A[idxA] > B[idxB])
        A[idx--] = A[idxA--];
      else
        A[idx--] = B[idxB--];
    }
}

static void testIntMinMax() {
  int x1 = INT_MIN, x2 = INT_MAX;
  int y1 = -x1, y2 = -x2;
  cout << "x1=" << x1 << ", y1=" << y1 << endl;
  cout << "x2=" << x2 << ", y2=" << y2 << endl;
  /*
   * x1=-2147483648, y1=-2147483648
   * x2=2147483647, y2=-2147483647
   */
}

///////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
  int time_start = time(NULL);

  return 0;
}
