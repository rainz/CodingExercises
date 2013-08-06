/*
 * utils.cpp
 *
 *  Created on: Jan 7, 2012
 *      Author: Yu
 */
#include "utils.h"
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

void tokenize(const string& str, vector<string> &str_vec, char delimiter)
{
  str_vec.clear();
  stringstream ss(str);
  string s;
  while (getline(ss, s, delimiter))
    str_vec.push_back(s);
}


void tokenize2(const string &s, vector<string> &ret, char delim = ',', char trim = '\0')
{
  size_t len = s.length();
  for (size_t i = 0; i < len;) {
    size_t delim_pos = s.find_first_of(delim, i);
    if (delim_pos == string::npos)
      delim_pos = s.length();
    size_t ii = delim_pos;
    if (trim != '\0') {
      // Trim front
      while (i < ii && s[i] == trim)
        ++i;
      // Trim back. Note if this is a blank token, i == ii.
      while (i < ii && s[ii-1] == trim)
        --ii;
    }
    ret.push_back(s.substr(i, ii-i));
    i = delim_pos + 1;
  }
}

void showArray(const int *array, int array_size)
{
  for (int i = 0; i < array_size; ++i)
    cout << array[i] << ", ";

  cout << endl;
}

void showVector(const vector<int>& vec)
{
  for (int i = 0; i < vec.size(); ++i)
    cout << vec[i] << ", ";

  cout << endl;
}
