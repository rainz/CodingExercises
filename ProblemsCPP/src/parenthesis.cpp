/*
 * parenthesis.cpp
 *
 *  Created on: Mar 26, 2013
 *      Author: Yu
 */


#include <iostream>
#include <stack>
#include <unordered_set>

using namespace std;

/*
 * Remove duplicate parentheses: (1+2)+((3+4)) ==> (1+2)+(3+4). Assume no space.
 */
static bool removeDupParen(const string& inStr, string& outStr)
{
  stack< pair<int, bool> > leftParen; // stores left parenthesis index and whether any letters exist for this pair
  unordered_set<int> toRemove;

  bool hasContent = false;
  int currLeft = -1;
  for (unsigned idx = 0; idx < inStr.length(); ++idx) {
    char c = inStr[idx];
    if (c == '(') {
      if (currLeft >= 0) {
        // Save current state.
        leftParen.push(make_pair(currLeft, hasContent));
      }
      hasContent = false;
      currLeft = idx;
    }
    else if (c == ')') {
      if (currLeft < 0) {
        return false; // invalid expression
      }
      if (!hasContent) {
        // Need to remove this duplicate pair of parentheses.
        toRemove.insert(currLeft); // left
        toRemove.insert(idx); // right
      }
      if (leftParen.empty()) {
        currLeft = -1;
      }
      else {
        pair<int, bool> p = leftParen.top();
        currLeft = p.first;
        hasContent = p.second;
        leftParen.pop();
      }
    }
    else {
      hasContent = true;
    }
  }
  if (currLeft >= 0) {
    return false; // invalid expression
  }
  outStr = "";
  for (unsigned idx = 0; idx < inStr.length(); ++ idx) {
    if (toRemove.find(idx) == toRemove.end()) {
      outStr += inStr[idx];
    }
  }

  return true;
}

static void testRemoveParenthese()
{
  string testCases[] = {
      "()",
      "1+1",
      "(1+1)",
      "1+2+(3+4)",
      "1+((2+3))+((4))",
      "1+(1.5+(2+3))+((4))",
      "1+(1.5+((2+3)+3.5))+((4))",
      "1+((2+(3+((4+5)))))+6+7",
      "(1+(2+3)",
      "1+((2+3)+4",
      "(1+2+3))+4",
      "(1+2+3))",
      "1+((2+3))+4)",
  };

  for (unsigned i = 0; i < sizeof(testCases)/sizeof(testCases[0]); ++i) {
    string outStr;
    const string& inStr = testCases[i];
    bool ret = removeDupParen(inStr, outStr);
    if (!ret) {
      outStr = "false";
    }
    cout << "'" << inStr << "'==>'" << outStr << "'" << endl;
  }
}

/*
 * Write code to do arithmetic expression validation:
 * digits: 0..9, operators: +, -, (, )
 * E.g.:
 * 1+2-3  valid
 * 1+(2-(3+4)) valid
 * -2 not valid
*/
enum EXPR_STATE {
  START, GOT_NUMBER, GOT_OPERATOR
};

static bool validExpression(const string& expr)
{
  stack<EXPR_STATE> states;

  EXPR_STATE currState = START;
  unsigned idx = 0;
  while (idx < expr.length()) {
    char c = expr[idx];
    if (c >= '0' && c <= '9') {
      // Read the entire number.
      while (expr[idx] >= '0' && expr[idx] <= '9') {
        ++idx;
      }

      switch (currState) {
      case START:
      case GOT_OPERATOR:
        currState = GOT_NUMBER;
        break;
      case GOT_NUMBER:
        return false;
      }
    }
    else if (c == '+' || c == '-') {
      switch (currState) {
      case START:
      case GOT_OPERATOR:
        return false;
      case GOT_NUMBER:
        currState = GOT_OPERATOR;
        break;
      }
      ++idx;
    }
    else if (c == '(') {
      if (currState != GOT_OPERATOR && currState != START) {
        return false;
      }
      states.push(currState);
      currState = START;
      ++idx;
    }
    else if (c == ')') {
      if (currState != GOT_NUMBER) {
        return false;
      }
      if (states.empty()) {
        return false;
      }
      if (states.top() != GOT_OPERATOR && states.top() != START) {
        return false;
      }
      states.pop();
      currState = GOT_NUMBER;
      ++idx;
    }
    else {
      ++idx;
    }
  }
  return ((currState == START || currState == GOT_NUMBER) && states.empty());
}

static void testValidExpression()
{
  string testCases[] = {
      "1+2-3",
      "1+(2-(3+4))",
      "-2+3",
      "(1+(3-4)",
      "(1+((3-4)))",
      "(1+(4-5)))",
      "(1+((4-5))-3)",
  };
  for (unsigned i = 0; i < sizeof(testCases)/sizeof(testCases[0]); ++i) {
    const string& inStr = testCases[i];
    cout << inStr << ": " << (validExpression(inStr) ? "true" : "false") << endl;
  }

}

void testParenthesis()
{
  testValidExpression();
}
