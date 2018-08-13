#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <cmath>
#include <unistd.h>
#include <fstream>
#include <algorithm>
#include <queue>
#include <chrono>

using namespace std;

class Solution {
private:
  void trim(string &s) {
    int i, j;
    for(i = 0; i < s.length() && s[i] == ' '; i++);
    if(i == s.length()) return;
    for(j = s.length() - 1; j >= 0 && s[j] == ' '; j--);
    // cout << "i: " << i << ", j: " << j << endl;
    s = s.substr(i, s.length() - i - (s.length() - j) + 1);
  }
public:
  bool isNumber(string s) {
    trim(s);
    // cout << "string: \"" << s << "\"" << endl;
    if(!s.length()) return false;
    if(s[0] == 'e') return false;
    if(s[s.length() - 1] == 'e'  || s[s.length() - 1] == 'E') return false;
    // if(s[s.length() - 1] == '.') return false;
    if(s[0] == '-') s = s.substr(1);
    
    bool eSeen = false;
    bool dotSeen = false;
    bool numSeenAfterE = false;
    bool numSeenAfterDot = false;
    bool numSeenBeforeDot = false;
    for(int i = 0; i < s.length(); i++) {
      // cout << "Char: \"" << s[i] << "\"" << endl;
      if(s[i] >= '0' && s[i] <= '9') {
        if(!dotSeen) numSeenBeforeDot = true;
        if(!eSeen && dotSeen && s[i - 1] == '.') numSeenAfterDot = true;
        if(eSeen) numSeenAfterE = true;
      } else {
        switch(s[i]) {
          case '.':
            if(dotSeen) return false;
            dotSeen = true;
            if(eSeen) return false;
            break;
          case 'e':
          case 'E':
            if(eSeen) return false;
            eSeen = true;
            if(s[i - 1] == '.') numSeenAfterDot = true;
            break;
          case '-':
            if(s[i - 1] != 'e' && s[i - 1] != 'E') return false;
            break;
          default:
            // cout << "Any other character: \"" << s[i] << "\"" << endl;
            return false;
        }
      }
    }
    cout << "dotSeen: " << dotSeen << ", numSeenAfterDot: " << numSeenAfterDot <<
      ", eSeen: " << eSeen << ", numSeenAfterE: " << numSeenAfterE <<
      ", numSeenBeforeDot: " << numSeenBeforeDot << endl;
    
    if(!eSeen && numSeenBeforeDot && dotSeen && s[s.length() - 1] == '.') numSeenAfterDot = true;
    if(dotSeen && !(numSeenAfterDot && numSeenBeforeDot)) return false;
    if((dotSeen && !numSeenAfterDot) || (eSeen && !numSeenAfterE)) return false;
    return true;
  }
};

int main() {
  Solution s;
  assert(!s.isNumber("  "));
  assert(!s.isNumber(" %&^$%&^$^$^& "));
  assert(!s.isNumber("abc"));
  assert(!s.isNumber("    1 a      "));
  assert(!s.isNumber("1 a"));
  assert(!s.isNumber("."));
  assert(!s.isNumber("e"));
  assert(!s.isNumber(".e"));
  assert(!s.isNumber(".1e"));
  assert(!s.isNumber("E"));
  assert(!s.isNumber(".E"));
  assert(!s.isNumber(".1E"));
  assert(s.isNumber("1.1"));
  assert(s.isNumber("1."));
  assert(s.isNumber("1.e1"));
  assert(s.isNumber("1.1e1"));
  assert(s.isNumber("1.E1"));
  assert(s.isNumber("1.1E1"));
  assert(s.isNumber(".1"));
  assert(s.isNumber("1.1e-1"));
  assert(s.isNumber("1.1E-1"));
  assert(s.isNumber("2E10"));
  assert(s.isNumber("2e10"));
  assert(s.isNumber("2E-10"));
  assert(s.isNumber("2e-10"));
  assert(s.isNumber("-1.1e-1"));
  assert(s.isNumber("1.1E-1"));
  assert(s.isNumber("-2E10"));
  assert(s.isNumber("-2e10"));
  assert(s.isNumber("-2E-10"));
  assert(s.isNumber("-2e-10"));
  assert(s.isNumber("12345678"));
  assert(s.isNumber("-12345678"));
  assert(s.isNumber("1234.5678"));
  assert(s.isNumber("-1234.5678"));
  assert(!s.isNumber("1234..5678"));
  assert(!s.isNumber("-1234..5678"));
  assert(!s.isNumber("1234ee5678"));
  assert(!s.isNumber("-1234ee5678"));
  assert(!s.isNumber("1234EE5678"));
  assert(!s.isNumber("-1234EE5678"));
  assert(!s.isNumber("1234eE5678"));
  assert(!s.isNumber("-1234Ee5678"));
  assert(!s.isNumber("12.34ee5678"));
  assert(!s.isNumber("-12.34ee5678"));
  assert(!s.isNumber("12.34EE5678"));
  assert(!s.isNumber("-1234EE5678"));
  assert(!s.isNumber("12.34eE5678"));
  assert(!s.isNumber("-12.34Ee5678"));
  assert(s.isNumber("1 "));
  assert(s.isNumber("          1 "));
  assert(s.isNumber("          -1 "));

  assert(!s.isNumber(".e1"));
  return 0;
}