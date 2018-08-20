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

using namespace std;

class Solution {
private:
  string trim(string &s) {
    int i = 0, j = s.length() - 1;
    while(i < s.length() && s[i] == ' ') i++;
    if(i == s.length()) return "";
    while(j >= 0 && s[j] == ' ') j--;
    return s.substr(i, j - i + 1);
  }
public:
  int myAtoi(string str) {
    str = trim(str);
    // cout << "Trimmed: \"" << str << "\"" << endl;
    bool negative = false;
    if(str[0] == '-' || str[0] == '+') {
      if(str[0] == '-') negative = true;
      str = str.substr(1);
    }
    // cout << "After First -/+: \"" << str << "\", negative: " << negative << endl;

    vector<char> digits;
    for(auto c: str) {
      if(c < '0' || c > '9') {
        if(!digits.size()) return 0;
        else break;
      } else {
        if(c == '0' && !digits.size()) continue;
        digits.push_back(c);
      }
    }

    long multiplier = 1;
    int result = 0;
    bool range = false;
    for(auto digit: digits) {
      cout << "digit: " << digit << endl;

      if(multiplier > INT32_MAX) {
        cout << "out of range!" << endl;
        range = true;
        break;
      }

      int d = digits.back() - '0';
      long addition = (long) d * multiplier;
      int remaining = INT32_MAX - result;
      cout << "digit: " << d <<
        ", multiplier: " << multiplier << 
        ", addition: " << addition << 
        ", remaining:" << remaining << 
        ", result: " << result << endl;
      if(addition > remaining) {
        cout << "out of range!" << endl;
        range = true;
        break;
      }
      result += addition;
      multiplier *= 10;
      digits.pop_back();
    }
    if(!range) return !negative ? result : -1 * result;
    else return !negative ? INT32_MAX : INT32_MIN;
  }
};

int main() {
  Solution s;
  int r = s.myAtoi("");

  r = s.myAtoi(" dcwdcwe      91283472332 ");
  // cout << "result: " << r << endl;
  // r = s.myAtoi("        ");
  // cout << "result: " << r << endl;
  // r = s.myAtoi("       91283472332 ");
  // cout << "result: " << r << endl;
  // r = s.myAtoi("       +91283472332 edgkvcwkec");
  // cout << "result: " << r << endl;
  // r = s.myAtoi("       -91283472332 cwkjdgcvwekc");
  // cout << "result: " << r << endl;
  // r = s.myAtoi("       -0 cwkjdgcvwekc");
  // cout << "result: " << r << endl;
  // r = s.myAtoi("       0 cwkjdgcvwekc");
  // cout << "result: " << r << endl;
  // r = s.myAtoi("       00000000000000020000000000000000000");
  // cout << "result: " << r << endl;

  // r = s.myAtoi("       -0000000000000-0020001");
  // cout << "result: " << r << endl;
  r = s.myAtoi("-2147483649");
  cout << "result: " << r << endl;
  return 0;
}