/*
 * RestoreIP.cpp
 *
 *  Created on: Apr 28, 2013
 *      Author: Yu
 */

#include <string>
#include <vector>

using namespace std;

class RestoreIP {
public:
    void helper(const string &s, string &ip, int idx, int parts, vector<string> &answer) {
      if (idx >= s.length()) {
        if (parts == 0)
          answer.push_back(ip);
        return;
      }
      if (parts <= 0) return;
      int ipLen = ip.length();
      if (parts < 4)
        ip += '.';
      char c1 = s[idx];
      ip += c1;
      helper(s, ip, idx+1, parts-1, answer);
      if (c1 != '0') {
        char c2 = s[idx+1];
        if (c2 != '\0') {
          ip += c2;
          helper(s, ip, idx+2, parts-1, answer);
          char c3 = s[idx+2];
          if (c3 != '\0') {
            int ipVal = 100*(c1-'0')+10*(c2-'0')+(c3-'0');
            if (ipVal <= 255) {
              ip += c3;
              helper(s, ip, idx+3, parts-1, answer);
            }
          }
        }
      }
      ip.resize(ipLen);
    }

    vector<string> restoreIpAddresses(string s) {
        vector<string> answer;
        string ip;
        helper(s, ip, 0, 4, answer);
        return answer;
    }
};
