#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include "utils.h"

using namespace std;
/*
 * Problem Statement # 1:
(Version: TwoSigmaCodeTestJumbleSort $Revision: 1.9 $)
You are to write a program that takes a list of strings containing integers
and words and returns a sorted version of the list.
The goal is to sort this list in such a way that all words are in
alphabetical order and all integers are in numerical order.  Furthermore,
if the nth element in the list is an integer it must remain an integer,
and if it is a word it must remain a word.

Input:
------
The input will contain a single, possibly empty, line containing a
space-separated list of strings to be sorted. Words will not contain spaces,
will contain only the lower-case letters a-z. Integers will be in the range
-999999 to 999999, inclusive. The line will be at most 1000 characters long.

Output:
-------
The program must output the list of strings, sorted per the requirements
above. Strings must be separated by a single space, with no leading space
at the beginning of the line or trailing space at the end of the line.

Constraints:
------------
The code you submit must take input from stdin and produce output to stdout
as specified above. No other output is permitted. You can assume the input
will be valid. Feel free to use standard libraries to assist in sorting.

In the examples below, the text "Input:" and "Output:" are not part of the
output, and neither are the blank lines.

Example 1:
----------
Input:
1

Output:
1

Example 2:
----------
Input:
car truck bus

Output:
bus car truck

Example 3:
----------
Input:
8 4 6 1 -2 9 5

Output:
-2 1 4 5 6 8 9

Example 4:
----------
Input:
car truck 8 4 bus 6 1

Output:
bus car 1 4 truck 6 8

 *
 */

int sortWordNum()
{
  cout << "Please enter the string to be sorted:" << endl;

  string line_in;
  getline(cin, line_in);
  vector<string> str_vec;
  tokenize(line_in, str_vec);

  vector<string> vec_words;
  vector<int> vec_numbers;
  vector<bool> vec_is_number;

  int total_size = str_vec.size();
  // Go through the strings and put them into either words list or numbers list
  for (int i = 0; i < total_size; ++i)
  {
    string &str = str_vec[i];
    if (str.empty())
      continue;
    bool is_digit = (!isalpha(str[0])); // is this a word or a number?

    if (is_digit)
      vec_numbers.push_back(atoi(str.c_str()));
    else
      vec_words.push_back(str);

    // Remember whether this position should contain a word or a number
    vec_is_number.push_back(is_digit);
  }

  sort(vec_words.begin(), vec_words.end());
  sort(vec_numbers.begin(), vec_numbers.end());

  int idx_word = 0;
  int idx_number = 0;

  for (int i = 0; i < total_size; ++i)
  {
    if (vec_is_number[i])
      cout << vec_numbers[idx_number++] << ' ';
    else
      cout << vec_words[idx_word++] << ' ';
  }
  cout << endl;

  return 0;
}
