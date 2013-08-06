#include <iostream>
#include <string>
#include <cstring>

using namespace std;


void longest_common_substring_dynamic(const string &str1, const string &str2)
{
  int len1 = str1.length();
  int len2 = str2.length();

  int longest[len1][len2];
  memset(longest, 0, len1*len2*sizeof(int));
  int start_idx = 0, end_idx = 0;
  int max_len = 0;
  for (int i = 0; i < len1; ++i) {
    for (int j = 0; j < len2; ++j) {
      if (str1[i] != str2[j]) {
        longest[i][j] = 0;
        continue;
      }

      if (i == 0 || j == 0) {
        longest[i][j] = 1;
        start_idx = i;
      }
      else {
        int l = longest[i-1][j-1] + 1;
        longest[i][j] = l;
        if (l > max_len) {
          max_len = l;
          start_idx = i - l + 1;
          end_idx = i + 1;
        }
      }
    }
  }
  cout << "Dynamic: " << str1.substr(start_idx, end_idx - start_idx) << endl;
}

int longest_common_substring_test()
{
  string str1 = "ABCDEFGHIJK";
  string str2 = "BCDFGHIJK";
  longest_common_substring_dynamic(str1, str2);
  return 0;
}
