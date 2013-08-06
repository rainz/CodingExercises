#include <vector>
#include <string>

using namespace std;

/*
 * Given an array of words and a length L, format the text such that each line has exactly L characters and is fully (left and right) justified.
 * You should pack your words in a greedy approach; that is, pack as many words as you can in each line. Pad extra spaces ' ' when necessary so that each line has exactly L characters.
 * Extra spaces between words should be distributed as evenly as possible. If the number of spaces on a line do not divide evenly between words, the empty slots on the left will be assigned more spaces than the slots on the right.
 * For the last line of text, it should be left justified and no extra space is inserted between words.
 */

// Passed LeetCode OJ
class TextJustify {
public:
    vector<string> fullJustify(vector<string> &words, int L) {
        vector<string> answer;
        int wordsCount = words.size(), idx = 0;
        while (idx < wordsCount) {
          int start = idx, end = idx + 1;

          // First try how many words can be included in this line
          int lineLen = words[start].length();
          while (end < wordsCount) {
            int nextLen = words[end].length();
            if (lineLen + nextLen + 1 > L)
              break; // max length reached.
            lineLen += nextLen + 1;
            ++end;
          }

          bool lastLine = (end >= wordsCount); // is this the last line?
          int slots = end - start - 1; // number of slots
          string line = words[start];
          int totalSpaces = L - lineLen + slots; // total spaces needed
          for (int i = start+1; i < end; ++i) {
            int numSpaces = totalSpaces/slots; // spaces per slot, rounded down
            if (totalSpaces % slots > 0) numSpaces++; // assign more spaces to slots on the left
            if (lastLine && slots > 0) numSpaces = 1; // no extra space for last line
            for (int j = 0; j < numSpaces; ++j) line += ' ';
            totalSpaces -= numSpaces;
            --slots;
            line += words[i];
          }
          int len = line.length();
          if (len < L) {
            // The last line is left-justified. So append spaces.
            for (int i = 0; i < L - len; ++i) line += ' ';
          }
          answer.push_back(line);
          idx = end;
        }
        return answer;
    }
};
