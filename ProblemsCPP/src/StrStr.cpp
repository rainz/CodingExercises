/*
 * StrStr.cpp
 *
 *  Created on: May 9, 2013
 *      Author: Yu
 */

#include <cstdlib>
#include <cstring>

/* StrStr with KMP method */

class StrStr {
public:
    /*
     * The goal of kmp() is to determine, at each position, if a suffix (tail) matches a prefix (head).
     * Example: abcxxxabyy
     * KMP:     0000001200
     *                ^ here a suffix="a" matches a prefix of length 1 ("a")
     *                 ^ here a suffix="ab" matches a prefix of length 2 ("ab")
     */
    void kmp(const char* needle, int* slide, int needleLen) {
      if (needleLen <= 0) return; // handle empty strings
      int prefix = 0;
      slide[0] = 0;
      for (int i = 1; i < needleLen; ++i) {
        if (needle[i] == needle[prefix])
          ++prefix;
        else
          prefix = 0;
        slide[i] = prefix;
      }
    }
    char *strStr(char *haystack, char *needle) {
        char *h = haystack;
        const int needleLen = strlen(needle);
        int *slide = new int[needleLen]; // to store kmp result
        kmp(needle, slide, needleLen); //preprocess needle

        int idx = 0; // index into needle;
        // In KMP method, haystack pointer never moves back.
        while (*h != '\0' && idx < needleLen) {
          if (*h == needle[idx]) {
            // Match at this position, increment both pointers.
            ++h; ++idx;
            continue;
          }
          if (idx == 0) {
            // No match at position 0, simply move haystack pointer forward
            ++h;
          }
          else {
            /*
             * Mismatch after partial match.
             * Example 1: simple case, no suffix matches prefix in needle :
             * ......abcX......     (X represents unknown but mismatched letter, ie, not 'd')
             *       abcde (slide[] = {0, 0, 0, 0, 0})
             *          ^ mismatch at idx=3, so last match idx is 2, slide[2] = 0
             * ==>      abcde, haystack pointer doesn't need change, but needle index becomes 0, start with 'a' and compare against X.
             * Example 2: needle has duplicate letter(s)
             * ......abcabX......   (X represents unknown but mismatched letter, ie, not 'd')
             *       abcabd ({0, 0, 0, 1, 2, 0})
             *            ^ mismatch at idx=5, so last match idx is 4 slide[4] = 2
             * ==>      abcabd, haystack pointer doesn't need change, needle index becomes 2, which points to 'c'.
             *          This is because we know the previous two letters ("ab") already match,
             *          so we start with 'c' to compare against X.
             */
            idx = slide[idx-1]; // don't move haystack pointer, but slide needle pointer
          }
        }
        delete [] slide;
        // If we exit the loop, then either we reached the end of haystack, or we found a match for needle
        if (idx == needleLen)
          return (h-needleLen); // found needle, so return where needle begins in haystack
        return NULL; // we reached the end of haystack without finding a complete match for needle.
    }
};
