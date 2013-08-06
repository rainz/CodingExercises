/*
 * BigIntMultiply.cpp
 *
 *  Created on: Mar 11, 2012
 *      Author: Yu
 */
#include <iostream>
#include <string>
#include <algorithm>
#include <stack>

using namespace std;


void addBig(const string &s1, const string &s2, string &output)
{
  stack<char> num_stack;

  int carry = 0;
  int s1_len = s1.length(), s2_len = s2.length();
  int max_len = max(s1_len, s2_len);
  for (int i = 0; i < max_len; ++i) {
    int idx1 = s1_len - 1 - i;
    int idx2 = s2_len - 1 - i;
    int d1 = idx1 >= 0 ? s1[idx1] - '0' : 0;
    int d2 = idx2 >= 0 ? s2[idx2] - '0' : 0;
    int sum = d1 + d2 + carry;
    if (sum > 9) {
      carry = 1;
      sum -= 10;
    }
    else
      carry = 0;
    num_stack.push(sum + '0');
  }
  if (carry)
    num_stack.push(carry + '0');
  while (!num_stack.empty()) {
    output += num_stack.top();
    num_stack.pop();
  }
}

void multiplyBig(const string &s1, const string &s2, string &output)
{
  output = "0";
  int s1_len = s1.length(), s2_len = s2.length();

  if ( (s1_len == 1 && s1[0] == '0') ||
       (s2_len == 1 && s2[0] == '0') )
    return;

  for (int i2 = s2.length() - 1; i2 >= 0; --i2) {
    int d2 = s2[i2] - '0';
    int carry = 0;
    stack<char> num_stack;
    for (int i1 = s1.length() - 1; i1 >= 0; --i1) {
      int d1 = s1[i1] - '0';
      int prod = d1*d2 + carry;
      carry = prod / 10;
      num_stack.push(prod % 10 + '0');
    }
    if (carry > 0)
      num_stack.push(carry + '0');
    string prod_str;
    while (!num_stack.empty()) {
      prod_str += num_stack.top();
      num_stack.pop();
    }
    string ending0(s2.length() - 1 - i2, '0');
    prod_str += ending0;
    string sum;
    addBig(output, prod_str, sum);
    output = sum;
  }
}


int testBigIntMultiply()
{
  string s1("99998"), s2("9876");
  int num1 = atoi(s1.c_str()), num2 = atoi(s2.c_str());
  int prod = num1*num2;
  int sum = num1+num2;
  string prod_str, sum_str;
  multiplyBig(s1, s2, prod_str);
  addBig(s1, s2, sum_str);
  cout << "num1 = " << num1 << ", num2 = " << num2 << endl;
  cout << "Multiply: " << prod_str << " vs " << prod << endl;
  cout << "Add: " << sum_str << " vs " << sum << endl;
  return 0;
}
